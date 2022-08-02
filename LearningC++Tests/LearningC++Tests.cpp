#include "pch.h"
#include "CppUnitTest.h"
#include "SumTo.h"
#include "Templates.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LearningCTests
{
	TEST_CLASS(LearningCTests)
	{
	public:
		
		TEST_METHOD(SumTo_Success)
		{
			Assert::AreEqual(sumTo(5), 15);
		}

		TEST_METHOD(SumTo_Fail)
		{
			Assert::AreNotEqual(sumTo(10), 15);
		}

		TEST_METHOD(Max_SameTypes_Success)
		{
			const int x{ 1 };
			const int y{ 4 };

			Assert::AreEqual(max(x, y), y);
		}

		TEST_METHOD(Max_SameTypes_Fail)
		{
			const int x{ 1 };
			const int y{ 4 };

			Assert::AreNotEqual(max(x, y), x);
		}

		TEST_METHOD(Max_DifferentTypes_Success)
		{
			const int x{ 1 };
			const double y{ 4.2 };

			Assert::AreEqual(max(x, y), y);
		}

		TEST_METHOD(Max_DifferentTypes_Fail)
		{
			const int x{ 1 };
			const double y{ 4 };

			Assert::AreNotEqual(max(x, y), static_cast<double>(x));
		}
	};
}
