// Copyright 2018 Minkyu Jo

#include "typing_machine.h"
#include "typing_machine_test.h"
#include "test.h"

class TmConstructorTestSuite
{
private:
    static void BarSeparatorTest() {
        TypingMachine tm;
        ASSERT_EQ(tm.Print('|'), std::string("|"));
        ASSERT_EQ(tm.EraseKey(), false);
        tm.LeftKey();
        ASSERT_EQ(tm.Print('|'), std::string("|"));
        tm.RightKey();
        ASSERT_EQ(tm.Print('|'), std::string("|"));
    }

    static void TypeKeyTest() {
        TypingMachine tm;
        ASSERT_EQ(tm.TypeKey('A'), true);
        ASSERT_EQ(tm.Print('|'), std::string("A|"));
        ASSERT_EQ(tm.TypeKey('B'), true);
        ASSERT_EQ(tm.Print('|'), std::string("AB|"));

        tm.LeftKey();
        ASSERT_EQ(tm.Print('|'), std::string("A|B"));
        tm.LeftKey();
        ASSERT_EQ(tm.Print('|'), std::string("|AB"));
        tm.LeftKey();
        ASSERT_EQ(tm.Print('|'), std::string("|AB"));

        tm.RightKey();
        ASSERT_EQ(tm.Print('|'), std::string("A|B"));
        tm.RightKey();
        ASSERT_EQ(tm.Print('|'), std::string("AB|"));
        tm.RightKey();
        ASSERT_EQ(tm.Print('|'), std::string("AB|"));

        tm.HomeKey();
        ASSERT_EQ(tm.Print('|'), std::string("|AB"));
        tm.HomeKey();
        ASSERT_EQ(tm.Print('|'), std::string("|AB"));

        tm.EndKey();
        ASSERT_EQ(tm.Print('|'), std::string("AB|"));
        tm.EndKey();
        ASSERT_EQ(tm.Print('|'), std::string("AB|"));

        tm.LeftKey();
        ASSERT_EQ(tm.Print('|'), std::string("A|B"));
        ASSERT_EQ(tm.TypeKey('C'), true);
        ASSERT_EQ(tm.Print('|'), std::string("AC|B"));

        ASSERT_EQ(tm.Print(0), std::string("ACB"));
    }

    static void TypeManyKeyTest() {
        TypingMachine tm;
        std::string result;

        // type 99 characters
        for (int i=0; i<99; i++) {
            tm.TypeKey('A');
            result += 'A';
        }
        ASSERT_EQ(tm.Print(';'), result + ';');

        // 100th character should be OK
        ASSERT_EQ(tm.TypeKey('A'), true);
        result += 'A';
        ASSERT_EQ(tm.Print(';'), result + ';');

        // 101th character should be rejected
        ASSERT_EQ(tm.TypeKey('A'), false);
        ASSERT_EQ(tm.Print(';'), result + ';');
    }

    static void EraseKeyTest() {
        TypingMachine tm;
        tm.TypeKey('A');
        tm.TypeKey('B');
        tm.TypeKey('C');
        ASSERT_EQ(tm.Print(';'), "ABC;");

        ASSERT_EQ(tm.EraseKey(), true);
        ASSERT_EQ(tm.Print(';'), "AB;");

        tm.TypeKey('C');
        ASSERT_EQ(tm.Print(';'), "ABC;");
        tm.LeftKey();
        ASSERT_EQ(tm.Print(';'), "AB;C");
        ASSERT_EQ(tm.EraseKey(), true);
        ASSERT_EQ(tm.Print(';'), "A;C");
        ASSERT_EQ(tm.EraseKey(), true);
        ASSERT_EQ(tm.Print(';'), ";C");
        ASSERT_EQ(tm.EraseKey(), false);
        ASSERT_EQ(tm.Print(';'), ";C");
    }

public:
    static void RunTest() {
        BarSeparatorTest();
        TypeKeyTest();
        TypeManyKeyTest();
        EraseKeyTest();
    }
};

class SomeOtherTestSuite
{
private:

public:
  static void RunTest() {
    // add more..
  }
};

void TypingMachineTest() {
  TmConstructorTestSuite::RunTest();
  // add more..
}
