#include <Uni/Methods/SeidelMethod.h>

namespace Uni::Methods
{

Matrix SeidelMethod::Solve(const Matrix& a, const Matrix& b,
        [[maybe_unused]] double eps)
{
    Matrix c(a.Rows(), a.Cols(), 0);
    Matrix d(a.Rows(), 1, 0);

    for (std::size_t i = 0; i < c.Rows(); ++i)
    {
        auto dividor = a.Get(i, i);
        d.Get(i, 0) = b.Get(i, 0) / dividor;

        for (std::size_t j = 0; j < c.Cols(); ++j)
        {
            if (i == j) continue;
            c.Get(i, j) = - a.Get(i, j) / dividor;
        }
    }

    Matrix prev(a.Rows(), 1);
    Matrix x = d;
    Matrix diff(a.Rows(), 1);

    double norm = c.Norm1();
    double factor = std::abs(norm / (1 - norm));

    do
    {
        prev = x;
        x = c * x + d;
        diff = x - prev;
    }
    while (factor * diff.Norm1() > eps);

    return x;
}

}

