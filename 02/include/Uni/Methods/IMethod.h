#pragma once

#include <Uni/Matrix.h>

#include <string>

namespace Uni::Methods
{

class IMethod
{
public:
    virtual Matrix Solve(const Matrix& a, const Matrix& b,
            [[maybe_unused]] double eps) = 0;

    virtual std::string GetName() const { return "Unknown"; }
};

}

