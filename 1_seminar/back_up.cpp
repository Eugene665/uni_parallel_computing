#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std::chrono;
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void out_arr_before(int* arr, int length_arr, string name_sort) {
    qDebug() << "Массив до сортировки " << QString::fromStdString(name_sort);
    QString output;
    for (int i = 0; i < length_arr; i++) {
        output += QString::number(arr[i]) + " ";
    }
    qDebug().noquote() << output;
}

void out_arr_after(int* arr, int length_arr, string name_sort) {
    qDebug() << "Массив после сортировки " << QString::fromStdString(name_sort);
    QString output;
    for (int i = 0; i < length_arr; i++) {
        output += QString::number(arr[i]) + " ";
    }
    qDebug().noquote() << output;
}

template<typename T>
void CopyArr(T* source_arr, T* sort_name_arr, int length_arr) {
    for (int i = 0; i < length_arr; i++) {
        sort_name_arr[i] = source_arr[i];
    }
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

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_all_sort_button_clicked()
{
    window = new sorting_results_window(this);

    int length_arr = ui->input_len_arr->text().toInt();
    bool flag_parallel = ui->parallel_radio_button->isChecked();
    bool flag_out_arr = ui->checkBox->isChecked();

    int arr[length_arr];
    for (int i = 0; i < length_arr; i++) {
        arr[i] = rand() % 100;
    }

    int bubble_arr[length_arr];
    int shaker_arr[length_arr];
    int selection_arr[length_arr];

    CopyArr(arr, bubble_arr, length_arr);
    CopyArr(arr, shaker_arr, length_arr);
    CopyArr(arr, selection_arr, length_arr);

    BubbleSort sorter_bubble;
    ShakerSort sorter_shaker;
    SelectionSort sorter_selection;
    auto sort_and_measure = [&](Sort& sorter, int* arr, std::string sort_name, double& seconds, int& comparisons, int& swaps) {
        if (flag_out_arr) out_arr_before(arr, length_arr, sort_name);

        auto start_time = std::chrono::high_resolution_clock::now();
        sorter.sort(arr, length_arr);
        auto end_time = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> time_span = end_time - start_time;
        seconds = time_span.count();

        QString Qsort_name = QString::fromStdString(sort_name);
        qDebug() << "sortname " << Qsort_name << "seconds " << seconds;

        comparisons = sorter.getComparisons();
        swaps = sorter.getSwaps();

        if (flag_out_arr) out_arr_after(arr, length_arr, sort_name);
    };

    double bubble_time, shaker_time, selection_time;
    int bubble_comparisons, bubble_swaps, shaker_comparisons, shaker_swaps, selection_comparisons, selection_swaps;

    if (flag_parallel) {
        std::thread th1([&]() {
            sort_and_measure(std::ref(sorter_bubble), bubble_arr, "пузырьком", std::ref(bubble_time), std::ref(bubble_comparisons), std::ref(bubble_swaps));
        });
        std::thread th2([&]() {
            sort_and_measure(std::ref(sorter_shaker), shaker_arr, "шейкером", std::ref(shaker_time), std::ref(shaker_comparisons), std::ref(shaker_swaps));
        });
        std::thread th3([&]() {
            sort_and_measure(std::ref(sorter_selection), selection_arr, "выбором", std::ref(selection_time), std::ref(selection_comparisons), std::ref(selection_swaps));
        });

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

