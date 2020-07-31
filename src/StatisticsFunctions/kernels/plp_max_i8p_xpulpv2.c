/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_max_i8p_xpulpv2.c
 * Description:  Kernel for calculation the max of 8-Bit integer input vectors on XPULPV2
 *
 * $Date:        31.07.2020
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and University of Bologna.
 *
 * Author: Matteo Spallanzani, ETH Zurich
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "plp_math.h"

/**
  @ingroup max
 */

/**
   @defgroup maxKernels Max Kernels
 */

/**
  @addtogroup maxKernels
  @{
 */

/**
   @brief         Max value of a 8-bit integer vector for XPULPV2 extension.
   @param[in]     task_args pointer to plp_max_instance_i8 as initialised by plp_max_i8_parallel
   @return        none
*/

void plp_max_i8p_xpulpv2(void* task_args) {

    plp_max_instance_i8 *S = (plp_max_instance_i8*) task_args;
    
    uint32_t srcSliceSize = S->nElems / S->nPE;
    uint32_t srcOffset;

    const int8_t *pSrc;
    uint32_t blockSize;
    int8_t *pRes;

    srcOffset = rt_core_id() * srcSliceSize;
    pSrc = (int8_t*)(S->pSrc + srcOffset);
 
    if (rt_core_id() == (S->nPE - 1)) {
        blockSize = S->nElems - srcOffset;  /* = srcSliceSize + (S->nElems % S->nPE) */
    } else {
        blockSize = srcSliceSize;
    }
    
    pRes = (int8_t*)(S->pRes + rt_core_id());

    plp_max_i8s_xpulpv2(pSrc, blockSize, pRes);
    rt_team_barrier();

}
