#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>
#include <time.h>
#include <thread>
#include <chrono>
using namespace std::chrono;
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

template<typename T>
void CopyArr(T* source_arr, T* sort_name_arr, int length_arr) {
    for (int i = 0; i < length_arr; i++) {
        sort_name_arr[i] = source_arr[i];
    }
}

class Sort {
public:
    //Виртуальный метод, который в последствии будет переопределён
    virtual void sort(int* arr, int length_arr) = 0;

    int getComparisons() const { return comparisons; }
    int getSwaps() const { return swaps; }

protected:
    int comparisons = 0;
    int swaps = 0;
};

class BubbleSort : public Sort {
public:
    // Переопределение функции
    void sort(int* arr, int length_arr) override {
        // Сброс счётчика сравнений и перестановок
        comparisons = 0;
        swaps = 0;
        // Проходим по всему списку
        for (int i = 0; i < length_arr - 1; i++) {
            // Проходим по списку до отсортированной части,
            // до чисел, которые уже "всплыли"
            for (int j = 0; j < length_arr - i - 1; j++) {
                // Увеличение счётчика сравнений
                comparisons++;
                // Если впереди стоящее число меньше,
                // числа меняюся местами
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
    //Виртуальный метод, который в последствии будет переопределён
    void sort(int* arr, int length_arr) override {
        comparisons = 0;  // Сброс счётчика сравнений
        swaps = 0;        // Сброс счётчика перестановок

        int left_pose = 0;
        int right_pose = length_arr - 1;
        while (left_pose <= right_pose) {
            // Идём вправо списки до правой позиции
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


    int length_arr = ui->input_len_arr->text().toInt();
    //qDebug() << "длина массива:" << length_arr;

    bool flag_parallel;
    if (ui->parallel_radio_button->isChecked()){
        flag_parallel = true;
    }
    if (ui->sequentially_radio_button->isChecked()){
        flag_parallel = false;
    }
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
        int num = 1 + rand() % 100;
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

    int bubble_arr[length_arr];
    int shaker_arr[length_arr];
    int selection_arr[length_arr];

    if (flag_parallel){
        std::thread th1([&]() { CopyArr(arr, bubble_arr, length_arr); });
        std::thread th2([&]() { CopyArr(arr, shaker_arr, length_arr); });
        std::thread th3([&]() { CopyArr(arr, selection_arr, length_arr); });

        th1.join();
        th2.join();
        th3.join();
    }

    else{
        CopyArr(arr, bubble_arr, length_arr);
        CopyArr(arr, shaker_arr, length_arr);
        CopyArr(arr, selection_arr, length_arr);
    }

    // Создание объекта BubbleSort
    BubbleSort sorter_bubble;

    // Создание объекта ShakerSort
    ShakerSort sorter_shaker;

    // Создание объекта SelectionSort
    SelectionSort sorter_selection;


    double seconds_bubble_sort;
    int comparisons_bubble;
    int swaps_bubble;

    double seconds_shaker_sort;
    int comparisons_shaker;
    int swaps_shaker;

    double seconds_selection_sort;
    int comparisons_selection ;
    int swaps_selection;


    if (flag_parallel){

        if (flag_out_arr == "да"){
            // Вывод массива до сортировки
            out_arr_before(bubble_arr, length_arr, "пузырьком");
        }
        // Начало измерения времини
        //clock_t start_bubble_sort = clock();
        auto start_bubble_sort = high_resolution_clock::now();

        std::thread th4([&](){ sorter_bubble.sort(bubble_arr, length_arr); });

        // Окончание измерения времени
        //clock_t end_bubble_sort = clock();
        auto end_bubble_sort = high_resolution_clock::now();

        duration<double> intervar_bubble_sort = end_bubble_sort - start_bubble_sort;
        seconds_bubble_sort = intervar_bubble_sort.count();

        qDebug() << "Затрачено секунд на сортироку пузырьком\n" << seconds_bubble_sort << "\n";

        comparisons_bubble = sorter_bubble.getComparisons();
        swaps_bubble = sorter_bubble.getSwaps();
        qDebug() << "Сравнений (пузырьковая сортировка):" << comparisons_bubble;
        qDebug() << "Перестановок (пузырьковая сортировка):" << swaps_bubble << "\n";

        if (flag_out_arr == "да"){
            // Вывод отсортированного массива
            out_arr_after(bubble_arr, length_arr, "пузырьком");
        }
        qDebug() << "\n\n\n";




        if (flag_out_arr == "да"){
            // Вывод массива до сортировки
            out_arr_before(shaker_arr, length_arr, "шейкером");
        }

        // Начало измерения времини
        //clock_t start_shaker_sort = clock();
        auto start_shaker_sort = high_resolution_clock::now();

        std::thread th5([&]() { sorter_shaker.sort(shaker_arr, length_arr); });

        // Окончание измерения времени
        //clock_t end_shaker_sort = clock();
        auto end_shaker_sort = high_resolution_clock::now();
        duration<double> intervar_shaker_sort = end_shaker_sort - start_shaker_sort;
        seconds_shaker_sort = intervar_shaker_sort.count();

        qDebug() << "Затрачено секунд на сортироку шейкером\n" << seconds_shaker_sort << "\n";

        comparisons_shaker = sorter_shaker.getComparisons();
        swaps_shaker = sorter_shaker.getSwaps();
        qDebug() << "Сравнений (сортировка шейкером):" << comparisons_shaker;
        qDebug() << "Перестановок (сортировка шейкером):" << swaps_shaker << "\n";

        if (flag_out_arr == "да"){
            // Вывод отсортированного массива
            out_arr_after(shaker_arr, length_arr, "шейкером");
        }
        qDebug() << "\n\n\n";




        if (flag_out_arr == "да"){
            // Вывод массива до сортировки
            out_arr_before(selection_arr, length_arr, "выбором");
        }

        // Начало измерения времини
        //clock_t start_selection_sort = clock();
        auto start_selection_sort = high_resolution_clock::now();

        std::thread th6([&]() { sorter_selection.sort(selection_arr, length_arr); });

        // Окончание измерения времени
        //clock_t end_selection_sort = clock();

        auto end_selection_sort = high_resolution_clock::now();

        duration<double> intervar_selection_sort  = end_selection_sort - start_selection_sort;
        seconds_selection_sort = intervar_selection_sort.count();

        qDebug() << "Затрачено секунд на сортироку выбором\n" << seconds_selection_sort << "\n";

        comparisons_selection = sorter_selection.getComparisons();
        swaps_selection = sorter_selection.getSwaps();
        qDebug() << "Сравнений (сортировка выбором):" << comparisons_selection;
        qDebug() << "Перестановок (сортировка выбором):" << swaps_selection << "\n";

        if (flag_out_arr == "да"){
            // Вывод отсортированного массива
            if (flag_out_arr == "да"){
                out_arr_after(selection_arr, length_arr, "выбором");
            }
        }

        th4.join();
        th5.join();
        th6.join();

        qDebug() << "\n\n";

    }

    else{
        if (flag_out_arr == "да"){
            // Вывод массива до сортировки
            out_arr_before(bubble_arr, length_arr, "пузырьком");
        }
        // Начало измерения времини
        //clock_t start_bubble_sort = clock();
        auto start_bubble_sort = high_resolution_clock::now();

        sorter_bubble.sort(bubble_arr, length_arr);

        // Окончание измерения времени
        //clock_t end_bubble_sort = clock();
        auto end_bubble_sort = high_resolution_clock::now();

        duration<double> intervar_bubble_sort = end_bubble_sort - start_bubble_sort;
        seconds_bubble_sort = intervar_bubble_sort.count();

        qDebug() << "Затрачено секунд на сортироку пузырьком\n" << seconds_bubble_sort << "\n";

        comparisons_bubble = sorter_bubble.getComparisons();
        swaps_bubble = sorter_bubble.getSwaps();
        qDebug() << "Сравнений (пузырьковая сортировка):" << comparisons_bubble;
        qDebug() << "Перестановок (пузырьковая сортировка):" << swaps_bubble << "\n";

        if (flag_out_arr == "да"){
            // Вывод отсортированного массива
            out_arr_after(bubble_arr, length_arr, "пузырьком");
        }
        qDebug() << "\n\n\n";




        if (flag_out_arr == "да"){
            // Вывод массива до сортировки
            out_arr_before(shaker_arr, length_arr, "шейкером");
        }

        // Начало измерения времини
        //clock_t start_shaker_sort = clock();
        auto start_shaker_sort = high_resolution_clock::now();

        sorter_shaker.sort(shaker_arr, length_arr);

        // Окончание измерения времени
        //clock_t end_shaker_sort = clock();
        auto end_shaker_sort = high_resolution_clock::now();
        duration<double> intervar_shaker_sort = end_shaker_sort - start_shaker_sort;
        seconds_shaker_sort = intervar_shaker_sort.count();

        qDebug() << "Затрачено секунд на сортироку шейкером\n" << seconds_shaker_sort << "\n";

        comparisons_shaker = sorter_shaker.getComparisons();
        swaps_shaker = sorter_shaker.getSwaps();
        qDebug() << "Сравнений (сортировка шейкером):" << comparisons_shaker;
        qDebug() << "Перестановок (сортировка шейкером):" << swaps_shaker << "\n";

        if (flag_out_arr == "да"){
            // Вывод отсортированного массива
            out_arr_after(shaker_arr, length_arr, "шейкером");
        }
        qDebug() << "\n\n\n";


        if (flag_out_arr == "да"){
            // Вывод массива до сортировки
            out_arr_before(selection_arr, length_arr, "выбором");
        }

        // Начало измерения времини
        //clock_t start_selection_sort = clock();
        auto start_selection_sort = high_resolution_clock::now();

        sorter_selection.sort(selection_arr, length_arr);

        // Окончание измерения времени
        //clock_t end_selection_sort = clock();

        auto end_selection_sort = high_resolution_clock::now();

        duration<double> intervar_selection_sort  = end_selection_sort - start_selection_sort;
        seconds_selection_sort = intervar_selection_sort.count();

        qDebug() << "Затрачено секунд на сортироку выбором\n" << seconds_selection_sort << "\n";

        comparisons_selection = sorter_selection.getComparisons();
        swaps_selection = sorter_selection.getSwaps();
        qDebug() << "Сравнений (сортировка выбором):" << comparisons_selection;
        qDebug() << "Перестановок (сортировка выбором):" << swaps_selection << "\n";

        if (flag_out_arr == "да"){
            // Вывод отсортированного массива
            if (flag_out_arr == "да"){
                out_arr_after(selection_arr, length_arr, "выбором");
            }
        }
        qDebug() << "\n\n";

    }

    // Здесть переменные для отображения почему-то уже равны нулю

    qDebug() << "Bubble sort time:" << seconds_bubble_sort;
    qDebug() << "Bubble sort comparisons:" << comparisons_bubble;
    qDebug() << "Bubble sort swaps:" << swaps_bubble;


    double sortData[9] = {seconds_bubble_sort, comparisons_bubble, swaps_bubble,
                          seconds_shaker_sort, comparisons_shaker, swaps_shaker,
                          seconds_selection_sort, comparisons_selection, swaps_selection};

    window->setSortData(sortData);
    window->setLength(length_arr);
    window->show();

}


