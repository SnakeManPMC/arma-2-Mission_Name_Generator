#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Widget *ui;
    void Load_Names();
    QVector<QString> missions_prefix;
    QVector<QString> missions_suffix;
    QVector<QString> campaigns_prefix;
    QVector<QString> campaigns_suffix;
    QString missionName,campaignName;

private slots:
    void on_All_clicked();
    void on_Campaign_clicked();
    void on_MissionName_clicked();
    void on_ClipboardMissionName_clicked();
    void on_ClipboardCampaignName_clicked();
    void on_ClipboardFileName_clicked();
};

#endif // WIDGET_H
