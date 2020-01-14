#include "SpecDatabase.h"

SpecDatabase::SpecDatabase() {
	// 접속 정보
	ODBC_Name = (SQLCHAR*)"your_ODBCname";
	ODBC_ID = (SQLCHAR*)"your_username";
	ODBC_PW = (SQLCHAR*)"your_password";

	DBConnect();
}

SpecDatabase::~SpecDatabase() {
	DBDisConnect();
}

// 데이터베이스 연결
bool SpecDatabase::DBConnect() {
	// ODBC 연결을 위한 환경을 관리하기 위한 핸들러 할당
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
		return false;
	// 환경 핸들러를 통해 ODBC 버전 정보 설정
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
		return false;
	// 데이터베이스 연결을 관리하기 위한 연결 핸들러 할당
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
		return false;
	// 데이터베이스 연결
	if (SQLConnectA(hDbc, ODBC_Name, SQL_NTS, ODBC_ID, SQL_NTS, ODBC_PW, SQL_NTS) != SQL_SUCCESS)
		return false;
	// 질의를 관리하기 위한 Statement 핸들러 할당
	if (SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt) != SQL_SUCCESS)
		return false;
	return true;
}

// 데이터베이스 연결 해제
void SpecDatabase::DBDisConnect() {
	// Statement 핸들러 해제
	if (hStmt)
		SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	// 데이터베이스 연결 종료
	if (hDbc)
		SQLDisconnect(hDbc);
	// 데이터베이스 연결 핸들러 해제
	if (hDbc)
		SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
	// 데이터베이스 연결 환경 핸들러 해제
	if (hEnv)
		SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}

// 질의 수행 (최적화 플랜 작성 + 질의 수행을 동시에 수행함)
bool SpecDatabase::DBExecuteSQL(SQLCHAR* query) {
	if (SQLExecDirectA(hStmt, query, SQL_NTS) != SQL_SUCCESS)
		return false;
	return true;
}

// 최적화 플랜 작성 (질의 수행과 분리)
bool SpecDatabase::DBPrepare(SQLCHAR* query_for_statement) {
	if (SQLPrepareA(hStmt, query_for_statement, SQL_NTS) != SQL_SUCCESS)
		return false;
	return true;
}

// 질의 수행 (최적화 플랜 작성과 분리)
bool SpecDatabase::DBExecuteSQL() {
	if (SQLExecute(hStmt) != SQL_SUCCESS)
		return false;
	return true;
}

// 기업의 합격자 평균 스펙을 전달함
int SpecDatabase::queryAvgPassedSpec(int inCompanyId, AvgSpec& outAvgSpec) {
	DBPrepare((SQLCHAR*)"SELECT AVG(gpa), AVG(toeic), AVG(opic), AVG(toeic_speaking), AVG(cert_count), AVG(lang_study), AVG(intern) FROM pass_spec GROUP BY company_id HAVING company_id = ?;");
	SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 0, 0, &inCompanyId, 0, NULL);
	DBExecuteSQL();
	return getAvgSpec(outAvgSpec);
}

// 기업의 지원자 평균 스펙을 전달함
int SpecDatabase::queryAvgAppliedSpec(int inCompanyId, AvgSpec& outAvgSpec) {
	DBPrepare((SQLCHAR*)"SELECT AVG(gpa), AVG(toeic), AVG(opic), AVG(toeic_speaking), AVG(cert_count), AVG(lang_study), AVG(intern) FROM apply_list AS a, user_spec AS u WHERE a.account_id = u.account_id GROUP BY company_id HAVING company_id = ?;");
	SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 0, 0, &inCompanyId, 0, NULL);
	DBExecuteSQL();
	return getAvgSpec(outAvgSpec);
}

// CompanyName으로부터 CompanyId를 찾아서 전달함
int SpecDatabase::queryCompanyId(const string& inCompanyName) {
	DBPrepare((SQLCHAR*)"SELECT company_id FROM company WHERE company_name = ?; ");
	SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)inCompanyName.c_str(), 0, NULL);
	DBExecuteSQL();
	return getCompanyId();
}

