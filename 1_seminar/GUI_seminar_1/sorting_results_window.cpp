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

