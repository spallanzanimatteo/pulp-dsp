/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_fill_I_f32s_xpulpv2.c
 * Description:  32-bit floating-point identity matrix creation for XPULPV2
 *
 * $Date:        16. July 2020
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2020 ETH Zurich and Ubiversity of Bologna. All rights reserved.
 *
 * Author: Tibor Schneider, ETH Zurich
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
  @ingroup MatFillI
 */

/**
  @addtogroup MatFillIKernels
  @{
 */

/**
  @brief      Create a 32-bit float identity matrix on XpulpV2
  @param[in]  N    Width and height of the matrix
  @param[out] pDst Points to the output matrix of shape NxN
  @return     none
 */

void plp_mat_fill_I_f32s_xpulpv2(uint32_t N, float *__restrict__ pDst) {

#define BASIC_VERSION // if used don't forget to also use the undefine at end of file
#ifdef BASIC_VERSION

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            pDst[i * N + j] = (float)(i == j);
        }
    }

#else

    // TODO: Hackathon

#endif
#undef BASIC_VERSION
}

/**
   @} end of MatFillIKernels group
*/
