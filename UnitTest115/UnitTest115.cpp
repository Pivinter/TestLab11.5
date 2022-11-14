#include "pch.h"
#include "CppUnitTest.h"
#include "../TestLab11.5/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest115
{
	TEST_CLASS(UnitTest115)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int t;
			t = main();
			Assert::AreEqual(t, 0);
		}
	};
}
