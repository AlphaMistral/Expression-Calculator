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

#include "../src/Calculation.hpp"

using namespace std;

int main (int argc, char ** argv)
{
    while (true)
    {
        Expression *expr = new Expression ("XB (5, 2) * max (sin (5), 17 ^ x)");
        Expression *funcExpr = new Expression ("a + b / a");
        Function *func = new Function ("XB", 2, funcExpr);
        shared_ptr<Numeric> xx (new Double (1.1));
        ExpressionParser *parser = new ExpressionParser (expr);
        parser->AddNewFunction (func);
        parser->SetVariable("x", xx.get ());
        CalculationResult result = parser->ParseExpression ();
        Double dou = *static_cast <Double *> (result.numeric.get ());
        cout << dou.GetValue () << endl;
        delete parser;
        delete expr;
        delete func;
        delete funcExpr;
        //delete xx;
    }
    return 0;
}