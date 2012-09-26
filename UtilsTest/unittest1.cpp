#include "stdafx.h"
#include "CppUnitTest.h"
#include <fib.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UtilsTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Fib0)
		{
			Assert::AreEqual(fib(0),1);
		}
		TEST_METHOD(Fib1)
		{
			Assert::AreEqual(fib(1),1);
		}
		TEST_METHOD(Fib2)
		{
			Assert::AreEqual(fib(2),2);
		}
		TEST_METHOD(Fib3)
		{
			Assert::AreEqual(fib(3),3);
		}
		TEST_METHOD(Fib4)
		{
			Assert::AreEqual(fib(4),5);
		}
		TEST_METHOD(Fib5)
		{
			Assert::AreEqual(fib(5),8);
		}
		


	};
}