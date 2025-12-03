#include "pch.h"
#include "CppUnitTest.h"
#include "Set.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SetNativeTests
{
    TEST_CLASS(SetBasicTests)
    {
    public:

        TEST_METHOD(DefaultConstructor_Empty)
        {
            Set s;
            Assert::IsTrue(s.isEmpty());
            Assert::AreEqual(0, s.size());
        }

        TEST_METHOD(AddAndContainsElement)
        {
            Set s;
            s.addElement("a");
            s.addElement("b");
            s.addElement("a");

            Assert::AreEqual(2, s.size());
            Assert::IsTrue(s.containsElement("a"));
            Assert::IsTrue(s["b"]);
            Assert::IsFalse(s.containsElement("c"));
        }

        TEST_METHOD(RemoveElement)
        {
            Set s;
            s.addElement("a");
            s.addElement("b");

            Assert::IsTrue(s.removeElement("a"));
            Assert::IsFalse(s.containsElement("a"));
            Assert::AreEqual(1, s.size());

            Assert::IsFalse(s.removeElement("x"));
        }

        TEST_METHOD(CopyConstructorAndAssignment_DeepCopy)
        {
            Set s;
            s.addElement("a");
            {
                Set inner;
                inner.addElement("x");
                s.addSet(inner);
            }

            Set copy(s);
            Set assigned;
            assigned = s;
            s.addElement("b");

            Assert::IsFalse(s.isEmpty());
            Assert::IsFalse(copy.isEmpty());
            Assert::IsFalse(assigned.isEmpty());
        }


        TEST_METHOD(IsValidString_BasicCases)
        {
            Assert::IsTrue(Set::IsValidString("{a,b}"));
            Assert::IsTrue(Set::IsValidString("{{a},{b}}"));
            Assert::IsFalse(Set::IsValidString("a,b"));
            Assert::IsFalse(Set::IsValidString("{a,b"));
            Assert::IsFalse(Set::IsValidString("a,b}"));
            Assert::IsTrue(Set::IsValidString("{}{}"));
        }


        TEST_METHOD(ConstructorFromString_FlatAndNested)
        {
            Set s1("{a,b,c}");
            Assert::AreEqual(3, s1.size());
            Assert::IsTrue(s1.containsElement("a"));
            Assert::IsTrue(s1.containsElement("b"));
            Assert::IsTrue(s1.containsElement("c"));

            Set s2("{a,{b,c}}");
            Assert::AreEqual(2, s2.size());
            Assert::IsTrue(s2.containsElement("a"));
        }

        TEST_METHOD(UnionOperatorPlus)
        {
            Set a("{a,b}");
            Set b("{b,c}");

            Set c = a + b;

            Assert::IsTrue(c.containsElement("a"));
            Assert::IsTrue(c.containsElement("b"));
            Assert::IsTrue(c.containsElement("c"));
            Assert::AreEqual(3, c.size());
        }

        TEST_METHOD(UnionOperatorPlusEquals)
        {
            Set a("{a,b}");
            Set b("{b,c}");

            a += b;

            Assert::IsTrue(a.containsElement("a"));
            Assert::IsTrue(a.containsElement("b"));
            Assert::IsTrue(a.containsElement("c"));
            Assert::AreEqual(3, a.size());
        }

        TEST_METHOD(IntersectionOperatorStar)
        {
            Set a("{a,b,c}");
            Set b("{b,c,d}");

            Set c = a * b;

            Assert::IsFalse(c.containsElement("a"));
            Assert::IsTrue(c.containsElement("b"));
            Assert::IsTrue(c.containsElement("c"));
            Assert::AreEqual(2, c.size());
        }

        TEST_METHOD(IntersectionOperatorStarEquals)
        {
            Set a("{a,b,c}");
            Set b("{b,c,d}");

            a *= b;

            Assert::IsFalse(a.containsElement("a"));
            Assert::IsTrue(a.containsElement("b"));
            Assert::IsTrue(a.containsElement("c"));
            Assert::AreEqual(2, a.size());
        }

        TEST_METHOD(DifferenceOperatorMinus)
        {
            Set a("{a,b,c}");
            Set b("{b}");

            Set c = a - b;

            Assert::IsTrue(c.containsElement("a"));
            Assert::IsTrue(c.containsElement("c"));
            Assert::IsFalse(c.containsElement("b"));
            Assert::AreEqual(2, c.size());
        }

        TEST_METHOD(DifferenceOperatorMinusEquals)
        {
            Set a("{a,b,c}");
            Set b("{b}");

            a -= b;

            Assert::IsTrue(a.containsElement("a"));
            Assert::IsTrue(a.containsElement("c"));
            Assert::IsFalse(a.containsElement("b"));
            Assert::AreEqual(2, a.size());
        }

        TEST_METHOD(PowerSet_OnThreeElements)
        {
            Set s("{a,b,c}");
            Set p = s.powerSet();

            Assert::AreEqual(8, p.size());
        }
    };
}
