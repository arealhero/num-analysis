#pragma once

#include <computers/computer.h>

#include <cmath>

class sqrt_computer : public computer
{
public:
    double operator()(const double x, const double eps) const override
    {
        double prev, next;

        next = 1.1;

        do
        {
            prev = next;
            next = (prev + x / prev) / 2;
        }
        while (std::abs(prev - next) > eps);

        return next;
    }
};

