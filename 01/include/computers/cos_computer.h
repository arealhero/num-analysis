#pragma once

#include "maclaurin_computer.h"

#include <math/factorial.h>

class cos_computer : public maclaurin_computer
{
protected:
    double get_init_value([[maybe_unused]] const double x) const override
    {
        return 0;
    }

    double generate_next(const double x, const long k) const override
    {
        return (k % 2 ? -1.0 : 1.0) * std::pow(x, 2 * k) / factorial(2 * k);
    }
};

