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

using namespace std;

class Matrix
{
    private :
    
    int row_num, col_num;
    double **ele;
    
    public :
    
    Matrix ();
    Matrix (int, int);
    Matrix (int, int, double **);
};
#endif /* Matrix_hpp */
