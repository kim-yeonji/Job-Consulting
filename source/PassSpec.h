#ifndef PASSSPEC_H
#define PASSSPEC_H

#include <string>

#include "Spec.h"

using namespace std;

class PassSpec : public Spec {
public:
	PassSpec();  // class constructor
	~PassSpec() {} // class destructor

	// getter
	int getSpecNo() { return mSpecNo; }
	int getCompanyID() { return mCompanyID; }
	string getCompanyJob() { return mCompanyJob; }

	// setter
	void setSpecNo(int inSpecNo) { mSpecNo = inSpecNo; }
	void setCompanyID(int inCompanyID) { mCompanyID = inCompanyID; }
	void setCompanyJob(string inCompanyJob) { mCompanyJob = inCompanyJob; }

protected:
	int mSpecNo;  // 스펙 번호 (일련번호)
	int mCompanyID;  // 기업 ID
	string mCompanyJob;  // 지원 분야
};


#endif // !PASSSPEC_H
