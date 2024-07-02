// Copyright 2024 Proyectos y Sistemas de Mantenimiento SL (eProsima).
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

#include <map>
#include <string>

#include <cpp_utils/testing/gtest_aux.hpp>
#include <gtest/gtest.h>

#include <fastdds/dds/core/policy/QosPolicies.hpp>

#include <cpp_utils/qos/qos_utils.hpp>

using namespace eprosima;
using namespace eprosima::fastdds::dds;

std::map<QosPolicyId_t, std::string> ids_to_str{
    {QosPolicyId_t::USERDATA_QOS_POLICY_ID, "User data"},
    {QosPolicyId_t::DURABILITY_QOS_POLICY_ID, "Durability"},
    {QosPolicyId_t::PRESENTATION_QOS_POLICY_ID, "Presentation"},
    {QosPolicyId_t::DEADLINE_QOS_POLICY_ID, "Deadline"},
    {QosPolicyId_t::LATENCYBUDGET_QOS_POLICY_ID, "Latency budget"},
    {QosPolicyId_t::OWNERSHIP_QOS_POLICY_ID, "Ownership"},
    {QosPolicyId_t::OWNERSHIPSTRENGTH_QOS_POLICY_ID, "Ownership strength"},
    {QosPolicyId_t::LIVELINESS_QOS_POLICY_ID, "Liveliness"},
    {QosPolicyId_t::TIMEBASEDFILTER_QOS_POLICY_ID, "Time-based filter"},
    {QosPolicyId_t::PARTITION_QOS_POLICY_ID, "Partition"},
    {QosPolicyId_t::RELIABILITY_QOS_POLICY_ID, "Reliability"},
    {QosPolicyId_t::DESTINATIONORDER_QOS_POLICY_ID, "Destination order"},
    {QosPolicyId_t::HISTORY_QOS_POLICY_ID, "History"},
    {QosPolicyId_t::RESOURCELIMITS_QOS_POLICY_ID, "Resource limits"},
    {QosPolicyId_t::ENTITYFACTORY_QOS_POLICY_ID, "Entity factory"},
    {QosPolicyId_t::WRITERDATALIFECYCLE_QOS_POLICY_ID, "Writer data lifecycle"},
    {QosPolicyId_t::READERDATALIFECYCLE_QOS_POLICY_ID, "Reader data lifecycle"},
    {QosPolicyId_t::TOPICDATA_QOS_POLICY_ID, "Topic data"},
    {QosPolicyId_t::GROUPDATA_QOS_POLICY_ID, "Group data"},
    {QosPolicyId_t::TRANSPORTPRIORITY_QOS_POLICY_ID, "Transport priority"},
    {QosPolicyId_t::LIFESPAN_QOS_POLICY_ID, "Lifespan"},
    {QosPolicyId_t::DURABILITYSERVICE_QOS_POLICY_ID, "Durability service"},
    {QosPolicyId_t::DATAREPRESENTATION_QOS_POLICY_ID, "Data representation"},
    {QosPolicyId_t::TYPECONSISTENCYENFORCEMENT_QOS_POLICY_ID, "Type consistency enforcement"},
    {QosPolicyId_t::DISABLEPOSITIVEACKS_QOS_POLICY_ID, "Disable positive acks"},
    {QosPolicyId_t::PARTICIPANTRESOURCELIMITS_QOS_POLICY_ID, "Participant resource limits"},
    {QosPolicyId_t::PROPERTYPOLICY_QOS_POLICY_ID, "Property policy"},
    {QosPolicyId_t::PUBLISHMODE_QOS_POLICY_ID, "Publish mode"},
    {QosPolicyId_t::READERRESOURCELIMITS_QOS_POLICY_ID, "Reader resource limits"},
    {QosPolicyId_t::RTPSENDPOINT_QOS_POLICY_ID, "RTPS endpoint"},
    {QosPolicyId_t::RTPSRELIABLEREADER_QOS_POLICY_ID, "RTPS reliable reader"},
    {QosPolicyId_t::RTPSRELIABLEWRITER_QOS_POLICY_ID, "RTPS reliable writer"},
    {QosPolicyId_t::TRANSPORTCONFIG_QOS_POLICY_ID, "Transport config"},
    {QosPolicyId_t::TYPECONSISTENCY_QOS_POLICY_ID, "Type consistency"},
    {QosPolicyId_t::WIREPROTOCOLCONFIG_QOS_POLICY_ID, "Wire protocol config"},
    {QosPolicyId_t::WRITERRESOURCELIMITS_QOS_POLICY_ID, "Writer resource limits"},
    {QosPolicyId_t::INVALID_QOS_POLICY_ID, "Invalid"}};

/**
 * Test \c qos_policy_id_to_string call
 */
TEST(qos_utils_test, qos_policy_id_to_string)
{
    for (const auto& id_to_str : ids_to_str)
    {
        const auto id_str = utils::qos_policy_id_to_string(id_to_str.first);
        ASSERT_EQ(id_str, id_to_str.second);
    }
}

/**
 * Test \c qos_policy_mask_to_string call
 */
TEST(qos_utils_test, qos_policy_mask_to_string)
{
    // Empty mask
    {
        const PolicyMask mask;
        const auto mask_str = utils::qos_policy_mask_to_string(mask);
        const auto mask_str_expected = ids_to_str.at(QosPolicyId_t::INVALID_QOS_POLICY_ID);
        ASSERT_EQ(mask_str, mask_str_expected);
    }

    // One policy
    {
        for (const auto& id_to_str : ids_to_str)
        {
            PolicyMask mask;
            mask.set(id_to_str.first);

            const auto mask_str = utils::qos_policy_mask_to_string(mask);
            const auto mask_str_expected = id_to_str.second;
            ASSERT_EQ(mask_str, mask_str_expected);
        }
    }

    // All policies
    {
        PolicyMask mask;

        for (const auto& id_to_str : ids_to_str)
        {
            mask.set(id_to_str.first);
        }

        const auto mask_str = utils::qos_policy_mask_to_string(mask);
        const auto mask_str_expected =
                "Invalid, User data, Durability, Presentation, Deadline, Latency budget, Ownership, "
                "Ownership strength, Liveliness, Time-based filter, Partition, Reliability, Destination order, "
                "History, Resource limits, Entity factory, Writer data lifecycle, Reader data lifecycle, Topic data, "
                "Group data, Transport priority, Lifespan, Durability service, Data representation, "
                "Type consistency enforcement, Disable positive acks, Participant resource limits, Property policy, "
                "Publish mode, Reader resource limits, RTPS endpoint, RTPS reliable reader, RTPS reliable writer, "
                "Transport config, Type consistency, Wire protocol config, Writer resource limits";
        ASSERT_EQ(mask_str, mask_str_expected);
    }

    // Invalid policy
    {
        PolicyMask mask;
        mask.set(QosPolicyId_t::INVALID_QOS_POLICY_ID);

        const auto mask_str = utils::qos_policy_mask_to_string(mask);
        const auto mask_str_expected = ids_to_str.at(QosPolicyId_t::INVALID_QOS_POLICY_ID);
        ASSERT_EQ(mask_str, mask_str_expected);
    }
}

int main(
        int argc,
        char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
