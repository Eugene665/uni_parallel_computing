#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <mutex>
#include <QDateTime>

using namespace std::chrono;
using namespace std;

std::mutex mtx;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// Функция для обмена значений без затирки
void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void out_arr_before(int* arr, int length_arr, const string& name_sort) {
    // Вывод массива до сортировки
    qDebug() << "Массив до сортировки " << QString::fromStdString(name_sort);
    // Тип QString для работы с дебагом Qt
    QString output;
    for (int i = 0; i < length_arr; i++) {
        // QString::number перевод числа в строку
        output += QString::number(arr[i]) + " ";
    }
    // Вывод без кавычек
    qDebug().noquote() << output;
    qDebug() << "\n";
}

void out_arr_after(int* arr, int length_arr, const string& name_sort) {
    // Вывод массива после сортировки
    qDebug() << "Массив после сортировки " << QString::fromStdString(name_sort);
    // Тип QString для работы с дебагом Qt
    QString output;
    for (int i = 0; i < length_arr; i++) {
        // QString::number перевод числа в строку
        output += QString::number(arr[i]) + " ";
    }
    // Вывод без кавычек
    qDebug().noquote() << output;
    qDebug() << "\n";
}


// Функция копирования исходного массива в отдельный массив для сортировки
void CopyArr(const int* source_arr, int* dest_arr, int length_arr) {
    std::copy(source_arr, source_arr + length_arr, dest_arr);
}

// Класс Sort с методом
class Sort {
public:
    // Виртуальная функция, которая в будующем будет перезаписана
    virtual void sort(int* arr, int length_arr) = 0;
    // Функции для получания кол-ва сравнений и обмена
    int getComparisons() const { return comparisons; }
    int getSwaps() const { return swaps; }

protected:
    // Счётчики сравнений и обмена
    int comparisons = 0;
    int swaps = 0;
};

class BubbleSort : public Sort {
public:
    // Переопределение виртуальной функции сортировки
    void sort(int* arr, int length_arr) override {
        // Сброс счётчиков сравнений и обмена
        comparisons = 0;
        swaps = 0;
        // Проходим по всему массиву
        for (int i = 0; i < length_arr - 1; i++) {
            // Проходим по всему массиву помимо чисел, которые уже всплыли
            for (int j = 0; j < length_arr - i - 1; j++) {
                // Увеличение счётчика сравнений
                comparisons++;
                if (arr[j] > arr[j + 1]) {
                    // Обмен значений при выполнении условия + увеличение счётчика сравнения
                    Swap(arr[j], arr[j + 1]);
                    swaps++;
                }

                // Получаем стандартный алгоритм всплытия значений
                //<-неотсортированная часть----------------> <-отсортированная часть с "всплывшими" значениями->
                //<-неотсортированная часть----------> <-------отсортированная часть с "всплывшими" значениями->
                //<-неотсортированная часть-> <----------------отсортированная часть с "всплывшими" значениями->

            }
        }
    }
};

class ShakerSort : public Sort {
public:
    // Переопределение виртуальной функции сортировки
    void sort(int* arr, int length_arr) override {
        // Сброс счётчиков сравнений и обмена
        comparisons = 0;
        swaps = 0;
        // Левый и правый указатель на границы
        int left_pose = 0;
        int right_pose = length_arr - 1;
        // Цикл до подхода левого указателя до правого указателя
        while (left_pose <= right_pose) {
            // Проход слева направо
            for (int i = right_pose; i > left_pose; i--) {
                // Увеличение счётчика сравнений
                comparisons++;
                if (arr[i - 1] > arr[i]) {
                    // Обмен значений при выполнении условия + увеличение счётчика сравнения
                    Swap(arr[i - 1], arr[i]);
                    swaps++;
                }
            }
            //  Пермещаем левый указатель вправо
            left_pose++;
            // Проход справа налево
            for (int i = left_pose; i < right_pose; i++) {
                // Увеличение счётчика сравнений
                comparisons++;
                if (arr[i] > arr[i + 1]) {
                    // Обмен значений при выполнении условия + увеличение счётчика сравнения
                    Swap(arr[i], arr[i + 1]);
                    swaps++;
                }
            }
            // Перемещаем правый указатель влево
            right_pose--;
            // Получаем сходящиеся указатели
            //отсортированная часть->         <-отсортированная часть
            // отсортированная часть->      <-отсортированная часть
            //   отсортированная часть->  <-отсортированная часть
        }
    }
};

