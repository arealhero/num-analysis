#pragma once

#include <unordered_map>

long factorial(long n)
{
    static std::unordered_map<long, long> lut = { { 0, 1 } };

    auto it = lut.find(n);
    if (it == lut.end())
        return lut.emplace(n, n * factorial(n - 1)).first->second;
    else
        return it->second;
}

