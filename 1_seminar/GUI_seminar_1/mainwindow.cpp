#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "ui_mainwindow.h"
#include <QDebug>

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

void MainWindow::on_start_all_sort_button_clicked()
{
    window = new sorting_results_window(this);
    window->show();

    bool parallel_sort;
    if (ui->parallel_radio_button->isChecked()){
        parallel_sort = true;
    }
    if (ui->sequentially_radio_button->isChecked()){
        parallel_sort = false;
    }

    QString leng_arr_str = ui->input_len_arr->text();
    int leng_arr = leng_arr_str.toInt(); // Преобразование QString в int

    qDebug() << "длина массива:" << leng_arr;



}

void MainWindow::on_input_len_arr_cursorPositionChanged(int arg1, int arg2)
{


}


void MainWindow::on_sequentially_radiobutton_clicked()
{

}

