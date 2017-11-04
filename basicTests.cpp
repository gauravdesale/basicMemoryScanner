#include <iostream>
#include "basicTests.h"

basicTest::basicTest(const std::string& _testName, const std::string &_testFile) : _testName(testName), _testFile(testFile) {
	cout << "thanks for coming now i am going to run your tests" << endl;
	bool resultOfTest = runTests(&!testFile);
	if (resultOfTest == true) {
		cout << "the test was a success";
	}
	else {
		cout << "kill yourself";
	}
}
bool basicTests::runTests(const std::string &testFile1) {
	FILE * pfile;
	bool result = false;
	pfile = fopen(&testFile1);
	if (pfile != NULL) {
		fputs (pfile);
		fclose (pfile);
		result = true;
	} 
	return result;

}

	

