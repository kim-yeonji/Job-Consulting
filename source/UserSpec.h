#ifndef USERSPEC_H
#define USERSPEC_H

#include <string>

#include "Spec.h"

using namespace std;

class UserSpec : public Spec {
public:
	UserSpec();  // class constructor
	~UserSpec() {}  // class destructor

	// getter
	string getAccountID() { return mAccountID; }

	// setter
	void setAccountID(string inAccountID) { mAccountID = inAccountID; }

protected:
	string mAccountID;  // 계정 ID
};

#endif // !USERSPEC_H