// AccountID로부터 사용자 스펙을 찾아서 전달함
int SpecDatabase::queryUserSpec(const string& inAccountID, UserSpec& outUserSpec) {
	DBPrepare((SQLCHAR*)"SELECT * FROM user_spec WHERE account_id = ?;");
	SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)inAccountID.c_str(), 0, NULL);
	DBExecuteSQL();
	return getUserSpec(outUserSpec);
}

// 질의 결과 평균 스펙을 전달함
int SpecDatabase::getAvgSpec(AvgSpec& outAvgSpec) {
	int result;

	SQLDOUBLE gpa;
	SQLDOUBLE toeic;
	SQLDOUBLE opic;
	SQLDOUBLE toeicSpeaking;
	SQLDOUBLE certCount;
	SQLDOUBLE langStudy;
	SQLDOUBLE intern;

	SQLLEN i_gpa;
	SQLLEN i_toeic;
	SQLLEN i_opic;
	SQLLEN i_toeicSpeaking;
	SQLLEN i_certCount;
	SQLLEN i_langStudy;
	SQLLEN i_intern;

	//select 질의 수행 결과를 저장할 변수를 지정한다.(Column Number는 1부터 시작한다)
	SQLBindCol(hStmt, 1, SQL_DOUBLE, &gpa, sizeof(gpa), &i_gpa);
	SQLBindCol(hStmt, 2, SQL_DOUBLE, &toeic, sizeof(toeic), &i_toeic);
	SQLBindCol(hStmt, 3, SQL_DOUBLE, &opic, sizeof(opic), &i_opic);
	SQLBindCol(hStmt, 4, SQL_DOUBLE, &toeicSpeaking, sizeof(toeicSpeaking), &i_toeicSpeaking);
	SQLBindCol(hStmt, 5, SQL_DOUBLE, &certCount, sizeof(certCount), &i_certCount);
	SQLBindCol(hStmt, 6, SQL_DOUBLE, &langStudy, sizeof(langStudy), &i_langStudy);
	SQLBindCol(hStmt, 7, SQL_DOUBLE, &intern, sizeof(intern), &i_intern);


	//질의 수행결과를 hStmt로 가져온다. 이때, 바인딩된 변수에 값이 할당된다.
	if (SQLFetch(hStmt) != SQL_NO_DATA) {
		outAvgSpec.setGpa((float)gpa);
		outAvgSpec.setToeic((float)toeic);
		outAvgSpec.setOpic((float)opic);
		outAvgSpec.setToeicSpeaking((float)toeicSpeaking);
		outAvgSpec.setCertCount((float)certCount);
		outAvgSpec.setLangStudy((float)langStudy);
		outAvgSpec.setIntern((float)intern);

		result = 0;
	}
	else
		result = -1;

	//hStmt 커서 해제
	if (hStmt)
		SQLCloseCursor(hStmt);

	return result;
}

// 질의 결과 CompanyId를 반환함
int SpecDatabase::getCompanyId() {
	int result;

	SQLINTEGER companyId;
	SQLLEN i_companyId;

	//select 질의 수행 결과를 저장할 변수를 지정한다.(Column Number는 1부터 시작한다)
	SQLBindCol(hStmt, 1, SQL_INTEGER, &companyId, sizeof(companyId), &i_companyId);

	//질의 수행결과를 hStmt로 가져온다. 이때, 바인딩된 변수에 값이 할당된다.
	if (SQLFetch(hStmt) != SQL_NO_DATA)
		result = (int)companyId;
	else
		result = -1;

	//hStmt 커서 해제
	if (hStmt)
		SQLCloseCursor(hStmt);

	return result;
}

