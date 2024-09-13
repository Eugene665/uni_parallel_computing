


#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>
#include <random>

// Функция для пузырьковой сортировки
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Функция для быстрой сортировки (quicksort)
void quickSort(std::vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j)
        quickSort(arr, left, j);
    if (i < right)
        quickSort(arr, i, right);
}

// Функция для генерации массива случайных чисел
void generateRandomArray(std::vector<int>& arr, int length) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000); // Генерация чисел от 1 до 1000

    arr.resize(length);
    for (int& num : arr) {
        num = dis(gen);
    }
}

// Функция для запуска пузырьковой сортировки в отдельном потоке
void runBubbleSort(std::vector<int>& arr) {
    bubbleSort(arr);
}

// Функция для запуска быстрой сортировки в отдельном потоке
void runQuickSort(std::vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}

int main() {
    int length;

    // Запрашиваем у пользователя длину массива
    std::cout << "Введите длину массива: ";
    std::cin >> length;

    if (length <= 0) {
        std::cerr << "Длина массива должна быть положительным числом." << std::endl;
        return 1;
    }

    std::vector<int> arr1;
    std::vector<int> arr2;

    // Генерация массива случайных чисел
    generateRandomArray(arr1, length);
    arr2 = arr1; // Копируем исходный массив для второй сортировки

    // Запуск сортировок в параллельных потоках
    std::thread t1(runBubbleSort, std::ref(arr1));
    std::thread t2(runQuickSort, std::ref(arr2));

    // Ожидание завершения потоков
    t1.join();
    t2.join();

    // Вывод сообщения о завершении сортировок
    std::cout << "Сортировки завершены." << std::endl;

    return 0;
}

