//
//  Calculation.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Matrix.hpp"
#include "Double.hpp"

#include "Calculation.hpp"
/*
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

CalculationResult :: CalculationResult (CalculationResult &calc)
{
    result = calc.result;
    isValid = calc.isValid;
    statusInformation = calc.statusInformation;
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

void CalculationResult :: AttachInformation (string s)
{
    statusInformation += s;
}

void CalculationResult :: OutputResult ()
{
    cerr << endl << "******The Output Result for the indicated operation is as follows******" << endl;
    cerr << "The numerical result is: " << result << endl;
    cerr << "The result is ";
    if (!isValid) cerr << "in";
    cerr << "valid." << endl;
    cerr << "The Status Information is: " << statusInformation << endl;
    cerr << "******This is the end of the result of the indicated operation******" << endl << endl;
}
*/




CalculationResult operator + (const Numeric a1, const Numeric a2)
{
    CalculationResult ret;
    if (a1.GetType () == a2.GetType () && a1.GetType () == NumericType :: DOUBLE)
    {
        ret.numeric = Double (*(double *)a1.GetValue () + *(double *)a2.GetValue ());
    }
    else if (a1.GetType () == a2.GetType () && a1.GetType () == NumericType :: MATRIX)
    {
        const Matrix *m1 = static_cast<const Matrix *> (&a1);
        const Matrix *m2 = static_cast<const Matrix *> (&a2);
        if (!m1->TestAddable (m2))
        {
            ret.statusInformation += "The two Matrices could not be added together because they have different sizes! \n";
        }
        else
        {
            ret.numeric = *m1 + *m2;
        }
    }
    else
    {
        ret.statusInformation += "The two elements are of different types, and thus it is totally illegal to add them together! \n";
    }
    return ret;
}

CalculationResult operator * (const Numeric a1, const Numeric a2)
{
    CalculationResult ret;
    if (a1.GetType () == a2.GetType () && a1.GetType () == NumericType :: DOUBLE)
    {
        ret.numeric = Double (*(double *)a1.GetValue () * *(double *)a2.GetValue ());
    }
    else if (a1.GetType () == a2.GetType () && a1.GetType () == NumericType :: MATRIX)
    {
        
    }
    else
    {
        
    }
    return ret;
}