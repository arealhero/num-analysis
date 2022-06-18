#include <Uni/Matrix.h>
#include <Uni/Methods/IMethod.h>
#include <Uni/Methods/GaussMethod.h>
#include <Uni/Methods/SeidelMethod.h>

#include <vector>
#include <memory>

#include <cstdio>
#include <cmath>

constexpr std::size_t MY_N = 11;
constexpr double MY_EPS = 1e-6;

constexpr std::size_t TEST_SIZE = 3;
constexpr std::size_t ILL_CONDITIONED_SIZE = 4;

void print(const Uni::Matrix& mat)
{
    for (std::size_t i = 0; i < mat.Rows(); ++i)
    {
        for (std::size_t j = 0; j < mat.Cols(); ++j)
            std::printf("%lf ", mat.Get(i, j));
        std::puts("");
    }
    std::puts("");
}

Uni::Matrix UpperTriangle(std::size_t n)
{
    Uni::Matrix result(n, n);
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t j = 0; j < n; ++j)
            result.Get(i, j) = j >= i;
    return result;
}

bool Verify(std::shared_ptr<Uni::Methods::IMethod> method, double eps)
{
    Uni::Matrix a(TEST_SIZE, TEST_SIZE, 1);
    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        a.Get(i, i) = MY_N + 2 * (i + 1);

    Uni::Matrix b(TEST_SIZE, 1, MY_N);
    for (std::size_t i = 0; i < TEST_SIZE; ++i)
        b.Get(i, 0) += 2 * (i + 2);

    auto x = method->Solve(a, b, eps);
    for (std::size_t i = 0; i < TEST_SIZE; ++i)
    {
        if (std::abs(x.Get(i, 0) - 1) > eps)
        {
            printf("ERROR: expected 1, got %lf\n", x.Get(i, 0));

            puts("a:");
            print(a);

            puts("b:");
            print(b);

            puts("x:");
            print(x);

            return false;
        }
    }

    return true;
}

void TestIllConditionedSystems(std::shared_ptr<Uni::Methods::IMethod> method)
{
    for (std::size_t n = 3; n < 6; ++n)
    {
        for (std::size_t p = 4; p < 7; ++p)
        {
            double eps = 1 / std::pow(10, p);
            std::printf("   ---> n: %ld, eps: %lf \n", n, eps);

            auto e = Uni::Matrix::Identity(n);
            auto ut = UpperTriangle(n);
            auto a_1 = 2 * e - ut;
            auto a_2 = ut.T() + e - ut;

            auto a = a_1 + MY_N * eps * a_2;

            Uni::Matrix b{n, 1, -1};
            b.Get(n - 1, 0) = 1;

            print(a);
            print(b);

            auto x = method->Solve(a, b, eps);
            print(x);

            print(a * x - b);
        }
    }
}

void TestMethod(std::shared_ptr<Uni::Methods::IMethod> method)
{
    double eps = 1e-6;

    std::printf(" --- %s --- \n", method->GetName().c_str());

    if (Verify(method, eps))
    {
        std::puts("Verification passed");
    }
    else
    {
        std::puts("Verification failed");
        return;
    }

    TestIllConditionedSystems(method);
}

int main()
{
    std::vector<std::shared_ptr<Uni::Methods::IMethod>> methods =
    {
        std::make_shared<Uni::Methods::GaussMethod>(),
        std::make_shared<Uni::Methods::SeidelMethod>(),
    };

    for (auto& method : methods)
        TestMethod(method);

    return 0;
}

