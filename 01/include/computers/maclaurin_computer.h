#pragma once

#include "computer.h"

#include <cmath>

class maclaurin_computer : public computer
{
public:
    double operator()(const double x, const double eps) const override
    {
        double prev, next;
        long k;

        prev = get_init_value(x);
        next = 0;
        k = 0;

        do
        {
            prev += next;
            next = generate_next(x, k++);
        }
        while (std::abs(next) > eps);

        return prev;
    }

protected:
    virtual double get_init_value([[maybe_unused]] const double x) const = 0;
    virtual double generate_next(const double x, const long k) const = 0;
};

