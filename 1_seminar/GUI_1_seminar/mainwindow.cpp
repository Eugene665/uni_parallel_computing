#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <time.h>

using namespace std;

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

void out_arr_before(int* arr, int length_arr, string name_sort) {
    // Вывод массива до сортировки
    qDebug() << "Массив до сортировки " << QString::fromStdString(name_sort);
    QString output;
    for (int i = 0; i < length_arr; i++) {
        output += QString::number(arr[i]) + " ";
    }
    qDebug().noquote() << output;
    qDebug() << "\n";
}

void out_arr_after(int* arr, int length_arr, string name_sort) {
    // Вывод массива после сортировки
    qDebug() << "Массив после сортировки " << QString::fromStdString(name_sort);
    QString output;
    for (int i = 0; i < length_arr; i++) {
        output += QString::number(arr[i]) + " ";
    }
    qDebug().noquote() << output;
    qDebug() << "\n";
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
        comparisons = 0;  // Сброс счётчика сравнений
        swaps = 0;        // Сброс счётчика перестановок

        for (int i = 0; i < length_arr - 1; i++) {
            for (int j = 0; j < length_arr - i - 1; j++) {
                comparisons++;  // Увеличение счётчика сравнений
                if (arr[j] > arr[j + 1]) {
                    Swap(arr[j], arr[j + 1]);
                    swaps++;  // Увеличение счётчика перестановок
                }
            }
        }
    }
};

class ShakerSort : public Sort {
public:
    void sort(int* arr, int length_arr) override {
        comparisons = 0;  // Сброс счётчика сравнений
        swaps = 0;        // Сброс счётчика перестановок

        int left_pose = 0;
        int right_pose = length_arr - 1;
        while (left_pose <= right_pose) {
            for (int i = right_pose; i > left_pose; i--) {
                comparisons++;  // Увеличение счётчика сравнений
                if (arr[i - 1] > arr[i]) {
                    Swap(arr[i - 1], arr[i]);
                    swaps++;  // Увеличение счётчика перестановок
                }
            }
            left_pose++;
            for (int i = left_pose; i < right_pose; i++) {
                comparisons++;  // Увеличение счётчика сравнений
                if (arr[i] > arr[i + 1]) {
                    Swap(arr[i], arr[i + 1]);
                    swaps++;  // Увеличение счётчика перестановок
                }
            }
            right_pose--;
        }
    }
};


