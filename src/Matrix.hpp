//
//  Matrix.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/31.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <algorithm>

#include "Numeric.hpp"

using namespace std;

class Matrix : public Numeric
{
    private :
    
    int row_num, col_num;
    double **ele;
    
    public :
    
    Matrix ();
    ~Matrix ();
    Matrix (int, int);
    Matrix (int, int, double **);
    Matrix (int, int, const double **);
    Matrix (const Matrix &other);
    
    static Matrix *Zero (int);
    static Matrix *Unit (int);
    
    virtual Numeric *Clone ();
    
    const NumericType GetType () const;
    const double **GetValue ();
    void SetValue (int, int, double **);
    
    bool TestAddable (const Matrix *) const;
    bool TestTimable (const Matrix *) const;
    
    Matrix operator + (const Matrix &) const;
    Matrix operator - (const Matrix &) const;
    Matrix operator * (const Matrix &) const;
    Matrix operator * (const double) const;
    Matrix operator *= (const double) const;
    Matrix operator *= (const Matrix &) const;
    
    Matrix &operator = (Matrix &);
    
    double & operator () (const int, const int);
    double operator () (const int, const int) const;
    
    Matrix Transpose () const;
    Matrix Inverse () const;
    Matrix Inverse_Transpose () const;
    
    void SetTranspose ();
    void SetInverse ();
    void SetInverse_Transpose ();
    
    void SwapRow (int, int);
    void AddRow (int, int, double);
    
    const int GetRowNum () const
    {
        return row_num;
    }
    
    const int GetColNum () const
    {
        return col_num;
    }
    
    void SetValue (int x, int y, double v)
    {
        ele[x][y] = v;
    }
    
    friend void swap (Matrix &first, Matrix &second)
    {
        using std :: swap;
        Matrix t(second);
        swap (first.row_num, t.row_num);
        swap (first.col_num, t.col_num);
        swap (first.ele, t.ele);
    }
    
    const double **GetAddress ()
    {
        return (const double **)ele;
    }
    
    static bool TestEquationSolvable (Matrix *, vector < double > *);
};

#endif /* Matrix_hpp */
