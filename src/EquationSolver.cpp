//
//  EquationSolver.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/30.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "EquationSolver.hpp"

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

EquationSolver :: EquationSolver (Expression *expr, ExpressionParser *p, string name)
{
    expression = expr;
    status = UnSolved;
    var_name = name;
    parser = p;
    result = p->SetToNewExpression (expression);
}

void EquationSolver :: SetVarName(string name)
{
    var_name = name;
}

CalculationResult *EquationSolver :: SetExpression(Expression *expr)
{
    expression = expr;
    CalculationResult *checkResult = parser->SetToNewExpression (expr);
    return checkResult;
}

CalculationResult *EquationSolver :: SetParser (ExpressionParser *p)
{
    parser = p;
    return parser->SetToNewExpression (expression);
}

void EquationSolver :: SetEPS(double eps)
{
    EPS = eps;
}

CalculationResult *EquationSolver :: SolveByBinarySearch (double l,  double r)
{
    CalculationResult *ret = new CalculationResult ();
    double mid = (l + r) / 2.0;
    while (abs (l - r) > EPS)
    {
        mid = (l + r) / 2.0;
        parser->SetVariable (var_name, l);
        double c1 = parser->ParseExpression ()->GetResult ();
        parser->SetVariable (var_name, mid);
        double c2 = parser->ParseExpression ()->GetResult ();
        parser->SetVariable (var_name, r);
        double c3 = parser->ParseExpression ()->GetResult ();
        if (c1 * c2 < 0)
        {
            r = mid;
        }
        else l = mid;
    }
    ret->SetAllParams(mid, true, "Suc! \n");
    return ret;
}