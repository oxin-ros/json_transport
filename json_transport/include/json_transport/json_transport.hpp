/**
Software License Agreement (BSD)

\file      json_transport.hpp
\authors   Paul Bovbel <pbovbel@locusrobotics.com>
\copyright Copyright (c) (2018,), Locus Robotics, All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted
provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions
and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of
conditions and the following disclaimer in the documentation and/or other materials provided with
the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to
endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

#ifndef JSON_TRANSPORT_JSON_TRANSPORT_HPP
#define JSON_TRANSPORT_JSON_TRANSPORT_HPP

#include "json_transport/nlohmann/json.hpp"
#include <json_msgs/Json.h>

#include <ros/message_traits.h>
#include <ros/serialization.h>
#include <ros/static_assert.h>

namespace json_transport
{
  typedef nlohmann::json json_t;
  typedef json_msgs::Json json_msg_t;

  inline json_t unpack(json_msg_t message)
  {
    return json_t::parse(message.json.empty() ? "null" : message.json);
  }

  inline json_msg_t pack(json_t data)
  {
    json_msg_t message{};
    message.json = data.dump();
    return message;
  }
}

namespace ros
{
namespace message_traits
{

ROS_STATIC_ASSERT(sizeof(json_transport::json_t) == 16);

template<>
struct MD5Sum<json_transport::json_t>
{
  static const char* value()
  {
    return MD5Sum<json_transport::json_msg_t>::value();
  }

  static const char* value(const json_transport::json_t&)
  {
    return value();
  }
};

template<>
struct DataType<json_transport::json_t>
{
  static const char* value()
  {
    return DataType<json_transport::json_msg_t>::value();
  }

  static const char* value(const json_transport::json_t&)
  {
    return value();
  }
};

template<>
struct Definition<json_transport::json_t>
{
  static const char* value()
  {
    return Definition<json_transport::json_msg_t>::value();
  }

  static const char* value(const json_transport::json_t&)
  {
    return value();
  }
};
} // namespace message_traits

namespace serialization
{

template<>
struct Serializer<json_transport::json_t>
{
  template<typename Stream>
  inline static void write(Stream& stream, const json_transport::json_t& json)
  {
    json_transport::json_msg_t message = json_transport::pack(json);
    Serializer<json_transport::json_msg_t>::write(stream, message);
  }

  template<typename Stream>
  inline static void read(Stream& stream, json_transport::json_t& json)
  {
    json_transport::json_msg_t message;
    Serializer<json_transport::json_msg_t>::read(stream, message);
    json = json_transport::unpack(message);
  }

  inline static uint32_t serializedLength(const json_transport::json_t& json)
  {
    return json.dump().length() + 4;
  }
};

} // namespace serialization
} // namespace ros

#endif  // JSON_TRANSPORT_JSON_TRANSPORT_HPP
