#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "ui_mainwindow.h"
//#include "sorting_results_window.h"
#include <QDebug>
#include <time.h>
#include <iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Функция для обмена значений без затирки
void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void out_arr_before(int* arr, int length_arr, string name_sort){
    // Вывод массива до сортировки
    cout << "Массив до сортировки " << name_sort << "\n";
    for (int i = 0; i < length_arr; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void out_arr_after(int* arr, int length_arr, string name_sort){
    // Вывод массива после сортировки
    cout << "Массив после сортировки " << name_sort << "\n";
    for (int i = 0; i < length_arr; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

class Sort {
public:
        //Виртуальный метод, который в последствии будет переопределён
    virtual void sort(int* arr, int length_arr) = 0;
};

class BubbleSort : public Sort {
public:
    // Переопределение функции
    void sort(int* arr, int length_arr) override {
        // Проходим по всему списку
        for (int i = 0; i < length_arr - 1; i++){
            // Проходим по списку до отсортированной части,
            // до чисел, которые уже "всплыли"
            for (int j = 0; j < length_arr - i - 1; j++) {
                // Если впереди стоящее число меньше,
                // числа меняюся местами
                if (arr[j] > arr[j + 1]) {
                    Swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
};


class ShakerSort : public Sort{
public:
    void sort(int* arr, int length_arr) override {
        // Вводим переменные позиций на левый и правый
        // участок неотсортированного массив
        int left_pose = 0;
        int right_pose = length_arr - 1;
        while (left_pose <= right_pose) {
            for (int i = right_pose; i > left_pose; i--) {
                if (arr[i - 1] > arr[i]) {
                    Swap(arr[i - 1], arr[i]);
                }
            }
            left_pose++;
            for (int i = left_pose; i < right_pose; i++) {
                if (arr[i] > arr[i + 1]){
                    Swap(arr[i], arr[i + 1]);
                }
            }
            right_pose--;
        }
    }
};

class SelectionSort : public Sort{
public:
    void sort(int* arr, int length_arr) override {
        for (int i = 0; i < length_arr - 1; i++) {
            int smallest_pose = i;
            for (int j = i + 1; j < length_arr; j++) {
                if (arr[j] < arr[smallest_pose]) {
                    smallest_pose = j;
                }
            }
            if (smallest_pose != i) {
                Swap(arr[i], arr[smallest_pose]);
            }
        }
    }
};



void MainWindow::on_start_all_sort_button_clicked()
{
    window = new sorting_results_window(this);

    window->show();


}

void MainWindow::on_input_len_arr_cursorPositionChanged(int arg1, int arg2)
{


}


void MainWindow::on_sequentially_radiobutton_clicked()
{

}

