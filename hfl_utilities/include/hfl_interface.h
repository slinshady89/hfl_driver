// Copyright 2020 Continental AG
// All rights reserved.
//
// Software License Agreement (BSD 2-Clause Simplified License)
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


///
/// @file hfl_interface.h
///
/// @brief This file defines the HFL camera's interface class.
///

#ifndef HFL_INTERFACE_H_
#define HFL_INTERFACE_H_
#include <hfl_configs.h>
#include <hfl_frame.h>

#ifdef _WIN32
#include <winsock2.h>
#elif __linux__
#include <arpa/inet.h>  // ntohl()
#endif

#include <string>
#include <vector>
#include <memory>

namespace hfl
{

static inline float big_to_native(float x)
{
  return ntohl(x);
}

static inline uint32_t big_to_native(uint32_t x)
{
  return ntohl(x);
}

static inline uint16_t big_to_native(uint16_t x)
{
  return ntohs(x);
}

static inline uint8_t big_to_native(uint8_t x)
{
  return x;
}

/// UDP ports types
enum udp_port_types
{
  frame_data,
  object_data,
  lut_data
};

/// Number of Bits
enum num_bits
{
  eight_bit = 0,
  ten_bit,
  twelve_bit,
  fourteen_bit
};

///
/// @brief Base class for all of the HFL cameras
///
class HflInterface
{
protected:
  /// Current camera model
  std::string model_;

  /// Current camera model
  std::string version_;

  /// Camera's IP address
  std::string ip_address_;

  /// Camera's UDP frame data port
  uint16_t frame_data_port_;

  /// Current publish tf state
  bool publish_tf_;

  /// current static tf values
  std::string parent_frame_;
  double x_;
  double y_;
  double z_;
  double roll_;
  double pitch_;
  double yaw_;
  bool extrinsics_reconfigured_;

  /// time offset
  double time_offset_;

  /// global range offset
  double global_offset_;

  /// Camera's frame configurations
  std::shared_ptr<hfl::Frame> frame_;

public:
  ///
  /// Gets the Model of the camera.
  ///
  /// @return string camera model
  ///
  std::string getModel() const;

  ///
  /// Gets the camera version.
  ///
  /// @return string camera model version
  ///
  std::string getVersion() const;

  ///
  /// Set the frame rate.
  ///
  /// @param[in] rate Camera frame rate
  ///
  /// @return bool true if given frame rate set
  ///
  virtual bool setFrameRate(double rate) = 0;

  ///
  /// Returns the current frame rate.
  ///
  /// @param[in] reg_format Indicates register format output
  /// @return current frame rate
  ///
  virtual double getFrameRate(bool reg_format = false) const = 0;

  ///
  /// Sets global range offset
  ///
  /// @param[in] offset global range offset to set
  ///
  /// @return bool true if given global range offset is set
  ///
  virtual bool setGlobalRangeOffset(double offset) = 0;

  ///
  /// Sets extrinsic translation roll
  ///
  /// @param[in] x extrinsic translation roll to set
  ///
  /// @return bool true if given extrinsic translation roll is set
  ///
  virtual bool setExtrinsicRotationRoll(double roll) = 0;

  ///
  /// Sets extrinsic translation pitch
  ///
  /// @param[in] x extrinsic translation pitch to set
  ///
  /// @return bool true if given extrinsic translation pitch is set
  ///
  virtual bool setExtrinsicRotationPitch(double pitch) = 0;

  ///
  /// Sets extrinsic translation yaw
  ///
  /// @param[in] x extrinsic translation yaw to set
  ///
  /// @return bool true if given extrinsic translation yaw is set
  ///
  virtual bool setExtrinsicRotationYaw(double yaw) = 0;

  ///
  /// Sets extrinsic translation x
  ///
  /// @param[in] x extrinsic translation x to set
  ///
  /// @return bool true if given extrinsic translation x is set
  ///
  virtual bool setExtrinsicTranslatationX(double x) = 0;

  ///
  /// Sets extrinsic translation y
  ///
  /// @param[in] y extrinsic translation y to set
  ///
  /// @return bool true if given extrinsic translation y is set
  ///
  virtual bool setExtrinsicTranslatationY(double y) = 0;

  ///
  /// Sets extrinsic rotation z
  ///
  /// @param[in] z extrinsic rotation z to set
  ///
  /// @return bool true if given extrinsic rotation z is set
  ///
  virtual bool setExtrinsicTranslatationZ(double z) = 0;

  ///
  /// Sets extrinsics_reconfigured flag
  ///
  /// @param[in] extrinsics_reconfigured flag to set
  ///
  /// @return bool true if given extrinsics reconfigured is set
  ///
  virtual bool setExtrinsicsReconfigured(bool extrinsics_reconfigured) = 0;

  ///
  /// Parse packet into depth and intensity image
  ///
  /// @param[in] start_byte starting byte, packet packet data to parse
  ///
  /// @return bool true if successfully parsed frame data
  ///
  virtual bool parseFrame(int start_byte, const std::vector<uint8_t>& packet) = 0;

  ///
  /// Process the frame data from udp packets
  ///
  /// @param[in] data frame data
  ///
  /// @return bool
  ///
  virtual bool processFrameData(const std::vector<uint8_t>& data) = 0;

  ///
  /// Parse packet into objects
  ///
  /// @param[in] start_byte starting byte, packet packet data to parse
  ///
  /// @return bool true if successfully parsed object data
  ///
  virtual bool parseObjects(int start_byte, const std::vector<uint8_t>& packet) = 0;

  ///
  /// Process the object data from udp packets
  ///
  /// @param[in] data object data
  ///
  /// @return bool
  ///
  virtual bool processObjectData(const std::vector<uint8_t>& data) = 0;

  ///
  /// Process the telemetry data from udp packets
  ///
  /// @param[in] data telemetry data
  ///
  /// @return bool
  ///
  virtual bool processTelemetryData(const std::vector<uint8_t>& data) = 0;

  ///
  /// Process the slice data from udp packets
  ///
  /// @param[in] data slice data
  ///
  /// @return bool
  ///
  virtual bool processSliceData(const std::vector<uint8_t>& data) = 0;
  
  ///
  /// Reference to the frame_ member variable
  ///
  /// @return frame shared_ptr
  ///
  std::shared_ptr<Frame> frame();
};

}  // namespace hfl
#endif  // HFL_INTERFACE_H_
