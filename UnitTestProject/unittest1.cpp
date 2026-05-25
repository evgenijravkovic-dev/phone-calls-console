
#include "CppUnitTest.h"
#include "book_subscription.h"
#include "processing.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestProject
{
    TEST_CLASS(PhoneCallTests)
    {
    public:
        TEST_METHOD(TestOneCall)
        {
            PhoneCall calls[1] = {};
            strcpy_s(calls[0].duration, "00:02:00");
            calls[0].costPerMinute = 3.0;

            double result = calculateAverageCostPerSecond(calls, 1);
            Assert::AreEqual(0.05, result, 0.0001);
        }

        TEST_METHOD(TestTwoCalls)
        {
            PhoneCall calls[2] = {};
            strcpy_s(calls[0].duration, "00:01:00");
            calls[0].costPerMinute = 2.0;
            strcpy_s(calls[1].duration, "00:02:00");
            calls[1].costPerMinute = 5.0;

            double result = calculateAverageCostPerSecond(calls, 2);
            Assert::AreEqual(0.066666, result, 0.0001);
        }

        TEST_METHOD(TestEmptyArray)
        {
            double result = calculateAverageCostPerSecond(nullptr, 0);
            Assert::AreEqual(0.0, result, 0.0001);
        }
    };
}