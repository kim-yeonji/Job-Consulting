#include "personalinfo.h"
#include "ui_personalinfo.h"
#include "menu.h"

Personalinfo::Personalinfo(SpecDatabase& inSpecDB, QWidget *parent) :
	mSpecDB(inSpecDB),
    QDialog(parent),
    ui(new Ui::Personalinfo)
{
    ui->setupUi(this);

}


//user_id 계속 넘겨주면서 띄워주기
void Personalinfo::get_user_id(QString inputid)
{
    userid = inputid;
    ui->label_inputID->setText(userid);
}


Personalinfo::~Personalinfo()
{
    delete ui;
}

void Personalinfo::on_pushButton_save_clicked()
{

	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("your_hostname");
	db.setUserName("your_username");
	db.setPassword("your_password");
	db.setDatabaseName("your_databasename");

	QString changed_password = ui->lineEdit_password->text();
	QString changed_email = ui->lineEdit_email->text();

	//DB의 회원 정보에서 위의 변수들로 갱신해야함
	//-----------------------------------------
	if (db.open()) {
		QSqlQuery query;
		query.prepare(QString("UPDATE user_account SET account_pw = :account_pw, email = :email WHERE account_id = :account_id "));
		query.bindValue(":account_pw", changed_password);
		query.bindValue(":email", changed_email);
		query.bindValue(":account_id", userid);
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

void Personalinfo::on_pushButton_back_clicked()
{
    hide();

    Menu menuDlg(mSpecDB);
    menuDlg.get_user_id(userid);
    menuDlg.setModal(true);
    menuDlg.exec();
}
