// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include "openvino/op/interpolate.hpp"

namespace CUDAPlugin::Interpolate::Details {

void getAxesAndScales(const ov::op::v4::Interpolate& node, std::vector<size_t>& axes, std::vector<float>& scales);

}  // namespace CUDAPlugin::Interpolate::Details
