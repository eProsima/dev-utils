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
#include <cpp_utils/time/time_utils.hpp>
#include <cpp_utils/wait/BooleanWaitHandler.hpp>

namespace test {

class A
{
public:

    A(int x)
        : x_(x)
    {
    }

    bool operator==(const A& other) const
    {
        return this->get() == other.get();
    }

    virtual int get() const
    {
        return x_;
    }

private:
    int x_;
};

class Aplus5 : public A
{
public:
    Aplus5(int x)
        : A(x + 5)
    {
    }
};

class Aminus5 : public A
{
public:
    Aminus5(int x)
        : A(x - 5)
    {
    }
};

class Key
{
public:

    Key(const char* name)
        : name_(name)
    {
    }

    bool operator<(const Key& other) const
    {
        return name_ < other.name();
    }

    virtual std::string name() const
    {
        return name_;
    }

private:
    std::string name_;
};

class NonCopyable
{
public:

    NonCopyable(const char* name)
        : name_(name)
    {
    }

    NonCopyable(const NonCopyable&) = delete;

    NonCopyable(NonCopyable&& other)
        : name_(std::move(other.name_))
    {
    }

    bool operator<(const NonCopyable& other) const
    {
        return name_ < other.name();
    }

    virtual std::string name() const
    {
        return name_;
    }

private:
    std::string name_;
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
 * Add some values to a <int, int> database and find them.
 *
 * STEPS:
 * - add values
 * - find values
 * - find a non existant value
 */
TEST(SimpleDatabaseTest, find)
{
    SimpleDatabase<int, int> db;

    // add values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));

    // find values
    auto it1 = db.find(1);
    ASSERT_EQ(it1->first, 1);
    ASSERT_EQ(it1->second, 1000);

    auto it2 = db.find(2);
    ASSERT_EQ(it2->first, 2);
    ASSERT_EQ(it2->second, 2000);

    // try to get a value that does not exist
    auto it_n = db.find(3);
    ASSERT_EQ(it_n, db.end());
}

/**
 * Add some values to a <int, int> database and retrieve them.
 *
 * STEPS:
 * - add values
 * - get values inserted
 * - try to get a value that does not exist
 */
TEST(SimpleDatabaseTest, at)
{
    SimpleDatabase<int, int> db;

    // add values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));

    // get values inserted
    ASSERT_EQ(db.at(1), 1000);
    ASSERT_EQ(db.at(2), 2000);

    // try to get a value that does not exist
    ASSERT_THROW(db.at(1000), std::out_of_range);
}

/**
 * Add some values to a <int, int> database and check size
 *
 * STEPS:
 * - get size
 * - add values
 * - get size
 * - remove values
 * - get size
 */
TEST(SimpleDatabaseTest, size)
{
    SimpleDatabase<int, int> db;

    // get size
    ASSERT_EQ(db.size(), 0u);

    // add values
    ASSERT_TRUE(db.add(1, 1000));
    ASSERT_TRUE(db.add(2, 2000));

    // get size
    ASSERT_EQ(db.size(), 2u);

    // remove values
    ASSERT_TRUE(db.erase(1));

    // get size
    ASSERT_EQ(db.size(), 1u);
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
        for(auto it = db.begin(); it != db.end(); ++it)
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
        for(auto it = db.begin(); it != db.end(); ++it)
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
    ASSERT_EQ(db.at(1), 1000);
    ASSERT_EQ(db.at(2), 2000);
    ASSERT_EQ(db.at(3), 3000);

    // modify them
    ASSERT_TRUE(db.modify(1, 2000));
    ASSERT_TRUE(db.modify(2, 4000));
    ASSERT_TRUE(db.modify(3, 3000));

    // get values again expecting new ones
    ASSERT_EQ(db.at(1), 2000);
    ASSERT_EQ(db.at(2), 4000);
    ASSERT_EQ(db.at(3), 3000);

    // try modify a non existant value
    ASSERT_FALSE(db.modify(4, 4000));
}

/**
 * Add some values to a <int, int> database and then erase them.
 *
 * STEPS:
 * - add some values
 * - get them
 * - erase some
 * - get values again expecting failures
 * - try erase an already erased value
 * - try erase a non existant value
 */
TEST(SimpleDatabaseTest, test_erase)
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

    // erase them
    ASSERT_TRUE(db.erase(1));
    ASSERT_TRUE(db.erase(2));

