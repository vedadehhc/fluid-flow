#include "Matrix.h"

namespace dev
{
    template <class T>
    Matrix<T>::Matrix(int rows, int cols) : rows(rows), cols(cols)
    {
        m_Arr = new T[rows * cols];
    }

    template <class T>
    Matrix<T>::~Matrix()
    {
        delete[] m_Arr;
    }

    template <class T>
    int Matrix<T>::getIndex(int r, int c)
    {
        return r * cols + c;
    }

    template <class T>
    std::pair<int, int> Matrix<T>::getShape()
    {
        return std::make_pair(rows, cols);
    }

    template <class T>
    int Matrix<T>::getWidth() { return cols; }

    template <class T>
    int Matrix<T>::getHeight() { return rows; }

    template <class T>
    Matrix<T> operator+(Matrix<T> lhs, const Matrix<T> &rhs)
    {
        if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
            throw MatrixShapeException();

        for (int i = 0; i < lhs.rows; i++)
        {
            for (int j = 0; j < rhs.rows; j++)
            {
                lhs(i, j) += rhs(i, j);
            }
        }

        return lhs;
    }

    template <class T>
    Matrix<T> operator-(Matrix<T> lhs, const Matrix<T> &rhs)
    {
        if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
            throw MatrixShapeException();

        for (int i = 0; i < lhs.rows; i++)
        {
            for (int j = 0; j < rhs.rows; j++)
            {
                lhs(i, j) -= rhs(i, j);
            }
        }

        return lhs;
    }

    template <class T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if (lhs.cols != rhs.rows)
            throw MatrixShapeException();

        Matrix<T> res(lhs.rows, rhs.cols);

        T val;
        for (int i = 0; i < lhs.rows; i++)
        {
            for (int j = 0; j < rhs.cols; j++)
            {
                val = 0;
                for (int k = 0; k < lhs.cols; k++)
                {
                    val += lhs(i, k) * rhs(k, j);
                }
                res(i, j) = val;
            }
        }

        return res;
    }

    template <class T>
    bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if (lhs.rows != rhs.rows || lhs.cols != rhs.cols)
            return false;
        
        for (int i = 0; i < lhs.rows; i++)
        {
            for (int j = 0; j < lhs.cols; j++)
            {
                if (lhs(i, j) !=  rhs(i, j))
                    return false;
            }
        }

        return true;
    }

    template <class T>
    bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        return !(lhs == rhs);
    }

    template <class T>
    T &Matrix<T>::operator()(int r, int c)
    {
        return m_Arr[getIndex(r, c)];
    }

    template <class T>
    T &Matrix<T>::operator()(std::pair<int, int> loc)
    {
        return m_Arr[getIndex(loc.first, loc.second)];
    }
}