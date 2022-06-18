#pragma once

class computer
{
public:
    virtual double operator()(const double x, const double eps) const = 0;
};

