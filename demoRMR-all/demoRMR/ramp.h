#ifndef RAMP_H
#define RAMP_H

#include "point.h"

class Ramp {
public:
    Ramp();
    ~Ramp();

    void compute(double *speed, double *speed_rot, double change_speed);
    void clear_time();
    void clear_time_hard();

private:
    double current_speed_multiplier;
    double max_speed = 1.0;  //to max speed 100%
};

#endif
