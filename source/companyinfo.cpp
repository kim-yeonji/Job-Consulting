#include "companyinfo.h"
#include "ui_companyinfo.h"
#include "menu.h"

Companyinfo::Companyinfo(SpecDatabase& inSpecDB, QWidget *parent) :
	mSpecDB(inSpecDB),
    QDialog(parent),
    ui(new Ui::Companyinfo)
{
    ui->setupUi(this);
}

//user_id 계속 넘겨주면서 띄워주기
void Companyinfo::get_user_id(QString inputid)
{
    userid = inputid;
}

Companyinfo::~Companyinfo()
{
    delete ui;
}

void Companyinfo::on_pushButton_back_clicked()
{
    hide();

    Menu menuDlg(mSpecDB);
    menuDlg.get_user_id(userid);
    menuDlg.setModal(true);
    menuDlg.exec();
}

void Companyinfo::on_pushButton_confirm_clicked()
{
	QSqlDatabase db;
	db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("your_hostname");
	db.setUserName("your_username");
	db.setPassword("your_password");
	db.setDatabaseName("your_databasename");
	QString company = ui->lineEdit_searchcompany->text();
	if (db.open()) {
		QSqlQuery query(QSqlDatabase::database("Connect"));
		query.prepare(QString("SELECT * FROM company WHERE company_name = :company_name "));
		query.bindValue(":company_name", company);
		if (!query.exec()) {
			QMessageBox::information(this, "Failed", "Query Failed To Execute");
		}
		else {
			while (query.next()) {

				QString companyFromDB = query.value(1).toString();
				QString categoryFromDB = query.value(2).toString();
				QString classFromDB = query.value(3).toString();
				QString addressFromDB = query.value(4).toString();
				QString salaryFromDB = query.value(5).toString();

				if (companyFromDB == company) {

					QMessageBox::information(this, "Success", "Exist company");
					ui->label_companyname->setText(companyFromDB);
					ui->label_category->setText(categoryFromDB);
					ui->label_class->setText(classFromDB);
					ui->label_address->setText(addressFromDB);
					ui->label_salary->setText(salaryFromDB);


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



}
