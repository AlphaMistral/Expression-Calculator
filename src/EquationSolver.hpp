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
    
    static int MAX_ITER_TIMES;
    
    static double EPS;
    
    public :
    
    EquationSolver ();
    ~EquationSolver ();
    EquationSolver (Expression *, ExpressionParser *, string);
    CalculationResult SolveByBinarySearch (double, double);
    CalculationResult SolveByNewton (Expression *, double);
    CalculationResult SolveBySecant (double, double);
    ExpressionParser *GetParser ();
    
    CalculationResult SetParser (ExpressionParser *);
    void SetVarName (string);
    CalculationResult SetExpression (Expression *);
    void SetEPS (double);
    
    static void SetMaxIterTimes (int);
};

#endif /* EquationSolver_hpp */
