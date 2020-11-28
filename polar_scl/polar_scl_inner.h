//=============================================================================
// Interface for polar_scl_inner.c
//
// Copyright 2019 and onwards Kirill Shabunov.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================

#ifndef POLAR_SCL_INNER_H

#define POLAR_SCL_INNER_H

//-----------------------------------------------------------------------------
// Defines

#if !defined LISTFLIPPINGFAST
#define FLSIZ_MULT 4
#endif

#ifdef LISTFLIPPINGFAST
#define FLSIZ_MULT 32
#endif

//-----------------------------------------------------------------------------
// Includes.

#include "../common/typedefs.h"
#include "../formats/formats.h"


//-----------------------------------------------------------------------------
// Typedefs.

typedef struct xlist_item {
  xlitem x;
  struct xlist_item* p;
} xlist_item;

typedef struct {
  int c_m; // code m parameter.
  int c_n; // Code length.
  int c_k; // Code dimension.
  int peak_lsiz; // Peak list size.
  #ifdef LISTFLIPPING
  int flip_num;
  double flip_alpha;
  #endif // LISTFLIPPING
  #if defined LISTFLIPPINGPRECALC || defined LISTFLIPPINGFAST
  int flip_num;
  #endif
  uint32 *node_table;
  int node_table_len;
  int p_num; // # of permutations.
  int *pxarr; // permutations for inf. seq. (after decoding).
  int *pyarr; // perm. for ch. output vector (before decoding).
  int ret_list; // If 1 - return the list of all candidate inf. sequences (not just the best).
  uint8 *mem_buf;
} decoder_type;


typedef struct {
  double l;
  double *llrs;
} lv;

//-----------------------------------------------------------------------------
// Prototypes.


// Decoding procedure.
int
polar_dec(
   decoder_type *dd, // Decoder instance data.
   double *y_input, // Decoder input.
   int *x_dec, // Decoded information sequence.
   double *s_dec, // Metric of x_dec (set NULL, if not needed).
   lv *lv_array, // Comparator value + llrs.
   int Ti, // Index of the flipping bit.
   int Si, // Index of the flipping step.
   double alpha, // SCLFlip constant.
   double *Malpha, // List of alphas.
   int *sfs,
   double *smal
);

#endif // #ifndef POLAR_SCL_INNER_H