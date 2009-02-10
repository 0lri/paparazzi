#ifndef BOOZ2_GUIDANCE_V
#define BOOZ2_GUIDANCE_V

#include "std.h"

#define BOOZ2_GUIDANCE_V_MODE_KILL   0
#define BOOZ2_GUIDANCE_V_MODE_DIRECT 1
#define BOOZ2_GUIDANCE_V_MODE_HOVER  2

extern uint8_t booz2_guidance_v_mode;

extern int32_t booz2_guidance_v_est_g;
extern int32_t booz2_guidance_v_est_zd;
extern int32_t booz2_guidance_v_z_sp;
extern int32_t booz2_guidance_v_z_sum_err;
extern int32_t booz2_guidance_v_delta_t;

extern int32_t booz2_guidance_v_kp;
extern int32_t booz2_guidance_v_kd;
extern int32_t booz2_guidance_v_ki;


extern void booz2_guidance_v_init(void);
extern void booz2_guidance_v_read_rc(void);
extern void booz2_guidance_v_mode_changed(uint8_t new_mode);
extern void booz2_guidance_v_run(bool_t in_flight);

#endif /* BOOZ2_GUIDANCE_V */