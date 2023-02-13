// Copyright 2023 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cpp_utils/testing/gtest_aux.hpp>
#include <gtest/gtest.h>

#include <cpp_utils/memory/Heritable.hpp>

using namespace eprosima::utils;

namespace test {

struct Parent
{
    Parent(int x)
        : int_value(x)
    {
    }

    Parent()
        : Parent(0)
    {
    }

    Parent(const Parent& other)
        : Parent(other.int_value)
    {
    }

    Parent& operator =(const Parent& other)
    {
        int_value = other.int_value;
        return *this;
    }

    bool operator ==(const Parent& other) const
    {
        return other.get_int() == this->get_int();
    }

    bool operator <(const Parent& other) const
    {
        return other.get_int() < this->get_int();
    }

    virtual int get_int() const
    {
        return int_value;
    }

    bool greater_than_10() const
    {
        return get_int() > 10;
    }

    int int_value;
};

struct Child_A : public Parent
{
    Child_A(int y)
        : Parent(10)
        , other_value(y)
    {
    }

    Child_A()
        : Child_A(1)
    {
    }

    virtual int get_int() const override
    {
        return Parent::get_int() + other_value;
    }

    int other_value;
};

struct Child_B : public Parent
{
    Child_B(int y)
        : Parent(2)
        , other_value(y)
    {
    }

    Child_B()
        : Child_B(1)
    {
    }

    virtual int get_int() const override
    {
        return Parent::get_int() * other_value;
    }

    int other_value;
};

} /* namespace test */

/**
 * TODO
 */
TEST(HeritableTest, constructor_int)
{
    // From ptr
    {
        Heritable<int> h(new int(1));
        ASSERT_EQ(h.get_reference(), 1);
    }

    // From make_heriable
    {
        Heritable<int> h = Heritable<int>::make_heritable(2);
        ASSERT_EQ(h.get_reference(), 2);
    }
}

/**
 * TODO
 */
// TEST(HeritableTest, constructor_string)
// {
//     // Default constructor
//     {
//         Heritable<std::string> h;
//         ASSERT_EQ(h.get_reference(), "");
//     }

//     // Construct from const char *
//     {
//         Heritable<std::string> h("Hello");
//         ASSERT_EQ(h.get_reference(), "Hello");
//     }

//     // Construct by loop
//     {
//         Heritable<std::string> h(5, '=');
//         ASSERT_EQ(h.get_reference(), "=====");
//     }

//     // Construct by copy
//     {
//         std::string x = "Yeah!";
//         Heritable<std::string> h(x);
//         ASSERT_EQ(h.get_reference(), x);
//     }

//     // Construct by movement
//     {
//         std::string x = "012345678901234567890123456789";
//         Heritable<std::string> h(std::move(x));
//         ASSERT_EQ(h.get_reference(), "012345678901234567890123456789");
//     }

//     // Construct by pointer
//     {
//         Heritable<std::string> h(new std::string("Yass"));
//         ASSERT_EQ(h.get_reference(), "Yass");
//     }

//     // Construct by coping other heritable
//     {
//         Heritable<std::string> origin("Hola");
//         Heritable<std::string> nova(origin);
//         ASSERT_EQ(origin.get_reference(), nova.get_reference());
//     }

//     // Construct by moving other heritable
//     {
//         Heritable<std::string> origin("abcdefghijklmnopqrstuvwxyz");
//         Heritable<std::string> nova(std::move(origin));
//         ASSERT_NE(origin.get_reference(), nova.get_reference());
//         ASSERT_EQ(nova.get_reference(), "abcdefghijklmnopqrstuvwxyz");
//     }

//     // Construct by copying operator from other heritable
//     {
//         Heritable<std::string> origin("Salut");
//         Heritable<std::string> nova("Some other str");
//         nova = origin;
//         ASSERT_EQ(origin.get_reference(), nova.get_reference());
//     }

//     // Construct by moving operator from other heritable
//     {
//         Heritable<std::string> origin("-abcdefghijklmnopqrstuvwxyz-");
//         Heritable<std::string> nova("Some other str");
//         nova = std::move(origin);
//         ASSERT_NE(origin.get_reference(), nova.get_reference());
//         ASSERT_EQ(nova.get_reference(), "-abcdefghijklmnopqrstuvwxyz-");
//     }
// }

/**
 * TODO
 */
TEST(HeritableTest, ptr_operator_parent)
{
    // ->
    {
        Heritable<test::Parent> h(Heritable<test::Parent>::make_heritable(4));
        ASSERT_EQ(h->get_int(), 4);
        ASSERT_FALSE(h->greater_than_10());
    }

    // *
    {
        Heritable<test::Parent> h(Heritable<test::Parent>::make_heritable(11));
        ASSERT_EQ((*h).get_int(), 11);
        ASSERT_TRUE((*h).greater_than_10());
    }
}

/**
 * TODO
 */
// TEST(HeritableTest, compare_operator_parent)
// {
//     // == heritable true
//     {
//         Heritable<test::Parent> h1(1);
//         Heritable<test::Parent> h2(1);
//         ASSERT_TRUE(h1.operator==(h2));
//     }

//     // == heritable false
//     {
//         Heritable<test::Parent> h1(1);
//         Heritable<test::Parent> h2(2);
//         ASSERT_FALSE(h1.operator==(h2));
//     }

//     // == object true
//     {
//         Heritable<test::Parent> h1(1);
//         test::Parent p(1);
//         ASSERT_TRUE(h1.operator==(p));
//     }