    // get values again expecting failures
    ASSERT_FALSE(db.is(1));
    ASSERT_FALSE(db.is(2));
    ASSERT_TRUE(db.is(3));

    // try erase an already erased value
    ASSERT_FALSE(db.erase(1));

    // try erase a non existant value
    ASSERT_FALSE(db.erase(4));
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
        ASSERT_EQ(db.at(i), i*1000);

        int sum = 0;
        for (const auto& it : db)
        {
            sum += it.second;
        }
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
 * Test functions of database for class Key and A.
 *
 * STEPS:
 * - add values
 * - try add value already in database
 * - check values exist
 * - get values
 * - modify values
 * - try modify non existent value
 * - get values
 * - remove values
 * - try remove already removed value
 * - get values
 * - add more values
 * - check values exist
 */
TEST(SimpleDatabaseTest, test_custom_classes)
{
    SimpleDatabase<test::Key, test::A> db;

    // add values
    {
        ASSERT_TRUE(db.add("value1", 1));
        ASSERT_TRUE(db.add("V2", 2));
        ASSERT_TRUE(db.add("3=1", 1));
    }

    // try add value already in database
    {
        ASSERT_FALSE(db.add("value1", 1));
        ASSERT_FALSE(db.add("value1", 2));
    }

    // check values exist
    {
        ASSERT_TRUE(db.is("value1"));
        ASSERT_TRUE(db.is("V2"));
        ASSERT_TRUE(db.is("3=1"));

        ASSERT_FALSE(db.is("value2"));
    }

    // get values
    {
        ASSERT_EQ(db.at("value1"), test::A(1));
        ASSERT_EQ(db.at("V2"), test::A(2));
        ASSERT_EQ(db.at("3=1"), test::A(1));

        ASSERT_THROW(db.at("value2"), std::out_of_range);
    }

    // modify values
    {
        ASSERT_TRUE(db.modify("V2", 4));
        ASSERT_TRUE(db.modify("3=1", 1));
    }

    // try modify non existent value
    {
        ASSERT_FALSE(db.modify("value2", 1));
    }

    // get values
    {
        ASSERT_EQ(db.at("value1"), test::A(1));
        ASSERT_EQ(db.at("V2"), test::A(4));
        ASSERT_EQ(db.at("3=1"), test::A(1));
    }

    // remove values
    {
        ASSERT_TRUE(db.erase("3=1"));
    }

    // try remove already removed value
    {
        ASSERT_FALSE(db.erase("3=1"));
    }

    // get values
    {
        ASSERT_EQ(db.at("value1"), test::A(1));
        ASSERT_EQ(db.at("V2"), test::A(4));
    }

    // add more values
    {
        ASSERT_TRUE(db.add("value2", 2));
    }

    // check values exist
    {
        ASSERT_EQ(db.at("value1"), test::A(1));
        ASSERT_EQ(db.at("V2"), test::A(4));
        ASSERT_EQ(db.at("value2"), test::A(2));
    }
}

/**
 * Test functions of database for class NonCopyable and unique ptr <A>
 * Values inside map could be of type inherited from A.
 *
 * STEPS:
 * - add values
 * - get values
 * - modify values
 * - remove value
 * - iterate over values
 */
TEST(SimpleDatabaseTest, test_unique_ptrs)
{
    SimpleDatabase<test::NonCopyable, std::unique_ptr<test::A>> db;

    // add values
    {
        ASSERT_TRUE(db.add(test::NonCopyable("value_10"), std::make_unique<test::A>(10)));
        ASSERT_TRUE(db.add(test::NonCopyable("value_plus"), std::make_unique<test::Aplus5>(10)));
        ASSERT_TRUE(db.add(test::NonCopyable("value_minus"), std::make_unique<test::Aminus5>(10)));
        ASSERT_TRUE(db.add(test::NonCopyable("value_to_gamble"), std::make_unique<test::A>(0)));
    }

    // get values
    {
        {
            auto it = db.find(test::NonCopyable("value_10"));
            ASSERT_EQ(it->first.name(), "value_10");
            ASSERT_EQ(it->second->get(), 10);
        }

        {
            auto it = db.find(test::NonCopyable("value_plus"));
            ASSERT_EQ(it->first.name(), "value_plus");
            ASSERT_EQ(it->second->get(), 15);
        }

        {
            auto it = db.find(test::NonCopyable("value_minus"));
            ASSERT_EQ(it->first.name(), "value_minus");
            ASSERT_EQ(it->second->get(), 5);
        }

        {
            auto it = db.find(test::NonCopyable("value_to_gamble"));
            ASSERT_EQ(it->first.name(), "value_to_gamble");
            ASSERT_EQ(it->second->get(), 0);
        }
    }

    // modify values
    {
        ASSERT_TRUE(db.modify("value_to_gamble", std::make_unique<test::A>(20)));

        {
            auto it = db.find(test::NonCopyable("value_to_gamble"));
            ASSERT_EQ(it->first.name(), "value_to_gamble");
            ASSERT_EQ(it->second->get(), 20);
        }
    }

    // remove value
    {
        ASSERT_TRUE(db.erase("value_to_gamble"));
        ASSERT_FALSE(db.is("value_to_gamble"));
        ASSERT_EQ(db.size(), 3u);
    }

    // iterate over values
    {
        int sum1 = 0;
        for (const auto& kv : db)
        {
            sum1 += kv.second->get();
        }

        int sum2 = 0;
        for (auto it = db.begin(); it != db.end(); ++it)
        {
            sum2 += it->second->get();
        }

        ASSERT_EQ(sum1, 30);
        ASSERT_EQ(sum1, sum2);
    }
}

/**
 * Check that iterate over a map maintains the map status, even when adding values.
 *
 * STEPS:
 * - Add some values
 * - Execute 2 threads
 * - thread A
 *   - wait for access
 *   - add a value to map
 * - thread B
 *   - start iteration
 *   - give access to A (add value to map)
 *   - wait to be sure the adding thread has awake
 *   - finish iteration and map should be kept intact
 */
TEST(SimpleDatabaseTest, loop_while_insertion)
{
    // Database
    SimpleDatabase<int, int> db;

    // Waiter to notify to add values
    event::BooleanWaitHandler waiter_add(false, true);

    // Add some values
    db.add(1, 1000);
    db.add(2, 2000);
    db.add(3, 3000);
    db.add(4, 4000);

    // thread A
    std::thread addition_test(
        [&db, &waiter_add](){
            // wait for access
            waiter_add.wait();

            // add a value to map
            db.add(5, 5000);
        }
    );

    // thread B
    std::thread iteration_test(
        [&db, &waiter_add](){

            int sum_key = 0;
            int sum_value = 0;
            int i = 0;

            // start iteration
            for (auto it = db.begin(); it != db.end(); ++it)
            {
                if (i == 2)
                {
                    waiter_add.open();
                    // give access to A (add value to map)

                    // wait to be sure the adding thread has awake
                    sleep_for(10);
                }
                sum_key += it->first;
                sum_value += it->second;

                i++;
            }

            // finish iteration and map should be kept intact
            ASSERT_EQ(sum_key, 10);
            ASSERT_EQ(sum_value, 10000);
        }
    );

    addition_test.join();
    iteration_test.join();

    ASSERT_EQ(db.size(), 5);
}

/**
 * Check that iterate over a map maintains the map status, even when removing values.
 * Same as before but removing values.
 */
TEST(SimpleDatabaseTest, loop_while_deletion)
{
    // Database
    SimpleDatabase<int, int> db;

    // Waiter to notify to add values
    event::BooleanWaitHandler waiter_erase(false, true);

    // Add some values
    db.add(1, 1000);
    db.add(2, 2000);
    db.add(3, 3000);
    db.add(4, 4000);

    // thread A
    std::thread erase_test(
        [&db, &waiter_erase](){
            // wait for access
            waiter_erase.wait();

            // add a value to map
            db.erase(1);
        }
    );

    // thread B
    std::thread iteration_test(
        [&db, &waiter_erase](){

            int sum_key = 0;
            int sum_value = 0;
            int i = 0;

            // start iteration
            for (auto it = db.begin(); it != db.end(); ++it)
            {
                if (i == 2)
                {
                    waiter_erase.open();
                    // give access to A (add value to map)

                    // wait to be sure the adding thread has awake
                    sleep_for(10);
                }
                sum_key += it->first;
                sum_value += it->second;

                i++;
            }

            // finish iteration and map should be kept intact
            ASSERT_EQ(sum_key, 10);
            ASSERT_EQ(sum_value, 10000);
        }
    );

    erase_test.join();
    iteration_test.join();

    ASSERT_EQ(db.size(), 3);
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
