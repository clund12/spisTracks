/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_testVolumeCalc_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 13-Mar-2019 16:44:43
 */

#ifndef _CODER_TESTVOLUMECALC_API_H
#define _CODER_TESTVOLUMECALC_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_testVolumeCalc_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real_T testVolumeCalc(real_T D[6], real_T R);
extern void testVolumeCalc_api(const mxArray * const prhs[2], int32_T nlhs,
  const mxArray *plhs[1]);
extern void testVolumeCalc_atexit(void);
extern void testVolumeCalc_initialize(void);
extern void testVolumeCalc_terminate(void);
extern void testVolumeCalc_xil_terminate(void);

#endif

/*
 * File trailer for _coder_testVolumeCalc_api.h
 *
 * [EOF]
 */
