// Copyright (C) 2018-2021 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#include "parameter.hpp"

#include <cuda_runtime.h>

#include <cuda_operation_registry.hpp>
#include <gsl/gsl_assert>
#include <ngraph/node.hpp>

namespace CUDAPlugin {

ParameterOp::ParameterOp(const CreationContext& context,
                         const ov::Node& node,
                         IndexCollection&& inputIds,
                         IndexCollection&& outputIds)
    : OperationBase(context, node, std::move(inputIds), std::move(outputIds)) {
    input_tensor_name_ = GetInputTensorName(node);
}

void ParameterOp::Execute(const InferenceRequestContext& context,
                          Inputs inputs,
                          Outputs outputs,
                          const Workbuffers&) const {
    Expects(inputs.size() == 0);
    Expects(outputs.size() == 1);
    Expects(context.HasInputBlob(input_tensor_name_));
    auto blob = context.GetInputBlob(input_tensor_name_);
    auto memory_ptr = std::static_pointer_cast<ngraph::HostTensor>(blob)->get_data_ptr();
    context.getThreadContext().stream().upload(outputs[0], memory_ptr, blob->get_size_in_bytes());
}

std::string ParameterOp::GetInputTensorName(const ov::Node& node) { return node.get_friendly_name(); }

OPERATION_REGISTER(ParameterOp, Parameter);
}  // namespace CUDAPlugin
