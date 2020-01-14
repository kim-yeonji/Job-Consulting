#include "recommendation.h"
#include "ui_recommendation.h"
#include "menu.h"


using namespace std;

Recommendation::Recommendation(SpecDatabase& inSpecDB, QWidget *parent) :
	mSpecDB(inSpecDB),
    QDialog(parent),
    ui(new Ui::Recommendation)
{
    ui->setupUi(this);

	int counter = 0;
	string *category_list = new string[20];

	mSpecDB.queryCountCategory(counter, category_list);
	//업종 리스트 받아서 jobs에 저장
	//-----------------------------------------

	QString *jobs = new QString[counter];//size 수정해야함

	for (int i = 0; i < counter; i++)
	{
		jobs[i] = QString::fromLocal8Bit(category_list[i].c_str());
		// string을 qstring으로 바로 넘겨주면 한글이 꺠짐. c_str으로 바꾼후 local8bit로 받아오는 식으로 넘겨야 안깨짐.

	}

	//업종들을 combobox에 add하는 코드
	for (int i = 0; i < counter; i++)//size 수정해야함
	{
		ui->comboBox_jobselection->addItem(jobs[i]);
	}
	//---------------------------------

}

//user_id 계속 넘겨주면서 띄워주기
void Recommendation::get_user_id(QString inputid)
{
    userid = inputid;
    ui->label_inputID->setText(userid);
}

Recommendation::~Recommendation()
{
    delete ui;
}

