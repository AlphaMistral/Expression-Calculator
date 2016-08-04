//
//  Matrix.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/31.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Matrix.hpp"

Matrix :: Matrix ()
{
    row_num = col_num = 0;
    ele = NULL;
    type = NumericType :: MATRIX;
}

Matrix :: Matrix (const Matrix &other)
{
    type = NumericType :: MATRIX;
    row_num = other.row_num;
    col_num = other.col_num;
    ele = new double *[row_num];
    for (int i = 0;i < row_num;i++)
    {
        ele[i] = new double[col_num];
        for (int j = 0;j < col_num;j++)
            ele[i][j] = other.ele[i][j];
    }
}

Matrix :: ~Matrix ()
{
    for (int i = 0;i < row_num;i++)
        delete[] ele[i];
    delete[] ele;
}

Matrix :: Matrix (int r, int c)
{
    type = NumericType :: MATRIX;
    row_num = r;
    col_num = c;
    ele = new double *[r];
    for (int i = 0;i < r;i++)
        ele[i] = new double[c];
}

Matrix :: Matrix (int r, int c, double **num)
{
    type = NumericType :: MATRIX;
    row_num = r;
    col_num = c;
    if (num == NULL)
        return;
    ele = new double *[r];
    for (int i = 0;i < r;i++)
        ele[i] = new double[c];
    for (int i = 0;i < r;i++)
        for (int j = 0;j < c;j++)
            ele[i][j] = num[i][j];
}

Matrix *Matrix :: Zero (int size)
{
    double **values = new double *[size];
    for (int i = 0;i < size;i++)
    {
        values[i] = new double [size];
        for (int j = 0;j < size;j++)
            values[i][j] = 0;
    }
    Matrix *ret = new Matrix (size, size, values);
    for (int i = 0;i < size;i++)
        delete[] values[i];
    delete [] values;
    return ret;
}

Matrix *Matrix :: Unit (int size)
{
    double **values = new double *[size];
    for (int i = 0;i < size;i++)
    {
        values[i] = new double[size];
        for (int j = 0;j < size;j++)
            values[i][j] = 0;
        values[i][i] = 1;
    }
    Matrix *ret = new Matrix (size, size, values);
    for (int i = 0;i < size;i++)
        delete[] values[i];
    delete[] values;
    return ret;
}

Numeric *Matrix :: Clone ()
{
    Matrix *ret = new Matrix (row_num, col_num, ele);
    ret->isValid = isValid;
    return ret;
}

const double **Matrix :: GetValue ()
{
    return (const double **)ele;
}

const NumericType Matrix :: GetType () const
{
    return NumericType :: MATRIX;
}

void Matrix :: SetValue(int r, int c, double **num)
{
    Matrix (r, c);
    for (int i = 0;i < r;i++)
        for (int j = 0;j < c;j++)
            ele[i][j] = num[i][j];
}

bool Matrix :: TestAddable (const Matrix *mat) const
{
    if (row_num == mat->row_num && col_num == mat->col_num)
        return true;
    else return false;
}

bool Matrix :: TestTimable (const Matrix *mat) const
{
    if (col_num == mat->row_num)
        return true;
    else return false;
}

Matrix &Matrix :: operator = (Matrix &mat)
{
    if (this == &mat)
    {
        return *this;
    }
    for (int i = 0;i < row_num;i++)
        delete[] ele[i];
    delete[] ele;
    row_num = mat.row_num;
    col_num = mat.col_num;
    ele = new double*[row_num];
    for (int i = 0;i < row_num;i++)
    {
        ele[i] = new double[col_num];
        for (int j = 0;j < col_num;j++)
            ele[i][j] = mat.ele[i][j];
    }
    return *this;
}

double &Matrix :: operator () (const int row, const int col)
{
    return ele[row][col];
}

double Matrix :: operator () (const int row, const int col) const
{
    if (row >= 0 && row < row_num && col >= 0 && col < col_num)
        return ele[row][col];
    return 0.0;
}

