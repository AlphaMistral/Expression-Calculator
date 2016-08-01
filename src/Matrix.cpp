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
    Matrix (r, c);
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

Matrix Matrix :: operator + (const Matrix mat) const
{
    Matrix ret (row_num, col_num, ele);
    for (int i = 0;i < row_num;i++)
        for (int j = 0;j < col_num;j++)
            ele[i][j] += mat.ele[i][j];
    
    return ret;
}


