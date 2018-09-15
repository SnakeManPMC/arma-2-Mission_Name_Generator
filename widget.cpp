#include "widget.h"
#include "ui_widget.h"
#include <QtWidgets>

Widget::Widget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Widget)
{
	ui->setupUi(this);

	setWindowTitle("Mission Name Generator " + pmcVersion + " by PMC");

	QTime timmy(0, 0, 0);
	qsrand(timmy.secsTo(QTime::currentTime()));
	
	Load_Names();
	Load_Dupes();
}

Widget::~Widget()
{
	delete ui;
}

void Widget::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type())
	{
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
		file2.errorString());
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
		file3.errorString());
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
		file4.errorString());
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

Load duplicate names

*/
void Widget::Load_Dupes()
{
	QFile file("Mission_Name_Generator.txt");

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, "unable to open file", "unable to open Mission_Name_Generator.txt!");
		return;
	}

	QTextStream in(&file);
	QString line;

	while (!in.atEnd())
	{
		line = in.readLine();
		if (line.size() > 0) dupe_names.push_back(line);
	}
	file.close();

	ui->textEdit_Status->append(QString::number(dupe_names.count()) + " mission names loaded.");
}


void Widget::Save_Dupes()
{
	QFile file("Mission_Name_Generator.txt");

	if (!file.open(QIODevice::WriteOnly))
	{
		QMessageBox::information(this, tr("Unable to open file"),
		file.errorString());
		return;
	}
	
	QTextStream out(&file);
	QString line;

	for (int i = 0; i < dupe_names.size(); i++)
	{
		out << dupe_names.at(i) << "\n";
	}
	file.close();

	ui->textEdit_Status->append("Dupe database saved to Mission_Name_Generator.txt, total of " + QString::number(dupe_names.count()) + " mission names.");
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

	// if we got duplicate name, lets randomize it until we get name that is not dupe
	while (dupe_names.contains(missionName))
	{
		int idx = qrand() % missions_prefix.size();
		missionName = (missions_prefix[idx]);
		missionName.append(" ");
		
		idx = qrand() % missions_suffix.size();
		missionName.append(missions_suffix[idx]);
		
		if (ui->checkBoxPMCPrefix->isChecked()) missionName.insert(0, "PMC ");
	}
	
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
	ui->textEdit_Status->append("Mission name " + missionName + " copied to clipboard.");
}


// clipboard campaign name
void Widget::on_ClipboardCampaignName_clicked()
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(campaignName);
	ui->textEdit_Status->append("Campaign name " + campaignName + " copied to clipboard.");
}


// file name in lowercase and replace spaces with underscores
void Widget::on_ClipboardFileName_clicked()
{
	QString missionFileName;
	missionFileName = missionName;
	missionFileName.replace(" ", "_");
	
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(missionFileName.toLower());

	ui->textEdit_Status->append("Mission file name " + missionFileName.toLower() + " copied to clipboard.");
}


// add mission name to dupe database
void Widget::on_missionDupe_clicked()
{
	dupe_names.push_back(missionName);
	ui->textEdit_Status->append("Mission name: " + missionName + " added to dupe database.");
}


// add campaign name to dupe database
void Widget::on_campaignDupe_clicked()
{
	dupe_names.push_back(campaignName);
	ui->textEdit_Status->append("Campaign name: " + campaignName + " added to dupe database.");
}


// save dupe database to file
void Widget::on_saveDupe_clicked()
{
	Save_Dupes();
}
