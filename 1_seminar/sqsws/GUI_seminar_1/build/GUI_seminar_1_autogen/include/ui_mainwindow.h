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

class Ui_MainWindo
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *start_all_sort_button;
    QLineEdit *main_len;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_5;
    QLineEdit *input_len_arr;
    QRadioButton *sequentially_radio_button;
    QRadioButton *parallel_radio_button;
    QCheckBox *checkBox;
    QStatusBar *statusbar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindo)
    {
        if (MainWindo->objectName().isEmpty())
            MainWindo->setObjectName(QString::fromUtf8("MainWindo"));
        MainWindo->resize(822, 342);
        QFont font;
        font.setPointSize(15);
        font.setBold(false);
        MainWindo->setFont(font);
        centralwidget = new QWidget(MainWindo);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setItalic(false);
        centralwidget->setFont(font1);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 241, 51));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setItalic(false);
        label->setFont(font2);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(300, 40, 111, 31));
        label_2->setFont(font2);
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(450, 40, 111, 31));
        label_3->setFont(font2);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(620, 30, 131, 51));
        label_4->setFont(font2);
        start_all_sort_button = new QPushButton(centralwidget);
        start_all_sort_button->setObjectName(QString::fromUtf8("start_all_sort_button"));
        start_all_sort_button->setGeometry(QRect(530, 150, 231, 81));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Cantarell"));
        font3.setPointSize(18);
        font3.setBold(true);
        font3.setItalic(true);
        start_all_sort_button->setFont(font3);
        main_len = new QLineEdit(centralwidget);
        main_len->setObjectName(QString::fromUtf8("main_len"));
        main_len->setGeometry(QRect(580, 100, 113, 26));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 120, 431, 136));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font2);

        horizontalLayout->addWidget(label_5);

        input_len_arr = new QLineEdit(layoutWidget);
        input_len_arr->setObjectName(QString::fromUtf8("input_len_arr"));

        horizontalLayout->addWidget(input_len_arr);


        verticalLayout->addLayout(horizontalLayout);

        sequentially_radio_button = new QRadioButton(layoutWidget);
        sequentially_radio_button->setObjectName(QString::fromUtf8("sequentially_radio_button"));
        sequentially_radio_button->setFont(font2);

        verticalLayout->addWidget(sequentially_radio_button);

        parallel_radio_button = new QRadioButton(layoutWidget);
        parallel_radio_button->setObjectName(QString::fromUtf8("parallel_radio_button"));
        parallel_radio_button->setFont(font2);

        verticalLayout->addWidget(parallel_radio_button);

        checkBox = new QCheckBox(layoutWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setFont(font2);

        verticalLayout->addWidget(checkBox);

        MainWindo->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindo);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindo->setStatusBar(statusbar);
        menuBar = new QMenuBar(MainWindo);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 822, 29));
        MainWindo->setMenuBar(menuBar);

        retranslateUi(MainWindo);

        QMetaObject::connectSlotsByName(MainWindo);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindo)
    {
        MainWindo->setWindowTitle(QCoreApplication::translate("MainWindo", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindo", "\320\230\321\201\320\277\320\276\320\273\321\214\320\267\321\203\320\265\320\274\321\213\320\265 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\320\270", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindo", "BubbleSort", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindo", "ShakerSort", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindo", "SelectionSort", nullptr));
        start_all_sort_button->setText(QCoreApplication::translate("MainWindo", "\320\235\320\260\321\207\320\260\321\202\321\214 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\272\321\203", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindo", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\273\320\270\320\275\321\203 \320\274\320\260\321\201\321\201\320\270\320\262\320\260", nullptr));
        sequentially_radio_button->setText(QCoreApplication::translate("MainWindo", "\320\237\320\276\321\201\320\273\320\265\320\264\320\276\320\262\320\260\321\202\320\265\320\273\321\214\320\275\320\276", nullptr));
        parallel_radio_button->setText(QCoreApplication::translate("MainWindo", "\320\237\320\260\321\200\320\260\320\273\320\273\320\265\320\273\321\214\320\275\320\276", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindo", "\320\222\321\213\320\262\320\265\321\201\321\202\320\270 \320\262 \321\202\320\265\321\200\320\274\320\270\320\275\320\260\320\273 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213 \321\201\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\276\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindo: public Ui_MainWindo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
