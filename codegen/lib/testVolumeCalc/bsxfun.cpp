//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: bsxfun.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 13-Mar-2019 16:44:43
//

// Include Files
#include "rt_nonfinite.h"
#include "testVolumeCalc.h"
#include "bsxfun.h"

// Function Definitions

//
// Arguments    : const double a[6]
//                double b
//                double c[6]
// Return Type  : void
//
void bsxfun(const double a[6], double b, double c[6])
{
  int k;
  int c_tmp;
  for (k = 0; k < 3; k++) {
    c_tmp = k << 1;
    c[c_tmp] = a[c_tmp] / b;
    c_tmp++;
    c[c_tmp] = a[c_tmp] / b;
  }
}

//
// File trailer for bsxfun.cpp
//
// [EOF]
//
