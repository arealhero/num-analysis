#pragma once

#include <Uni/Matrix.h>
#include <Uni/Methods/IMethod.h>

namespace Uni::Methods
{

class SeidelMethod : public IMethod
{
public:
    Matrix Solve(const Matrix& a, const Matrix& b,
            [[maybe_unused]] double eps) override;

    std::string GetName() const override { return "Seidel"; }
};

}

