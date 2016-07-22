//
//  Expression.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Expression.hpp"

Expression :: Expression ()
{
    expr = "";
    expr_size = 0;
    status = ExpressionStatus :: uncertain;
}

Expression :: Expression (string s)
{
    expr = s;
    expr_size = (int)expr.size ();
    status = ExpressionStatus :: uncertain;
}

void Expression :: SetToNewExpression (string s)
{
    expr = s;
    expr_size = (int)expr.size ();
    status = ExpressionStatus :: uncertain;
}

bool Expression :: IsValid ()
{
    return status == ExpressionStatus :: valid;
}

void Expression :: SetStatus(ExpressionStatus stat)
{
    status = stat;
}