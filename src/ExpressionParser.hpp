//
//  ExpressionParser.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef ExpressionParser_hpp
#define ExpressionParser_hpp

#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <ctype.h>
#include <climits>

#include "Expression.hpp"
#include "Function.hpp"

using namespace std;

class ExpressionParser
{
    const static int INCOMPLETE = -1;
    const static int CORRECT = 0;
    const static int SYNTAX = 1;
    const static int BRACELET = 2;
    const static int DIVIDEZERO = 3;
    
    const static int NONEXIST = -1;
    const static int SINGLE = 0;
    const static int ADD = 1;
    const static int SUB = 2;
    const static int MUL = 3;
    const static int DIV = 4;
    const static int EXP = 5;
    
    private :
    
    Expression *originalExpr;
    string parsedExpr;
    int p_expr_size;
    map < string, double > var_dic;
    map < string, Function * > func_dic;
    CalculationResult *result;
    
    double GetValue (int, int);
    double GetSingleValue (int, int);
    double GetFuncValue (string, int, int);
    double GetThreeItemOperationValue (int, double, double);
    double GetUserDefinedFuncValue (string, int, int);
    
    vector< pair < int, int > > *GetParameters (int, int);
    int GetChildExpressionPos (int);
    int OperatorReflection (char);
    
    void CheckSingleExpression (CalculationResult *, int, int);
    void CheckFunctionExpression (CalculationResult *, string, int, int);
    void CheckThreeItemExpression (CalculationResult *, int, int);
    
    public :
    
    //Constructors
    ExpressionParser ();
    ExpressionParser (Expression *);
    
    //Member Methods
    void ParseExpression ();
    void ParseExpression (Expression *);
    CalculationResult *GetResult ();
    
    CalculationResult *SetVariable (string, double);
    CalculationResult *DeleteVariable (string);
    CalculationResult *AddNewFunction (Function *);
    CalculationResult *DeleteFunction (string);
    
    CalculationResult *CheckExpression ();
    
    void InitializeFunctionLib (map < string, Function * > *);
};
#endif /* ExpressionParser_hpp */
