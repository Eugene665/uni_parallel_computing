import sys
import socket
import threading
from PyQt5.QtWidgets import (
    QApplication, QWidget, QVBoxLayout, QHBoxLayout, QTextEdit, QLineEdit, QPushButton, QLabel
)
from PyQt5.QtGui import QPixmap, QPainter, QPen
from PyQt5.QtCore import Qt, QPoint
import json

class ChatClient(QWidget):
    def __init__(self, host="127.0.0.1", port=5002):
        super().__init__()
        self.setWindowTitle("Графический чат")
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect((host, port))
        self.pen_mode = "draw"
        self.canvas_size = 20
        self.cell_size = 20
        self.canvas_matrix = [[0 for _ in range(self.canvas_size)] for _ in range(self.canvas_size)]
        self.init_ui()

    def init_ui(self):
        layout = QVBoxLayout()

        # Логин
        login_layout = QHBoxLayout()
        self.login_input = QLineEdit()
        self.login_input.setPlaceholderText("Логин")
        self.login_button = QPushButton("Login")
        self.login_button.clicked.connect(self.login)
        login_layout.addWidget(self.login_input)
        login_layout.addWidget(self.login_button)
        layout.addLayout(login_layout)

        # Чат
        self.chat_display = QTextEdit()
        self.chat_display.setReadOnly(True)
        self.message_input = QLineEdit()
        self.message_input.setPlaceholderText("Введите сообщение...")
        self.send_button = QPushButton("Send")
        self.send_button.clicked.connect(self.send_message)
        chat_layout = QVBoxLayout()
        chat_layout.addWidget(self.chat_display)
        chat_layout.addWidget(self.message_input)
        chat_layout.addWidget(self.send_button)
        layout.addLayout(chat_layout)

        # Поле для рисования
        self.drawing_area = QLabel()
        self.canvas = QPixmap(self.canvas_size * self.cell_size, self.canvas_size * self.cell_size)
        self.canvas.fill(Qt.white)
        self.drawing_area.setPixmap(self.canvas)

        # Кнопки "Рисовать" и "Ластик"
        drawing_controls = QHBoxLayout()
        self.draw_button = QPushButton("Рисовать")
        self.draw_button.clicked.connect(self.set_draw_mode)
        self.erase_button = QPushButton("Ластик")
        self.erase_button.clicked.connect(self.set_erase_mode)
        drawing_controls.addWidget(self.draw_button)
        drawing_controls.addWidget(self.erase_button)

        layout.addWidget(self.drawing_area)
        layout.addLayout(drawing_controls)
        self.drawing_area.mousePressEvent = self.update_drawing
        self.setLayout(layout)

    def login(self):
        self.username = self.login_input.text()
        if self.username:
            self.socket.send(f"{self.username} подключился".encode())
            threading.Thread(target=self.receive_messages, daemon=True).start()

    def send_message(self):
        message = self.message_input.text()
        if message:
            self.socket.send(f"{self.username}: {message}".encode())
            self.message_input.clear()

    def receive_messages(self):
        buffer_size = 4096  # Увеличиваем размер буфера
        while True:
            try:
                data = b""
                while True:
                    part = self.socket.recv(buffer_size)
                    data += part
                    if len(part) < buffer_size:  # Признак конца сообщения
                        break
                data = data.decode()

                if data.startswith("DRAWING:"):
                    # Обновление рисунка
                    self.canvas_matrix = json.loads(data[8:])
                    self.update_canvas()
                else:
                    # Сообщение чата
                    self.chat_display.append(data)
            except (ConnectionResetError, json.JSONDecodeError) as e:
                print(f"Ошибка при получении данных: {e}")
                break

    def set_draw_mode(self):
        self.pen_mode = "draw"

    def set_erase_mode(self):
        self.pen_mode = "erase"

    def update_drawing(self, event):
        pos = event.pos()
        x, y = pos.x() // self.cell_size, pos.y() // self.cell_size
        value = 1 if self.pen_mode == "draw" else 0
        self.canvas_matrix[x][y] = value
        self.socket.send(f"DRAW:{json.dumps({'x': x, 'y': y, 'value': value})}".encode())
        self.update_canvas()

    def update_canvas(self):
        painter = QPainter(self.canvas)
        for x in range(self.canvas_size):
            for y in range(self.canvas_size):
                color = Qt.black if self.canvas_matrix[x][y] == 1 else Qt.white
                painter.fillRect(x * self.cell_size, y * self.cell_size, self.cell_size, self.cell_size, color)
        self.drawing_area.setPixmap(self.canvas)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    client = ChatClient()
    client.show()
    sys.exit(app.exec_())
