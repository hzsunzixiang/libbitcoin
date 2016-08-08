/*
 * Copyright (c) 2011-2013 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * libbitcoin is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <boost/test/unit_test.hpp>
#include <boost/iostreams/stream.hpp>
#include <bitcoin/bitcoin.hpp>

using namespace bc;

BOOST_AUTO_TEST_SUITE(memory_pool_tests)

BOOST_AUTO_TEST_CASE(from_data_insufficient_version_failure)
{
    const message::memory_pool expected;
    const data_chunk data = expected.to_data(protocol_version);
    message::memory_pool instance{};

    BOOST_REQUIRE_EQUAL(false, instance.from_data(
        message::memory_pool::version_minimum - 1, data));
    BOOST_REQUIRE_EQUAL(false, instance.is_valid());
}

BOOST_AUTO_TEST_CASE(roundtrip_to_data_factory_from_data_chunk)
{
    const message::memory_pool expected{};
    const auto data = expected.to_data(protocol_version);
    const auto result = message::memory_pool::factory_from_data(
        protocol_version, data);

    BOOST_REQUIRE_EQUAL(0u, data.size());
    BOOST_REQUIRE(result.is_valid());
    BOOST_REQUIRE_EQUAL(0u, result.serialized_size(protocol_version));
}

BOOST_AUTO_TEST_CASE(roundtrip_to_data_factory_from_data_stream)
{
    const message::memory_pool expected{};
    const auto data = expected.to_data(protocol_version);
    boost::iostreams::stream<byte_source<data_chunk>> istream(data);
    const auto result = message::memory_pool::factory_from_data(
        protocol_version, istream);

    BOOST_REQUIRE_EQUAL(0u, data.size());
    BOOST_REQUIRE(result.is_valid());
    BOOST_REQUIRE_EQUAL(0u, result.serialized_size(protocol_version));
}

BOOST_AUTO_TEST_CASE(roundtrip_to_data_factory_from_data_reader)
{
    const message::memory_pool expected{};
    const auto data = expected.to_data(protocol_version);
    boost::iostreams::stream<byte_source<data_chunk>> istream(data);
    istream_reader source(istream);
    const auto result = message::memory_pool::factory_from_data(
        protocol_version, source);

    BOOST_REQUIRE_EQUAL(0u, data.size());
    BOOST_REQUIRE(result.is_valid());
    BOOST_REQUIRE_EQUAL(0u, result.serialized_size(protocol_version));
}

BOOST_AUTO_TEST_SUITE_END()