// 질의 결과 사용자 스펙을 반환함
int SpecDatabase::getUserSpec(UserSpec& outUserSpec) {
	int result;

	SQLCHAR accountID[65];
	SQLCHAR university[65];
	SQLCHAR major[65];
	SQLDOUBLE gpa;
	SQLINTEGER toeic;
	SQLINTEGER opic;
	SQLINTEGER toeicSpeaking;
	SQLINTEGER certCount;
	SQLINTEGER langStudy;
	SQLINTEGER intern;

	SQLLEN i_accountID;
	SQLLEN i_university;
	SQLLEN i_major;
	SQLLEN i_gpa;
	SQLLEN i_toeic;
	SQLLEN i_opic;
	SQLLEN i_toeicSpeaking;
	SQLLEN i_certCount;
	SQLLEN i_langStudy;
	SQLLEN i_intern;

	//select 질의 수행 결과를 저장할 변수를 지정한다.(Column Number는 1부터 시작한다)
	SQLBindCol(hStmt, 1, SQL_CHAR, accountID, sizeof(accountID), &i_accountID);
	SQLBindCol(hStmt, 2, SQL_CHAR, university, sizeof(university), &i_university);
	SQLBindCol(hStmt, 3, SQL_CHAR, major, sizeof(major), &i_major);
	SQLBindCol(hStmt, 4, SQL_DOUBLE, &gpa, sizeof(gpa), &i_gpa);
	SQLBindCol(hStmt, 5, SQL_INTEGER, &toeic, sizeof(toeic), &i_toeic);
	SQLBindCol(hStmt, 6, SQL_INTEGER, &opic, sizeof(opic), &i_opic);
	SQLBindCol(hStmt, 7, SQL_INTEGER, &toeicSpeaking, sizeof(toeicSpeaking), &i_toeicSpeaking);
	SQLBindCol(hStmt, 8, SQL_INTEGER, &certCount, sizeof(certCount), &i_certCount);
	SQLBindCol(hStmt, 9, SQL_INTEGER, &langStudy, sizeof(langStudy), &i_langStudy);
	SQLBindCol(hStmt, 10, SQL_INTEGER, &intern, sizeof(intern), &i_intern);


	//질의 수행결과를 hStmt로 가져온다. 이때, 바인딩된 변수에 값이 할당된다.
	if (SQLFetch(hStmt) != SQL_NO_DATA) {
		outUserSpec.setAccountID(string((char*)accountID));
		outUserSpec.setUniversity(string((char*)university));
		outUserSpec.setMajor(string((char*)major));
		outUserSpec.setGpa((float)gpa);
		outUserSpec.setToeic((int)toeic);
		outUserSpec.setOpic((int)opic);
		outUserSpec.setToeicSpeaking((int)toeicSpeaking);
		outUserSpec.setCertCount((int)certCount);
		outUserSpec.setLangStudy((int)langStudy);
		outUserSpec.setIntern((int)intern);

		result = 0;
	}
	else
		result = -1;

	//hStmt 커서 해제
	if (hStmt)
		SQLCloseCursor(hStmt);

	return result;
}

