/********************************************************************************
** Form generated from reading UI file 'sorting_results_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SORTING_RESULTS_WINDOW_H
#define UI_SORTING_RESULTS_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_sorting_results_window
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lengthLabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLineEdit *time_bubble;
    QLineEdit *comparisons_bubble;
    QLineEdit *swap_bubble;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *time_shaker;
    QLineEdit *comparisons_shaker;
    QLineEdit *swap_shaker;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *time_selection;
    QLineEdit *comparisons_selection;
    QLineEdit *swap_selection;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *sorting_results_window)
    {
        if (sorting_results_window->objectName().isEmpty())
            sorting_results_window->setObjectName(QString::fromUtf8("sorting_results_window"));
        sorting_results_window->resize(781, 359);
        buttonBox = new QDialogButtonBox(sorting_results_window);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(370, 290, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(sorting_results_window);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 30, 121, 21));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label_2 = new QLabel(sorting_results_window);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(430, 30, 111, 21));
        label_2->setFont(font);
        label_3 = new QLabel(sorting_results_window);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(570, 20, 131, 31));
        label_3->setFont(font);
        lengthLabel = new QLineEdit(sorting_results_window);
        lengthLabel->setObjectName(QString::fromUtf8("lengthLabel"));
        lengthLabel->setGeometry(QRect(50, 20, 91, 31));
        widget = new QWidget(sorting_results_window);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(250, 50, 471, 211));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        time_bubble = new QLineEdit(widget);
        time_bubble->setObjectName(QString::fromUtf8("time_bubble"));

        verticalLayout->addWidget(time_bubble);

        comparisons_bubble = new QLineEdit(widget);
        comparisons_bubble->setObjectName(QString::fromUtf8("comparisons_bubble"));

        verticalLayout->addWidget(comparisons_bubble);

        swap_bubble = new QLineEdit(widget);
        swap_bubble->setObjectName(QString::fromUtf8("swap_bubble"));

        verticalLayout->addWidget(swap_bubble);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        time_shaker = new QLineEdit(widget);
        time_shaker->setObjectName(QString::fromUtf8("time_shaker"));

        verticalLayout_2->addWidget(time_shaker);

        comparisons_shaker = new QLineEdit(widget);
        comparisons_shaker->setObjectName(QString::fromUtf8("comparisons_shaker"));

        verticalLayout_2->addWidget(comparisons_shaker);

        swap_shaker = new QLineEdit(widget);
        swap_shaker->setObjectName(QString::fromUtf8("swap_shaker"));

        verticalLayout_2->addWidget(swap_shaker);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        time_selection = new QLineEdit(widget);
        time_selection->setObjectName(QString::fromUtf8("time_selection"));

        verticalLayout_3->addWidget(time_selection);

        comparisons_selection = new QLineEdit(widget);
        comparisons_selection->setObjectName(QString::fromUtf8("comparisons_selection"));

        verticalLayout_3->addWidget(comparisons_selection);

        swap_selection = new QLineEdit(widget);
        swap_selection->setObjectName(QString::fromUtf8("swap_selection"));

        verticalLayout_3->addWidget(swap_selection);


        horizontalLayout->addLayout(verticalLayout_3);

        widget1 = new QWidget(sorting_results_window);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(50, 70, 191, 171));
        verticalLayout_4 = new QVBoxLayout(widget1);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(widget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setPointSize(13);
        label_4->setFont(font1);

        verticalLayout_4->addWidget(label_4);

        label_5 = new QLabel(widget1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        verticalLayout_4->addWidget(label_5);

        label_6 = new QLabel(widget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        verticalLayout_4->addWidget(label_6);


        retranslateUi(sorting_results_window);
        QObject::connect(buttonBox, SIGNAL(accepted()), sorting_results_window, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), sorting_results_window, SLOT(reject()));

        QMetaObject::connectSlotsByName(sorting_results_window);
    } // setupUi

    void retranslateUi(QDialog *sorting_results_window)
    {
        sorting_results_window->setWindowTitle(QCoreApplication::translate("sorting_results_window", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("sorting_results_window", "BubbleSort", nullptr));
        label_2->setText(QCoreApplication::translate("sorting_results_window", "ShakerSort", nullptr));
        label_3->setText(QCoreApplication::translate("sorting_results_window", "SelectionSort", nullptr));
        label_4->setText(QCoreApplication::translate("sorting_results_window", "\320\222\321\200\320\265\320\274\321\217", nullptr));
        label_5->setText(QCoreApplication::translate("sorting_results_window", "\320\232\320\276\320\273-\320\262\320\276 \321\201\321\200\320\260\320\262\320\275\320\265\320\275\320\270\320\271", nullptr));
        label_6->setText(QCoreApplication::translate("sorting_results_window", "\320\232\320\276\320\273-\320\262\320\276 \320\277\320\265\321\200\320\265\321\201\321\202\320\260\320\275\320\276\320\262\320\276\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sorting_results_window: public Ui_sorting_results_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SORTING_RESULTS_WINDOW_H
