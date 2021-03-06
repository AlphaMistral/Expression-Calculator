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
#include "Calculation.hpp"

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
    map < string, Numeric* > var_dic;
    map < string, Function * > func_dic;
    vector <Function *> funcs;
    vector <Numeric *> nums;
    CalculationResult result;
    
    Numeric *GetValue (int, int);
    Numeric *GetSingleValue (int, int);
    Numeric *GetFuncValue (string, int, int);
    Numeric *GetThreeItemOperationValue (int, Numeric *, Numeric *);
    Numeric *GetUserDefinedFuncValue (string, int, int);
    
    vector< pair < int, int > > *GetParameters (int, int);
    int GetChildExpressionPos (int);
    int OperatorReflection (char);
    
    void CheckSingleExpression (CalculationResult *, int, int);
    void CheckFunctionExpression (CalculationResult *, string, int, int);
    void CheckThreeItemExpression (CalculationResult *, int, int);
    
    CalculationResult CheckFunctionValidity (Function *);
    
    public :
    
    //Constructors
    ExpressionParser ();
    ExpressionParser (Expression *);
    
    ~ExpressionParser ();
    
    //Member Methods
    CalculationResult ParseExpression ();
    CalculationResult ParseExpression (Expression *);
    CalculationResult GetResult ();
    
    void SetVariable (string, Numeric *);
    void DeleteVariable (string);
    CalculationResult AddNewFunction (Function *);
    CalculationResult AddNewFunction (string, int, string);
    CalculationResult DeleteFunction (string);
    
    CalculationResult CheckExpression ();
    CalculationResult CheckExpression (Expression *);
    void InitializeFunctionLib (map < string, Function * >);
    
    vector <Function *> GetFunctionList ();
    
    CalculationResult SetToNewExpression (Expression *expr);
    
    void ExtractErrorMessage (CalculationResult);
};
#endif /* ExpressionParser_hpp */
