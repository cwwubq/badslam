// Copyright 2019 ETH Zürich, Thomas Schöps
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "badslam/cuda_image_processing.h"
#include "badslam/cuda_image_processing.cuh"
#include "badslam/cuda_util.cuh"

namespace vis {

template <typename T>
void UpscaleBufferBilinearly(
    cudaStream_t stream,
    const CUDABuffer<T>& src,
    CUDABuffer<T>* dest) {
  CUDA_CHECK();
  cudaTextureObject_t texture;
  src.CreateTextureObject(
      cudaAddressModeClamp, cudaAddressModeClamp,
      cudaFilterModeLinear, cudaReadModeElementType,
      true, &texture);
  
  UpscaleBufferBilinearlyCUDA(
      stream,
      texture,
      &dest->ToCUDA());
  
  cudaDestroyTextureObject(texture);
  CUDA_CHECK();
}

template void UpscaleBufferBilinearly<float>(cudaStream_t stream, const CUDABuffer<float>& src, CUDABuffer<float>* dest);

}
