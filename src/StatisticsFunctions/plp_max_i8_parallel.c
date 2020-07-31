/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_max_i8_parallel.c
 * Description:  Maximum value of a 8-bit integer vector glue code
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
   @ingroup groupStats
*/

/**
   @defgroup max Max

*/

/**
   @addtogroup max
   @{
*/

/**
   @brief         Glue code for max value of a 8-bit integer vector (parallel version).
   @param[in]     pSrc       points to the input vector
   @param[in]     blockSize  number of samples in input vector
   @param[out]    pRes    max value returned here
   @param[in]     nPE     number of processing elements
   @return        none
 */

void plp_max_i8_parallel(const int8_t *__restrict__ pSrc, uint32_t blockSize, int8_t *__restrict__ pRes, const uint8_t nPE) {

    int8_t *pResBuffer;

    if (rt_cluster_id() == ARCHI_FC_CID) {

       printf("Parallel processing supported only for cluster side!\n");
       return;

    } else {

        if (nPE > 1) {

            if (blockSize < 2 * nPE) {

               if (rt_core_id() == 0) {
                  plp_max_i8s_xpulpv2(pSrc, blockSize, pRes);
               }


            } else {

               pResBuffer = (int8_t*)rt_alloc(RT_ALLOC_CL_DATA, sizeof(int8_t) * nPE);  /* does not need initialization since it will be written */

               plp_max_instance_i8 S = {
                  .pSrc = pSrc,
                  .nElems = blockSize,
                  .pRes = pResBuffer,
                  .nPE = nPE
               };

               rt_team_fork(nPE, plp_max_i8p_xpulpv2, (void*) &S);

               if (rt_core_id() == 0) {
                  printf("C\n");
                  plp_max_i8s_xpulpv2(pResBuffer, nPE, pRes);
               }
               
               rt_free(RT_ALLOC_CL_DATA, pResBuffer, sizeof(uint8_t) * nPE);
            }

        } else {

            plp_max_i8s_xpulpv2(pSrc, blockSize, pRes);

        }
    }
}

/**
  @} end of mean group
 */
