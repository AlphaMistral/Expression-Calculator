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
    for (int i = 0;i < 100000000;i++)
    {
        break;
        Expression *expr1 = new Expression ("7 * 1.5 ^ 3 + 8 + sin (1)");
        ExpressionParser *parser1 = new ExpressionParser (expr1);
        CalculationResult *rrr = parser1->CheckExpression ();
        rrr->OutputResult ();
        delete expr1;
        delete parser1;
        delete rrr;
    }
    for (int i = 0;i < 100000000;i++)
    {
        Expression *expr = new Expression ("fx (1.1, 88) + 3 * 3");
        Expression *expr1 = new Expression ("a * a * a");
        Expression *expr2 = new Expression ("max (a, f (a)) + b");
        ExpressionParser *parser = new ExpressionParser (expr);
        parser->SetVariable ("x", 5);
        parser->SetVariable ("t", 4);
        Function *f1 = new Function ("f", 1, expr1);
        Function *f2 = new Function ("fx", 2, expr2);
        CalculationResult *c1 = parser->AddNewFunction(f1);
        CalculationResult *c2 = parser->AddNewFunction(f2);
        //CalculationResult *rrr = parser->CheckExpression();
        //rrr->OutputResult ();
        delete expr;
        delete expr1;
        delete expr2;
        delete f1;
        delete f2;
        delete parser;
        delete c1;
        delete c2;
        //delete rrr;
    }
    return 0;/*
    expr->SetToNewExpression("7.xx+512*sin(11).14)");
    ExpressionParser *newParser = new ExpressionParser (expr);
    Function *f3 = new Function ("fx", 2, new Expression ("a + b +"));
    CalculationResult *check = newParser->AddNewFunction(f3);
    cout << check->GetInformation () << endl;
    CalculationResult *res2 = newParser->CheckExpression ();
    cout << res2->GetInformation () << endl;
    
    Expression *xExpression = new Expression ("x + sin (17 * x + 4)");
    ExpressionParser *xParser = new ExpressionParser (xExpression);
    EquationSolver *solver = new EquationSolver (xExpression, xParser, "x");
    CalculationResult *xRes = solver->SolveByBinarySearch (-200, 200);
    cout << xRes->GetResult () << endl;
    Expression *xxExpression = new Expression ("1 + 17 * cos (17 * x + 4)");
    CalculationResult *nRes = solver->SolveByNewton (xxExpression, 0.8);
    cout << nRes->GetResult () << endl;
    xParser->SetVariable("x", 0.126825);
    cout << xParser->ParseExpression ()->GetResult () << endl;
    CalculationResult *sRes = solver->SolveBySecant (0.8, 0.801);
    cout << sRes->GetResult () << endl;
    return 0;
              */
}