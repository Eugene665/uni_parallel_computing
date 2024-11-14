import numpy as np
import multiprocessing
import os
import time

# Размерность матриц
N = 3000

# Генерация случайных матриц A и B
A = np.random.rand(N, N)
B = np.random.rand(N, N)
C = np.zeros((N, N))

# Функция для вычисления произведения строки на столбец
def multiply_row(start_row, end_row):
    global A, B, C
    # Ограничение доступных процессу ядер
    os.sched_setaffinity(0, {0, 1, 2, 3})  # Устанавливаем доступные ядра
    for i in range(start_row, end_row):
        C[i] = np.dot(A[i], B)

# Количество процессов
num_processes = 4

# Замер времени выполнения
start_time = time.time()

# Создание пула процессов и распределение задачи
with multiprocessing.Pool(processes=num_processes) as pool:
    rows_per_process = N // num_processes
    tasks = [
        (i * rows_per_process, (i + 1) * rows_per_process if i != num_processes - 1 else N)
        for i in range(num_processes)
    ]
    pool.starmap(multiply_row, tasks)

# Завершение замера времени выполнения
end_time = time.time()
print("Время выполнения:", end_time - start_time, "секунд")
