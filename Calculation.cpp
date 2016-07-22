//
//  Calculation.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Calculation.hpp"

CalculationResult :: CalculationResult ()
{
    result = 0;
    isValid = false;
    statusInformation = "";
}

CalculationResult :: CalculationResult (double r, bool v, string s)
{
    result = r;
    isValid = v;
    statusInformation = s;
}

void CalculationResult :: SetAllParams (double r, bool v, string s)
{
    result = r;
    isValid = v;
    statusInformation = s;
}

void CalculationResult :: SetResult (double r)
{
    result = r;
}

void CalculationResult :: SetValidity (bool v)
{
    isValid = v;
}

void CalculationResult :: SetInformation (string s)
{
    statusInformation = s;
}

double CalculationResult :: GetResult ()
{
    return result;
}

bool CalculationResult :: GetValidity ()
{
    return isValid;
}

string CalculationResult :: GetInformation ()
{
    return statusInformation;
}