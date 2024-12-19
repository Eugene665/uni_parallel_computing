import numpy as np
import socket
import pickle
from multiprocessing import Pool

# Функция для вычисления значения в множестве Мандельброта для комплексного числа c
def mandelbrot(c, max_iter):
    z = 0
    n = 0
    while abs(z) <= 2 and n < max_iter:
        z = z * z + c
        n += 1
    if n == max_iter:
        return 0  # Точка принадлежит множеству Мандельброта
    else:
        return 255 - int(255 * n / max_iter)  # Точка не принадлежит множеству

# Обертка для функции mandelbrot, чтобы она принимала кортеж аргументов
def mandelbrot_wrapper(args):
    x, y, max_iter = args
    c = complex(x, y)
    return mandelbrot(c, max_iter)

# Функция для вычисления фрактала Мандельброта
def compute_fractal(xmin, xmax, ymin, ymax, width, height, max_iter, parallel):
    x = np.linspace(xmin, xmax, width)  # Генерация координат x
    y = np.linspace(ymin, ymax, height)  # Генерация координат y
    coords = [(x[j], y[i], max_iter) for i in range(height) for j in range(width)]  # Создание списка координат и max_iter

    if parallel:
        # Параллельное вычисление с использованием пула процессов
        with Pool() as pool:
            results = pool.map(mandelbrot_wrapper, coords)
    else:
        # Последовательное вычисление
        results = [mandelbrot_wrapper(coord) for coord in coords]

    return np.array(results, dtype=np.uint8).reshape((height, width))  # Преобразование результата в массив numpy

# Функция для отправки данных клиенту через сокет
def send_data(client_socket, data):
    data_bytes = pickle.dumps(data)  # Сериализация данных с помощью pickle
    client_socket.sendall(len(data_bytes).to_bytes(4, byteorder='big'))  # Отправка длины данных
    client_socket.sendall(data_bytes)  # Отправка самих данных

# Функция для обработки запроса клиента
def handle_client(client_socket):
    data = client_socket.recv(4096)  # Получение данных от клиента
    xmin, xmax, ymin, ymax, width, height, max_iter, parallel = pickle.loads(data)  # Десериализация данных
    img = compute_fractal(xmin, xmax, ymin, ymax, width, height, max_iter, parallel)  # Вычисление фрактала
    send_data(client_socket, img)  # Отправка результата клиенту

# Главная функция сервера
def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Создание сокета
    server.bind(('0.0.0.0', 9998))  # Привязка сокета к адресу и порту
    server.listen(5)  # Прослушивание входящих соединений
    print("Server listening on port 9998")

    while True:
        client_socket, addr = server.accept()  # Принятие входящего соединения
        print(f"Accepted connection from {addr}")
        handle_client(client_socket)  # Обработка клиентского запроса
        client_socket.close()  # Закрытие соединения

if __name__ == "__main__":
    main()  # Запуск сервера