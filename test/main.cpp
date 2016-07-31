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
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>

#include "../src/ExpressionParser.hpp"
#include "../src/EquationSolver.hpp"
#include "../src/OpenGLPlotter.hpp"

using namespace std;

int main (int argc, char ** argv)
{
    glutInit (&argc, argv);
    cout << sqlite3_version << endl;
    cout << "Hello World!" << endl;
    Expression *y = new Expression ("tan (sin (x) ^ max (x, x * x))");
    ExpressionParser *pp = new ExpressionParser (y);
    OpenGLPlotter *plotter = new OpenGLPlotter (pp, make_pair (-3, 3), 0.1);
    cout << "We are here!" << endl;
    plotter->Plot ();
    cout << "Hello Again!" << endl;
    return 0;
    for (int i = 0;i < 10000000;i++)
    {
        //break;
        Expression *expr1 = new Expression ("fx (1.1, 88) + 19 * sin (11)");
        Expression *expr2 = new Expression ("a * a * a");
        Expression *expr3 = new Expression ("max (a, f (a)) + b");
        ExpressionParser *parser = new ExpressionParser (expr1);
        Function *f1 = new Function ("f", 1, expr2);
        Function *f2 = new Function ("fx", 2, expr3);
        parser->AddNewFunction (f1);
        parser->AddNewFunction (f2);
        cout << parser->ParseExpression().result << endl;
        delete expr1;
        delete expr2;
        delete expr3;
        delete parser;
        delete f1;
        delete f2;
    }
    for (int i = 0;i < 10000000;i++)
    {
        Expression *xExpression = new Expression ("x + sin (17 * x + 4)");
        ExpressionParser *xParser = new ExpressionParser (xExpression);
        EquationSolver *solver = new EquationSolver (xExpression, xParser, "x");
        CalculationResult xRes = solver->SolveByBinarySearch (-200, 200);
        cout << xRes.result << endl;
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
        //delete nRes;
        //delete sRes;
        //delete tt;
        //delete xxExpression;
    }
    return 0;
}