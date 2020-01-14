#ifndef PERSONALINFO_H
#define PERSONALINFO_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "SpecDatabase.h"

namespace Ui {
class Personalinfo;
}

class Personalinfo : public QDialog
{
    Q_OBJECT

public:
    explicit Personalinfo(SpecDatabase& inSpecDB, QWidget *parent = 0);
    void get_user_id(QString inputid);
    ~Personalinfo();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::Personalinfo *ui;
	SpecDatabase& mSpecDB;
    QString userid;
	QSqlDatabase database;
};

#endif // PERSONALINFO_H
