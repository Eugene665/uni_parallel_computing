
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

// Функция для генерации массива случайных чисел от 0 до 20
vector<int> generateArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 20);
    generate(arr.begin(), arr.end(), [&]() { return dis(gen); });
    return arr;
}

// Пузырьковая сортировка
void bubbleSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Шейкерная сортировка
void shakerSort(vector<int>& arr) {
    bool swapped = true;
    size_t start = 0;
    size_t end = arr.size() - 1;
    while (swapped) {
        swapped = false;
        for (size_t i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
        swapped = false;
        --end;
        for (size_t i = end; i > start; --i) {
            if (arr[i - 1] > arr[i]) {
                swap(arr[i - 1], arr[i]);
                swapped = true;
            }
        }
        ++start;
    }
}

// Сортировка вставками
void insertionSort(vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Функция для замера времени сортировки
template<typename Func>
void measureSortTime(Func sortFunction, vector<int> arr, const string& sortName) {
    auto start = high_resolution_clock::now();
    sortFunction(arr);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << sortName << " завершена за: " << duration.count() << " мс" << endl;
}

// Последовательная сортировка
void sequentialSort(vector<int> arr) {
    measureSortTime(bubbleSort, arr, "Пузырьковая сортировка");
    measureSortTime(shakerSort, arr, "Шейкерная сортировка");
    measureSortTime(insertionSort, arr, "Сортировка вставками");
}

// Параллельная сортировка
void parallelSort(vector<int> arr) {
    thread t1([&]() { measureSortTime(bubbleSort, arr, "Пузырьковая сортировка"); });
    thread t2([&]() { measureSortTime(shakerSort, arr, "Шейкерная сортировка"); });
    thread t3([&]() { measureSortTime(insertionSort, arr, "Сортировка вставками"); });

    t1.join();
    t2.join();
    t3.join();
}

int main() {
    vector<int> arr = generateArray(50000);

    cout << "Выберите тип сортировки: " << endl;
    cout << "1. Последовательная сортировка" << endl;
    cout << "2. Параллельная сортировка" << endl;
    int choice;
    cin >> choice;

    if (choice == 1) {
        sequentialSort(arr);
    } else if (choice == 2) {
        parallelSort(arr);
    } else {
        cout << "Неверный выбор!" << endl;
    }

    return 0;
}



