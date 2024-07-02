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

/**
 * @file qos_utils.cpp
 */

#include <string>

#include <fastdds/dds/core/policy/QosPolicies.hpp>

#include <cpp_utils/qos/qos_utils.hpp>

using namespace eprosima::fastdds::dds;

namespace eprosima {
namespace utils {

std::string qos_policy_id_to_string(
        const QosPolicyId_t& qos_policy_id)
{
    switch (qos_policy_id)
    {
        case QosPolicyId_t::USERDATA_QOS_POLICY_ID:
            return "User data";
        case QosPolicyId_t::DURABILITY_QOS_POLICY_ID:
            return "Durability";
        case QosPolicyId_t::PRESENTATION_QOS_POLICY_ID:
            return "Presentation";
        case QosPolicyId_t::DEADLINE_QOS_POLICY_ID:
            return "Deadline";
        case QosPolicyId_t::LATENCYBUDGET_QOS_POLICY_ID:
            return "Latency budget";
        case QosPolicyId_t::OWNERSHIP_QOS_POLICY_ID:
            return "Ownership";
        case QosPolicyId_t::OWNERSHIPSTRENGTH_QOS_POLICY_ID:
            return "Ownership strength";
        case QosPolicyId_t::LIVELINESS_QOS_POLICY_ID:
            return "Liveliness";
        case QosPolicyId_t::TIMEBASEDFILTER_QOS_POLICY_ID:
            return "Time-based filter";
        case QosPolicyId_t::PARTITION_QOS_POLICY_ID:
            return "Partition";
        case QosPolicyId_t::RELIABILITY_QOS_POLICY_ID:
            return "Reliability";
        case QosPolicyId_t::DESTINATIONORDER_QOS_POLICY_ID:
            return "Destination order";
        case QosPolicyId_t::HISTORY_QOS_POLICY_ID:
            return "History";
        case QosPolicyId_t::RESOURCELIMITS_QOS_POLICY_ID:
            return "Resource limits";
        case QosPolicyId_t::ENTITYFACTORY_QOS_POLICY_ID:
            return "Entity factory";
        case QosPolicyId_t::WRITERDATALIFECYCLE_QOS_POLICY_ID:
            return "Writer data lifecycle";
        case QosPolicyId_t::READERDATALIFECYCLE_QOS_POLICY_ID:
            return "Reader data lifecycle";
        case QosPolicyId_t::TOPICDATA_QOS_POLICY_ID:
            return "Topic data";
        case QosPolicyId_t::GROUPDATA_QOS_POLICY_ID:
            return "Group data";
        case QosPolicyId_t::TRANSPORTPRIORITY_QOS_POLICY_ID:
            return "Transport priority";
        case QosPolicyId_t::LIFESPAN_QOS_POLICY_ID:
            return "Lifespan";
        case QosPolicyId_t::DURABILITYSERVICE_QOS_POLICY_ID:
            return "Durability service";
        case QosPolicyId_t::DATAREPRESENTATION_QOS_POLICY_ID:
            return "Data representation";
        case QosPolicyId_t::TYPECONSISTENCYENFORCEMENT_QOS_POLICY_ID:
            return "Type consistency enforcement";
        case QosPolicyId_t::DISABLEPOSITIVEACKS_QOS_POLICY_ID:
            return "Disable positive acks";
        case QosPolicyId_t::PARTICIPANTRESOURCELIMITS_QOS_POLICY_ID:
            return "Participant resource limits";
        case QosPolicyId_t::PROPERTYPOLICY_QOS_POLICY_ID:
            return "Property policy";
        case QosPolicyId_t::PUBLISHMODE_QOS_POLICY_ID:
            return "Publish mode";
        case QosPolicyId_t::READERRESOURCELIMITS_QOS_POLICY_ID:
            return "Reader resource limits";
        case QosPolicyId_t::RTPSENDPOINT_QOS_POLICY_ID:
            return "RTPS endpoint";
        case QosPolicyId_t::RTPSRELIABLEREADER_QOS_POLICY_ID:
            return "RTPS reliable reader";
        case QosPolicyId_t::RTPSRELIABLEWRITER_QOS_POLICY_ID:
            return "RTPS reliable writer";
        case QosPolicyId_t::TRANSPORTCONFIG_QOS_POLICY_ID:
            return "Transport config";
        case QosPolicyId_t::TYPECONSISTENCY_QOS_POLICY_ID:
            return "Type consistency";
        case QosPolicyId_t::WIREPROTOCOLCONFIG_QOS_POLICY_ID:
            return "Wire protocol config";
        case QosPolicyId_t::WRITERRESOURCELIMITS_QOS_POLICY_ID:
            return "Writer resource limits";
        case QosPolicyId_t::INVALID_QOS_POLICY_ID:
        default:
            return "Invalid";
    }
}

std::string qos_policy_mask_to_string(
        const PolicyMask& qos_policy_mask)
{
    if (qos_policy_mask.none())
    {
        return qos_policy_id_to_string(QosPolicyId_t::INVALID_QOS_POLICY_ID);
    }

    std::string policy_mask_str;
    bool first_id_in_mask = true;

    for (std::uint32_t id_int = QosPolicyId_t::INVALID_QOS_POLICY_ID; id_int < QosPolicyId_t::NEXT_QOS_POLICY_ID;
            id_int++)
    {
        const auto qos_policy_id = static_cast<QosPolicyId_t>(id_int);

        if (qos_policy_mask.test(qos_policy_id))
        {
            if (first_id_in_mask)
            {
                first_id_in_mask = false;
            }
            else
            {
                policy_mask_str += ", ";
            }

            policy_mask_str += qos_policy_id_to_string(qos_policy_id);
        }
    }

    return policy_mask_str;
}

} /* namespace utils */
} /* namespace eprosima */
