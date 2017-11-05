#pragma once 
#include "LuaEngine.h"
//this is one file will be implemented later 
#include <lists>

class basesTest {
	public:
		basesTest(const std::string& _testName);
		virtual ~basesTest();
		virtual bool runTest(const LuaEngine &engine);
		static void runAllTests(const LuaEngine &engine);
	private:
		std::string<int*> testName;
		static std::list<basesTest*> lists;
		TestBase(const basesTest&);
		void operator=(const basesTest&);
		void operator^(const basesTest&);
};
	
