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
}

Matrix :: Matrix (const Matrix &other)
{
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
    row_num = r;
    col_num = c;
    ele = new double *[r];
    for (int i = 0;i < r;i++)
        ele[i] = new double[c];
}

Matrix :: Matrix (int r, int c, double **num)
{
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

const void *Matrix :: GetValue () const
{
    return ele;
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


