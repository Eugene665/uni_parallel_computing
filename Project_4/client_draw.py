import socket
import threading
import json
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QLineEdit, QHBoxLayout
from PyQt5.QtGui import QPainter, QColor, QMouseEvent
from PyQt5.QtCore import Qt, pyqtSignal, QThread

HOST = '127.0.0.1'
PORT = 65432

class NetworkThread(QThread):
    data_received = pyqtSignal(str)

    def __init__(self, host, port):
        super().__init__()
        self.host = host
        self.port = port
        self.socket = None

    def run(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((self.host, self.port))

        while True:
            try:
                data = self.socket.recv(1024).decode()
                if data:
                    self.data_received.emit(data)
            except Exception as e:
                print(f"Ошибка сети: {e}")
                break

    def send(self, message):
        try:
            self.socket.send(f"{message}\n".encode())
        except Exception as e:
            print(f"Ошибка отправки данных: {e}")

class DrawingWidget(QWidget):
    def __init__(self, network_thread):
        super().__init__()
        self.network_thread = network_thread
        self.pixels = []
        self.is_logged_in = False  # Флаг для блокировки рисования
        self.setWindowTitle("Рисование")

    def mousePressEvent(self, event: QMouseEvent):
        if self.is_logged_in:
            self.draw_pixel(event.x(), event.y())

    def mouseMoveEvent(self, event: QMouseEvent):
        if self.is_logged_in:
            self.draw_pixel(event.x(), event.y())

    def draw_pixel(self, x, y):
        self.pixels.append((x, y))
        self.update()
        self.network_thread.send(f"DRAW:{json.dumps({'x': x, 'y': y, 'value': 1})}")

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setBrush(QColor(0, 0, 0))
        for x, y in self.pixels:
            painter.drawRect(x, y, 1, 1)

class ClientApp(QWidget):
    def __init__(self):
        super().__init__()
        self.network_thread = NetworkThread(HOST, PORT)
        self.network_thread.data_received.connect(self.handle_server_message)
        self.network_thread.start()

        self.login = None  # Логин пользователя
        self.init_ui()

    def init_ui(self):
        self.setWindowTitle("Клиент")
        self.setGeometry(70, 50, 500, 500)  # Увеличиваем размеры окна

        self.layout = QVBoxLayout()

        # Вложенный макет для центрирования логина и кнопки
        self.center_layout = QVBoxLayout()
        self.center_layout.setAlignment(Qt.AlignCenter)

        # Поле ввода логина
        self.login_label = QLabel("Введите ваш логин:")
        self.center_layout.addWidget(self.login_label)

        self.login_input = QLineEdit()
        self.center_layout.addWidget(self.login_input)

        # Кнопка входа
        self.login_button = QPushButton("Войти")
        self.login_button.clicked.connect(self.login_user)
        self.center_layout.addWidget(self.login_button)

        # Добавление вложенного макета в основной макет
        self.layout.addLayout(self.center_layout)

        # Виджет для рисования
        self.drawing_widget = DrawingWidget(self.network_thread)
        self.drawing_widget.setFixedSize(600, 500)  # Увеличиваем размеры виджета для рисования
        self.layout.addWidget(self.drawing_widget)

        # Метка с логином
        self.user_label = QLabel("")
        self.layout.addWidget(self.user_label)

        self.setLayout(self.layout)

    def login_user(self):
        self.login = self.login_input.text().strip()
        if self.login:
            self.network_thread.send(f"LOGIN:{self.login}")
            self.user_label.setText(f"Вы вошли как: {self.login}")
            self.user_label.setAlignment(Qt.AlignBottom)  # Выровнять по низу
            self.login_label.hide()
            self.login_input.hide()
            self.login_button.hide()
            self.drawing_widget.is_logged_in = True
        else:
            self.user_label.setText("Логин не может быть пустым!")

    def handle_server_message(self, message):
        if message.startswith("DRAW:"):
            try:
                draw_data = json.loads(message[5:])
                print(f"Получены данные для рисования: {draw_data}")
                self.drawing_widget.pixels.append((draw_data['x'], draw_data['y']))
                self.drawing_widget.update()
            except Exception as e:
                print(f"Ошибка обработки сообщения: {e}")
        elif message.startswith("LOGIN:"):
            print(f"Пользователь вошел: {message[6:]}")

if __name__ == "__main__":
    app = QApplication([])
    client = ClientApp()
    client.show()
    app.exec()