#pragma once
#include "basesTest.h"

#include <string>

class basicTests : basesTest {
	public:
		basicTests(const std::string& testName, const std::wstring &testFile);
		~basicTests();
		bool runTest();//add an object parameter here later 
	private:
		std::wstring testFile;
};
