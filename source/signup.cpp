#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"

Signup::Signup(SpecDatabase& inSpecDB, QWidget *parent) :
	mSpecDB(inSpecDB),
    QDialog(parent),
    ui(new Ui::Signup)
{
	ui->setupUi(this);
	ui->lineEdit_id->setPlaceholderText("Enter Your Id");
	ui->lineEdit_password->setPlaceholderText("Enter Your Password");
	ui->lineEdit_name->setPlaceholderText("Enter Your Name");
	ui->lineEdit_email->setPlaceholderText("Enter Your E-mail");
}

Signup::~Signup()
{
    delete ui;
}

void Signup::on_pushButton_confirm_clicked()
{
	database = QSqlDatabase::addDatabase("QMYSQL");
	database.setHostName("your_hostname");
	database.setUserName("your_username");
	database.setPassword("your_password");
	database.setDatabaseName("your_databasename");


    QString my_id = ui->lineEdit_id->text();
	if (database.open()) {
		QString id = ui->lineEdit_id->text();
		QString password = ui->lineEdit_password->text();
		QString name = ui->lineEdit_name->text();
		QString email = ui->lineEdit_email->text();

		//Run our Insert Query
		QSqlQuery qry;

		qry.prepare("INSERT INTO user_account(account_id, account_pw, account_name, email)"
			"VALUES (:account_id, :account_pw, :account_name, :email)");
		qry.bindValue(":account_id", id);
		qry.bindValue(":account_pw", password);
		qry.bindValue(":account_name", name);
		qry.bindValue(":email", email);

		if (qry.exec()) {
			QMessageBox::information(this, "Inserted", "Data Inserted Successfully");
		}
		else {
			QMessageBox::information(this, "Not Inserted", "Data Is Not Inserted");
		}

	}
	else {
		QMessageBox::information(this, "Not Connected", "Database Is Not Connected");
	}

    //DB에 위에서 받은 회원가입 정보 변수들 저장해야함
    //-----------------------------------------



    //-----------------------------------------
    //회원가입창을 끔
    hide();
}
