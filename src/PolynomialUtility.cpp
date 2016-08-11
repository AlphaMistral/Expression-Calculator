//
//  PolynomialUtility.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/11.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "PolynomialUtility.hpp"

PolynomialUtility :: PolynomialUtility ()
{
    
}

CalculationResult PolynomialUtility :: GetPolynomialResult (Expression *expr, double xValue)
{
    CalculationResult ret;
    ExpressionParser *parser = new ExpressionParser (expr);
    Double *d1 = new Double (xValue);
    parser->SetVariable ("x", d1);
    ret = parser->ParseExpression ();
    delete parser;
    return ret;
}

CalculationResult PolynomialUtility :: GetPolynomialResult (vector < double > *array, double xValue)
{
    double yValue = 0;
    int index = 0;
    for (vector < double > :: iterator iter = array->begin ();iter != array->end ();iter++)
    {
        yValue += pow (xValue, index++) * (*iter);
    }
    CalculationResult ret;
    ret.numeric.reset (new Double (yValue));
    return ret;
}

CalculationResult PolynomialUtility :: GetPolynomialResult (Array<double> *array, double xValue)
{
    CalculationResult ret;
    double yValue = 0;
    int index = 0;
    vector < double > vec = array->GetCopy ();
    for (vector < double > :: iterator iter = vec.begin ();iter != vec.end ();iter++)
    {
        yValue += pow (xValue, index++) * (*iter);
    }
    return ret;
}

double PolynomialUtility :: LagrangeInterpolation(vector < double > *xValues, vector < double > *yValues, double xi)
{
    double ans = 0;
    int size = (int)xValues->size ();
    for (int i = 0;i < size;i++)
    {
        int s = 1, t = 1;
        for (int j = 0;j < size;j++)
        {
            if (j != i)
            {
                s = s * (xi - (*xValues)[j]);
                t = t * ((*xValues)[i] - (*xValues)[j]);
            }
        }
        ans += (s / t) * (*yValues)[i];
    }
    return ans;
}

double PolynomialUtility :: LagrangeInterpolation(Array < double > *xValues, Array < double > *yValues, double xi)
{
    double ans = 0;
    vector < double > x = xValues->GetCopy ();
    vector < double > y = yValues->GetCopy ();
    int size = (int)x.size ();
    for (int i = 0;i < size;i++)
    {
        int s = 1, t = 1;
        for (int j = 0;j < size;j++)
        {
            if (j != i)
            {
                s = s * (xi - x[i]);
                t = t * (x[i] - x[j]);
            }
        }
        ans += (s / t) * y[i];
    }
    return ans;
}

double PolynomialUtility :: NewtonInterpolation(vector < double > *xValues, vector < double > *yValues, double xi)
{
    double ans = 0;
    int size = (int)xValues->size ();
    vector < double > x = *xValues;
    vector < double > y = *yValues;
    for (int i = 0;i < size;i++)
    {
        for (int k = size - 1;k > i;k--)
        {
            y[k] = (y[k] - y[k - 1]) / (x[k] - x[k - i - 1]);
        }
    }
    double mult = 1;
    for (int i = size - 1;i >= 0;i--)
    {
        mult = 1;
        for (int j = 0;j < i;j++)
            mult *= (xi - x[j]);
        mult *= y[i];
        ans += mult;
    }
    return ans;
}

double PolynomialUtility :: NewtonInterpolation (Array < double > *xValues, Array < double > *yValues, double xi)
{
    double ans = 0;
    vector < double > x = xValues->GetCopy ();
    vector < double > y = yValues->GetCopy ();
    int size = (int)x.size ();
    for (int i = 0;i < size;i++)
    {
        for (int k = size - 1;k > i;k--)
        {
            y[k] = (y[k] - y[k - 1]) / (x[k] - x[k - i - 1]);
        }
    }
    double mult = 1;
    for (int i = size - 1;i >= 0;i--)
    {
        mult = 1;
        for (int j = 0;j < i;j++)
            mult *= (xi - x[j]);
        mult *= y[i];
        ans += mult;
    }
    return ans;
}