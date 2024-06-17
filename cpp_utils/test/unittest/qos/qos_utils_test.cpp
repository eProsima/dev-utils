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

#include <gtest/gtest.h>

#include <fastdds/dds/core/policy/QosPolicies.hpp>

#include <cpp_utils/qos/qos_utils.hpp>
#include <cpp_utils/testing/gtest_aux.hpp>

using namespace eprosima;
using namespace eprosima::fastdds::dds;

/**
 * Test \c qos_policy_id_to_string call
 */
TEST(qos_utils_test, qos_policy_id_to_string)
{
    // User data
    {
        const auto id = QosPolicyId_t::USERDATA_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "User data";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Durability
    {
        const auto id = QosPolicyId_t::DURABILITY_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Durability";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Presentation
    {
        const auto id = QosPolicyId_t::PRESENTATION_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Presentation";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Deadline
    {
        const auto id = QosPolicyId_t::DEADLINE_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Deadline";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Latency budget
    {
        const auto id = QosPolicyId_t::LATENCYBUDGET_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Latency budget";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Ownership
    {
        const auto id = QosPolicyId_t::OWNERSHIP_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Ownership";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Ownership strength
    {
        const auto id = QosPolicyId_t::OWNERSHIPSTRENGTH_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Ownership strength";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Liveliness
    {
        const auto id = QosPolicyId_t::LIVELINESS_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Liveliness";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Time-based filter
    {
        const auto id = QosPolicyId_t::TIMEBASEDFILTER_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Time-based filter";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Partition
    {
        const auto id = QosPolicyId_t::PARTITION_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Partition";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Reliability
    {
        const auto id = QosPolicyId_t::RELIABILITY_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Reliability";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Destination order
    {
        const auto id = QosPolicyId_t::DESTINATIONORDER_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Destination order";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // History
    {
        const auto id = QosPolicyId_t::HISTORY_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "History";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Resource limits
    {
        const auto id = QosPolicyId_t::RESOURCELIMITS_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Resource limits";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Entity factory
    {
        const auto id = QosPolicyId_t::ENTITYFACTORY_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Entity factory";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Writer data lifecycle
    {
        const auto id = QosPolicyId_t::WRITERDATALIFECYCLE_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Writer data lifecycle";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Reader data lifecycle
    {
        const auto id = QosPolicyId_t::READERDATALIFECYCLE_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Reader data lifecycle";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Topic data
    {
        const auto id = QosPolicyId_t::TOPICDATA_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Topic data";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Group data
    {
        const auto id = QosPolicyId_t::GROUPDATA_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Group data";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Transport priority
    {
        const auto id = QosPolicyId_t::TRANSPORTPRIORITY_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Transport priority";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Lifespan

    {
        const auto id = QosPolicyId_t::LIFESPAN_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Lifespan";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Durability service
    {
        const auto id = QosPolicyId_t::DURABILITYSERVICE_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Durability service";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Data representation

    {
        const auto id = QosPolicyId_t::DATAREPRESENTATION_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Data representation";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Type consistency enforcement
    {
        const auto id = QosPolicyId_t::TYPECONSISTENCYENFORCEMENT_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Type consistency enforcement";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Disable positive acks
    {
        const auto id = QosPolicyId_t::DISABLEPOSITIVEACKS_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Disable positive acks";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Participant resource limits
    {
        const auto id = QosPolicyId_t::PARTICIPANTRESOURCELIMITS_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Participant resource limits";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Property policy
    {
        const auto id = QosPolicyId_t::PROPERTYPOLICY_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Property policy";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Publish mode
    {
        const auto id = QosPolicyId_t::PUBLISHMODE_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Publish mode";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Reader resource limits
    {
        const auto id = QosPolicyId_t::READERRESOURCELIMITS_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Reader resource limits";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // RTPS endpoint
    {
        const auto id = QosPolicyId_t::RTPSENDPOINT_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "RTPS endpoint";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // RTPS reliable reader
    {
        const auto id = QosPolicyId_t::RTPSRELIABLEREADER_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "RTPS reliable reader";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // RTPS reliable writer
    {
        const auto id = QosPolicyId_t::RTPSRELIABLEWRITER_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "RTPS reliable writer";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Transport config
    {
        const auto id = QosPolicyId_t::TRANSPORTCONFIG_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Transport config";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Type consistency
    {
        const auto id = QosPolicyId_t::TYPECONSISTENCY_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Type consistency";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Wire protocol config
    {
        const auto id = QosPolicyId_t::WIREPROTOCOLCONFIG_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Wire protocol config";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Writer resource limits
    {
        const auto id = QosPolicyId_t::WRITERRESOURCELIMITS_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Writer resource limits";
        ASSERT_EQ(id_str, id_str_expected);
    }

    // Invalid

    {
        const auto id = QosPolicyId_t::INVALID_QOS_POLICY_ID;
        const auto id_str = utils::qos_policy_id_to_string(id);
        const auto id_str_expected = "Invalid";
        ASSERT_EQ(id_str, id_str_expected);
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
        const auto mask_str_expected = "Invalid";
        ASSERT_EQ(mask_str, mask_str_expected);
    }

    // One policy

    {
        PolicyMask mask;
        mask.set(QosPolicyId_t::USERDATA_QOS_POLICY_ID);

        const auto mask_str = utils::qos_policy_mask_to_string(mask);
        const auto mask_str_expected = "User data";
        ASSERT_EQ(mask_str, mask_str_expected);
    }

    // Some policies
    {
        PolicyMask mask;
        mask.set(QosPolicyId_t::USERDATA_QOS_POLICY_ID);
        mask.set(QosPolicyId_t::DURABILITY_QOS_POLICY_ID);
        mask.set(QosPolicyId_t::PRESENTATION_QOS_POLICY_ID);
        mask.set(QosPolicyId_t::DEADLINE_QOS_POLICY_ID);

        const auto mask_str = utils::qos_policy_mask_to_string(mask);
        const auto mask_str_expected = "User data, Durability, Presentation, Deadline";
        ASSERT_EQ(mask_str, mask_str_expected);

    }

    // All policies
    {
        PolicyMask mask;
        for (std::uint32_t id_int = QosPolicyId_t::USERDATA_QOS_POLICY_ID; id_int < QosPolicyId_t::NEXT_QOS_POLICY_ID;
                id_int++)
        {
            mask.set(static_cast<QosPolicyId_t>(id_int));
        }

        const auto mask_str = utils::qos_policy_mask_to_string(mask);
        const auto mask_str_expected =
                "User data, Durability, Presentation, Deadline, Latency budget, Ownership, Ownership strength, "
                "Liveliness, Time-based filter, Partition, Reliability, Destination order, History, Resource limits, "
                "Entity factory, Writer data lifecycle, Reader data lifecycle, Topic data, Group data, "
                "Transport priority, Lifespan, Durability service, Data representation, Type consistency enforcement, "
                "Disable positive acks, Participant resource limits, Property policy, Publish mode, "
                "Reader resource limits, RTPS endpoint, RTPS reliable reader, RTPS reliable writer, Transport config, "
                "Type consistency, Wire protocol config, Writer resource limits";
        ASSERT_EQ(mask_str, mask_str_expected);
    }

    // Invalid policy
    {
        PolicyMask mask;
        mask.set(QosPolicyId_t::INVALID_QOS_POLICY_ID);

        const auto mask_str = utils::qos_policy_mask_to_string(mask);
        const auto mask_str_expected = "Invalid";
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
