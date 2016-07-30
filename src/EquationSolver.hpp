//
//  EquationSolver.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/30.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef EquationSolver_hpp
#define EquationSolver_hpp

#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>

#include "ExpressionParser.hpp"

using namespace std;

class EquationSolver
{
    private :
    
    enum EquationStatus
    {
        UnSolved,
        Solved,
        Error
    };
    
    Expression *expression;
    EquationStatus status;
    CalculationResult *result;
    string var_name;
    ExpressionParser *parser;
    
    double EPS = 1e-5;
    
    public :
    
    EquationSolver ();
    EquationSolver (Expression *, ExpressionParser *, string);
    CalculationResult *SolveByBinarySearch (double, double);
    ExpressionParser *GetParser ();
    
    CalculationResult *SetParser (ExpressionParser *);
    void SetVarName (string);
    CalculationResult *SetExpression (Expression *);
    void SetEPS (double);
};
#endif /* EquationSolver_hpp */
