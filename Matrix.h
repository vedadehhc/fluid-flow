#ifndef MATRIX_H
#define MATRIX_H

#include <exception>
#include <utility>

namespace dev
{
    class MatrixShapeException : public std::exception
    {
    public:
        char *what() { return "Matrix shapes not compatible."; }
    };

    template <class T>
    class Matrix
    {
    private:
        int rows, cols;
        T *m_Arr;

        int getIndex(int r, int c);

    public:
        Matrix(int rows, int cols);
        ~Matrix();

        std::pair<int, int> getShape();
        int getWidth();
        int getHeight();

        friend Matrix operator+(Matrix lhs, const Matrix &rhs);
        friend Matrix operator-(Matrix lhs, const Matrix &rhs);
        friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);

        friend bool operator==(const Matrix &lhs, const Matrix &rhs);
        friend bool operator!=(const Matrix &lhs, const Matrix &rhs);

        T &operator()(int r, int c);
        T &operator()(std::pair<int, int> loc);
    };
}

#endif