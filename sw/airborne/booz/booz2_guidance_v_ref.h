#ifndef BOOZ2_GUIDANCE_V_REF_H
#define BOOZ2_GUIDANCE_V_REF_H

#include "inttypes.h"
#include "booz_geometry_mixed.h"

/* altitude setpoint in meters (input)            */
/* Q23.8 : accuracy 0.0039, range 8388km          */
extern int32_t b2_gv_z_sp;
#define B2_GV_Z_SP_FRAC IPOS_FRAC

/* update frequency                               */
#define B2_GV_FREQ_FRAC 9
#define B2_GV_FREQ (1<<B2_GV_FREQ_FRAC)

/* reference model vaccel in meters/sec2 (output) */
/* Q23.8 : accuracy 0.0039 , range 8388km/s2      */
extern int32_t b2_gv_zdd_ref;
#define B2_GV_ZDD_REF_FRAC 8

/* reference model vspeed in meters/sec (output)  */
/* Q14.17 : accuracy 0.0000076 , range 16384m/s2  */
extern int32_t b2_gv_zd_ref;
#define B2_GV_ZD_REF_FRAC (B2_GV_ZDD_REF_FRAC + B2_GV_FREQ_FRAC)

/* reference model altitude in meters (output)    */
/* Q37.26 :                                       */
extern int64_t b2_gv_z_ref;
#define B2_GV_Z_REF_FRAC (B2_GV_ZD_REF_FRAC + B2_GV_FREQ_FRAC)

/* Saturations definition */
#define B2_GV_MIN_ZDD_F (-0.8*9.81)
#define B2_GV_MIN_ZDD BOOZ_INT_OF_FLOAT(B2_GV_MIN_ZDD_F, B2_GV_ZDD_REF_FRAC)
#define B2_GV_MAX_ZDD_F ( 2.0*9.81)
#define B2_GV_MAX_ZDD BOOZ_INT_OF_FLOAT(B2_GV_MAX_ZDD_F, B2_GV_ZDD_REF_FRAC)
#define B2_GV_MIN_ZD_F  (-5.)
#define B2_GV_MIN_ZD  BOOZ_INT_OF_FLOAT(B2_GV_MIN_ZD_F , B2_GV_ZD_REF_FRAC)
#define B2_GV_MAX_ZD_F  ( 5.)
#define B2_GV_MAX_ZD  BOOZ_INT_OF_FLOAT(B2_GV_MAX_ZD_F , B2_GV_ZD_REF_FRAC)

/* second order model natural frequency and damping */
#define B2_GV_OMEGA RadOfDeg(100.)
#define B2_GV_ZETA  0.85
#define B2_GV_ZETA_OMEGA_FRAC 10
#define B2_GV_ZETA_OMEGA BOOZ_INT_OF_FLOAT((B2_GV_ZETA*B2_GV_OMEGA), B2_GV_ZETA_OMEGA_FRAC)
#define B2_GV_OMEGA_2_FRAC 7
#define B2_GV_OMEGA_2    BOOZ_INT_OF_FLOAT((B2_GV_OMEGA*B2_GV_OMEGA), B2_GV_OMEGA_2_FRAC)


#ifdef B2_GUIDANCE_V_C
static inline void b2_gv_set_ref(int32_t alt, int32_t speed, int32_t accel);
static inline void b2_gv_update_ref(void);

int32_t b2_gv_z_sp;
int64_t b2_gv_z_ref;
int32_t b2_gv_zd_ref;
int32_t b2_gv_zdd_ref;

static inline void b2_gv_set_ref(int32_t alt, int32_t speed, int32_t accel) {
  int64_t new_ref = ((int64_t)alt)<<(B2_GV_Z_REF_FRAC - B2_GV_Z_SP_FRAC);
  b2_gv_z_ref   = new_ref;
  b2_gv_zd_ref  = speed;
  b2_gv_zdd_ref = accel;
}

static inline void b2_gv_update_ref(void) {

  b2_gv_z_ref  += b2_gv_zd_ref;
  b2_gv_zd_ref += b2_gv_zdd_ref;
  
  // compute the "speed part" of zdd = -2*zeta*omega*zd -omega^2(z_sp - z)
  int32_t zd_zdd_res = b2_gv_zd_ref>>(B2_GV_ZD_REF_FRAC - B2_GV_ZDD_REF_FRAC);
  int32_t zdd_speed = ((int32_t)(-2*B2_GV_ZETA_OMEGA)*zd_zdd_res)>>(B2_GV_ZETA_OMEGA_FRAC);
  // compute z error in z_sp resolution
  int32_t z_err_sp = b2_gv_z_sp - (int32_t)(b2_gv_z_ref>>(B2_GV_Z_REF_FRAC-B2_GV_Z_SP_FRAC));
  // convert to accel resolution
  int32_t z_err_accel = z_err_sp>>(B2_GV_Z_SP_FRAC-B2_GV_ZDD_REF_FRAC);
  int32_t zdd_pos = ((int32_t)(B2_GV_OMEGA_2)*z_err_accel)>>B2_GV_OMEGA_2_FRAC;
  b2_gv_zdd_ref = zdd_speed + zdd_pos;

  /* Saturate accelerations */
  Bound(b2_gv_zdd_ref, B2_GV_MIN_ZDD, B2_GV_MAX_ZDD);
  
  /* Saturate speed and adjust acceleration accordingly */
  if (b2_gv_zd_ref <= B2_GV_MIN_ZD) {
    b2_gv_zd_ref = B2_GV_MIN_ZD;
    if (b2_gv_zdd_ref < 0)
      b2_gv_zdd_ref = 0;
  }
  else if (b2_gv_zd_ref >= B2_GV_MAX_ZD) {
    b2_gv_zd_ref = B2_GV_MAX_ZD;
    if (b2_gv_zdd_ref > 0)
      b2_gv_zdd_ref = 0;
  }
}


#endif /* B2_GUIDANCE_V_C */

#endif /* BOOZ2_GUIDANCE_V_REF_H */
