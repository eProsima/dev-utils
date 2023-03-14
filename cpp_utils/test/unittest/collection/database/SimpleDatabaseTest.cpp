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

#include <string>
#include <thread>

#include <cpp_utils/collection/database/SimpleDatabase.hpp>

namespace test {

class A
{
public:

    A(int x)
        : x_(x)
    {
    }

    virtual int get()
    {
        return x_;
    }

private:
    int x_;
};

class Key
{
public:

    Key(const char* name)
        : name_(name)
    {
    }

    virtual std::string name()
    {
        return name_;
    }

private:
    std::string name_;
};

class NonCopyable
{
public:

    NonCopyable(int x)
        : x_(x)
    {
    }

    NonCopyable(const NonCopyable&) = delete;

    int get()
    {
        return x_;
    }

private:
    int x_;
};

} // namespace test

using namespace eprosima::utils;

/**
 * Create a SimpleDatabase and expect not failures.
 *
 * CASES:
 * - string, int
 * - Key, A
 * - shared_ptr, unique_ptr
 */
TEST(SimpleDatabaseTest, create)
{
    // string, int
    {
        SimpleDatabase<std::string, int> db;
    }

    // Key, A
    {
        SimpleDatabase<test::Key, test::A> db;
    }

    // shared_ptr, unique_ptr
    {
        SimpleDatabase<std::shared_ptr<int>, std::unique_ptr<test::NonCopyable>> db;
    }
}

/**
 * Add values to a <int, int> database.
 *
 * STEPS:
 * - add N values
 * - try to add an already existant value
 */
TEST(SimpleDatabaseTest, add)
{
    SimpleDatabase<int, int> db;

    // add N values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));
    ASSERT_TRUE(db.add(1000, 1000000));

    // try to add an already existant value
    ASSERT_FALSE(db.add(1, 2));
    ASSERT_FALSE(db.add(1, 1000));
}

/**
 * Add some values to a <int, int> database and check they exist.
 *
 * STEPS:
 * - check values does not exist
 * - add values
 * - check values inserted exist
 */
TEST(SimpleDatabaseTest, is)
{
    SimpleDatabase<int, int> db;

    // check values does not exist
    ASSERT_FALSE(db.is(1));
    ASSERT_FALSE(db.is(2));
    ASSERT_FALSE(db.is(1000));

    // add values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));

    // check values inserted exist
    ASSERT_TRUE(db.is(1));
    ASSERT_TRUE(db.is(2));
    ASSERT_FALSE(db.is(1000));
}

/**
 * Add some values to a <int, int> database and retrieve them.
 *
 * STEPS:
 * - add values
 * - get values inserted
 * - try to get a value that does not exist
 */
TEST(SimpleDatabaseTest, get)
{
    SimpleDatabase<int, int> db;

    // add values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));

    // get values inserted
    ASSERT_EQ(*db.get(1), 1000);
    ASSERT_EQ(*db.get(2), 2000);

    // try to get a value that does not exist
    ASSERT_EQ(db.get(1000), nullptr);
}

/**
 * Iterate over values on an <int, int> database.
 *
 * STEPS:
 * - iterate over an empty database by loop range
 * - iterate over an empty database by begin end loop
 * - add values
 * - iterate over database and check all values are included by loop range
 * - iterate over database and check all values are included by begin end loop
 */
