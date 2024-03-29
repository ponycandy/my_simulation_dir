//
// File: jac_mat_file.cpp
//
// MATLAB Coder version            : 5.2
// C/C++ source code generated on  : 02-May-2023 18:30:37
//

// Include Files
#include "jac_mat_file.h"
#include <math.h>

// Function Definitions
//
// JAC_MAT_FILE
//     JAC_MAT = JAC_MAT_FILE(DTHETA,F,G,L,M1,M2,THETA)
//
// Arguments    : double Dtheta
//                double F
//                double g
//                double l
//                double m1
//                double m2
//                double theta
//                double jac_mat[20]
// Return Type  : void
//
void jac_mat_file(double Dtheta, double F, double g, double l, double m1,
                  double m2, double theta, double jac_mat[20])
{
  double b_jac_mat_tmp;
  double c_jac_mat_tmp;
  double d_jac_mat_tmp;
  double e_jac_mat_tmp;
  double f_jac_mat_tmp;
  double jac_mat_tmp;
  double jac_mat_tmp_tmp;
  double t10;
  double t13;
  double t14;
  double t2;
  double t3;
  double t4;
  double t7;
  double t8;
  double t9;
  //     This function was generated by the Symbolic Math Toolbox version 8.7.
  //     28-Apr-2023 18:15:00
  t2 = cos(theta);
  t3 = sin(theta);
  t4 = Dtheta * Dtheta;
  t9 = 1.0 / l;
  t7 = t2 * t2;
  t8 = t3 * t3;
  t10 = m2 * t7 * 3.0;
  t13 = 1.0 / ((m1 * 4.0 + m2 * 4.0) + -t10);
  t14 = t13 * t13;
  jac_mat[0] = 0.0;
  jac_mat[1] = t2 * t9 * t13 * -3.0;
  jac_mat[2] = 0.0;
  jac_mat[3] = t13 * 4.0;
  jac_mat[4] = 0.0;
  jac_mat_tmp_tmp = l * m2;
  jac_mat_tmp = jac_mat_tmp_tmp * t4;
  b_jac_mat_tmp = g * m1;
  c_jac_mat_tmp = g * m2;
  d_jac_mat_tmp = jac_mat_tmp_tmp * t2;
  e_jac_mat_tmp = m2 * t2 * t3;
  f_jac_mat_tmp = c_jac_mat_tmp * t2;
  jac_mat[5] = t9 * t13 *
                   ((((F * t3 * -2.0 + b_jac_mat_tmp * t2) + f_jac_mat_tmp) +
                     jac_mat_tmp * t7 * 2.0) -
                    jac_mat_tmp * t8 * 2.0) *
                   -1.5 +
               e_jac_mat_tmp * t9 * t14 *
                   (((F * t2 * 2.0 + b_jac_mat_tmp * t3) + c_jac_mat_tmp * t3) +
                    d_jac_mat_tmp * t3 * t4 * 2.0) *
                   9.0;
  jac_mat[6] = 0.0;
  jac_mat[7] =
      t13 * ((g * t10 - c_jac_mat_tmp * t8 * 3.0) + d_jac_mat_tmp * t4 * 8.0) /
          2.0 -
      e_jac_mat_tmp * t14 *
          ((F * 8.0 + f_jac_mat_tmp * t3 * 3.0) +
           jac_mat_tmp_tmp * t3 * t4 * 8.0) *
          3.0;
  jac_mat[8] = 1.0;
  jac_mat[9] = Dtheta * m2 * t2 * t3 * t13 * -6.0;
  jac_mat[10] = 0.0;
  jac_mat[11] = Dtheta * l * m2 * t3 * t13 * 8.0;
  jac_mat[12] = 0.0;
  jac_mat[13] = 0.0;
  jac_mat[14] = 0.0;
  jac_mat[15] = 0.0;
  jac_mat[16] = 0.0;
  jac_mat[17] = 0.0;
  jac_mat[18] = 1.0;
  jac_mat[19] = 0.0;
}

//
// File trailer for jac_mat_file.cpp
//
// [EOF]
//
