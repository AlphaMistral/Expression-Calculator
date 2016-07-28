//
//  main.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <sqlite3.h>

#include "ExpressionParser.hpp"

using namespace std;

int main ()
{
    cout << sqlite3_version << endl;
    cout << "Hello World!" << endl;
    Expression *expr = new Expression ("fx (1.1, 88) + 3 * 3 )");
    ExpressionParser *parser = new ExpressionParser (expr);
    parser->SetVariable ("x", 5);
    parser->SetVariable ("t", 4);
    parser->AddNewFunction("f", 1, "a * a * a");
    parser->AddNewFunction("fx", 2, "max (a, f (a)) + b");
    parser->ParseExpression ();
    CalculationResult *res1 = parser->GetResult ();
    res1->OutputResult ();
    res1->SetResult(14161231);
    res1->OutputResult ();
    parser->GetResult ()->OutputResult ();
    expr->SetToNewExpression("7.xx+512*sin(11).14)");
    ExpressionParser *newParser = new ExpressionParser (expr);
    newParser->AddNewFunction("fx", 2, "a + b");
    CalculationResult *res2 = newParser->CheckExpression ();
    cout << res2->GetInformation () << endl;
    return 0;
}