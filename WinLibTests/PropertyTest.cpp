#include "stdafx.h"
#include "CppUnitTest.h"
#include <Property.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WinLibTests
{		
	TEST_CLASS(PropertyTest)
	{
	public:
		
		TEST_METHOD(NewPropTest)
		{
			Property<int> prop(6);
			Assert::AreEqual(6, prop.propValue);
		}
		TEST_METHOD(PropAssignTest)
		{
			Property<int> prop1(6);
			Property<int> prop2(7);
			prop1=prop2;
			Assert::AreEqual(prop1.propValue, prop2.propValue);
		}
		TEST_METHOD(PropEqualityTest)
		{
			Property<int> prop1(12);
			Property<int> prop2(12);
			Assert::AreEqual(prop1,prop2);
		}
		TEST_METHOD(propPrimitiveAssignment)
		{
			Property<int> prop1(12);
			prop1 = 13;
			Assert::AreEqual(prop1.propValue, 13);
		}
		TEST_METHOD(propPrimitiveEquality)
		{
			Property<int> prop1(12);
			Assert::IsTrue(prop1 == 12);
		}
	};
}