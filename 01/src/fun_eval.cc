#include <computers/cos_computer.h>
#include <computers/sin_computer.h>
#include <computers/arctan_computer.h>
#include <computers/sqrt_computer.h>

#include <math/constants.h>

#include <iostream>
#include <iomanip>

#include <cstdlib>
#include <cmath>

constexpr long PRECISION = 4;
constexpr double EPS = std::pow(10, -PRECISION + 1);

//constexpr long PI_NUMBERS = 8;

static const double sin_error = EPS / 1.92;
static const double sqrt_error = sin_error;
static const double arctan_error = EPS / 0.5;

double my_eval(const double x)
{
    sin_computer sin;
    sqrt_computer sqrt;
    arctan_computer arctan;

    return sin(HALF_PI - (2.8 * x + sqrt(1 + x, sqrt_error)), sin_error)
        * arctan(1.5 * x + 0.2, arctan_error);
}

double std_eval(double x)
{
    return std::cos(2.8 * x + std::sqrt(1 + x))
        * std::atan(1.5 * x + 0.2);
}

int main()
{
    cos_computer cos;
    sin_computer sin;
    arctan_computer arctan;
    sqrt_computer sqrt;

    constexpr std::size_t text_width = PRECISION + 7;
   
    std::cout << std::setprecision(PRECISION) << std::scientific;

    std::cout
        << "eps: " << EPS << " (precision: " << PRECISION << ')'
        << "\nsin_error: " << sin_error
        << "\nsqrt_error: " << sqrt_error
        << "\narctan_error: " << arctan_error << '\n';

    std::cout
        << std::right << std::setw(text_width) << "x" << " | "
        << std::right << std::setw(text_width) << "std" << " | "
        << std::right << std::setw(text_width) << "my" << " | "
        << std::right << std::setw(text_width) << "diff" << '\n';

    for (double x = 0.1; x <= 0.21; x += 0.01)
    {
        const double std_res = std_eval(x);
        const double my_res = my_eval(x);

        std::cout
            << std::right << std::setw(text_width) << x << " | "
            << std::right << std::setw(text_width) << std_res << " | "
            << std::right << std::setw(text_width) << my_res << " | "
            << std::right << std::setw(text_width) << std_res - my_res << '\n';
    }

    return EXIT_SUCCESS;
}

