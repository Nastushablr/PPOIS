#include "pch.h"
#include "CppUnitTest.h"
#include "Rectangle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RectangleNativeTests
{
    TEST_CLASS(RectangleTests)
    {
    public:

        TEST_METHOD(ConstructorAndMove)
        {
            Rectangle r(1, 2, 3, 4);
            r.move(5, -1);
            Rectangle expected(6, 1, 8, 3);
            Assert::IsTrue(r == expected);
        }

        TEST_METHOD(ResizeAndEquality)
        {
            Rectangle r(1, 2, 3, 4);
            r.resize(2, -1);
            Rectangle expected(1, 2, 5, 3);

            Assert::IsTrue(r == expected);
            Assert::IsFalse(r != expected);
        }

        TEST_METHOD(IncrementDecrement)
        {
            Rectangle r(0, 0, 1, 1);

            Rectangle& prefInc = ++r;
            Assert::IsTrue(&prefInc == &r);
            Assert::IsTrue(r == Rectangle(0, 0, 2, 2));

            Rectangle postInc = r++;
            Assert::IsTrue(postInc == Rectangle(0, 0, 2, 2));
            Assert::IsTrue(r == Rectangle(0, 0, 3, 3));

            Rectangle& prefDec = --r;
            Assert::IsTrue(&prefDec == &r);
            Assert::IsTrue(r == Rectangle(0, 0, 2, 2));

            Rectangle postDec = r--;
            Assert::IsTrue(postDec == Rectangle(0, 0, 2, 2));
            Assert::IsTrue(r == Rectangle(0, 0, 1, 1));
        }

        TEST_METHOD(PlusMinusOperators)
        {
            Rectangle a(0, 0, 2, 2);
            Rectangle b(1, 1, 3, 3);

            Rectangle u = a + b;
            Assert::IsTrue(u == Rectangle(0, 0, 3, 3));

            Rectangle inter = a - b;
            Assert::IsTrue(inter == Rectangle(1, 1, 2, 2));

            Rectangle dis1(0, 0, 1, 1);
            Rectangle dis2(2, 2, 3, 3);
            Rectangle empty = dis1 - dis2;
            Assert::IsTrue(empty == Rectangle(0, 0, 0, 0));
        }

        TEST_METHOD(PlusEqualsMinusEquals)
        {
            Rectangle a(0, 0, 2, 2);
            Rectangle b(1, 1, 3, 3);

            a += b;
            Assert::IsTrue(a == Rectangle(0, 0, 3, 3));

            a -= b;
            Assert::IsTrue(a == Rectangle(1, 1, 3, 3));
        }
    };
}

