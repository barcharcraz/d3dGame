///-------------------------------------------------------------------------------------------------
// file:	MSPropertyTests.cpp
//
// summary:	Tests to insure that the macros defined for properties work corectly
///-------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "CppUnitTest.h"
#include <Property.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WinLibTests
{
	TEST_CLASS(MSPropertyTests)
	{
	private:
		int _test;
	public:
		PROPERTY(int, test);
		GET(test)
		{
			return _test;
		}
		SET(test)
		{
			_test = value;
		}
		TEST_METHOD(MSPropertyMacroTest1)
		{
			test = 4;
			Assert::AreEqual(4, test);
		}

	};
}