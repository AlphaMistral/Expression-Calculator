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
    Expression *expr = new Expression ("max(2,8)");
    ExpressionParser *parser = new ExpressionParser (expr);
    parser->SetVariable ("x", 5);
    parser->SetVariable ("t", 4);
    parser->ParseExpression ();
    CalculationResult *res1 = parser->GetResult ();
    res1->OutputResult ();
    res1->SetResult(14161231);
    res1->OutputResult ();
    parser->GetResult ()->OutputResult ();
    return 0;
}