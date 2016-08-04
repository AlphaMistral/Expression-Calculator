//
//  EquationSolver.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/30.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "EquationSolver.hpp"

int EquationSolver :: MAX_ITER_TIMES = 500;
double EquationSolver :: EPS = 1e-5;

void EquationSolver :: SetMaxIterTimes (int times)
{
    MAX_ITER_TIMES = times;
}

bool dcmp (double a, double b, double EPS = 1e-5)
{
    return abs (a - b) <= EPS;
}

EquationSolver :: EquationSolver ()
{
    expression = NULL;
    status = UnSolved;
    var_name = "";
    result = NULL;
    parser = NULL;
}

EquationSolver :: ~EquationSolver ()
{
    //delete result;
}

EquationSolver :: EquationSolver (Expression *expr, ExpressionParser *p, string name)
{
    expression = expr;
    status = UnSolved;
    var_name = name;
    parser = p;
    p->SetToNewExpression (expression);
}

void EquationSolver :: SetVarName(string name)
{
    var_name = name;
}

CalculationResult EquationSolver :: SetExpression(Expression *expr)
{
    expression = expr;
    CalculationResult checkResult = parser->SetToNewExpression (expr);
    return checkResult;
}

CalculationResult EquationSolver :: SetParser (ExpressionParser *p)
{
    parser = p;
    return parser->SetToNewExpression (expression);
}

void EquationSolver :: SetEPS(double eps)
{
    EPS = eps;
}

CalculationResult EquationSolver :: SolveByBinarySearch (double l,  double r)
{
    CalculationResult ret = CalculationResult ();
    double mid = (l + r) / 2.0;
    shared_ptr <Numeric> v1 (new Double (l));
    shared_ptr <Numeric> v2 (new Double (r));
    shared_ptr <Numeric> v3;
    parser->SetVariable (var_name, v1.get ());
    double t1 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
    parser->SetVariable (var_name, v2.get ());
    double t2 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
    if (t1 == 0)
    {
        v1.reset (new Double (l));
        ret.SetAllParams(v1.get ()->Clone (), true, "The left end point is the solution. \n");
        return ret;
    }
    else if (t2 == 0)
    {
        v2.reset (new Double (r));
        ret.SetAllParams(v2.get ()->Clone (), true, "The right end point is the solution. \n");
        return ret;
    }
    else if (t1 * t2 > 0)
    {
        v1.reset (new Numeric ());
        ret.SetAllParams(v1.get ()->Clone (), false, "The indicated interval may not include a solution since the function has values of the same sign on the two end points. Please check. \n");
        return ret;
    }
    while (abs (l - r) > EPS)
    {
        mid = (l + r) / 2.0;
        v1.reset (new Double (l));
        v2.reset (new Double (r));
        v3.reset (new Double (mid));
        parser->SetVariable (var_name, v1.get ());
        double c1 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
        parser->SetVariable (var_name, v3.get ());
        double c2 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
        parser->SetVariable (var_name, v2.get ());
        double c3 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
        if (c1 * c2 < 0)
        {
            r = mid;
        }
        else if (c1 * c2 > 0)
            l = mid;
        else
        {
            if (c1 == 0)
                mid = l;
            else if (c3 == 0)
                mid = r;
            break;
        }
    }
    v3.reset (new Double (mid));
    ret.SetAllParams(v3.get ()->Clone (), true, "A solution is found in the interval. However it may not be the only solution to the equation. \n");
    return ret;
}

CalculationResult EquationSolver :: SolveByNewton(Expression *expr, double prediction = 0)
{
    CalculationResult ret = CalculationResult ();
    double last = prediction;
    bool isMaxIterReached = true;
    for (int iter = 0;iter < MAX_ITER_TIMES;iter++)
    {
        parser->SetVariable (var_name, new Double (last));
        double current = parser->ParseExpression (expression).result;
        current /= parser->ParseExpression (expr).result;
        current = -current + last;
        if (abs (last - current) < EPS)
        {
            isMaxIterReached = false;
            last = current;
            break;
        }
        last = current;
    }
    if (isMaxIterReached)
        ret.SetAllParams(new Double (last), true, "The answer may not be accurate because the max iteration time is reached and the itertaion is broken in the middle way. \n");
    else ret.SetAllParams(new Double (last), true, "The answer has reached the indicated accuracy. \n");
    return ret;
}

CalculationResult EquationSolver :: SolveBySecant (double p1, double p2)
{
    CalculationResult ret = CalculationResult ();
    double last1 = p1;
    double last2 = p2;
    bool isMaxIterReached = true;
    for (int iter = 0;iter < MAX_ITER_TIMES;iter++)
    {
        parser->SetVariable (var_name, new Double (last1));
        double t1 = parser->ParseExpression ().result;
        parser->SetVariable (var_name, new Double (last2));
        double t2 = parser->ParseExpression ().result;
        double current = last2 - (last2 - last1) / (t2 - t1) * t2;
        if (abs (current - last2) <= EPS)
        {
            last2 = current;
            isMaxIterReached = false;
            break;
        }
        last1 = last2;
        last2 = current;
    }
    if (isMaxIterReached)
        ret.SetAllParams(new Double (last2), true, "The answer may not be accurate because the max iteration time is reached and the itertaion is broken in the middle way. \n");
    else ret.SetAllParams(new Double (last2), true, "The answer has reached the indicated accuracy. \n");
    return ret;
}