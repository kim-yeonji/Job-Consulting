#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "menu.h"
#include "signup.h"
#include <qmessagebox.h>
QString getid;
MainWindow::MainWindow(SpecDatabase& inSpecDB, QWidget *parent) :
	mSpecDB(inSpecDB),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_login_clicked()
{
	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QMYSQL", "MyConnect");
	db.setHostName("your_hostname");
	db.setUserName("your_username");
	db.setPassword("your_password");
	db.setDatabaseName("your_databasename");

	QString username = ui->lineEdit_username->text();
	QString password = ui->lineEdit_password->text();

	if (db.open()) {
		QMessageBox::information(this, "Database Success", "Database Connection Success");

		QSqlQuery query(QSqlDatabase::database("MyConnect"));

		query.prepare(QString("SELECT * FROM user_account WHERE account_id = :account_id AND account_pw = :account_pw"));

		query.bindValue(":account_id", username);
		query.bindValue(":account_pw", password);

		if (!query.exec()) {
			QMessageBox::information(this, "Failed", "Query Failed To Execute");
		}
		else {

			while (query.next()) {

				QString usernameFromDB = query.value(0).toString();
				QString passwordFromDB = query.value(1).toString();

				if (usernameFromDB == username && passwordFromDB == password) {

					getid = username;
					QMessageBox::information(this, "Success", "Login Success");

					Menu menuDlg(mSpecDB);
					menuDlg.get_user_id(username);
					menuDlg.setModal(true);
					menuDlg.exec();

				}
				else {
					QMessageBox::information(this, "Failed", "Login Failed");
				}
			}
		}
	}
	else {
		QMessageBox::information(this, "Database Failed", "Database Connection Failed");
	}

}

void MainWindow::on_pushButton_exit_clicked()
{
    close();
}

void MainWindow::on_pushButton_signup_clicked()
{
    //Signup 프레임으로 넘어간다.
    Signup signupDlg(mSpecDB);
    signupDlg.setModal(true);
    signupDlg.exec();
}
