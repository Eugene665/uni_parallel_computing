#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sorting_results_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_start_all_sort_button_clicked();

    void on_input_len_arr_cursorPositionChanged(int arg1, int arg2);

    void on_sequentially_radiobutton_clicked();

private:
    Ui::MainWindow *ui;
    sorting_results_window *window;
};
#endif // MAINWINDOW_H
