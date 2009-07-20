/*
 * $Id$
 *  
 * Copyright (C) 2008-2009 Antoine Drouin <poinix@gmail.com>
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA. 
 */

/*
 *
 * simulator plug for the booz2 v1 imu arch dependant functions
 *
 */
#ifndef BOOZ2_IMU_B2_ARCH_H
#define BOOZ2_IMU_B2_ARCH_H


#define booz_imu_feed_gyro_accel() {					\
    booz2_max1168_values[IMU_GYRO_P_CHAN] = bsm.gyro->ve[AXIS_P];	\
    booz2_max1168_values[IMU_GYRO_Q_CHAN] = bsm.gyro->ve[AXIS_Q];	\
    booz2_max1168_values[IMU_GYRO_R_CHAN] = bsm.gyro->ve[AXIS_R];	\
    booz2_max1168_values[IMU_ACCEL_X_CHAN] = bsm.accel->ve[AXIS_X];	\
    booz2_max1168_values[IMU_ACCEL_Y_CHAN] = bsm.accel->ve[AXIS_Y];	\
    booz2_max1168_values[IMU_ACCEL_Z_CHAN] = bsm.accel->ve[AXIS_Z];	\
    booz2_max1168_status = STA_MAX1168_DATA_AVAILABLE;			\
  }


#endif /* BOOZ2_IMU_B2_HW_H */