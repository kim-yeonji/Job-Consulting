#ifndef RECOMMENDATION_H
#define RECOMMENDATION_H

#include <QDialog>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include "SpecDatabase.h"

namespace Ui {
class Recommendation;
}

class Recommendation : public QDialog
{
    Q_OBJECT

public:
    explicit Recommendation(SpecDatabase& inSpecDB, QWidget *parent = 0);
    void get_user_id(QString inputid);
    ~Recommendation();

private slots:
    void on_pushButton_confirm_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::Recommendation *ui;
	SpecDatabase& mSpecDB;
    QString userid;
};

#endif // RECOMMENDATION_H
