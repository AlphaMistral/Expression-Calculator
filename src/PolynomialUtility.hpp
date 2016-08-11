//
//  PolynomialUtility.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/11.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef PolynomialUtility_hpp
#define PolynomialUtility_hpp

#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Calculation.hpp"
#include "ExpressionParser.hpp"

using namespace std;

class PolynomialUtility
{
    private :
    
    
    
    public :
    
    PolynomialUtility ();
    
    CalculationResult GetPolynomialResult (Expression *, double);
    CalculationResult GetPolynomialResult (vector < double > *, double);
    CalculationResult GetPolynomialResult (Array < double > *, double);
    
    double LagrangeInterpolation (vector < double > *, vector < double > *, double);
    double LagrangeInterpolation (Array < double > *, Array < double > *, double);
    
    double NewtonInterpolation (vector < double > *, vector < double > *, double);
    double NewtonInterpolation (Array < double > *, Array < double > *, double);
    
    Array < double > * PolynomialFitting (vector < double > *, vector < double > *, int);
    Array < double > * PolynomialFitting (Array < double > *, Array < double > *, int);
};

#endif /* PolynomialUtility_hpp */
