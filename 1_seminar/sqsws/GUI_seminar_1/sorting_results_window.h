#ifndef SORTING_RESULTS_WINDOW_H
#define SORTING_RESULTS_WINDOW_H

#include <QDialog>

namespace Ui {
class sorting_results_window;
}

class sorting_results_window : public QDialog
{
    Q_OBJECT

public:
    explicit sorting_results_window(QWidget *parent = nullptr);
    ~sorting_results_window();

    void setLength(int length);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::sorting_results_window *ui;
};

#endif // SORTING_RESULTS_WINDOW_H
