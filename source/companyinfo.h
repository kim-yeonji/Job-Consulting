#ifndef COMPANYINFO_H
#define COMPANYINFO_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "SpecDatabase.h"

namespace Ui {
class Companyinfo;
}

class Companyinfo : public QDialog
{
    Q_OBJECT

public:
    explicit Companyinfo(SpecDatabase& inSpecDB, QWidget *parent = 0);
    ~Companyinfo();
    void get_user_id(QString inputid);

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_confirm_clicked();

private:
    Ui::Companyinfo *ui;
	SpecDatabase& mSpecDB;
    QString userid;
	QSqlDatabase database;
};

#endif // COMPANYINFO_H
