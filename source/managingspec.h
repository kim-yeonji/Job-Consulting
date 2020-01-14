#ifndef MANAGINGSPEC_H
#define MANAGINGSPEC_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "SpecDatabase.h"

namespace Ui {
class ManagingSpec;
}

class ManagingSpec : public QDialog
{
    Q_OBJECT

public:
    explicit ManagingSpec(SpecDatabase& inSpecDB, QWidget *parent = 0);
    void get_user_id(QString inputid);
    ~ManagingSpec();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_save_clicked();

private:
    Ui::ManagingSpec *ui;
	SpecDatabase& mSpecDB;
    QString userid;
};

#endif // MANAGINGSPEC_H
