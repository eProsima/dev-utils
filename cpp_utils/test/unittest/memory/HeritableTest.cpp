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

    int int_value;
};

struct TestClass
{
    TestClass()
        : int_value(42)
        , string_value("Douglas Adams")
        , vector_value({'T', 'U', 'H', 'G'})
    {
    }

    int get_int()
    {
        return int_value;
    }

    std::string get_str()
    {
        return string_value;
    }

    std::vector<char> get_vec()
    {
        return vector_value;
    }

    int int_value;
    std::string string_value;
    std::vector<char> vector_value;
};

} /* namespace test */

/**
 * TODO
 */
TEST(HeritableTest, constructor_int)
{
    {
        Heritable<int> h;
    }

    {
        Heritable<int> h(3);
        ASSERT_EQ(h.get_reference(), 3);
    }

    {
        int x = 5;
        Heritable<int> h(x);
        ASSERT_EQ(h.get_reference(), x);
    }

    {
        Heritable<int> h(new int(7));
        ASSERT_EQ(h.get_reference(), 7);
    }
}

/**
 * TODO
 */
TEST(HeritableTest, constructor_string)
{
    // Default constructor
    {
        Heritable<std::string> h;
        ASSERT_EQ(h.get_reference(), "");
    }

    // Construct from const char *
    {
        Heritable<std::string> h("Hello");
        ASSERT_EQ(h.get_reference(), "Hello");
    }

    // Construct by loop
    {
        Heritable<std::string> h(5, '=');
        ASSERT_EQ(h.get_reference(), "=====");
    }

    // Construct by copy
    {
        std::string x = "Yeah!";
        Heritable<std::string> h(x);
        ASSERT_EQ(h.get_reference(), x);
    }

    // Construct by movement
    {
        std::string x = "012345678901234567890123456789";
        Heritable<std::string> h(std::move(x));
        ASSERT_EQ(h.get_reference(), "012345678901234567890123456789");
    }

    // Construct by pointer
    {
        Heritable<std::string> h(new std::string("Yass"));
        ASSERT_EQ(h.get_reference(), "Yass");
    }

    // Construct by coping other heritable
    {
        Heritable<std::string> origin("Hola");
        Heritable<std::string> nova(origin);
        ASSERT_EQ(origin.get_reference(), nova.get_reference());
    }

    // Construct by moving other heritable
    {
        Heritable<std::string> origin("abcdefghijklmnopqrstuvwxyz");
        Heritable<std::string> nova(std::move(origin));
        ASSERT_NE(origin.get_reference(), nova.get_reference());
        ASSERT_EQ(nova.get_reference(), "abcdefghijklmnopqrstuvwxyz");
    }

    // Construct by copying operator from other heritable
    {
        Heritable<std::string> origin("Salut");
        Heritable<std::string> nova("Some other str");
        nova = origin;
        ASSERT_EQ(origin.get_reference(), nova.get_reference());
    }

    // Construct by moving operator from other heritable
    {
        Heritable<std::string> origin("-abcdefghijklmnopqrstuvwxyz-");
        Heritable<std::string> nova("Some other str");
        nova = std::move(origin);
        ASSERT_NE(origin.get_reference(), nova.get_reference());
        ASSERT_EQ(nova.get_reference(), "-abcdefghijklmnopqrstuvwxyz-");
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
