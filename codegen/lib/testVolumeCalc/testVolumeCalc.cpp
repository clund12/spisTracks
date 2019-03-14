//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: testVolumeCalc.cpp
//
// MATLAB Coder version            : 4.1
// C/C++ source code generated on  : 13-Mar-2019 16:44:43
//

// Include Files
#include <cmath>
#include <math.h>
#include "rt_nonfinite.h"
#include "testVolumeCalc.h"
#include "bsxfun.h"

// Function Definitions

//
// D = [1 2 3; 4 5 6];
// D = [1 2 3];
// Arguments    : const double D[6]
//                double R
// Return Type  : double
//
double testVolumeCalc(const double D[6], double R)
{
  double voxel_side;
  double b_voxel_side[3];
  int k0;
  double voxel_pos_data[6];
  double x[6];
  int nb;
  int k;
  boolean_T p;
  boolean_T exitg1;
  signed char idx_idx_0;
  signed char idx_idx_1;
  int j;
  int exitg2;
  int absxk_tmp;
  double b_absxk_tmp;
  double r;
  int exponent;
  voxel_side = 2.0 * R;
  b_voxel_side[0] = voxel_side / 2.0;
  b_voxel_side[1] = voxel_side / 2.0;
  b_voxel_side[2] = voxel_side / 2.0;
  for (k0 = 0; k0 < 3; k0++) {
    nb = k0 << 1;
    voxel_pos_data[nb] = D[nb] + b_voxel_side[k0];
    nb++;
    voxel_pos_data[nb] = D[nb] + b_voxel_side[k0];
  }

  bsxfun(voxel_pos_data, voxel_side, x);
  for (k = 0; k < 6; k++) {
    x[k] = std::floor(x[k]);
  }

  p = true;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 3)) {
    k0 = k << 1;
    voxel_side = x[1 + k0];
    if ((x[k0] == voxel_side) || (rtIsNaN(x[k << 1]) && rtIsNaN(voxel_side))) {
      k++;
    } else {
      if ((x[k << 1] <= voxel_side) || rtIsNaN(voxel_side)) {
      } else {
        p = false;
      }

      exitg1 = true;
    }
  }

  if (p) {
    idx_idx_0 = 1;
    idx_idx_1 = 2;
  } else {
    idx_idx_0 = 2;
    idx_idx_1 = 1;
  }

  for (j = 0; j < 3; j++) {
    nb = j << 1;
    voxel_side = x[(idx_idx_1 + nb) - 1];
    x[nb] = x[(idx_idx_0 + nb) - 1];
    x[1 + nb] = voxel_side;
  }

  for (k0 = 0; k0 < 6; k0++) {
    voxel_pos_data[k0] = x[k0];
  }

  nb = -1;
  k = 1;
  while (k <= 2) {
    k0 = k - 1;
    do {
      exitg2 = 0;
      k++;
      if (k > 2) {
        exitg2 = 1;
      } else {
        p = false;
        j = 0;
        exitg1 = false;
        while ((!exitg1) && (j < 3)) {
          absxk_tmp = j << 1;
          b_absxk_tmp = voxel_pos_data[1 + absxk_tmp];
          voxel_side = std::abs(b_absxk_tmp / 2.0);
          if ((!rtIsInf(voxel_side)) && (!rtIsNaN(voxel_side))) {
            if (voxel_side <= 2.2250738585072014E-308) {
              r = 4.94065645841247E-324;
            } else {
              frexp(voxel_side, &exponent);
              r = std::ldexp(1.0, exponent - 53);
            }
          } else {
            r = rtNaN;
          }

          voxel_side = voxel_pos_data[k0 + absxk_tmp];
          if ((std::abs(b_absxk_tmp - voxel_side) < r) || (rtIsInf(voxel_side) &&
               rtIsInf(b_absxk_tmp) && ((voxel_side > 0.0) == (b_absxk_tmp > 0.0))))
          {
            j++;
          } else {
            p = true;
            exitg1 = true;
          }
        }

        if (p) {
          exitg2 = 1;
        }
      }
    } while (exitg2 == 0);

    nb++;
    voxel_pos_data[nb] = voxel_pos_data[k0];
    voxel_pos_data[nb + 2] = voxel_pos_data[k0 + 2];
    voxel_pos_data[nb + 4] = voxel_pos_data[k0 + 4];
  }

  // voxel_pos = unique(cell2mat(add_vox),'rows');
  // voxCentres = bsxfun(@times, voxel_pos, voxel_side) + voxel_side/2;
  // n_voxels = size(voxel_pos,1);
  // aAV = n_voxels * voxel_side^3;
  return 1.0;
}

//
// File trailer for testVolumeCalc.cpp
//
// [EOF]
//
