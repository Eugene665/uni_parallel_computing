import socket
import threading
import json

HOST = '127.0.0.1'
PORT = 65432

clients = []
logins = {}


def handle_client(client_socket, address):
    print(f"Клиент {address} подключился.")
    clients.append(client_socket)
    buffer = b""

    try:
        while True:
            data = client_socket.recv(1024)
            if not data:
                break

            buffer += data
            while b'\n' in buffer:
                # Отделяем одно сообщение
                message, buffer = buffer.split(b'\n', 1)
                process_message(message.decode(), client_socket)
    except Exception as e:
        print(f"Ошибка: {e}")
    finally:
        print(f"Клиент {address} отключился.")
        clients.remove(client_socket)
        if client_socket in logins:
            del logins[client_socket]
        client_socket.close()


def process_message(message, client_socket):
    if message.startswith("DRAW:"):
        try:
            draw_data = json.loads(message[5:])
            print(f"Рисование: {draw_data}")
            broadcast(message)  # Рассылка всем клиентам
        except json.JSONDecodeError as e:
            print(f"Ошибка JSON: {e}")
    elif message.startswith("LOGIN:"):
        login = message[6:]
        logins[client_socket] = login
        broadcast(f"LOGIN:{login}")
        print(f"Пользователь вошел: {login}")
    else:
        print(f"Получено сообщение: {message}")


def broadcast(message):
    for client in clients:
        try:
            client.send(f"{message}\n".encode())
        except Exception as e:
            print(f"Ошибка отправки данных клиенту: {e}")


def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen()
    print(f"Сервер запущен на {HOST}:{PORT}")

    while True:
        client_socket, address = server.accept()
        threading.Thread(target=handle_client, args=(client_socket, address)).start()


if __name__ == "__main__":
    start_server()
