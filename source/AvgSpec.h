#ifndef AVGSPEC_H
#define AVGSPEC_H

class AvgSpec {
public:
	AvgSpec();  // class constructor
	~AvgSpec() {}  // class destructor

	// getter
	float getGpa() { return mGpa; }
	float getToeic() { return mToeic; }
	float getOpic() { return mOpic; }
	float getToeicSpeaking() { return mToeicSpeaking; }
	float getCertCount() { return mCertCount; }
	float getLangStudy() { return mLangStudy; }
	float getIntern() { return mIntern; }
	float getScore() { return mScore; }

	// setter
	void setGpa(float inGpa) { mGpa = inGpa; }
	void setToeic(float inToeic) { mToeic = inToeic; }
	void setOpic(float inOpic) { mOpic = inOpic; }
	void setToeicSpeaking(float inToeicSpeaking) { mToeicSpeaking = inToeicSpeaking; }
	void setCertCount(float inCertCount) { mCertCount = inCertCount; }
	void setLangStudy(float inLangStudy) { mLangStudy = inLangStudy; }
	void setIntern(float inIntern) { mIntern = inIntern; }
	void setScore(float inScore) { mScore = inScore; }

protected:
	float mGpa;  // 학점
	float mToeic;  // 토익
	float mOpic;  // 오픽
	float mToeicSpeaking;  // 토스
	float mCertCount;  // 자격증 개수
	float mLangStudy;  // 어학연수 횟수
	float mIntern;  // 인턴 횟수
	float mScore; //대학 평점
};

#endif // !AVGSPEC_H
