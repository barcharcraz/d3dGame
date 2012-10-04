#include "stdafx.h"
#include "CppUnitTest.h"
#include <strcmp.cpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilsTest
{
	TEST_CLASS(strcmpTest)
	{
	public:
		
		TEST_METHOD(strcmp1)
		{
			char * t1 = "test";
			char * t2 = "test";
			Assert::AreEqual(scratch::strcmp(t1, t2),0);
		}

	};
}