/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Thu Apr 22 20:05:55 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPlainTextEdit *plainMissionName;
    QPushButton *MissionName;
    QPushButton *Campaign;
    QPushButton *All;
    QPlainTextEdit *plainCampaignName;
    QLabel *Label_MissionName;
    QLabel *Label_CampaignName;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(600, 217);
        plainMissionName = new QPlainTextEdit(Widget);
        plainMissionName->setObjectName(QString::fromUtf8("plainMissionName"));
        plainMissionName->setGeometry(QRect(10, 70, 571, 41));
        MissionName = new QPushButton(Widget);
        MissionName->setObjectName(QString::fromUtf8("MissionName"));
        MissionName->setGeometry(QRect(10, 10, 75, 23));
        Campaign = new QPushButton(Widget);
        Campaign->setObjectName(QString::fromUtf8("Campaign"));
        Campaign->setGeometry(QRect(110, 10, 75, 23));
        All = new QPushButton(Widget);
        All->setObjectName(QString::fromUtf8("All"));
        All->setGeometry(QRect(210, 10, 75, 23));
        plainCampaignName = new QPlainTextEdit(Widget);
        plainCampaignName->setObjectName(QString::fromUtf8("plainCampaignName"));
        plainCampaignName->setGeometry(QRect(10, 150, 571, 41));
        Label_MissionName = new QLabel(Widget);
        Label_MissionName->setObjectName(QString::fromUtf8("Label_MissionName"));
        Label_MissionName->setGeometry(QRect(20, 50, 71, 16));
        Label_CampaignName = new QLabel(Widget);
        Label_CampaignName->setObjectName(QString::fromUtf8("Label_CampaignName"));
        Label_CampaignName->setGeometry(QRect(20, 130, 71, 16));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        MissionName->setText(QApplication::translate("Widget", "Mission", 0));
        Campaign->setText(QApplication::translate("Widget", "Campaign", 0));
        All->setText(QApplication::translate("Widget", "All", 0));
        Label_MissionName->setText(QApplication::translate("Widget", "Mission name", 0));
        Label_CampaignName->setText(QApplication::translate("Widget", "Campaign name", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
