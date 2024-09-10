/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QLineEdit *input_len_arr;
    QRadioButton *sequentially_radio_button;
    QRadioButton *parallel_radio_button;
    QCheckBox *checkBox;
    QPushButton *start_all_sort_button;
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(788, 307);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 110, 431, 136));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        label_5->setFont(font);

        horizontalLayout_2->addWidget(label_5);

        input_len_arr = new QLineEdit(layoutWidget);
        input_len_arr->setObjectName(QString::fromUtf8("input_len_arr"));

        horizontalLayout_2->addWidget(input_len_arr);


        verticalLayout_2->addLayout(horizontalLayout_2);

        sequentially_radio_button = new QRadioButton(layoutWidget);
        sequentially_radio_button->setObjectName(QString::fromUtf8("sequentially_radio_button"));
        sequentially_radio_button->setFont(font);

        verticalLayout_2->addWidget(sequentially_radio_button);

        parallel_radio_button = new QRadioButton(layoutWidget);
        parallel_radio_button->setObjectName(QString::fromUtf8("parallel_radio_button"));
        parallel_radio_button->setFont(font);

        verticalLayout_2->addWidget(parallel_radio_button);

        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFont(font);

        verticalLayout_2->addWidget(checkBox);

        start_all_sort_button = new QPushButton(centralwidget);
        start_all_sort_button->setObjectName(QString::fromUtf8("start_all_sort_button"));
        start_all_sort_button->setGeometry(QRect(490, 150, 261, 81));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Cantarell"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setItalic(true);
        start_all_sort_button->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(310, 30, 111, 31));
        label_2->setFont(font);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 241, 51));
        label->setFont(font);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(460, 30, 111, 31));
        label_3->setFont(font);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(630, 20, 131, 51));
        label_4->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 788, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\273\320\270\320\275\321\203 \320\274\320\260\321\201\321\201\320\270\320\262\320\260", nullptr));
        sequentially_radio_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\201\320\273\320\265\320\264\320\276\320\262\320\260\321\202\320\265\320\273\321\214\320\275\320\276", nullptr));
        parallel_radio_button->setText(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\273\320\273\320\265\320\273\321\214\320\275\320\276", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270 \320\262 \321\202\320\265\321\200\320\274\320\270\320\275\320\260\320\273 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\276\320\272", nullptr));
        start_all_sort_button->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\321\203", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "BubbleSort", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\320\274\321\213\320\265 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\320\270", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "ShakerSort", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<p>SelectionSort</p>\n"
"", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
