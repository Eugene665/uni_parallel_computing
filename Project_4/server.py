import socket
import threading
import sqlite3
import json

class ChatServer:
    def __init__(self, host="127.0.0.1", port=5002):
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((host, port))
        self.server.listen(5)
        print(f"Сервер запущен на {host}:{port}")
        self.clients = []
        self.db_conn = sqlite3.connect("chat.db", check_same_thread=False)
        self.create_tables()
        self.canvas_size = 20
        self.canvas_matrix = [[0 for _ in range(self.canvas_size)] for _ in range(self.canvas_size)]

    def create_tables(self):
        cursor = self.db_conn.cursor()
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS chat_history (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                message TEXT
            )
        """)
        cursor.execute("""
            CREATE TABLE IF NOT EXISTS drawing (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                matrix TEXT
            )
        """)
        self.db_conn.commit()

    def save_message(self, message):
        cursor = self.db_conn.cursor()
        cursor.execute("INSERT INTO chat_history (message) VALUES (?)", (message,))
        self.db_conn.commit()

    def load_chat_history(self):
        cursor = self.db_conn.cursor()
        cursor.execute("SELECT message FROM chat_history")
        return [row[0] for row in cursor.fetchall()]

    def save_drawing(self):
        cursor = self.db_conn.cursor()
        matrix_str = json.dumps(self.canvas_matrix)
        cursor.execute("INSERT INTO drawing (matrix) VALUES (?)", (matrix_str,))
        self.db_conn.commit()

    def broadcast(self, message, client_socket=None):
        self.save_message(message)
        for client in self.clients:
            client.send(message.encode())

    def broadcast_drawing(self):
        # Сериализуем данные рисунка в JSON
        drawing_data = json.dumps(self.canvas_matrix)
        message = f"DRAWING:{drawing_data}"
        # Отправляем сообщение всем клиентам
        for client in self.clients:
            client.sendall(message.encode())

    def handle_client(self, client_socket):
        try:
            # Отправляем историю чата и текущий рисунок новому клиенту
            for message in self.load_chat_history():
                client_socket.send(message.encode() + b'\n')

            client_socket.send(f"DRAWING:{json.dumps(self.canvas_matrix)}".encode())

            while True:
                data = client_socket.recv(1024).decode()
                if not data:
                    break

                if data.startswith("DRAW:"):
                    # Обновление рисунка
                    draw_data = json.loads(data[5:])
                    x, y, value = draw_data["x"], draw_data["y"], draw_data["value"]
                    self.canvas_matrix[x][y] = value
                    self.save_drawing()
                    self.broadcast_drawing()
                else:
                    # Сообщение в чате
                    print(f"Получено сообщение: {data}")
                    self.broadcast(data)
        except ConnectionResetError:
            pass
        finally:
            print("Клиент отключился.")
            self.clients.remove(client_socket)
            client_socket.close()

    def start(self):
        while True:
            client_socket, _ = self.server.accept()
            print("Новое подключение.")
            self.clients.append(client_socket)
            threading.Thread(target=self.handle_client, args=(client_socket,), daemon=True).start()

if __name__ == "__main__":
    server = ChatServer()
    server.start()
