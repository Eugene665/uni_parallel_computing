import numpy as np
import sys
import os
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QGraphicsView, QGraphicsScene, QLabel, QVBoxLayout,
    QHBoxLayout, QWidget, QPushButton, QRadioButton, QLineEdit, QButtonGroup
)
from PyQt5.QtGui import QImage, QPixmap
from PyQt5.QtCore import Qt, QThread, pyqtSignal, QTimer
import time
from multiprocessing import Pool
import csv


# Класс для расчёта фрактала Мандельброта в отдельном потоке
class MandelbrotWorker(QThread):
    result_ready = pyqtSignal(np.ndarray, float, float, float, float, float)

    def __init__(self, xmin, xmax, ymin, ymax, width, height, max_iter, parallel=False):
        super().__init__()
        # Границы фрактала по 4-м сторонам
        self.xmin = xmin
        self.xmax = xmax
        self.ymin = ymin
        self.ymax = ymax
        # Ширина, высота фото
        self.width = width
        self.height = height
        # максимальное кол-во итераций для расчёта
        self.max_iter = max_iter
        # Флаг для параллельного вычисления
        self.parallel = parallel

    def run(self):
        # Начало времени вычислений
        start_time = time.time()
        # Если включено параллельное вычисление,
        # используем параллельность, иначе последовательность
        if self.parallel:
            img = self.compute_parallel()
        else:
            img = self.compute_sequential()
        # Заканчиваем считать время
        elapsed_time = time.time() - start_time
        self.result_ready.emit(img, self.xmin, self.xmax, self.ymin, self.ymax, elapsed_time)
        # Отправляем сигнал с результатами вычисления

    # Метод для последовательного расчёта фрактала
    def compute_sequential(self):
        # Генерируем линейное распределение координат по x и по y
        x = np.linspace(self.xmin, self.xmax, self.width)
        y = np.linspace(self.ymin, self.ymax, self.height)

        # Инициализируем пустое изображение (массив нулей)
        img = np.zeros((self.height, self.width), dtype=np.uint8)
        # Циклы для прохода по всем пикселям в каждой строке
        for i in range(self.height):
            for j in range(self.width):
                # Создаём комплексное число для текущей точки
                c = complex(x[j], y[i])
                # Вычисляем значение для точки с помощью функции Mandelbrot
                img[i, j] = MandelbrotWorker.mandelbrot(c, self.max_iter)
        # Возвращаем готовое изображение
        return img

    # Метод для параллельного расчёта фрактала
    def compute_parallel(self):
        # Генерируем линейное распределение координат по x и по y
        x = np.linspace(self.xmin, self.xmax, self.width)
        y = np.linspace(self.ymin, self.ymax, self.height)

        # Создаём список всех координат и максимального числа итераций
        coords = [(x[j], y[i], self.max_iter) for i in range(self.height) for j in range(self.width)]
        # Создаём пул процессов для параллельной обработки
        with Pool() as pool:
            # Распределяем вычисления функции Mandelbrot среди процессов
            results = pool.map(self.mandelbrot_wrapper, coords)
        # Возвращаем результаты в изображение
        return np.array(results, dtype=np.uint8).reshape((self.height, self.width))

    # Статический метод для расчёта значения в точке фрактала
    @staticmethod
    def mandelbrot(c, max_iter):
        # Начальное значение Z
        z = 0
        # Счётчик итераций
        n = 0
        while abs(z) <= 2 and n < max_iter:
            # Пока модуль Z не превышает 2 и не достигнут предел итераций
            z = z * z + c  # Основное уравнение фрактала
            n += 1  # Увеличиваем счётчик итераций
        if n == max_iter:  # Если точка принадлежит фракталу (достигнут предел итераций)
            return 0  # Цвет чёрный
        else:  # Если точка не принадлежит фракталу
            return 255 - int(255 * n / max_iter)  # Цвет зависит от числа итераций

    # Вспомогательная функция для параллельной обработки
    @staticmethod
    def mandelbrot_wrapper(args):
        x, y, max_iter = args  # Распаковываем координаты и число итераций
        c = complex(x, y)  # Создаём комплексное число
        return MandelbrotWorker.mandelbrot(c, max_iter)
        # Вызываем метод Mandelbrot для вычисления значения

