import sys
import os
import socket
import pickle
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QGraphicsView, QGraphicsScene, QLabel, QVBoxLayout,
    QHBoxLayout, QWidget, QPushButton, QRadioButton, QLineEdit, QButtonGroup
)
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtCore import Qt, QTimer
import time


class MandelbrotViewer(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()  # Инициализация интерфейса пользователя
        self.initData()  # Инициализация данных для фрактала

    def initUI(self):
        self.setWindowTitle("Фрактал Мандельброта")  # Установка заголовка окна
        self.setGeometry(100, 100, 1000, 900)  # Установка размера и положения окна

        central_widget = QWidget()
        self.setCentralWidget(central_widget)  # Установка центрального виджета

        control_layout = QHBoxLayout()  # Горизонтальное расположение для элементов управления

        # Добавляем радиокнопки для выбора режима генерации
        self.radio_sequential = QRadioButton("Последовательное")
        self.radio_parallel = QRadioButton("Параллельное")
        self.radio_sequential.setChecked(True)  # По умолчанию выбран последовательный режим
        control_layout.addWidget(self.radio_sequential)
        control_layout.addWidget(self.radio_parallel)

        self.iter_input = QLineEdit()  # Поле ввода для глубины генерации
        self.iter_input.setPlaceholderText("Глубина генерации (по умолч. 300)")
        control_layout.addWidget(self.iter_input)

        self.timer_label = QLabel("Время: 0.00 сек")  # Метка для отображения времени генерации
        control_layout.addWidget(self.timer_label)

        self.reset_button = QPushButton("Назад")  # Кнопка для сброса зума
        self.reset_button.clicked.connect(self.reset_zoom)
        control_layout.addWidget(self.reset_button)

        # Создаем сцену и вид для отображения фрактала
        self.scene = QGraphicsScene()
        self.view = QGraphicsView(self.scene)
        self.view.setMouseTracking(True)  # Включаем отслеживание мыши

        main_layout = QVBoxLayout(central_widget)
        main_layout.addLayout(control_layout)  # Добавляем элементы управления на главный макет
        main_layout.addWidget(self.view)  # Добавляем вид

        # Группируем радиокнопки для выбора только одного режима
        self.radio_group = QButtonGroup()
        self.radio_group.addButton(self.radio_sequential)
        self.radio_group.addButton(self.radio_parallel)

    def initData(self):
        self.history = []  # История состояний для возможности возврата
        self.xmin, self.xmax = -2.0, 1.0  # Начальные координаты по оси X
        self.ymin, self.ymax = -1.5, 1.5  # Начальные координаты по оси Y
        self.width, self.height = 800, 800  # Размер изображения
        self.max_iter = 300  # Максимальное количество итераций
        self.calculate_fractal()  # Расчет фрактала

    def calculate_fractal(self):
        # Проверяем, изменились ли координаты, и добавляем их в историю
        if not self.history or (self.xmin, self.xmax, self.ymin, self.ymax) != self.history[-1]:
            self.history.append((self.xmin, self.xmax, self.ymin, self.ymax))

        # Получаем значение максимального количества итераций из поля ввода
        max_iter = self.iter_input.text()
        self.max_iter = int(max_iter) if max_iter.isdigit() else 300

        parallel = self.radio_parallel.isChecked()  # Проверяем выбранный режим генерации

        self.timer_start = time.time()  # Запускаем таймер
        self.timer_label.setText("Время: 0.00 сек")
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_timer)
        self.timer.start(10)  # Обновляем таймер каждые 10 миллисекунд

        server_address = ('0.0.0.0', 9998)  # Адрес сервера
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect(server_address)  # Подключаемся к серверу
            data = (self.xmin, self.xmax, self.ymin, self.ymax, self.width, self.height, self.max_iter, parallel)
            s.send(pickle.dumps(data))  # Отправляем данные на сервер
            img = self.receive_data(s)  # Получаем изображение от сервера
            self.update_view(img, self.xmin, self.xmax, self.ymin, self.ymax, time.time() - self.timer_start)

    def receive_data(self, sock):
        # Получаем длину данных
        data_length = int.from_bytes(sock.recv(4), byteorder='big')
        data = b''
        while len(data) < data_length:
            packet = sock.recv(4096)  # Получаем данные порциями
            if not packet:
                break
            data += packet
        return pickle.loads(data)  # Распаковываем данные

    def update_timer(self):
        # Обновляем метку времени
        elapsed_time = time.time() - self.timer_start
        self.timer_label.setText(f"Время: {elapsed_time:.2f} сек")

    def update_view(self, img, xmin, xmax, ymin, ymax, elapsed_time):
        self.timer.stop()
        self.xmin, self.xmax = xmin, xmax
        self.ymin, self.ymax = ymin, ymax
        height, width = img.shape
        qimage = QImage(img.data, width, height, QImage.Format_Grayscale8)
        pixmap = QPixmap.fromImage(qimage)
        self.scene.clear()
        self.scene.addPixmap(pixmap)
        self.timer_label.setText(f"Время: {elapsed_time:.2f} сек")

    def mouseDoubleClickEvent(self, event):
        # Обрабатываем двойной щелчок мыши для зума
        x_ratio = event.x() / self.view.width()
        y_ratio = event.y() / self.view.height()
        x_center = self.xmin + (self.xmax - self.xmin) * x_ratio
        y_center = self.ymin + (self.ymax - self.ymin) * y_ratio
        if event.button() == Qt.LeftButton:
            self.zoom(x_center, y_center, zoom_in=True)
        elif event.button() == Qt.RightButton:
            self.zoom(x_center, y_center, zoom_in=False)

    def zoom(self, x_center, y_center, zoom_in):
        # Выполняем зум изображения
        zoom_factor = 0.5 if zoom_in else 1.5
        x_width = (self.xmax - self.xmin) * zoom_factor
        y_width = (self.ymax - self.ymin) * zoom_factor
        self.xmin = x_center - x_width / 2
        self.xmax = x_center + x_width / 2
        self.ymin = y_center - y_width / 2
        self.ymax = y_center + y_width / 2
        self.calculate_fractal()

    def reset_zoom(self):
        # Возвращаемся к предыдущему состоянию зума
        if len(self.history) > 1:
            self.history.pop()
            self.xmin, self.xmax, self.ymin, self.ymax = self.history[-1]
            self.calculate_fractal()
        else:
            print("Нет предыдущих состояний для возврата.")


if __name__ == '__main__':
    os.environ['QT_QPA_PLATFORM'] = 'xcb'  # Устанавливаем платформу для Qt
    app = QApplication(sys.argv)  # Создаем приложение
    viewer = MandelbrotViewer()  # Создаем объект основного окна
    viewer.show()  # Показываем окно
    sys.exit(app.exec_())  # Запускаем главный цикл приложения