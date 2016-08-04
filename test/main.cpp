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
        break;
        double **a = new double *[2];
        a[1] = new double [2];
        a[0] = new double [2];
        a[0][0] = a[0][1] = a[1][0] = a[1][1] = 1.5;
        Numeric *mat = new Matrix (2, 2, a);
        Expression *expr = new Expression ("a * a");
        ExpressionParser *parser = new ExpressionParser (expr);
        parser->SetVariable("a", mat);
        CalculationResult res = parser->ParseExpression ();
        Matrix *ans = static_cast<Matrix *> (res.numeric.get ());
        cout << ans->GetValue ()[0][0] << endl;
        delete[] a[0];
        delete[] a[1];
        delete[] a;
        delete mat;
        delete expr;
        delete parser;
    }
    while (true)
    {
        Expression *equation = new Expression ("x - 5");
        ExpressionParser *parser = new ExpressionParser (equation);
        EquationSolver *solver = new EquationSolver (equation, parser, "x");
        Expression *dEquation = new Expression ("1");
        CalculationResult result = solver->SolveBySecant (0, 1);
        Double *re = static_cast <Double *> (result.numeric.get ());
        cout <<re->GetValue () << endl;
        delete equation;
        delete parser;
        delete solver;
        delete dEquation;
    }
    return 0;
}