//     // == object false
//     {
//         Heritable<test::Parent> h1(1);
//         test::Parent p(2);
//         ASSERT_FALSE(h1.operator==(p));
//     }

//     // < heritable true
//     {
//         Heritable<test::Parent> h1(0);
//         Heritable<test::Parent> h2(1);
//         ASSERT_TRUE(h1.operator<(h2));
//     }

//     // < heritable false
//     {
//         Heritable<test::Parent> h1(0);
//         Heritable<test::Parent> h2(-1);
//         ASSERT_FALSE(h1.operator<(h2));
//     }

//     // < object true
//     {
//         Heritable<test::Parent> h1(1);
//         test::Parent p(2);
//         ASSERT_TRUE(h1.operator<(p));
//     }

//     // < object false
//     {
//         Heritable<test::Parent> h1(1);
//         test::Parent p(0);
//         ASSERT_FALSE(h1.operator<(p));
//     }
// }

/**
 * TODO
 */
TEST(HeritableTest, access_data_methods_parent)
{
    // get_reference
    {
        test::Parent p = test::Parent(11);
        Heritable<test::Parent> h(Heritable<test::Parent>::make_heritable(p));
        test::Parent& p_ref = h.get_reference();
        ASSERT_TRUE(p_ref.operator==(p));
        ASSERT_NE(&p_ref, &p);
    }
}

/**
 * TODO
 */
// TEST(HeritableTest, cast_operator)
// {
//     // cast to itself
//     {
//         Heritable<test::Parent> h(11);
//         test::Parent& p = h;
//         ASSERT_TRUE(p.greater_than_10());
//         ASSERT_EQ(p.get_int(), 11);
//     }

//     // Cast to parent
//     {
//         Heritable<test::Child_A> h;
//         ASSERT_TRUE(h->greater_than_10());
//         test::Parent& p_ref = h;
//         ASSERT_TRUE(p_ref.greater_than_10());

//         // Create a child from child conserves value
//         test::Child_A a = reinterpret_cast<test::Child_A&>(p_ref);
//         ASSERT_TRUE(p_ref.greater_than_10());

//         // Create a parent from child does not conserve value
//         test::Parent p = p_ref;
//         ASSERT_FALSE(p.greater_than_10());
//     }
// }

/**
 * TODO
 */
// TEST(HeritableTest, cast_methods)
// {
//     // Cast to parent
//     {
//         Heritable<test::Child_A> h(Heritable<test::Child_A>::make_heritable());
//         ASSERT_TRUE(h->greater_than_10());

//         ASSERT_TRUE(h.can_cast<test::Parent>());
//         Heritable<test::Parent> p = h.dyn_cast<test::Parent>();
//         ASSERT_TRUE(p->greater_than_10());

//         // Create a child from child conserves value
//         test::Child_A a = dynamic_cast<test::Child_A&>(p.get_reference());
//         ASSERT_TRUE(a.greater_than_10());

//         // Create a parent from child does not conserve value
//         test::Parent p_ = p.get_reference();
//         ASSERT_FALSE(p_.greater_than_10());
//     }
// }

/**
 * TODO
 */
// TEST(HeritableTest, cast_methods_negative)
// {
//     // cast from parent to child
//     {
//         Heritable<test::Parent> h(Heritable<test::Parent>::make_heritable());
//         ASSERT_FALSE(h.can_cast<test::Child_A>());
//         ASSERT_THROW(
//             h.dyn_cast<test::Child_A>(),
//             std::bad_cast);
//     }

//     // cast from child A to child B
//     {
//         Heritable<test::Child_A> h(Heritable<test::Child_A>::make_heritable());;
//         ASSERT_FALSE(h.can_cast<test::Child_B>());
//         ASSERT_THROW(
//             h.dyn_cast<test::Child_B>(),
//             std::bad_cast);
//     }
// }

/**
 * TODO
 */
TEST(HeritableTest, inheritance_set_test)
{
    std::set<Heritable<test::Parent>> p_set;

    // Add a Parent value
    Heritable<test::Parent> p1(Heritable<test::Parent>::make_heritable(1));
    logError(DEBUG, "0");
    ASSERT_EQ(p_set.find(p1), p_set.end());
    p_set.insert(p1);
    ASSERT_NE(p_set.find(p1), p_set.end());

    logError(DEBUG, "1");

    // Add another Parent value created in call
    ASSERT_EQ(p_set.find(Heritable<test::Parent>::make_heritable(2)), p_set.end());
    p_set.insert(Heritable<test::Parent>::make_heritable(2));
    ASSERT_NE(p_set.find(Heritable<test::Parent>::make_heritable(2)), p_set.end());

    logError(DEBUG, "2");

    // Add a child A value
    Heritable<test::Child_A> a3(Heritable<test::Child_A>::make_heritable(3));
    logError(DEBUG, "3");
    ASSERT_EQ(p_set.find(a3), p_set.end());
    p_set.insert(a3);
    ASSERT_NE(p_set.find(a3), p_set.end());

    logError(DEBUG, "4");

    // // Add another child A value
    // test::Child_A a2(5);
    // auto it = p_set.find(a2);

    // std::cout << (*it)->get_int() << std::endl;

    // ASSERT_EQ(p_set.find(a2), p_set.end());
    // p_set.insert(a2);
    // ASSERT_NE(p_set.find(test::Child_A(5)), p_set.end());
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
