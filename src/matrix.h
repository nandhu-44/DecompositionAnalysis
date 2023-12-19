#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cmath>
#include <iomanip>
#include <tuple>
#include <fstream>
#include <sstream>

class Matrix
{
public:
    int rows;
    int cols;
    float **data;

    Matrix() {}
    Matrix(int rows, int cols);
    Matrix(const Matrix &m);
    Matrix(const std::string &filename);
    void setMatrix();
    void printMatrix();
    Matrix operator*(const Matrix &m2);
};

bool isSymmetric(const Matrix &m);
std::tuple<Matrix, Matrix> CLDecomposition(const Matrix &m);
std::tuple<Matrix, Matrix> LUDecomposition(const Matrix &m);
std::tuple<Matrix, Matrix> QRDecomposition(const Matrix &m);
Matrix transpose(const Matrix &m);

Matrix::Matrix(int rows, int cols)
    : rows(rows), cols(cols), data(new float *[rows])
{
    for (int i = 0; i < rows; i++)
    {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = 0;
        }
    }
}

Matrix::Matrix(const std::string &filename) : rows(0), cols(0), data(nullptr)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        int rowCount = 0;
        int colCount = 0;

        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            float value;
            colCount = 0;
            while (ss >> value)
            {
                colCount++;
                if (ss.peek() == ',')
                {
                    ss.ignore();
                }
            }
            rowCount++;
        }

        rows = rowCount;
        cols = colCount;
        data = new float *[rows];
        for (int i = 0; i < rows; i++)
        {
            data[i] = new float[cols];
        }

        file.clear();
        file.seekg(0, std::ios::beg);

        int row = 0;
        while (std::getline(file, line))
        {
            std::stringstream ss(line);
            int col = 0;
            float value;
            while (ss >> value)
            {
                if (col < cols)
                {
                    data[row][col++] = value;
                }
                if (ss.peek() == ',' || ss.peek() == ' ')
                {
                    ss.ignore();
                }
            }
            row++;
        }

        file.close();
        std::cout << "Matrix loaded from CSV file: " << filename << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

Matrix::Matrix(const Matrix &m) : rows(m.rows), cols(m.cols), data(new float *[rows])
{
    for (int i = 0; i < rows; i++)
    {
        data[i] = new float[cols];
        for (int j = 0; j < cols; j++)
        {
            data[i][j] = m.data[i][j];
        }
    }
}

void Matrix::setMatrix()
{
    std::cout << "Enter the elements of the matrix" << std::endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cin >> data[i][j];
        }
    }
}

void Matrix::printMatrix()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            std::cout << std::setw(10) << data[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

Matrix Matrix::operator*(const Matrix &m2)
{
    if (cols != m2.rows)
    {
        std::cout << "Error: Matrix multiplication not possible." << std::endl;
        exit(1);
    }
    Matrix m(rows, m2.cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < m2.cols; j++)
        {
            m.data[i][j] = 0;
            for (int k = 0; k < cols; k++)
            {
                m.data[i][j] += data[i][k] * m2.data[k][j];
            }
        }
    }
    return m;
}

bool isSymmetric(const Matrix &m)
{
    if (m.rows != m.cols)
    {
        return false;
    }
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = i + 1; j < m.cols; j++)
        {
            if (m.data[i][j] != m.data[j][i])
            {
                return false;
            }
        }
    }
    return true;
}

std::tuple<Matrix, Matrix> CLDecomposition(const Matrix &m)
{
    if (!isSymmetric(m))
    {
        throw std::invalid_argument("[CL] => Matrix is not symmetric.");
    }
    int n = m.rows;
    Matrix L(n, n), Lt(n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            float sum = 0;
            if (i == j)
            {
                for (int k = 0; k < j; k++)
                {
                    sum += L.data[j][k] * L.data[j][k];
                }
                if (m.data[j][j] - sum < 0)
                {
                    throw std::invalid_argument("[CL] => Negative value under square root.");
                }
                L.data[j][j] = sqrt(m.data[j][j] - sum);
            }
            else if (i > j)
            {
                for (int k = 0; k < j; k++)
                {
                    sum += L.data[i][k] * L.data[j][k];
                }
                if (L.data[j][j] == 0)
                {
                    throw std::invalid_argument("[CL] => Division by zero.");
                }
                L.data[i][j] = (m.data[i][j] - sum) / L.data[j][j];
            }
        }
    }
    Lt = transpose(L);

    return std::make_tuple(L, Lt);
}

std::tuple<Matrix, Matrix> LUDecomposition(const Matrix &m)
{
    int n = m.rows;
    Matrix L(n, n), U(n, n);

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            float sum = 0;
            for (int k = 0; k < i; k++)
            {
                sum += L.data[i][k] * U.data[k][j];
            }
            U.data[i][j] = m.data[i][j] - sum;
        }
        for (int j = i; j < n; j++)
        {
            if (i == j)
            {
                if (U.data[i][i] == 0)
                {
                    throw std::invalid_argument("[LU] => Division by zero.");
                }
                L.data[i][i] = 1;
            }
            else
            {
                float sum = 0;
                for (int k = 0; k < i; k++)
                {
                    sum += L.data[j][k] * U.data[k][i];
                }
                L.data[j][i] = (m.data[j][i] - sum) / U.data[i][i];
            }
        }
    }

    return std::make_tuple(L, U);
}

std::tuple<Matrix, Matrix> QRDecomposition(const Matrix &m)
{
    int n = m.rows;
    Matrix Q(n, n), R(n, n);

    for (int i = 0; i < n; i++)
    {
        float sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += m.data[j][i] * m.data[j][i];
        }
        if (sum == 0)
        {
            throw std::invalid_argument("[QR] => Division by zero.");
        }
        R.data[i][i] = sqrt(sum);
        for (int j = 0; j < n; j++)
        {
            Q.data[j][i] = m.data[j][i] / R.data[i][i];
        }
        for (int j = i + 1; j < n; j++)
        {
            float sum = 0;
            for (int k = 0; k < n; k++)
            {
                sum += Q.data[k][i] * m.data[k][j];
            }
            R.data[i][j] = sum;
        }
    }

    return std::make_tuple(Q, R);
}

Matrix transpose(const Matrix &m)
{
    Matrix t(m.cols, m.rows);
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.cols; j++)
        {
            t.data[j][i] = m.data[i][j];
        }
    }
    return t;
}

#endif
