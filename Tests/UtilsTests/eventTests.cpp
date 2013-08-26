#include <gtest/gtest.h>
#include <Utils/event.h>

namespace {
	class TestTarget {
	public:
		TestTarget() : num(0) {};
		void addOne() {
			num++;
		}
		int num;
	};
	TEST(eventsTest, testCallVoid) {
		
		utils::Slot<void()> sl;
		int test = 0;
		sl.connect([&](){test = 1; });
		sl();
		ASSERT_EQ(test, 1);
	}
	TEST(eventsTest, testCallArgs) {
		utils::Slot<void(int, int, int&)> sl;
		int foo = 8;
		int bar = 4;
		int out = 0;
		sl.connect([](int a, int b, int& c){c = a + b; });
		sl(foo, bar, out);
		ASSERT_EQ(out, foo + bar);
	}
	TEST(eventsTest, testMemBind) {
		utils::Slot<void()> sl;
		TestTarget targ;
		ASSERT_EQ(targ.num, 0);
		sl.connect(&TestTarget::addOne, &targ);
		sl();
		ASSERT_EQ(targ.num, 1);
	}
	TEST(eventsTest, testMulticast) {
		utils::Slot < void() > sl;
		int test1 = 0;
		int test2 = 0;
		sl.connect([&](){test1 = 1; });
		sl.connect([&](){test2 = 1; });
		sl();
		ASSERT_EQ(test1, 1);
		ASSERT_EQ(test2, 1);
	}
}