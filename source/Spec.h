#ifndef SPEC_H
#define SPEC_H

#include <string>
using namespace std;

class Spec {
public:
	Spec();  // class constructor
	~Spec() {}  // class destructor

	// getter
	string getUniversity() { return mUniversity; }
	string getMajor() { return mMajor; }
	float getGpa() { return mGpa; }
	int getToeic() { return mToeic; }
	int getOpic() { return mOpic; }
	int getToeicSpeaking() { return mToeicSpeaking; }
	int getCertCount() { return mCertCount; }
	int getLangStudy() { return mLangStudy; }
	int getIntern() { return mIntern; }

	// setter
	void setUniversity(string inUniversity) { mUniversity = inUniversity; }
	void setMajor(string inMajor) { mMajor = inMajor; }
	void setGpa(float inGpa) { mGpa = inGpa; }
	void setToeic(int inToeic) { mToeic = inToeic; }
	void setOpic(int inOpic) { mOpic = inOpic; }
	void setToeicSpeaking(int inToeicSpeaking) { mToeicSpeaking = inToeicSpeaking; }
	void setCertCount(int inCertCount) { mCertCount = inCertCount; }
	void setLangStudy(int inLangStudy) { mLangStudy = inLangStudy; }
	void setIntern(int inIntern) { mIntern = inIntern; }

protected:
	string mUniversity;  // 출신 대학
	string mMajor;  // 전공
	float mGpa;  // 학점
	int mToeic;  // 토익 (없는 경우 0)
	int mOpic;  // 오픽 (없는 경우 0)
	int mToeicSpeaking;  // 토스 (없는 경우 0)
	int mCertCount;  // 자격증 개수
	int mLangStudy;  // 어학연수 횟수
	int mIntern;  // 인턴 횟수
};

#endif // !SPEC_H
