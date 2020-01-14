#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

#include "SpecDatabase.h"

namespace Ui {
class Signup;
}

class Signup : public QDialog
{
    Q_OBJECT

public:
    explicit Signup(SpecDatabase &inSpecDB, QWidget *parent = 0);
    ~Signup();

private slots:
    void on_pushButton_confirm_clicked();

private:
    Ui::Signup *ui;
	SpecDatabase& mSpecDB;
	QSqlDatabase database;
};

#endif // SIGNUP_H
