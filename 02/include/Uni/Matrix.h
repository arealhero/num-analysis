#pragma once

#include <array>
#include <functional>

#include <cstdint>
#include <cassert>

namespace Uni
{

class Matrix
{
public:
    using ValueType = double;
    using Mapper = std::function<ValueType(ValueType)>;
    using Reducer = std::function<ValueType(ValueType, ValueType)>;
    using Comparator = std::function<bool(ValueType, ValueType)>;

    explicit Matrix(std::size_t rows, std::size_t cols, ValueType initValue = 0);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other);
    ~Matrix();

    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other);

    ValueType& Get(std::size_t i, std::size_t j);
    const ValueType& Get(std::size_t i, std::size_t j) const;

    std::size_t Rows() const { return m_rows; }
    std::size_t Cols() const { return m_cols; }

    std::size_t FindBestInRow(std::size_t row,
            const Comparator& comparator) const;
    std::size_t FindBestInCol(std::size_t col,
            const Comparator& comparator) const;

    void ApplyToRow(std::size_t row, const Mapper& mapper);
    void ApplyToCol(std::size_t col, const Mapper& mapper);

    ValueType ReduceRow(std::size_t row, const Reducer& reducer,
            ValueType initValue) const;
    ValueType ReduceCol(std::size_t col, const Reducer& reducer,
            ValueType initValue) const;

    void SwapRows(std::size_t i, std::size_t j);
    void SwapCols(std::size_t i, std::size_t j);

    Matrix T() const;
    ValueType Norm1() const;
    ValueType NormInf() const;

    Matrix& operator+=(ValueType value);
    Matrix& operator-=(ValueType value);
    Matrix& operator*=(ValueType value);
    Matrix& operator/=(ValueType value);

    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

    friend Matrix operator+(const Matrix& mat, ValueType value);
    friend Matrix operator-(const Matrix& mat, ValueType value);
    friend Matrix operator*(const Matrix& mat, ValueType value);
    friend Matrix operator/(const Matrix& mat, ValueType value);

    friend Matrix operator*(ValueType value, const Matrix& mat);

    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

    static Matrix Identity(std::size_t n);

private:
    ValueType* m_data = nullptr;

    std::size_t m_rows;
    std::size_t m_cols;
};

}

