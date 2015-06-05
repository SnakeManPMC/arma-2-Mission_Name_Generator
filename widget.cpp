#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("Mission Name Generator v1.0 by PMC");

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
	// clear the text box
	ui->plainMissionName->clear();

	// randomly select one name and write it.
	int idx = qrand() % missions_prefix.size();
	missionName = (missions_prefix[idx]);
	missionName.append(" ");

	idx = qrand() % missions_suffix.size();
	missionName.append(missions_suffix[idx]);

	if (ui->checkBoxPMCPrefix->isChecked()) missionName.insert(0, "PMC ");

	ui->plainMissionName->appendPlainText(missionName);
}


/*

Create campaign names

*/
void Widget::on_Campaign_clicked()
{
	// clear the text box
	ui->plainCampaignName->clear();

	// randomly select one name and write it.
	int idx = qrand() % campaigns_prefix.size();
	campaignName = (campaigns_prefix[idx]);
	campaignName.append(" ");

	idx = qrand() % campaigns_suffix.size();
	campaignName.append(campaigns_suffix[idx]);

	if (ui->checkBoxPMCPrefix->isChecked()) campaignName.insert(0, "PMC ");

	ui->plainCampaignName->appendPlainText(campaignName);
}


/*

Create mission and campaign names

*/
void Widget::on_All_clicked()
{
	on_MissionName_clicked();
	on_Campaign_clicked();
}


// clipboard mission name
void Widget::on_ClipboardMissionName_clicked()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(missionName);
}


// clipboard campaign name
void Widget::on_ClipboardCampaignName_clicked()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(campaignName);
}


// file name in lowercase and replace spaces with underscores
void Widget::on_ClipboardFileName_clicked()
{
	QString missionFileName;
	missionFileName = missionName;
	missionFileName.replace(" ", "_");

	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(missionFileName.toLower());
}
