//
//  Calculation.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Calculation_hpp
#define Calculation_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>

#include "Numeric.hpp"
#include "Matrix.hpp"
#include "Double.hpp"

using namespace std;

struct CalculationResult
{
    Numeric numeric;
    
    double result;
    bool isValid;
    string statusInformation;
    
    CalculationResult ()
    {
        result = 0.0;
        isValid = false;
        statusInformation = "";
    }
    
    CalculationResult (double r, bool i, string s)
    {
        result = r;
        isValid = i;
        statusInformation = s;
    }
    
    void SetAllParams (double r, bool i, string s)
    {
        result = r;
        isValid = i;
        statusInformation = s;
    }
    
    void OutputResult ()
    {
        cerr << endl << "******The Output Result for the indicated operation is as follows******" << endl;
        cerr << "The numerical result is: " << result << endl;
        cerr << "The result is ";
        if (!isValid) cerr << "in";
        cerr << "valid." << endl;
        cerr << "The Status Information is: " << statusInformation << endl;
        cerr << "******This is the end of the result of the indicated operation******" << endl << endl;
    }
};


CalculationResult operator + (const Numeric &a1, const Numeric &a2);
CalculationResult operator * (const Numeric &a1, const Numeric &a2);
CalculationResult operator - (const Numeric &a1, const Numeric &a2);
CalculationResult operator / (const Numeric &a1, const Numeric &a2);
CalculationResult operator ^ (const Numeric &a1, const Numeric &a2);

CalculationResult operator += (const Numeric &a1, const Numeric &a2);
CalculationResult operator *= (const Numeric &a1, const Numeric &a2);
CalculationResult operator -= (const Numeric &a1, const Numeric &a2);
CalculationResult operator /= (const Numeric &a1, const Numeric &a2);
CalculationResult operator ^= (const Numeric &a1, const Numeric &a2);
#endif /* Calculation_hpp */
