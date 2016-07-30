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

#include "../src/ExpressionParser.hpp"

using namespace std;

int main ()
{
    cout << sqlite3_version << endl;
    cout << "Hello World!" << endl;
    Expression *expr = new Expression ("fx (1.1, 88) + 3 * 3");
    ExpressionParser *parser = new ExpressionParser (expr);
    parser->SetVariable ("x", 5);
    parser->SetVariable ("t", 4);
    Function *f1 = new Function ("f", 1, new Expression ("a * a * a"));
    Function *f2 = new Function ("fx", 2, new Expression ("max (a, f (a)) + b"));
    parser->AddNewFunction(f1);
    parser->AddNewFunction(f2);
    parser->ParseExpression ();
    parser->GetResult ()->OutputResult ();
    expr->SetToNewExpression("7.xx+512*sin(11).14)");
    ExpressionParser *newParser = new ExpressionParser (expr);
    Function *f3 = new Function ("fx", 2, new Expression ("a + b"));
    newParser->AddNewFunction(f3);
    CalculationResult *res2 = newParser->CheckExpression ();
    cout << res2->GetInformation () << endl;
    return 0;
}