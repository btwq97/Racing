#pragma once

#ifndef CAR_HPP
#define CAR_HPP

#include <cmath>

struct Car
{
    /*
        Characteristics
    */
    float x, y, speed, angle; int n;

    // Initialisation
    Car() { x = 0; y = 0; speed = 2; angle = 0; n = 0; }
    /*
        change x & y coor
    */
    void move();
    /*
        Update car positions
    */
    void findTarget();
    /*
        Reset car characteristics
    */
    void reset();
};

#endif