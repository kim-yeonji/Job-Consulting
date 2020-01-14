#include "managingspec.h"
#include "ui_managingspec.h"
#include "menu.h"

ManagingSpec::ManagingSpec(SpecDatabase& inSpecDB, QWidget *parent) :
	mSpecDB(inSpecDB),
    QDialog(parent),
    ui(new Ui::ManagingSpec)
{
    ui->setupUi(this);

}

//user_id 계속 넘겨주면서 띄워주기
void ManagingSpec::get_user_id(QString inputid)
{
    userid = inputid;
    ui->label_inputID->setText(userid);
}

ManagingSpec::~ManagingSpec()
{
    delete ui;
}

void ManagingSpec::on_pushButton_back_clicked()
{
    hide();

    Menu menuDlg(mSpecDB);
    menuDlg.get_user_id(userid);
    menuDlg.setModal(true);
    menuDlg.exec();
}

void ManagingSpec::on_pushButton_save_clicked()
{

	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("your_hostname");
	db.setUserName("your_username");
	db.setPassword("your_password");
	db.setDatabaseName("your_databasename");
	//save 버튼 클릭시
	//lineedit에 입력한 스펙들을 각각의 변수에 저장했음
	QString my_university = ui->lineEdit_university->text();
	QString my_major = ui->lineEdit_major->text();
	QString my_grade = ui->lineEdit_grade->text();
	QString my_toeic = ui->lineEdit_toeic->text();
	QString my_opic = ui->lineEdit_opic->text();
	QString my_tos = ui->lineEdit_tos->text();
	QString my_certificate = ui->lineEdit_numberofcirtificate->text();
	QString my_intern = ui->lineEdit_numberofintern->text();
	QString my_study = ui->lineEdit_langstudy->text();


	//userid의 스펙정보 DB에 각각의 변수를 저장하는 코드 필요
	//-----------------------------------------
	if (db.open()) {
		QSqlQuery query;
		query.prepare("INSERT INTO user_spec(account_id, university, major, gpa, toeic, opic, toeic_speaking, cert_count, lang_study, intern)"
			"VALUES (:account_id, :university, :major, :gpa, :toeic, :opic, :toeic_speaking, :cert_count, :lang_study, :intern)");
		query.bindValue(":account_id", userid);
		query.bindValue(":university", my_university);
		query.bindValue(":major", my_major);
		query.bindValue(":gpa", my_grade);
		query.bindValue(":toeic", my_toeic);
		query.bindValue(":opic", my_opic);
		query.bindValue(":toeic_speaking", my_tos);
		query.bindValue(":cert_count", my_certificate);
		query.bindValue(":lang_study", my_study);
		query.bindValue(":intern", my_intern);
		if (!query.exec()) {
			QMessageBox::information(this, "Failed", "Query Failed To Execute");
		}
		else {

			QMessageBox::information(this, "Success", "Change Success");

		}
	}
	else {
		QMessageBox::information(this, "Failed", "Connection Failed");
	}

	//-----------------------------------------
}
