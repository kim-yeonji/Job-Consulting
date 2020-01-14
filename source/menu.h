#ifndef MENU_H
#define MENU_H

#include <QDialog>

#include "SpecDatabase.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(SpecDatabase& inSpecDB, QWidget *parent = 0);
    void get_user_id(QString inputid);
    ~Menu();

private slots:

    void on_pushButton_ManagingSpec_clicked();

    void on_pushButton_Apply_clicked();

    void on_pushButton_Recommendation_clicked();

    void on_pushButton_Companyinfo_clicked();

    void on_pushButton_Personalinfo_clicked();

    void on_pushButton_logout_clicked();

private:
    Ui::Menu *ui;
	SpecDatabase& mSpecDB;
    QString userid;
};

#endif // MENU_H
