#include "pch.h"
#include "CppUnitTest.h"
#include "../LAB2/Source.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LAB2TESTS
{
	TEST_CLASS(LAB2TESTS)
	{
	public:
		
		TEST_METHOD(Testting_no_solution)
		{
			Logger::WriteMessage(L"Test Testting_no_solution");
			Assert::IsTrue(calculate(0, 0, 0, 0, 2, 3) == "0", L"Assert 1");
			Logger::WriteMessage(L"Assert 1 (0, 0, 0, 0, 2, 3) [a=b=c=d=0 e,f!=0] passed!");
			Assert::IsTrue(calculate(-4, -4, -5, -5, 0, 1) == "0", L"Assert 2");
			Logger::WriteMessage(L"Assert 2 (-4, -4, -5, -5, 0, 1) [a=b=c=d=0<0 e,f!=0] passed!");
			Assert::IsTrue(calculate(1, 1, 100, 100, 10, 1) == "0", L"Assert 3");
			Logger::WriteMessage(L"Assert 3 (1, 1, 100, 100, 10, 1) [a=b,c=d a<b e>f] passed!");
			Assert::IsTrue(calculate(0.5, 0.5, 0.5, 0.5, -0.5, +0.5) == "0", L"Assert 4");
			Logger::WriteMessage(L"Assert 4 (0.5, 0.5, 0.5, 0.5, -0.5, +0.5) [a=b=c=d e!=f] passed!");
			Assert::IsTrue(calculate(1, 1, -1, -1, 100, 100) == "0", L"Assert 5");
			Logger::WriteMessage(L"Assert 5 (1, 1, -1, -1, 100, 100) [a=b=-c=-d e=f] passed!");
		}

		TEST_METHOD(Testting_infinity_solutions)
		{
			Logger::WriteMessage(L"Test Testting_infinity_solution");
			Assert::IsTrue(calculate(1, 1, 1, 1, 1, 1) == "1 " + std::to_string(-1.0) + " " + std::to_string(1.0), L"Assert 1");
			Logger::WriteMessage(L"Assert 1 (1, 1, 1, 1, 1, 1) [y = -x+1] passed!");
			Assert::IsTrue(calculate(-10, 1, -10, 1, 20, 20) == "1 " + std::to_string(10.0) + " " + std::to_string(20.0), L"Assert 2");
			Logger::WriteMessage(L"Assert 2 (-10, 1, -10, 1, 20, 20) [y = 10x+20] passed!");
			Assert::IsTrue(calculate(1, 0, 1, 0, 0, 0) == "3 " + std::to_string(0.0), L"Assert 3");
			Logger::WriteMessage(L"Assert 3 (1, 0, 1, 0, 0, 0) [x=x0=0 y=any] passed!");
			Assert::IsTrue(calculate(0, 1, 0, 1, 0, 0) == "4 " + std::to_string(0.0), L"Assert 4");
			Logger::WriteMessage(L"Assert 4 (0, 1, 0, 1, 0, 0) [y=y0=0 x=any] passed!");
			Assert::IsTrue(calculate(0, 0, 0, 0, 0, 0) == "5", L"Assert 5");
			Logger::WriteMessage(L"Assert 5 (0, 0, 0, 0, 0, 0) [any pair (x,y)] passed!");
		}

		TEST_METHOD(Testting_one_solution)
		{
			Logger::WriteMessage(L"Test Testting_one_solution");
			Assert::IsTrue(calculate(1, 2, 3, 1, 2, 3) == "2 " + std::to_string(0.8) + " " + std::to_string(0.6), L"Assert 1");
			Logger::WriteMessage(L"Assert 1 (1, 2, 3, 1, 2, 3) passed");
			Assert::IsTrue(calculate(3, 3, 0, 3, 18, 9) == "2 " + std::to_string(3.0) + " " + std::to_string(3.0), L"Assert 2");
			Logger::WriteMessage(L"Assert 2 (3, 3, 3, 0, 18, 9) passed");
			Assert::IsTrue(calculate(0, 3, 3, 3, 9, 18) == "2 " + std::to_string(3.0) + " " + std::to_string(3.0), L"Assert 3");
			Logger::WriteMessage(L"Assert 3 (0, 3, 3, 3, 9, 18) passed");
			Assert::IsTrue(calculate(1, 2, 2, 1, 5, 4) == "2 " + std::to_string(1.0) + " " + std::to_string(2.0), L"Assert 4");
			Logger::WriteMessage(L"Assert 4 (1, 2, 2, 1, 5, 4) passed");
			Assert::IsTrue(calculate(13, 2, -1, 1, -11, 2) == "2 " + std::to_string(-1.0) + " " + std::to_string(1.0), L"Assert 5");
			Logger::WriteMessage(L"Assert 5 (13, 2, -1, 1, -11, 2) passed");
			
		}
	};
}
