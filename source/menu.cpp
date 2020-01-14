#include "menu.h"
#include "ui_menu.h"
#include "qstring.h"
#include "managingspec.h"
#include "apply.h"
#include "recommendation.h"
#include "companyinfo.h"
#include "personalinfo.h"
#include "mainwindow.h"
Menu::Menu(SpecDatabase& inSpecDB, QWidget *parent) :
	mSpecDB(inSpecDB),
    QDialog(parent),
    ui(new Ui::Menu)
{
    userid = "";
    ui->setupUi(this);
}

//user_id 계속 넘겨주면서 띄워주기
void Menu::get_user_id(QString inputid)
{
    userid = inputid;
    ui->label_inputID->setText(userid);
}

Menu::~Menu()
{
    delete ui;
}


void Menu::on_pushButton_ManagingSpec_clicked()
{
    hide();

    ManagingSpec specDlg(mSpecDB);
    specDlg.get_user_id(userid);
    specDlg.setModal(true);
    specDlg.exec();
}

void Menu::on_pushButton_Apply_clicked()
{
    hide();

    Apply applyDlg(mSpecDB);
    applyDlg.get_user_id(userid);
    applyDlg.setModal(true);
    applyDlg.exec();
}

void Menu::on_pushButton_Recommendation_clicked()
{
    hide();

    Recommendation recommendDlg(mSpecDB);
    recommendDlg.get_user_id(userid);
    recommendDlg.setModal(true);
    recommendDlg.exec();
}

void Menu::on_pushButton_Companyinfo_clicked()
{
    hide();

    Companyinfo companyDlg(mSpecDB);
	companyDlg.get_user_id(userid);
	companyDlg.setModal(true);
    companyDlg.exec();
}

void Menu::on_pushButton_Personalinfo_clicked()
{
    hide();

    Personalinfo personalDlg(mSpecDB);
    personalDlg.get_user_id(userid);
    personalDlg.setModal(true);
    personalDlg.exec();
}

void Menu::on_pushButton_logout_clicked()
{
    hide();
}
