#ifndef SPECDATABASE_H
#define SPECDATABASE_H

#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <math.h>

#include "AvgSpec.h"
#include "UserSpec.h"

using namespace std;


// DB 관련된 작업들을 할 수 있는 클래스
class SpecDatabase {
public:
	SpecDatabase();  // class constructor (Connect Database)
	~SpecDatabase();  // class destructor (Disconnect Database)

	bool DBExecuteSQL(SQLCHAR* query);  // 질의 수행 (최적화 플랜 작성 + 질의 수행을 동시에 수행함)
	bool DBPrepare(SQLCHAR* query_for_statement);  // 최적화 플랜 작성 (질의 수행과 분리)
	bool DBExecuteSQL();  // 질의 수행 (최적화 플랜 작성과 분리)

	// 기업의 CompanyId를 입력 받아 그 기업의 합격자 평균 스펙을 DB에 질의한 후 전달함
	// 정상적으로 전달하면 0, CompanyId가 DB에 존재하지 않으면 -1을 반환함
	int queryAvgPassedSpec(int inCompanyId, AvgSpec& outAvgSpec);

	// 기업의 CompanyId를 입력 받아 그 기업의 지원자 평균 스펙을 DB에 질의한 후 전달함
	// 정상적으로 전달하면 0, 그 기업에 지원한 지원자가 없으면 -1을 반환함
	int queryAvgAppliedSpec(int inCompanyId, AvgSpec& outAvgSpec);

	// 기업의 CompanyName을 입력 받아 그 기업의 CompanyId를 DB에 질의한 후 전달함
	// CompanyName이 존재하는 경우 그 기업의 CompanyId(>0)을 반환하고, CompanyName이 없으면 -1을 반환함
	int queryCompanyId(const string& inCompanyName);

	// 사용자의 AccountID를 입력 받아 그 사용자의 스펙을 DB에 질의한 후 전달함
	// 정상적으로 전달하면 0, 사용자의 스펙 정보가 존재하지 않으면 -1을 반환함
	int queryUserSpec(const string& inAccountID, UserSpec& outUserSpec);


	// 카테고리 갯수와 내용을 받아오는 함수. 아직 잘 모름. 성공시 return 1 (recommendation에서 사용됨)
	int queryCountCategory(int& counter, string* category_str);

	// 카테고리와 유저 점수(문자열)를 받아 3위까지 평균 스펙과 기업이름을 전달해주는 함수.  (recommendation에서 사용됨)
	int* queryRecommendation(char* user_score, char* category, string* outCompanyName, AvgSpec* outAvgSpec);

	// 사용자의 AccountID와 CompanyID를 사용하여 지원 정보를 추가함
	void insertApply(const string& inAccountID, int inCompanyID);

protected:
	bool DBConnect();  // 데이터베이스 연결
	void DBDisConnect();  // 데이터베이스 연결 해제

	// 질의 결과로 나온 평균 스펙을 읽어와서 outAvgSpec에 저장
	// 정상적으로 저장하면 0, 질의 결과가 없다면 -1을 반환함
	int getAvgSpec(AvgSpec& outAvgSpec);

	// 질의 결과로 나온 CompanyId를 읽어와서 반환함
	// 질의 결과가 존재하는 경우 CompanyId(>0)를 반환하고, 없으면 -1을 반환함
	int getCompanyId();

	// 질의 결과로 나온 사용자 스펙을 읽어와서 outUserSpec에 저장
	// 정상적으로 저장하면 0, 질의 결과가 없다면 -1을 반환함
	int getUserSpec(UserSpec& outUserSpec);

	// ODBC conn
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;

	// 접속 정보
	SQLCHAR* ODBC_Name;
	SQLCHAR* ODBC_ID;
	SQLCHAR* ODBC_PW;
};

#endif // !SPECDATABASE_H