void Recommendation::on_pushButton_confirm_clicked()
{
	QString job = ui->comboBox_jobselection->currentText();
	QString idFromDB;
	QString univFromDB;
	QString majorFromDB;
	qfloat16 gpaFromDB;
	qfloat16 toeicFromDB;
	qfloat16 opicFromDB;
	qfloat16 tosFromDB;
	qfloat16 certificateFromDB;
	qfloat16 studyFromDB;
	qfloat16 internFromDB;
	qfloat16 univ_scoreFromDB;
	qfloat16 user_score;

	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("your_hostname");
	db.setUserName("your_username");
	db.setPassword("your_password");
	db.setDatabaseName("your_databasename");

	//my spec 출력하기
	if (db.open()) {
		QSqlQuery query;
		query.prepare(QString("SELECT * FROM user_spec WHERE account_id = :account_id "));
		query.bindValue(":account_id", userid);
		if (!query.exec()) {
			QMessageBox::information(this, "Failed", "Query Failed To Execute");
		}
		else {
			while (query.next()) {
				idFromDB = query.value(0).toString();
				univFromDB = query.value(1).toString();
				majorFromDB = query.value(2).toString();
				gpaFromDB = query.value(3).toFloat();
				toeicFromDB = query.value(4).toFloat();
				opicFromDB = query.value(5).toFloat();
				tosFromDB = query.value(6).toFloat();
				certificateFromDB = query.value(7).toFloat();
				studyFromDB = query.value(8).toFloat();
				internFromDB = query.value(9).toFloat();

				if (idFromDB == userid) {
					
					ui->label_myspec1->setText(QString::number(gpaFromDB));
					ui->label_myspec2->setText(QString::number(toeicFromDB));
					ui->label_myspec3->setText(QString::number(opicFromDB));
					ui->label_myspec4->setText(QString::number(tosFromDB));
					ui->label_myspec5->setText(QString::number(certificateFromDB));
					ui->label_myspec6->setText(QString::number(studyFromDB));
					ui->label_myspec7->setText(QString::number(internFromDB));

				}
				else {
					QMessageBox::information(this, "Failed", "Not Exist");
				}
			}
		}
	}
	else {
		QMessageBox::information(this, "Failed", "Connection Failed");
	}

	if (db.open()) {
		QSqlQuery query;
		query.prepare(QString("SELECT SCORE FROM university_list WHERE name = :university "));
		query.bindValue(":university", univFromDB);
		if (!query.exec()) {
			QMessageBox::information(this, "Failed", "Query Failed To Execute");
		}
		else {
			while (query.next()) {
				univ_scoreFromDB = query.value(0).toFloat();
				

				if (idFromDB == userid) {
					ui->label_myspec0->setText(QString::number(univ_scoreFromDB));

				}
				else {
					QMessageBox::information(this, "Failed", "Not Exist");
				}
			}
		}
	}
	else {
		QMessageBox::information(this, "Failed", "Connection Failed");
	}
	//user_score = (LOG2(SCORE)+ gpa + IFNULL(toeic/200,0) + IFNULL(opic,0) + IFNULL(toeic_speaking,0) + IFNULL(cert_count,0) +  lang_study +  intern)
	user_score = log2(univ_scoreFromDB) +gpaFromDB + toeicFromDB/200 + opicFromDB + tosFromDB + certificateFromDB + studyFromDB + internFromDB;
	string job_s = job.toLocal8Bit();
	char job_p[32];
	strcpy(job_p, job_s.c_str());
	string user_score_s = QString::number(user_score).toLocal8Bit();
	char user_score_p[16];
	strcpy(user_score_p, user_score_s.c_str());


	AvgSpec SpecRecommendated[3];
	string CompanyNameRe[3];

	mSpecDB.queryRecommendation(user_score_p, job_p, CompanyNameRe, SpecRecommendated);

	//업종 job에 따른 추천기업을 불러와서 함수실행해야함

	ui->label_company1->setText(QString::fromLocal8Bit(CompanyNameRe[0].c_str()));
	ui->label_c1spec0->setText(QString::number(SpecRecommendated[0].getScore()));
	ui->label_c1spec1->setText(QString::number(SpecRecommendated[0].getGpa()));
	ui->label_c1spec2->setText(QString::number(SpecRecommendated[0].getToeic()));
	ui->label_c1spec3->setText(QString::number(SpecRecommendated[0].getOpic()));
	ui->label_c1spec4->setText(QString::number(SpecRecommendated[0].getToeicSpeaking()));
	ui->label_c1spec5->setText(QString::number(SpecRecommendated[0].getCertCount()));
	ui->label_c1spec6->setText(QString::number(SpecRecommendated[0].getLangStudy()));
	ui->label_c1spec7->setText(QString::number(SpecRecommendated[0].getIntern()));

	ui->label_company2->setText(QString::fromLocal8Bit(CompanyNameRe[1].c_str()));
	ui->label_c2spec0->setText(QString::number(SpecRecommendated[1].getScore()));
	ui->label_c2spec1->setText(QString::number(SpecRecommendated[1].getGpa()));
	ui->label_c2spec2->setText(QString::number(SpecRecommendated[1].getToeic()));
	ui->label_c2spec3->setText(QString::number(SpecRecommendated[1].getOpic()));
	ui->label_c2spec4->setText(QString::number(SpecRecommendated[1].getToeicSpeaking()));
	ui->label_c2spec5->setText(QString::number(SpecRecommendated[1].getCertCount()));
	ui->label_c2spec6->setText(QString::number(SpecRecommendated[1].getLangStudy()));
	ui->label_c2spec7->setText(QString::number(SpecRecommendated[1].getIntern()));

	ui->label_company3->setText(QString::fromLocal8Bit(CompanyNameRe[2].c_str()));
	ui->label_c3spec0->setText(QString::number(SpecRecommendated[2].getScore()));
	ui->label_c3spec1->setText(QString::number(SpecRecommendated[2].getGpa()));
	ui->label_c3spec2->setText(QString::number(SpecRecommendated[2].getToeic()));
	ui->label_c3spec3->setText(QString::number(SpecRecommendated[2].getOpic()));
	ui->label_c3spec4->setText(QString::number(SpecRecommendated[2].getToeicSpeaking()));
	ui->label_c3spec5->setText(QString::number(SpecRecommendated[2].getCertCount()));
	ui->label_c3spec6->setText(QString::number(SpecRecommendated[2].getLangStudy()));
	ui->label_c3spec7->setText(QString::number(SpecRecommendated[2].getIntern()));
    //실제 코드는 switch써야할듯한데 연동할때 업종 개수보고 짜면될듯
    //-----------------------------------------


    //-----------------------------------------

}

void Recommendation::on_pushButton_back_clicked()
{
    hide();

    Menu menuDlg(mSpecDB);
    menuDlg.get_user_id(userid);
    menuDlg.setModal(true);
    menuDlg.exec();
}
