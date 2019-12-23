/* =====================================================================
 * Project:      PULP DSP Library
 * Title:        plp_mat_mult_i32.c
 * Description:  32-bit integer matrix multiplication glue code
 *
 * $Date:        22. December 2019
 * $Revision:    V0
 *
 * Target Processor: PULP cores
 * ===================================================================== */
/*
 * Copyright (C) 2019 ETH Zurich and Ubiversity of Bologna. All rights reserved.
 *
 * Author: Tom Kuchler, ETH Zurich
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
  @ingroup groupMath
 */

/**
  @defgroup BasicMatMult Matrix Transposed Matrix Multiplication
  This module contains the glue code for Matrix Transposed Matrix Multiplication. The kernel codes (kernels) are in the Moducle Matrix Transposed Matrix Multiplication Kernels.

  The Matrix Transposed Matrix Multiplication computes the product of two matrices with dimensions MxN and NxO, the second matrix is transposed in memory.
  The both matrices are accessed row wise, all values form the first are multiplied with the values of the second and then sum of the result gives the value for the result matrix.
  <pre>
      pDst[i,k] = pSrcA[i*M]*pSrcB[k*N] + pSrcA[i*M+1]*pSrcB[k*N +1] + ... + pSrcA[i*M+N-1]*pSrcB[k*N+N-1]
  </pre>
  There are functions for integer 32- 16- and 8-bit data types. For lower precision integers (16- and 8-bit), functions exploiting SIMD instructions are provided.

  The naming scheme of the functions follows the following pattern (for example plp_mat_mult_i32s):
  <pre>
  <pulp> _ <function name> _ <data type> <precision> <method> _ <isa extension>, with

  data type = {f, i, q} respectively for floats, integers, fixed points

  precision = {32, 16, 8} bits

  method = {s, v, p} meaning single (or scalar, i.e. not using packed SIMD), vectorized (i.e. using SIMD instructions), and parallel (for multicore parallel computing), respectively.

  isa extension = rv32im, xpulpv2, etc. of which rv32im is the most general one.

  </pre>


 */

/**
  @addtogroup BasicMatMult
  @{
 */

/**
  @brief Glue code for matrix mutliplication of 32-bit integer matrices.
  @param[in]  pSrcA     points to the first input matrix
  @param[in]  pSrcB     points to the second input matrix
  @param[in]  M         height of the first input matrix
  @param[in]  N         width of the first input matrix and hight of the second
  @param[in]  O         width of the second input matrix
  @param[out] pDstC     points to the output matrix
  @return        none
 */

void plp_mat_mult_trans_i32(
                         const int32_t * __restrict__ pSrcA,
                         const int32_t * __restrict__ pSrcB,
                         uint32_t M,
                         uint32_t N,
                         uint32_t O,
                         int32_t * __restrict__ pDstC){
  
  if (rt_cluster_id() == ARCHI_FC_CID){
    plp_mat_mult_trans_i32s_rv32im(pSrcA, pSrcB, M, N, O, pDstC);
  }
  else{
    plp_mat_mult_trans_i32s_xpulpv2(pSrcA, pSrcB, M, N, O, pDstC);
  }

}

/**
  @} end of BasicMatMult group
 */


