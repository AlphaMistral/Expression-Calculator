//
//  Function.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/27.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Function.hpp"

Function :: Function ()
{
    expr_func = NULL;
    name_func = "";
    num_func = 0;
}

Function :: Function (string name, int num, Expression *expr)
{
    expr_func = expr;
    name_func = name;
    num_func = num;
}

void Function :: SetExpression (Expression *expr)
{
    expr_func = expr;
}

void Function :: SetNum (int num)
{
    num_func = num;
}

void Function :: SetName (string name)
{
    name_func = name;
}

string Function :: GetName ()
{
    return name_func;
}

Expression *Function :: GetExpression ()
{
    return expr_func;
}

int Function :: GetVarNum ()
{
    return num_func;
}