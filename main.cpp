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

#include "ExpressionParser.hpp"

using namespace std;

int main ()
{
    cout << "Hello World!" << endl;
    Expression *expr = new Expression ("-5 / 17 * (-109)");
    ExpressionParser *parser = new ExpressionParser (expr);
    parser->ParseExpression ();
    parser->GetResult ()->OutputResult ();
    return 0;
}