Matrix Matrix :: operator + (const Matrix &mat) const
{
    if (col_num != mat.col_num || row_num != mat.row_num)
    {
        Matrix *t = new Matrix (-1, -1, NULL);
        return *t;
    }
    Matrix *temp = new Matrix (row_num, col_num, ele);
    for (int i = 0;i < row_num;i++)
        for (int j = 0;j < col_num;j++)
            temp->ele[i][j] += mat.ele[i][j];
    Matrix ret = *temp;
    delete temp;
    return ret;
}

Matrix Matrix :: operator - (const Matrix &mat) const
{
    if (col_num != mat.col_num || row_num != mat.row_num)
    {
        return Matrix (-1, -1, NULL);
    }
    Matrix *temp = new Matrix (row_num, col_num, ele);
    for (int i = 0;i < row_num;i++)
        for (int j = 0;j < col_num;j++)
            ele[i][j] -= mat.ele[i][j];
    Matrix ret = *temp;
    delete temp;
    return ret;
}

Matrix Matrix :: operator * (const Matrix &mat) const
{
    if (col_num != mat.row_num)
    {
        return Matrix (-1, -1, NULL);
    }
    double **eles = new double *[row_num];
    for (int i = 0;i < row_num;i++)
    {
        eles[i] = new double [mat.col_num];
        for (int j = 0;j < mat.col_num;j++)
            eles[i][j] = 0;
    }
    Matrix ret (row_num, mat.col_num, eles);
    for (int i = 0;i < row_num;i++)
    {
        for (int j = 0;j < mat.col_num;j++)
        {
            for (int k = 0;k < col_num;k++)
            {
                ret.ele[i][j] += ele[i][k] * mat.ele[k][j];
            }
        }
    }
    for (int i = 0;i < row_num;i++)
        delete[] eles[i];
    delete [] eles;
    return ret;
}

Matrix Matrix :: operator * (const double x) const
{
    Matrix *temp = new Matrix (row_num, col_num, ele);
    for (int i = 0;i < row_num;i++)
        for (int j = 0;j < col_num;j++)
            temp->ele[i][j] *= x;
    Matrix ret = *temp;
    delete temp;
    return ret;
}

Matrix Matrix :: operator *= (const double x) const
{
    for (int i = 0;i < row_num;i++)
        for (int j = 0;j < col_num;j++)
            ele[i][j] *= x;
    Matrix *temp = new Matrix (row_num, col_num, ele);
    Matrix ret = *temp;
    delete temp;
    return ret;
}

Matrix Matrix :: operator *= (const Matrix &mat) const
{
    if (col_num != mat.row_num)
    {
        return Matrix (-1, -1, NULL);
    }
    double **eles = new double *[row_num];
    for (int i = 0;i < row_num;i++)
    {
        eles[i] = new double [mat.col_num];
        for (int j = 0;j < mat.col_num;j++)
            eles[i][j] = 0;
    }
    Matrix ret (row_num, mat.col_num, eles);
    for (int i = 0;i < row_num;i++)
    {
        for (int j = 0;j < mat.col_num;j++)
        {
            for (int k = 0;k < col_num;k++)
            {
                ret.ele[i][j] += ele[i][k] * mat.ele[k][j];
            }
        }
    }
    for (int i = 0;i < row_num;i++)
        delete[] eles[i];
    delete [] eles;
    return ret;
}

void Matrix :: SetTranspose ()
{
    double **originalValue = ele;
    double **newValue = new double*[col_num];
    for (int i = 0;i < col_num;i++)
        newValue[i] = new double [row_num];
    for (int i = 0;i < col_num;i++)
        for (int j = 0;j < row_num;j++)
            newValue[i][j] = originalValue[j][i];
    for (int i = 0;i < row_num;i++)
        delete[] ele[i];
    delete[] ele;
    ele = newValue;
    std :: swap (row_num, col_num);
}

Matrix Matrix :: Transpose() const
{
    double **eles = new double*[col_num];
    for (int i = 0;i < col_num;i++)
        eles[i] = new double [row_num];
    for (int i = 0;i < col_num;i++)
        for (int j = 0;j < row_num;j++)
            eles[i][j] = ele[j][i];
    Matrix *temp = new Matrix (col_num, row_num, eles);
    Matrix ret = *temp;
    delete temp;
    return ret;
}
