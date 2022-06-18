#include <Uni/Methods/GaussMethod.h>

namespace Uni::Methods
{

Matrix GaussMethod::Solve(const Matrix& a, const Matrix& b,
        [[maybe_unused]] double eps)
{
    auto aCopy = a;
    auto bCopy = b;
    
    Down(aCopy, bCopy);
    Up(aCopy, bCopy);
    return bCopy;
}

void GaussMethod::Down(Matrix& a, Matrix& b)
{
    for (std::size_t currentIndex = 0; currentIndex < a.Rows(); ++currentIndex)
    {
        std::size_t maxRowIndex = a.FindBestInRow(currentIndex,
                [](double lhs, double rhs)
                {
                    return std::abs(lhs) < std::abs(rhs);
                });

        a.SwapRows(currentIndex, maxRowIndex);
        b.SwapRows(currentIndex, maxRowIndex);

        auto maxElement = a.Get(currentIndex, currentIndex);
        auto divider = [maxElement](double value)
        {
            return value / maxElement;
        };

        a.ApplyToRow(currentIndex, divider);
        b.ApplyToRow(currentIndex, divider);

        for (std::size_t i = currentIndex + 1; i < a.Rows(); ++i)
        {
            double factor = a.Get(i, currentIndex);

            for (std::size_t j = 0; j < a.Cols(); ++j)
                a.Get(i, j) -= factor * a.Get(currentIndex, j);

            for (std::size_t j = 0; j < b.Cols(); ++j)
                b.Get(i, j) -= factor * b.Get(currentIndex, j);
        }
    }
}

void GaussMethod::Up(Matrix& a, Matrix& b)
{
    for (std::size_t currentIndex = a.Rows() - 1; currentIndex != 0; --currentIndex)
    {
        for (std::size_t i = currentIndex; i != 0; --i)
        {
            auto factor = a.Get(i - 1, currentIndex);

            for (std::size_t j = 0; j < a.Cols(); ++j)
                a.Get(i - 1, j) -= factor * a.Get(currentIndex, j);

            for (std::size_t j = 0; j < b.Cols(); ++j)
                b.Get(i - 1, j) -= factor * b.Get(currentIndex, j);
        }
    }
}

}

