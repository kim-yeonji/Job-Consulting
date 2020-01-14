#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>

#include "SpecDatabase.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SpecDatabase& inSpecDB, QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_login_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_signup_clicked();

private:
    Ui::MainWindow *ui;
	SpecDatabase& mSpecDB;

	QSqlDatabase database;
    // 데이터베이스 연동 QsqlDatabase mydb;
};

#endif // MAINWINDOW_H
