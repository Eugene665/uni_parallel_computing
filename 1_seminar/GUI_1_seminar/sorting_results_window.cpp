#include "sorting_results_window.h"
#include "ui_sorting_results_window.h"

sorting_results_window::sorting_results_window(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::sorting_results_window)
{
    ui->setupUi(this);
}

sorting_results_window::~sorting_results_window()
{
    delete ui;
}

void sorting_results_window::on_buttonBox_accepted()
{

}

void sorting_results_window::setLength(int length)
{
    ui->lengthLabel->setText(QString::number(length));
}

void sorting_results_window::setSortData(double* sortdata) {
    ui->time_bubble->setText(QString::number(sortdata[0], 'f', 6));
    ui->comparisons_bubble->setText(QString::number(static_cast<int>(sortdata[1])));
    ui->swap_bubble->setText(QString::number(static_cast<int>(sortdata[2])));

    ui->time_shaker->setText(QString::number(sortdata[3], 'f', 6));
    ui->comparisons_shaker->setText(QString::number(static_cast<int>(sortdata[4])));
    ui->swap_shaker->setText(QString::number(static_cast<int>(sortdata[5])));

    ui->time_selection->setText(QString::number(sortdata[6], 'f', 6));
    ui->comparisons_selection->setText(QString::number(static_cast<int>(sortdata[7])));
    ui->swap_selection->setText(QString::number(static_cast<int>(sortdata[8])));
}


