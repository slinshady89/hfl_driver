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
/// @file base_hfl110dcu.h
///
/// @brief This file defines the HFL110DCU camera base class.
///
#ifndef BASE_HFL110DCU_H_
#define BASE_HFL110DCU_H_
#include <hfl_interface.h>
#include <string>
#include <vector>

namespace hfl
{
/// Default frame rows
const uint16_t FRAME_ROWS{ 32 };
/// Default frame cols
const uint16_t FRAME_COLUMNS{ 128 };
/// Default frame cols
const uint16_t PIXEL_RETURNS{ 2 };
/// Default frame cols
const uint16_t PIXEL_SLICES{ 128 };
///  Default bits used for intensity
const uint8_t INTENSITY_BITS{ 13 };
/// Default bits used for range
const uint8_t RANGE_BITS{ 16 };
/// Default frame ID
const char FRAME_ID[] = "hfl110dcu";
/// Default camera intrinsics
const char CAMERA_INTRINSICS[] = "min000000";
/// Default expected memory address
const uint32_t EXPECTED_ADDRESS{ 0xffffffff };

///
/// @brief Base class for the HFL110DCU cameras
///
class BaseHFL110DCU : public HflInterface
{
public:
  ///
  /// Sets the specified frame rate.
  ///
  /// @param[in] rate Frame rate to be set
  ///
  /// @return bool true if given frame rate set
  ///
  bool setFrameRate(double rate) override
  {
    return false;
  }

  ///
  /// Returns the current frame rate.
  ///
  /// @return current frame rate
  ///
  double getFrameRate(bool reg_format = false) const
  {
    return 25.0;
  };

  ///
  /// Sets global range offset
  ///
  /// @param[in] offset global range offset to set
  ///
  /// @return bool true if given global range offset is set
  ///
  bool setGlobalRangeOffset(double offset);

  ///
  /// Sets extrinsic translation roll
  ///
  /// @param[in] x extrinsic translation roll to set
  ///
  /// @return bool true if given extrinsic translation roll is set
  ///
  bool setExtrinsicRotationRoll(double roll);

  ///
  /// Sets extrinsic translation pitch
  ///
  /// @param[in] x extrinsic translation pitch to set
  ///
  /// @return bool true if given extrinsic translation pitch is set
  ///
  bool setExtrinsicRotationPitch(double pitch);

  ///
  /// Sets extrinsic translation yaw
  ///
  /// @param[in] x extrinsic translation yaw to set
  ///
  /// @return bool true if given extrinsic translation yaw is set
  ///
  bool setExtrinsicRotationYaw(double yaw);

  ///
  /// Sets extrinsic translation x
  ///
  /// @param[in] x extrinsic translation x to set
  ///
  /// @return bool true if given extrinsic translation x is set
  ///
  bool setExtrinsicTranslatationX(double x);

  ///
  /// Sets extrinsic translation y
  ///
  /// @param[in] y extrinsic translation y to set
  ///
  /// @return bool true if given extrinsic translation y is set
  ///
  bool setExtrinsicTranslatationY(double y);

  ///
  /// Sets extrinsic rotation z
  ///
  /// @param[in] z extrinsic rotation z to set
  ///
  /// @return bool true if given extrinsic rotation z is set
  ///
  bool setExtrinsicTranslatationZ(double z);

  ///
  /// Sets extrinsics_reconfigured flag
  ///
  /// @param[in] extrinsics_reconfigured flag to set
  ///
  /// @return bool true if given extrinsics reconfigured is set
  ///
  bool setExtrinsicsReconfigured(bool extrinsics_reconfigured);

protected:
  /// Range Magic Number
  double range_magic_number_;

  /// Current mode parameters
  Attribs_map mode_parameters;

  /// UDP sender function
  std::function<void(const std::vector<uint8_t>&)> udp_send_function_;

  /// HFL110DCU camera memory_types
  enum HFL110DCU_memory_types
  {
    mem_ri = 0,
    types_size
  };

  ///
  /// Gets the available memory modes, its params and register
  /// offset addresses.
  ///
  /// @param model The model of the current lidar
  /// @param version The HFL110DCU SW version
  ///
  /// @return Available memory modes
  ///
  bool getConfiguration(std::string model, std::string version);

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
};
}  // namespace hfl

#endif  // BASE_HFL110DCU_H_
