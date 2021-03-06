/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#include <AP_HAL/AP_HAL.h>

#if HAL_CPU_CLASS >= HAL_CPU_CLASS_150

/*
  optionally turn down optimisation for debugging
 */
// #pragma GCC optimize("O0")

#include "AP_NavEKF2.h"
#include "AP_NavEKF2_core.h"
#include <AP_AHRS/AP_AHRS.h>
#include <AP_Vehicle/AP_Vehicle.h>

#include <stdio.h>

extern const AP_HAL::HAL& hal;

// reset the body axis gyro bias states to zero and re-initialise the corresponding covariances
void NavEKF2_core::resetGyroBias(void)
{
    stateStruct.gyro_bias.zero();
    zeroRows(P,9,11);
    zeroCols(P,9,11);
    P[9][9] = sq(radians(InitialGyroBiasUncertainty() * dtIMUavg));
    P[10][10] = P[9][9];
    P[11][11] = P[9][9];
}

/*
   vehicle specific initial gyro bias uncertainty in deg/sec
 */
float NavEKF2_core::InitialGyroBiasUncertainty(void) const
{
    return 5.0f;
}


#endif // HAL_CPU_CLASS