class MandelbrotViewer(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()  # Инициализация пользовательского интерфейса
        self.initData()  # Инициализация данных (настройки фрактала)

    def initUI(self):
        # Заголовок + размер окна
        self.setWindowTitle("Фрактал Мандельброта")
        self.setGeometry(100, 100, 1000, 900)

        # Основной виджет, который будет содержать все элементы управления
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Верхняя панель управления, содержащая элементы управления фракталом
        control_layout = QHBoxLayout()
        # Радиокнопки для последовательных и параллельных вычислений
        self.radio_sequential = QRadioButton("Последовательное")
        self.radio_parallel = QRadioButton("Параллельное")
        # Значение по умолчанию на первой кнопке
        self.radio_sequential.setChecked(True)
        # Добавляем кнопки в макет
        control_layout.addWidget(self.radio_sequential)
        control_layout.addWidget(self.radio_parallel)

        # Поле для глубины итераций + добавление текстового поля в макет
        self.iter_input = QLineEdit()
        self.iter_input.setPlaceholderText("Глубина генерации (по умолч. 300)")
        control_layout.addWidget(self.iter_input)

        # Метка секундомера и добавление текста в макет
        self.timer_label = QLabel("Время: 0.00 сек")
        control_layout.addWidget(self.timer_label)

        # Кнопка возврата к прошлому шагу
        self.reset_button = QPushButton("Назад")
        # + обработчик событий
        self.reset_button.clicked.connect(self.reset_zoom)
        control_layout.addWidget(self.reset_button)

        # Центральный виджет с графикой: создание сцены для отображения фрактала
        # + представления сцены
        self.scene = QGraphicsScene()
        self.view = QGraphicsView(self.scene)
        # Включение отслеживания движения мыши на сцене
        self.view.setMouseTracking(True)

        # Общий макет для центрального виджета
        main_layout = QVBoxLayout(central_widget)  # Создание вертикального макета
        main_layout.addLayout(control_layout)  # Добавляем панель управления в макет
        main_layout.addWidget(self.view)

        # Группа радиокнопок для управления методом расчёта
        self.radio_group = QButtonGroup()  # Создание группы радиокнопок
        self.radio_group.addButton(self.radio_sequential)
        self.radio_group.addButton(self.radio_parallel)

    def initData(self):
        # Список истории, диапазон осей по X и Y, разрешение фрактала, кло-во итераций
        self.history = []
        self.xmin, self.xmax = -2.0, 1.0
        self.ymin, self.ymax = -1.5, 1.5
        self.width, self.height = 800, 800
        self.max_iter = 300

        self.calculate_fractal()  # Вызываем метод для расчёта фрактала

    def calculate_fractal(self):
        # Проверяем, нет ли повторений текущего состояния
        if not self.history or (self.xmin, self.xmax, self.ymin, self.ymax) != self.history[-1]:
            self.history.append((self.xmin, self.xmax, self.ymin,
                                 self.ymax))  # Добавляем текущее состояние в историю

        # Получаем значение глубины генерации фрактала из поля ввода
        max_iter = self.iter_input.text()
        self.max_iter = int(
            max_iter) if max_iter.isdigit() else 300  # Преобразуем в целое число или используем 300 по умолчанию

        # Проверяем, выбран ли параллельный режим
        parallel = self.radio_parallel.isChecked()

        # Запускаем таймер для отображения времени
        self.timer_start = time.time()  # Засекаем текущее время
        self.timer_label.setText("Время: 0.00 сек")  # Устанавливаем начальный текст для метки времени
        self.timer = QTimer()  # Создаём объект таймера
        self.timer.timeout.connect(self.update_timer)  # Подключаем метод для обновления времени
        self.timer.start(10)  # Запускаем таймер с интервалом 10 мс

        # Создаём и запускаем рабочий процесс для вычисления фрактала
        self.worker = MandelbrotWorker(
            self.xmin, self.xmax, self.ymin, self.ymax,  # Параметры для вычислений
            self.width, self.height, self.max_iter, parallel  # Параметры для изображения
        )
        self.worker.result_ready.connect(
            self.update_view)  # Подключаем метод для обновления вида, когда результат готов
        self.worker.start()  # Запускаем рабочий процесс

    def update_timer(self):  # Метод для обновления таймера
        elapsed_time = time.time() - self.timer_start  # Рассчитываем прошедшее время
        self.timer_label.setText(f"Время: {elapsed_time:.2f} сек")  # Обновляем метку времени с точностью до 2 знаков

    def update_view(self, img, xmin, xmax, ymin, ymax, elapsed_time):  # Метод для обновления вида фрактала
        self.timer.stop()  # Останавливаем таймер

        # Обновляем координаты области фрактала
        self.xmin, self.xmax = xmin, xmax
        self.ymin, self.ymax = ymin, ymax
        height, width = img.shape  # Получаем размеры изображения
        # Преобразуем изображение в формат QImage
        qimage = QImage(img.data, width, height, QImage.Format_Grayscale8)
        pixmap = QPixmap.fromImage(qimage)

        # Очищаем сцену и добавляем новое изображение
        self.scene.clear()
        self.scene.addPixmap(pixmap)

        # Логирование производительности
        mode = "Параллельный" if self.radio_parallel.isChecked() else "Последовательный"  # Определяем режим расчёта
        self.save_performance_data(mode, self.max_iter, elapsed_time)  # Сохраняем данные о производительности

        # Обновляем метку времени
        self.timer_label.setText(f"Время: {elapsed_time:.2f} сек")  # Отображаем время, прошедшее на расчёт

    def mouseDoubleClickEvent(self, event):
        # Рассчитываем относительную координату по оси X и Y
        x_ratio = event.x() / self.view.width()
        y_ratio = event.y() / self.view.height()

        # Преобразуем относительные координаты в координаты фрактала
        x_center = self.xmin + (self.xmax - self.xmin) * x_ratio
        y_center = self.ymin + (self.ymax - self.ymin) * y_ratio

        # Если была нажата левая кнопка мыши, увеличиваем масштаб
        if event.button() == Qt.LeftButton:
            self.zoom(x_center, y_center, zoom_in=True)
        # Если была нажата правая кнопка мыши, уменьшаем масштаб
        elif event.button() == Qt.RightButton:
            self.zoom(x_center, y_center, zoom_in=False)

    # Метод для изменения масштаба
    def zoom(self, x_center, y_center, zoom_in):
        zoom_factor = 0.5 if zoom_in else 1.5
        # Новая ширина и высота фрактала
        x_width = (self.xmax - self.xmin) * zoom_factor
        y_width = (self.ymax - self.ymin) * zoom_factor

        # Обновляем координаты фрактала, чтобы центр был в точке, по которой кликнули
        self.xmin = x_center - x_width / 2
        self.xmax = x_center + x_width / 2
        self.ymin = y_center - y_width / 2
        self.ymax = y_center + y_width / 2

        self.calculate_fractal()  # Перерасчитываем фрактал с новым масштабом

    # Метод для сброса масштаба
    def reset_zoom(self):
        if len(self.history) > 1:  # Проверяем, есть ли история изменений масштаба
            self.history.pop()  # Убираем текущее состояние из истории
            self.xmin, self.xmax, self.ymin, self.ymax = self.history[-1]  # Восстанавливаем предыдущие координаты
            self.calculate_fractal()  # Перерасчитываем фрактал
        else:
            print("Нет предыдущих состояний для возврата.")

    def save_performance_data(self, mode, max_iter,
                              elapsed_time):  # Метод для сохранения данных о производительности в файл
        file_name = "performance_log.csv"
        # Проверяем, существует ли файл
        file_exists = os.path.isfile(file_name)
        with open(file_name, mode="a", newline="") as file:  # Открываем файл в режиме добавления
            writer = csv.writer(file)  # Создаём объект для записи в CSV
            if not file_exists:  # Если файл не существует, записываем заголовки
                writer.writerow(["Режим", "Глубина", "Время (сек)"])
            writer.writerow([mode, max_iter, elapsed_time])

if __name__ == '__main__':
    os.environ['QT_QPA_PLATFORM'] = 'xcb'  # Устанавливаем платформу для работы с Qt
    app = QApplication(sys.argv)  # Создаём экземпляр приложения Qt
    viewer = MandelbrotViewer()  # Создаём объект для отображения фрактала
    viewer.show()  # Показываем окно приложения
    sys.exit(app.exec_())  # Запускаем основной цикл приложения
