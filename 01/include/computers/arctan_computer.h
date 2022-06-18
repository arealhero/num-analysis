#pragma once

#include <computers/maclaurin_computer.h>

#include <math/math.h>
#include <cmath>

class arctan_computer : public maclaurin_computer
{
protected:
    double get_init_value([[maybe_unused]] const double x) const override
    {
        return std::abs(x) < 1 ? 0 : HALF_PI * sgn(x);
    }

    double generate_next(const double x, const long k) const override
    {
        if (std::abs(x) < 1)
            return (k % 2 ? -1.0 : 1.0) * std::pow(x, 2 * k + 1) / (2 * k + 1);
        else
            return (k % 2 ? 1.0 : -1.0) * std::pow(x, -(2 * k + 1)) / (2 * k + 1);
    }
};

