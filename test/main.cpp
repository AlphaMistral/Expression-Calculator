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
#include "../src/EquationSolver.hpp"

using namespace std;

int main ()
{
    cout << sqlite3_version << endl;
    cout << "Hello World!" << endl;
    for (int i = 0;i < 10000000;i++)
    {
        Expression *xExpression = new Expression ("x + sin (17 * x + 4)");
        ExpressionParser *xParser = new ExpressionParser (xExpression);
        EquationSolver *solver = new EquationSolver (xExpression, xParser, "x");
        CalculationResult *xRes = solver->SolveByBinarySearch (-200, 200);
        cout << xRes->GetResult () << endl;
        //Expression *xxExpression = new Expression ("1 + 17 * cos (17 * x + 4)");
        //CalculationResult *nRes = solver->SolveByNewton (xxExpression, 0.8);
        //cout << nRes->GetResult () << endl;
        //xParser->SetVariable("x", 0.126825);
        //CalculationResult *tt = xParser->ParseExpression ();
        //cout << tt->GetResult () << endl;
        //CalculationResult *sRes = solver->SolveBySecant (0.8, 0.801);
        //cout << sRes->GetResult () << endl;
        delete xExpression;
        delete xParser;
        delete solver;
        delete xRes;
        //delete nRes;
        //delete sRes;
        //delete tt;
        //delete xxExpression;
    }
    return 0;
}