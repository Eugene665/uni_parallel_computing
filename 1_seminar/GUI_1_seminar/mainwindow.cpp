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
    QString output;
    for (int i = 0; i < length_arr; i++) {
        output += QString::number(arr[i]) + " ";
    }
    qDebug().noquote() << output;
    qDebug() << "\n";
}

void out_arr_after(int* arr, int length_arr, const string& name_sort) {
    // Вывод массива после сортировки
    qDebug() << "Массив после сортировки " << QString::fromStdString(name_sort);
    QString output;
    for (int i = 0; i < length_arr; i++) {
        output += QString::number(arr[i]) + " ";
    }
    qDebug().noquote() << output;
    qDebug() << "\n";
}

template<typename T>
void CopyArr(const T* source_arr, T* dest_arr, int length_arr) {
    std::copy(source_arr, source_arr + length_arr, dest_arr);
}

class Sort {
public:
    virtual void sort(int* arr, int length_arr) = 0;
    int getComparisons() const { return comparisons; }
    int getSwaps() const { return swaps; }

protected:
    int comparisons = 0;
    int swaps = 0;
};

class BubbleSort : public Sort {
public:
    void sort(int* arr, int length_arr) override {
        comparisons = 0;
        swaps = 0;
        for (int i = 0; i < length_arr - 1; i++) {
            for (int j = 0; j < length_arr - i - 1; j++) {
                comparisons++;
                if (arr[j] > arr[j + 1]) {
                    Swap(arr[j], arr[j + 1]);
                    swaps++;
                }
            }
        }
    }
};

class ShakerSort : public Sort {
public:
    void sort(int* arr, int length_arr) override {
        comparisons = 0;
        swaps = 0;
        int left_pose = 0;
        int right_pose = length_arr - 1;
        while (left_pose <= right_pose) {
            for (int i = right_pose; i > left_pose; i--) {
                comparisons++;
                if (arr[i - 1] > arr[i]) {
                    Swap(arr[i - 1], arr[i]);
                    swaps++;
                }
            }
            left_pose++;
            for (int i = left_pose; i < right_pose; i++) {
                comparisons++;
                if (arr[i] > arr[i + 1]) {
                    Swap(arr[i], arr[i + 1]);
                    swaps++;
                }
            }
            right_pose--;
        }
    }
};

class SelectionSort : public Sort {
public:
    void sort(int* arr, int length_arr) override {
        comparisons = 0;
        swaps = 0;
        for (int i = 0; i < length_arr - 1; i++) {
            int smallest_pose = i;
            for (int j = i + 1; j < length_arr; j++) {
                comparisons++;
                if (arr[j] < arr[smallest_pose]) {
                    smallest_pose = j;
                }
            }
            if (smallest_pose != i) {
                Swap(arr[i], arr[smallest_pose]);
                swaps++;
            }
        }
    }
};

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_start_all_sort_button_clicked() {
    window = new sorting_results_window(this);

    int length_arr = ui->input_len_arr->text().toInt();
    bool flag_parallel = ui->parallel_radio_button->isChecked();
    bool flag_out_arr = ui->checkBox->isChecked();

    std::vector<int> arr(length_arr);
    std::generate(arr.begin(), arr.end(), []() { return rand() % 20; });

    std::vector<int> bubble_arr(length_arr);
    std::vector<int> shaker_arr(length_arr);
    std::vector<int> selection_arr(length_arr);

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

    BubbleSort sorter_bubble;
    ShakerSort sorter_shaker;
    SelectionSort sorter_selection;

    auto sort_and_measure = [&](Sort& sorter, std::vector<int>& arr, const std::string& sort_name, double& seconds, int& comparisons, int& swaps) {
        if (flag_out_arr) out_arr_before(arr.data(), length_arr, sort_name);

        auto start_time = high_resolution_clock::now();

        sorter.sort(arr.data(), length_arr);

        auto end_time = high_resolution_clock::now();

        std::chrono::duration<double> time_span = end_time - start_time;
        seconds = time_span.count();

        comparisons = sorter.getComparisons();
        swaps = sorter.getSwaps();

        if (flag_out_arr) out_arr_after(arr.data(), length_arr, sort_name);
    };

    double bubble_time, shaker_time, selection_time;
    int bubble_comparisons, shaker_comparisons, selection_comparisons;
    int bubble_swaps, shaker_swaps, selection_swaps;

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

    window->setSortData(sortData);
    window->setLength(length_arr);
    window->show();
}