class SelectionSort : public Sort {
public:
    void sort(int* arr, int length_arr) override {
        // Сброс счётчиков сравнений и обмена
        comparisons = 0;
        swaps = 0;
        // Внешний цикл проходит по каждому элементу массива, кроме последнего
        for (int i = 0; i < length_arr - 1; i++) {
            // Предполагаем, что текущий элемент (i) является наименьшим
            int smallest_pose = i;
            // Внутренний цикл находит наименьший элемент в оставшейся части массива(от i + 1 до конца)
            for (int j = i + 1; j < length_arr; j++) {
                // Увеличение счётчика сравнений
                comparisons++;
                if (arr[j] < arr[smallest_pose]) {
                    // Обновление позиции наименьшего элемента
                    smallest_pose = j;
                }
            }
            // Если наименьший элемент найден, меняем его с текущим элементом
            if (smallest_pose != i) {
                // Обмен значений при выполнении условия + увеличение счётчика сравнения
                Swap(arr[i], arr[smallest_pose]);
                swaps++;
            }
            // Начинаем сравнение с первого и нулевого элемента
            //
        }
    }
};

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_start_all_sort_button_clicked() {
    window = new sorting_results_window(this);

    // Вводим в программу данные из GUI
    int length_arr = ui->input_len_arr->text().toInt();
    bool flag_parallel = ui->parallel_radio_button->isChecked();
    bool flag_out_arr = ui->checkBox->isChecked();

    // Создаём вектор и генерируем исходный массив
    std::vector<int> arr(length_arr);
    std::generate(arr.begin(), arr.end(), []() { return rand() % 20; });

    // Создаём 3 вертора для 3-х сортировок
    std::vector<int> bubble_arr(length_arr);
    std::vector<int> shaker_arr(length_arr);
    std::vector<int> selection_arr(length_arr);

    // Копируем массив в массивы для сортировок в параллельном или в последовательном режиме
    if (flag_parallel) {
        std::thread th1([&]() { CopyArr(arr.data(), bubble_arr.data(), length_arr); });
        std::thread th2([&]() { CopyArr(arr.data(), shaker_arr.data(), length_arr); });
        std::thread th3([&]() { CopyArr(arr.data(), selection_arr.data(), length_arr); });

        th1.join();
        th2.join();
        th3.join();

    } else {
        CopyArr(arr.data(), bubble_arr.data(), length_arr);
        CopyArr(arr.data(), shaker_arr.data(), length_arr);
        CopyArr(arr.data(), selection_arr.data(), length_arr);
    }

    // Создаём элементы классов
    BubbleSort sorter_bubble;
    ShakerSort sorter_shaker;
    SelectionSort sorter_selection;

    // Лямбда-функция для сортировки
    // Принимает ссылку на элемент класса сортировки, вектор, имя сортировки, ссылки на время сортировки и сравнений с обменом
    auto sort_and_measure = [&](Sort& sorter, std::vector<int>& arr, const std::string& sort_name, double& seconds, int& comparisons, int& swaps) {
        // Вывод массива до сортировки при флажке со значением true
        if (flag_out_arr) out_arr_before(arr.data(), length_arr, sort_name);
        // Начало счёта времени
        auto start_time = high_resolution_clock::now();
        // Запуск метода класса сортировки
        sorter.sort(arr.data(), length_arr);
        // Окончание счёта времени
        auto end_time = high_resolution_clock::now();
        // Подсчёт длительности сортировки
        std::chrono::duration<double> time_span = end_time - start_time;
        seconds = time_span.count();
        // Вытаскиваем кол-ва сравнений и перемещений
        comparisons = sorter.getComparisons();
        swaps = sorter.getSwaps();
        // Вывод массива после сортировки при флажке со значением true
        if (flag_out_arr) out_arr_after(arr.data(), length_arr, sort_name);
    };

    double bubble_time, shaker_time, selection_time;
    int bubble_comparisons, shaker_comparisons, selection_comparisons;
    int bubble_swaps, shaker_swaps, selection_swaps;

    // Сортировка в параллельном/последовательном режиме
    if (flag_parallel) {

        std::thread th1([&]() { sort_and_measure(sorter_bubble, bubble_arr, "пузырьком", bubble_time, bubble_comparisons, bubble_swaps); });
        std::thread th2([&]() { sort_and_measure(sorter_shaker, shaker_arr, "шейкером", shaker_time, shaker_comparisons, shaker_swaps); });
        std::thread th3([&]() { sort_and_measure(sorter_selection, selection_arr, "выбором", selection_time, selection_comparisons, selection_swaps); });

        th1.join();
        th2.join();
        th3.join();

    } else {

        sort_and_measure(sorter_bubble, bubble_arr, "пузырьком", bubble_time, bubble_comparisons, bubble_swaps);
        sort_and_measure(sorter_shaker, shaker_arr, "шейкером", shaker_time, shaker_comparisons, shaker_swaps);
        sort_and_measure(sorter_selection, selection_arr, "выбором", selection_time, selection_comparisons, selection_swaps);
    }

    // Запись данных в массив данных
    double sortData[9] = {
        bubble_time,
        static_cast<double>(bubble_comparisons),
        static_cast<double>(bubble_swaps),
        shaker_time,
        static_cast<double>(shaker_comparisons),
        static_cast<double>(shaker_swaps),
        selection_time,
        static_cast<double>(selection_comparisons),
        static_cast<double>(selection_swaps)
    };

    // Отображение длины массива, результатов и отображение окна с результатами
    window->setSortData(sortData);
    window->setLength(length_arr);
    window->show();
}
