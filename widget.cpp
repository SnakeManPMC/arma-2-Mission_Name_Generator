#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    // initialize random seed:
    QTime timmy(0, 0, 0);
    qsrand(timmy.secsTo(QTime::currentTime()));

    // at start we need to load the names
    Load_Names();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


/*

Load mission names from text file.

*/
void Widget::Load_Names()
{
	QString line;

	// mission name prefix
	QFile file(":text/mission_names_prefix.txt");

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, tr("Unable to open file"),
		file.errorString());
		return;
	}

	QTextStream in(&file);

	while (!in.atEnd())
	{
		line = in.readLine();
		if (line.size() > 0) missions_prefix.push_back(line);
	}
	file.close();

	// mission name suffix
	QFile file2(":text/mission_names_suffix.txt");

	if (!file2.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, tr("Unable to open file"),
		file.errorString());
		return;
	}

	QTextStream in2(&file2);

	while (!in2.atEnd())
	{
		line = in2.readLine();
		if (line.size() > 0) missions_suffix.push_back(line);
	}
	file2.close();

	// campaign name prefix
	QFile file3(":text/campaign_names_prefix.txt");

	if (!file3.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, tr("Unable to open file"),
		file.errorString());
		return;
	}

	QTextStream in3(&file3);

	while (!in3.atEnd())
	{
		line = in3.readLine();
		if (line.size() > 0) campaigns_prefix.push_back(line);
	}
	file3.close();

	// campaign name suffix
	QFile file4(":text/campaign_names_suffix.txt");

	if (!file4.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, tr("Unable to open file"),
		file.errorString());
		return;
	}

	QTextStream in4(&file4);

	while (!in4.atEnd())
	{
		line = in4.readLine();
		if (line.size() > 0) campaigns_suffix.push_back(line);
	}
	file4.close();
}


/*

Create mission names

*/
void Widget::on_MissionName_clicked()
{
	QString str;

	// clear the text box
	ui->plainMissionName->clear();

	// randomly select one name and write it.
	int idx = qrand() % missions_prefix.size();
	str.append(missions_prefix[idx]);
	str.append(" ");

	idx = qrand() % missions_suffix.size();
	str.append(missions_suffix[idx]);

	ui->plainMissionName->appendPlainText(str);
}


/*

Create campaign names

*/
void Widget::on_Campaign_clicked()
{
	QString str;

	// clear the text box
	ui->plainCampaignName->clear();

	// randomly select one name and write it.
	int idx = qrand() % campaigns_prefix.size();
	str.append(campaigns_prefix[idx]);
	str.append(" ");

	idx = qrand() % campaigns_suffix.size();
	str.append(campaigns_suffix[idx]);

	ui->plainCampaignName->appendPlainText(str);
}


/*

Create mission and campaign names

*/
void Widget::on_All_clicked()
{
	on_MissionName_clicked();
	on_Campaign_clicked();
}
