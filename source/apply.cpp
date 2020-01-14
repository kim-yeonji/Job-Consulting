#include "apply.h"
#include "ui_apply.h"
#include "menu.h"
#include <QLabel>

Apply::Apply(SpecDatabase& inSpecDB, QWidget *parent) :
	mSpecDB(inSpecDB),
    QDialog(parent),
    ui(new Ui::Apply)
{
    ui->setupUi(this);

}

//user_id 계속 넘겨주면서 띄워주기
void Apply::get_user_id(QString inputid)
{
    userid = inputid;
    ui->label_inputID->setText(userid);
}
Apply::~Apply()
{
    delete ui;
}

void Apply::on_pushButton_back_clicked()
{
    hide();


    Menu menuDlg(mSpecDB);
    menuDlg.get_user_id(userid);
    menuDlg.setModal(true);
    menuDlg.exec();
}

void Apply::on_pushButton_confirm_clicked()
{
    //지원된 기업을 변수에 저장
    QString company = ui->lineEdit_apply->text();
	int companyId;

	// 사용자의 스펙 정보를 출력한다
	UserSpec userSpec;
	if (mSpecDB.queryUserSpec(userid.toLocal8Bit().constData(), userSpec) < 0) {
		// Alert : 스펙 정보 존재하지 않음.
		QMessageBox::information(this, "Alert", "No user spec data.");
	}
	else {
		ui->label_myspec1->setText(QString::number(userSpec.getGpa()));  // gpa
		ui->label_myspec2->setText(QString::number(userSpec.getToeic()));  // toeic
		ui->label_myspec3->setText(QString::number(userSpec.getOpic()));  // opic
		ui->label_myspec4->setText(QString::number(userSpec.getToeicSpeaking()));  // toeic speaking
		ui->label_myspec5->setText(QString::number(userSpec.getCertCount()));  // certification
		ui->label_myspec6->setText(QString::number(userSpec.getIntern()));  // intern
		ui->label_myspec7->setText(QString::number(userSpec.getLangStudy()));  // lang study
	}

    //ui의 lineEdit_apply에 입력된 기업 이름을 해당 label에 띄워준다.
    ui->label_inputcompany->setText(company);
	if ((companyId = mSpecDB.queryCompanyId(company.toLocal8Bit().constData())) < 0) {
		// Alert : 기업명 존재하지 않음.
		QMessageBox::information(this, "Alert", "No company data.");
	}
	else {
		AvgSpec avgPassedSpec, avgAppliedSpec;
		if (mSpecDB.queryAvgPassedSpec(companyId, avgPassedSpec) < 0) {
			// Alert : 합격 데이터 존재하지 않음.
			QMessageBox::information(this, "Alert", "No passed spec data.");
		}
		else {
			ui->label_spec1->setText(QString::number(avgPassedSpec.getGpa()));  // gpa
			ui->label_spec2->setText(QString::number(avgPassedSpec.getToeic()));  // toeic
			ui->label_spec3->setText(QString::number(avgPassedSpec.getOpic()));  // opic
			ui->label_spec4->setText(QString::number(avgPassedSpec.getToeicSpeaking()));  // toeic speaking
			ui->label_spec5->setText(QString::number(avgPassedSpec.getCertCount()));  // certification
			ui->label_spec6->setText(QString::number(avgPassedSpec.getIntern()));  // intern
			ui->label_spec7->setText(QString::number(avgPassedSpec.getLangStudy()));  // lang study
		}

		mSpecDB.insertApply(userid.toLocal8Bit().constData(), companyId);

		if (mSpecDB.queryAvgAppliedSpec(companyId, avgAppliedSpec) < 0) {
			// Alert : 지원 데이터 존재하지 않음.
			QMessageBox::information(this, "Alert", "No applied spec data.");
		}
		else {
			ui->label_candidate1->setText(QString::number(avgAppliedSpec.getGpa()));  // gpa
			ui->label_candidate2->setText(QString::number(avgAppliedSpec.getToeic()));  // toeic
			ui->label_candidate3->setText(QString::number(avgAppliedSpec.getOpic()));  // opic
			ui->label_candidate4->setText(QString::number(avgAppliedSpec.getToeicSpeaking()));  // toeic speaking
			ui->label_candidate5->setText(QString::number(avgAppliedSpec.getCertCount()));  // certification
			ui->label_candidate6->setText(QString::number(avgAppliedSpec.getIntern()));  // intern
			ui->label_candidate7->setText(QString::number(avgAppliedSpec.getLangStudy()));  // lang study

		}
	}
}

