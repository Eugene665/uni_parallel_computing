import numpy as np
import threading
import time

# Размерность матриц
N = 3000

# Генерация случайных матриц A и B
A = np.random.rand(N, N)
B = np.random.rand(N, N)
C = np.zeros((N, N))  # Результирующая матрица

# Функция для умножения строк матрицы
def multiply_row(start_row, end_row):
    global A, B, C
    for i in range(start_row, end_row):
        C[i] = np.dot(A[i], B)

# Параметры многопоточности
num_threads = 4
threads = []
rows_per_thread = N // num_threads

# Замер времени выполнения
start_time = time.time()

# Запуск потоков
for i in range(num_threads):
    start_row = i * rows_per_thread
    end_row = (i + 1) * rows_per_thread if i != num_threads - 1 else N
    thread = threading.Thread(target=multiply_row, args=(start_row, end_row))
    threads.append(thread)
    thread.start()

# Ожидание завершения всех потоков
for thread in threads:
    thread.join()

# Завершение замера времени выполнения
end_time = time.time()
print("Время выполнения:", end_time - start_time, "секунд")
