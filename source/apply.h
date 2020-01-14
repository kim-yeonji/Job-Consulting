#ifndef APPLY_H
#define APPLY_H

#include <QDialog>
#include <string>
#include <qmessagebox.h>

#include "SpecDatabase.h"
#include "AvgSpec.h"
#include "UserSpec.h"

namespace Ui {
class Apply;
}

class Apply : public QDialog
{
    Q_OBJECT

public:
    explicit Apply(SpecDatabase& inSpecDB, QWidget *parent = 0);
    void get_user_id(QString inputid);
    ~Apply();

private slots:
    void on_pushButton_back_clicked();

    void on_pushButton_confirm_clicked();


private:
    Ui::Apply *ui;
	SpecDatabase& mSpecDB;
    QString userid;
};

#endif // APPLY_H