//카테고리 갯수 가져옴 
int SpecDatabase::queryCountCategory(int& counter, string* category_str)
{
	DBExecuteSQL((SQLCHAR*)"SELECT distinct(category) FROM specDB.company");
	SQLCHAR CATEGORY[32];
	SQLLEN i_category;

	SQLBindCol(hStmt, 1, SQL_CHAR, &CATEGORY, sizeof(CATEGORY), &i_category);

	while (SQLFetch(hStmt) != SQL_NO_DATA)
	{


		category_str[counter] = string((const char*)CATEGORY);

		counter++;
	}



	return 0;
}
//아 ㅋㅋ
int* SpecDatabase::queryRecommendation(char* user_score, char* category, string* outCompanyName, AvgSpec* outAvgSpec)
{
	int counter = 0;
	char query[1024] = "SELECT  company_name, avg(SCORE) , avg(gpa), avg(IFNULL(toeic,0)), avg(IFNULL(opic,0)), avg(IFNULL(toeic_speaking,0)), avg(cert_count),avg(lang_study), avg(intern),(LOG2(SCORE)+ gpa + IFNULL(toeic/200,0) + IFNULL(opic,0) + IFNULL(toeic_speaking,0) + IFNULL(cert_count,0) +  lang_study +  intern) AS FITNESS		FROM(			SELECT *			FROM specDB.pass_spec AS P, specDB.university_list AS V			WHERE  P.university = V.name)T, specDB.company AS C		WHERE T.company_id = C.company_id		AND CATEGORY = ";
	strcat_s(query, "\"");
	strcat_s(query, category);
	strcat_s(query, "\"");
	strcat_s(query, "AND (LOG2(SCORE)+ gpa + IFNULL(toeic/200,0) + IFNULL(opic,0) + IFNULL(toeic_speaking,0) + IFNULL(cert_count,0) +  lang_study +  intern) < ");
	strcat_s(query, user_score);
	strcat_s(query, "\n");
	strcat_s(query, "GROUP BY T.company_id		ORDER BY FITNESS DESC;");

	DBExecuteSQL((SQLCHAR*)query);

	SQLCHAR COMPANY[32];
	SQLDOUBLE UNIVERSITY;
	SQLDOUBLE GPA;
	SQLDOUBLE TOEIC;
	SQLDOUBLE OPIC;
	SQLDOUBLE TOEICSPEAKING;
	SQLDOUBLE CERTCOUNT;
	SQLDOUBLE LANGSTUDY;
	SQLDOUBLE INTERN;
	SQLDOUBLE FITNESS;

	SQLLEN i_comapny, i_university, i_gpa, i_toeic, i_opic, i_toeicspeaking, i_certcount, i_langstudy, i_intern, i_fitness;

	SQLBindCol(hStmt, 1, SQL_CHAR, COMPANY, sizeof(COMPANY), &i_comapny);
	SQLBindCol(hStmt, 2, SQL_DOUBLE, &UNIVERSITY, sizeof(UNIVERSITY), &i_university);
	SQLBindCol(hStmt, 3, SQL_DOUBLE, &GPA, sizeof(GPA), &i_gpa);
	SQLBindCol(hStmt, 4, SQL_DOUBLE, &TOEIC, sizeof(TOEIC), &i_toeic);
	SQLBindCol(hStmt, 5, SQL_DOUBLE, &OPIC, sizeof(OPIC), &i_opic);
	SQLBindCol(hStmt, 6, SQL_DOUBLE, &TOEICSPEAKING, sizeof(TOEICSPEAKING), &i_toeicspeaking);
	SQLBindCol(hStmt, 7, SQL_DOUBLE, &CERTCOUNT, sizeof(CERTCOUNT), &i_certcount);
	SQLBindCol(hStmt, 8, SQL_DOUBLE, &LANGSTUDY, sizeof(LANGSTUDY), &i_langstudy);
	SQLBindCol(hStmt, 9, SQL_DOUBLE, &INTERN, sizeof(INTERN), &i_intern);
	SQLBindCol(hStmt, 10, SQL_DOUBLE, &FITNESS, sizeof(FITNESS), &i_fitness);


	while (SQLFetch(hStmt) != SQL_NO_DATA && counter != 3)
	{
		outCompanyName[counter] = (const char*)COMPANY;
		outAvgSpec[counter].setGpa((float)GPA);
		outAvgSpec[counter].setToeic((float)TOEIC);
		outAvgSpec[counter].setOpic((float)OPIC);
		outAvgSpec[counter].setToeicSpeaking((float)TOEICSPEAKING);
		outAvgSpec[counter].setCertCount((float)CERTCOUNT);
		outAvgSpec[counter].setLangStudy((float)LANGSTUDY);
		outAvgSpec[counter].setIntern((float)INTERN);
		outAvgSpec[counter].setScore((float)UNIVERSITY);
		counter++;
	}

	//hStmt 커서 해제
	if (hStmt)
		SQLCloseCursor(hStmt);

	return 0;

}


// 사용자의 AccountID와 CompanyID를 사용하여 지원 정보를 추가함
void SpecDatabase::insertApply(const string& inAccountID, int inCompanyID) {
	DBPrepare((SQLCHAR*)"INSERT apply_list VALUES(?, ?, CURDATE());");
	SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_CHAR, SQL_CHAR, 0, 0, (SQLCHAR*)inAccountID.c_str(), 0, NULL);
	SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_INTEGER, SQL_INTEGER, 0, 0, &inCompanyID, 0, NULL);
	DBExecuteSQL();
}
