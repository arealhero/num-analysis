#include <Uni/Matrix.h>

#include <cstring>

namespace Uni
{

Matrix::Matrix(std::size_t rows, std::size_t cols, ValueType initValue)
    : m_rows(rows)
    , m_cols(cols)
{
    assert(rows > 0 && cols > 0);
    m_data = (ValueType*) malloc(sizeof(ValueType) * m_rows * m_cols);

    for (std::size_t i = 0; i < m_rows; ++i)
        for (std::size_t j = 0; j < m_cols; ++j)
            Get(i, j) = initValue;
}
Matrix::Matrix(const Matrix& other)
    : m_rows(other.Rows())
    , m_cols(other.Cols())
{
	const std::size_t bytes = sizeof(ValueType) * m_rows * m_cols;
	m_data = (ValueType*) malloc(bytes);
    std::memcpy(m_data, other.m_data, bytes);
}
Matrix::Matrix(Matrix&& other)
    : m_rows(other.Rows())
    , m_cols(other.Cols())
{
    m_data = other.m_data;
    other.m_data = nullptr;
}

Matrix::~Matrix()
{
    if (m_data)
        free(m_data);
}

Matrix& Matrix::operator=(const Matrix& other)
{
    m_rows = other.m_rows;
    m_cols = other.m_cols;

	const std::size_t bytes = sizeof(ValueType) * m_rows * m_cols;
	m_data = (ValueType*) malloc(bytes);
    std::memcpy(m_data, other.m_data, bytes);

    return *this;
}

Matrix& Matrix::operator=(Matrix&& other)
{
    m_rows = other.m_rows;
    m_cols = other.m_cols;

    m_data = other.m_data;
    other.m_data = nullptr;

    return *this;
}

Matrix::ValueType& Matrix::Get(std::size_t i, std::size_t j)
{
    assert(i < m_rows && j < m_cols);
    return m_data[i * m_cols + j];
}
const Matrix::ValueType& Matrix::Get(std::size_t i, std::size_t j) const
{
    assert(i < m_rows && j < m_cols);
    return m_data[i * m_cols + j];
}

std::size_t Matrix::FindBestInRow(std::size_t row,
        const Matrix::Comparator& comparator) const
{
    assert(row < m_rows);

    ValueType best = Get(row, 0);
    std::size_t bestIndex = 0;

    for (std::size_t col = 1; col < m_cols; ++col)
    {
        auto& current = Get(row, col);
        if (comparator(best, current))
        {
            best = current;
            bestIndex = col;
        }
    }
    return bestIndex;
}

std::size_t Matrix::FindBestInCol(std::size_t col,
        const Matrix::Comparator& comparator) const
{
    assert(col < m_cols);

    ValueType best = Get(0, col);
    std::size_t bestIndex = 0;

    for (std::size_t row = 1; row < m_rows; ++row)
    {
        auto& current = Get(row, col);
        if (comparator(best, current))
        {
            best = current;
            bestIndex = row;
        }
    }
    return bestIndex;
}

void Matrix::ApplyToRow(std::size_t row, const Matrix::Mapper& mapper)
{
    assert(row < m_rows);

    for (std::size_t col = 0; col < m_cols; ++col)
    {
        auto& current = Get(row, col);
        current = mapper(current);
    }
}

void Matrix::ApplyToCol(std::size_t col, const Matrix::Mapper& mapper)
{
    assert(col < m_cols);

    for (std::size_t row = 0; row < m_rows; ++row)
    {
        auto& current = Get(row, col);
        current = mapper(current);
    }
}

Matrix::ValueType Matrix::ReduceRow(std::size_t row,
        const Matrix::Reducer& reducer,
        Matrix::ValueType initValue) const
{
    assert(row < m_rows);

    ValueType result = initValue;
    for (std::size_t col = 0; col < m_cols; ++col)
    {
        result = reducer(result, Get(row, col));
    }
    return result;
}

Matrix::ValueType Matrix::ReduceCol(std::size_t col,
        const Matrix::Reducer& reducer,
        Matrix::ValueType initValue) const
{
    assert(col < m_cols);

    ValueType result = initValue;
    for (std::size_t row = 0; row < m_rows; ++row)
    {
        result = reducer(result, Get(row, col));
    }
    return result;
}

void Matrix::SwapRows(std::size_t i, std::size_t j)
{
    assert(i < m_rows && j < m_rows);

    for (std::size_t col = 0; col < m_cols; ++col)
    {
        ValueType temp = Get(i, col);
        Get(i, col) = Get(j, col);
        Get(j, col) = temp;
    }
}

void Matrix::SwapCols(std::size_t i, std::size_t j)
{
    assert(i < m_cols && j < m_cols);

    for (std::size_t row = 0; row < m_rows; ++row)
    {
        ValueType temp = Get(row, i);
        Get(row, i) = Get(row, j);
        Get(row, j) = temp;
    }
}

Matrix Matrix::T() const
{
    Matrix result(m_cols, m_rows);
    for (std::size_t i = 0; i < m_rows; ++i)
        for (std::size_t j = 0; j < m_cols; ++j)
            result.Get(i, j) = Get(j, i);
    return result;
}

Matrix::ValueType Matrix::Norm1() const
{
    ValueType result = 0;

    for (std::size_t j = 0; j < m_cols; ++j)
    {
        ValueType sum = 0;

        for (std::size_t i = 0; i < m_rows; ++i)
            sum += std::abs(Get(i, j));

        if (sum > result)
            result = sum;
    }

    return result;
}

Matrix::ValueType Matrix::NormInf() const
{
    ValueType result = 0;

    for (std::size_t i = 0; i < m_rows; ++i)
    {
        ValueType sum = 0;

        for (std::size_t j = 0; j < m_cols; ++j)
            sum += std::abs(Get(i, j));

        if (sum > result)
            result = sum;
    }

    return result;
}

Matrix& Matrix::operator+=(Matrix::ValueType value)
{
    for (std::size_t i = 0; i < m_rows; ++i)
        for (std::size_t j = 0; j < m_cols; ++j)
            Get(i, j) += value;
    return *this;
}
Matrix& Matrix::operator-=(Matrix::ValueType value)
{
    for (std::size_t i = 0; i < m_rows; ++i)
        for (std::size_t j = 0; j < m_cols; ++j)
            Get(i, j) -= value;
    return *this;
}
Matrix& Matrix::operator*=(Matrix::ValueType value)
{
    for (std::size_t i = 0; i < m_rows; ++i)
        for (std::size_t j = 0; j < m_cols; ++j)
            Get(i, j) *= value;
    return *this;
}
Matrix& Matrix::operator/=(Matrix::ValueType value)
{
    for (std::size_t i = 0; i < m_rows; ++i)
        for (std::size_t j = 0; j < m_cols; ++j)
            Get(i, j) /= value;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& other)
{
    assert(Rows() == other.Rows() && Cols() == other.Cols());

    for (std::size_t i = 0; i < m_rows; ++i)
        for (std::size_t j = 0; j < m_cols; ++j)
            Get(i, j) += other.Get(i, j);
    return *this;
}
Matrix& Matrix::operator-=(const Matrix& other)
{
    assert(Rows() == other.Rows() && Cols() == other.Cols());

    for (std::size_t i = 0; i < m_rows; ++i)
        for (std::size_t j = 0; j < m_cols; ++j)
            Get(i, j) -= other.Get(i, j);
    return *this;
}

Matrix operator+(const Matrix& mat, Matrix::ValueType value)
{
    Matrix result(mat);
    result += value;
    return result;
}
Matrix operator-(const Matrix& mat, Matrix::ValueType value)
{
    Matrix result(mat);
    result -= value;
    return result;
}
Matrix operator*(const Matrix& mat, Matrix::ValueType value)
{
    Matrix result(mat);
    result *= value;
    return result;
}
Matrix operator/(const Matrix& mat, Matrix::ValueType value)
{
    Matrix result(mat);
    result /= value;
    return result;
}

Matrix operator*(Matrix::ValueType value, const Matrix& mat)
{
    Matrix result(mat);
    result *= value;
    return result;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
    assert(lhs.Rows() == rhs.Rows() && lhs.Cols() == rhs.Cols());

    Matrix result(lhs);
    result += rhs;
    return result;
}
Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
    assert(lhs.Rows() == rhs.Rows() && lhs.Cols() == rhs.Cols());

    Matrix result(lhs);
    result -= rhs;
    return result;
}
Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    assert(lhs.Cols() == rhs.Rows());

    Matrix result(lhs.Rows(), rhs.Cols());
    for (std::size_t i = 0; i < result.Rows(); ++i)
        for (std::size_t j = 0; j < result.Cols(); ++j)
            for (std::size_t k = 0; k < lhs.Cols(); ++k)
                result.Get(i, j) += lhs.Get(i, k) * rhs.Get(k, j);
    return result;
}

Matrix Matrix::Identity(std::size_t n)
{
    assert(n > 0);

    Matrix identity(n, n);
    for (std::size_t i = 0; i < n; ++i)
        for (std::size_t j = 0; j < n; ++j)
            identity.Get(i, j) = (i == j);
    return identity;
}

}