class SelectionSort : public Sort {
public:
    void sort(int* arr, int length_arr) override {
        comparisons = 0;  // Сброс счётчика сравнений
        swaps = 0;        // Сброс счётчика перестановок

        for (int i = 0; i < length_arr - 1; i++) {
            int smallest_pose = i;
            for (int j = i + 1; j < length_arr; j++) {
                comparisons++;  // Увеличение счётчика сравнений
                if (arr[j] < arr[smallest_pose]) {
                    smallest_pose = j;
                }
            }
            if (smallest_pose != i) {
                Swap(arr[i], arr[smallest_pose]);
                swaps++;  // Увеличение счётчика перестановок
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

    bool parallel_sort;
    if (ui->parallel_radio_button->isChecked()){
        parallel_sort = true;
    }
    if (ui->sequentially_radio_button->isChecked()){
        parallel_sort = false;
    }

    int length_arr = ui->input_len_arr->text().toInt();
    //qDebug() << "длина массива:" << length_arr;

    setlocale(LC_ALL,"Rus");

    /*
    // Обозначение переменной для длины массива и её ввод от пользователя
    int length_arr;
    cout << "Введите длину массива: ";
    cin >> length_arr;

    // Обозначение массива и ввод содержимого от пользователя
    int arr[length_arr];
    cout << "Введите числа для массива через пробел: ";
    for (int i = 0; i < length_arr; i++){
      cin >> arr[i];
    }
    */

    // Исходный массив
    //int length_arr = 50;
    //int arr[length_arr]{6, 10, 1, 3, 2};
    int arr[length_arr];

    for (int i = 0; i < length_arr; i++){
        int num = 1 + rand() % 10;
        arr[i] = num;
    }

    string flag_out_arr;
    //cout << "Хотите выводить массивы до и после сортировки(да/нет): ";
    //cin >> flag_out_arr;
    if (ui->checkBox->isChecked()){
        flag_out_arr = "да";
    }

    if (flag_out_arr == "да") {
        // Вывод исходного массива
        qDebug() << "Исходный массив";
        QString output;
        for (int i = 0; i < length_arr; i++) {
            output += QString::number(arr[i]) + " ";
        }
        qDebug().noquote() << output;
    }
    qDebug() << "\n\n\n";

    //int bubbleData[3];
    //int shakerData[3];
    //int selectionData[3];

    //BubbleSort---------------------------------------
    // Копирования массива для сортировки пузырьком
    int bubble_arr[length_arr];
    for (int i = 0; i < length_arr; i++) {
        bubble_arr[i] = arr[i];
    }

    if (flag_out_arr == "да"){
        // Вывод массива до сортировки
        out_arr_before(bubble_arr, length_arr, "пузырьком");
    }

    // Создание объекта BubbleSort
    BubbleSort sorter_bubble;
    // Начало измерения времини
    clock_t start_bubble_sort = clock();
    // Вызов метода сортировки
    sorter_bubble.sort(bubble_arr, length_arr);
    // Окончание измерения времени
    clock_t end_bubble_sort = clock();
    double seconds_bubble_sort = (double)(end_bubble_sort - start_bubble_sort) / CLOCKS_PER_SEC;
    qDebug() << "Затрачено секунд на сортироку пузырьком\n" << seconds_bubble_sort << "\n";

    int comparisons_bubble = sorter_bubble.getComparisons();
    int swaps_bubble = sorter_bubble.getSwaps();
    qDebug() << "Сравнений (пузырьковая сортировка):" << comparisons_bubble;
    qDebug() << "Перестановок (пузырьковая сортировка):" << swaps_bubble << "\n";
    //bubbleData[0] = seconds_bubble_sort;
    //bubbleData[1] = comparisons_bubble;
    //bubbleData[2] = swaps_bubble;

    if (flag_out_arr == "да"){
        // Вывод отсортированного массива
        out_arr_after(bubble_arr, length_arr, "пузырьком");
    }
    qDebug() << "\n\n\n";

    //ShakerSort-------------------------------------------
    // Копирования массива для сортировки шейкером
    int shaker_arr[length_arr];
    for (int i = 0; i < length_arr; i++) {
        shaker_arr[i] = arr[i];
    }

    if (flag_out_arr == "да"){
        // Вывод массива до сортировки
        out_arr_before(shaker_arr, length_arr, "шейкером");
    }

    // Создание объекта ShakerSort
    ShakerSort sorter_shaker;
    // Начало измерения времини
    clock_t start_shaker_sort = clock();
    // Вызов метода сортировки
    sorter_shaker.sort(shaker_arr, length_arr);
    // Окончание измерения времени
    clock_t end_shaker_sort = clock();
    double seconds_shaker_sort = (double)(end_shaker_sort - start_shaker_sort) / CLOCKS_PER_SEC;
    qDebug() << "Затрачено секунд на сортироку шейкером\n" << seconds_shaker_sort << "\n";

    int comparisons_shaker = sorter_shaker.getComparisons();
    int swaps_shaker = sorter_shaker.getSwaps();
    qDebug() << "Сравнений (сортировка шейкером):" << comparisons_shaker;
    qDebug() << "Перестановок (сортировка шейкером):" << swaps_shaker << "\n";
    //shakerData[0] = seconds_shaker_sort;
    //shakerData[1] = comparisons_shaker;
    //shakerData[2] = swaps_shaker;

    if (flag_out_arr == "да"){
        // Вывод отсортированного массива
        out_arr_after(shaker_arr, length_arr, "шейкером");
    }
    qDebug() << "\n\n\n";

    //SelectionSort----------------------------------------
    // Копирования массива для сортировки выбором
    int  selection_arr[length_arr];
    for (int i = 0; i < length_arr; i++) {
        selection_arr[i] = arr[i];
    }

    if (flag_out_arr == "да"){
        // Вывод массива до сортировки
        out_arr_before(selection_arr, length_arr, "выбором");
    }

    // Создание объекта SelectionSort
    SelectionSort sorter_selection;
    // Начало измерения времини
    clock_t start_selection_sort = clock();
    // Вызов метода сортировки
    sorter_selection.sort(selection_arr, length_arr);
    // Окончание измерения времени
    clock_t end_selection_sort = clock();
    double seconds_selection_sort = (double)(end_selection_sort - start_selection_sort) / CLOCKS_PER_SEC;
    qDebug() << "Затрачено секунд на сортироку выбором\n" << seconds_selection_sort << "\n";

    int comparisons_selection = sorter_selection.getComparisons();
    int swaps_selection = sorter_selection.getSwaps();
    qDebug() << "Сравнений (сортировка выбором):" << comparisons_selection;
    qDebug() << "Перестановок (сортировка выбором):" << swaps_selection << "\n";
    //selectionData[0] = seconds_selection_sort;
    //selectionData[1] = comparisons_selection;
    //selectionData[2] = swaps_selection;

    if (flag_out_arr == "да"){
        // Вывод отсортированного массива
        if (flag_out_arr == "да"){
            out_arr_after(selection_arr, length_arr, "выбором");
        }
    }
    qDebug() << "\n\n";

    double sortData[9] = {seconds_bubble_sort, comparisons_bubble, swaps_bubble,
                          seconds_shaker_sort, comparisons_shaker, swaps_shaker,
                          seconds_selection_sort, comparisons_selection, swaps_selection};

    window->setSortData(sortData);
    window->setLength(length_arr);
    window->show();

}