TEST(SimpleDatabaseTest, iterate)
{
    SimpleDatabase<int, int> db;

    // iterate over an empty database by loop range
    {
        int count = 0;
        for(const auto& v : db)
        {
            count++;
            static_cast<void>(v);
        }
        ASSERT_EQ(count, 0);
    }

    // iterate over an empty database by begin end loop
    {
        int count = 0;
        for(auto it = db.begin(); it != db.end(); it++)
        {
            count++;
            static_cast<void>(it);
        }
        ASSERT_EQ(count, 0);
    }

    // add values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));
    ASSERT_TRUE(db.add(3, 5));

    // iterate over database and check all values are included by loop range
    {
        int count = 0;
        int key_sum = 0;
        int value_sum = 0;
        for(const auto& v : db)
        {
            count++;
            key_sum += v.first;
            value_sum += v.second;
        }
        ASSERT_EQ(count, 3);
        ASSERT_EQ(key_sum, 6);
        ASSERT_EQ(value_sum, 3005);
    }

    // iterate over database and check all values are included by begin end loop
    {
        int count = 0;
        int key_sum = 0;
        int value_sum = 0;
        for(auto it = db.begin(); it != db.end(); it++)
        {
            count++;
            key_sum += it->first;
            value_sum += it->second;
        }
        ASSERT_EQ(count, 3);
        ASSERT_EQ(key_sum, 6);
        ASSERT_EQ(value_sum, 3005);
    }
}

/**
 * Add some values to a <int, int> database and then modify them.
 *
 * STEPS:
 * - add some values
 * - get them
 * - modify them
 * - get values again expecting new ones
 * - try modify a non existant value
 */
TEST(SimpleDatabaseTest, modify)
{
    SimpleDatabase<int, int> db;

    // add some values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));
    ASSERT_TRUE(db.add(3, 3000));

    // get them
    ASSERT_EQ(*db.get(1), 1000);
    ASSERT_EQ(*db.get(2), 2000);
    ASSERT_EQ(*db.get(3), 3000);

    // modify them
    ASSERT_TRUE(db.modify(1, 2000));
    ASSERT_TRUE(db.modify(2, 4000));
    ASSERT_TRUE(db.modify(3, 3000));

    // get values again expecting new ones
    ASSERT_EQ(*db.get(1), 2000);
    ASSERT_EQ(*db.get(2), 4000);
    ASSERT_EQ(*db.get(3), 3000);

    // try modify a non existant value
    ASSERT_FALSE(db.modify(4, 4000));
}

/**
 * Add some values to a <int, int> database and then remove them.
 *
 * STEPS:
 * - add some values
 * - get them
 * - remove some
 * - get values again expecting failures
 * - try remove a non existant value
 */
TEST(SimpleDatabaseTest, test_remove)
{
    SimpleDatabase<int, int> db;

    // add some values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));
    ASSERT_TRUE(db.add(3, 3000));

    // get them
    ASSERT_TRUE(db.is(1));
    ASSERT_TRUE(db.is(2));
    ASSERT_TRUE(db.is(3));

    // remove them
    ASSERT_TRUE(db.remove(1));
    ASSERT_TRUE(db.remove(2));

    // get values again expecting failures
    ASSERT_FALSE(db.is(1));
    ASSERT_FALSE(db.is(2));
    ASSERT_TRUE(db.is(3));

    // try remove a non existant value
    ASSERT_FALSE(db.remove(4));
}

/**
 * Access database from different threads at the same time
 * Create a common routine of adding a value and getting it and execute it from multiple threads.
 */
TEST(SimpleDatabaseTest, test_thread_safe)
{
    SimpleDatabase<int, int> db;

    auto routine = [&db](int i){
        ASSERT_TRUE(db.add(int(i), i*1000));
        ASSERT_TRUE(db.is(i));
        ASSERT_EQ(*db.get(i), i*1000);
    };

    std::vector<std::thread> threads(10);
    for (int i=0; i<10; i++)
    {
        threads[i] = std::thread(routine, i);
    }

    for (int i=0; i<10; i++)
    {
        threads[i].join();
    }
}

/**
 * TODO
 */
TEST(SimpleDatabaseTest, test_custom_classes)
{
    // TODO
    ASSERT_FALSE(true);
}

/**
 * TODO
 */
TEST(SimpleDatabaseTest, test_unique_ptrs)
{
    // TODO
    ASSERT_FALSE(true);
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
