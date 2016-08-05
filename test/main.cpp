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
        Expression *expr = new Expression ("a + 1");
        ExpressionParser *parser = new ExpressionParser (expr);
        parser->SetVariable("a", mat);
        CalculationResult res = parser->ParseExpression ();
        cout << res.statusInformation << endl;
        delete[] a[0];
        delete[] a[1];
        delete[] a;
        delete mat;
        delete expr;
        delete parser;
    }
    while (true)
    {
        break;
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
    while (true)
    {
        double a[4][4] = { {1, -1, 2, -1}, {2, -2, 3, -3}, {1, 1, 1, 0}, {1, -1, 4, 3} };
        vector < double > *b = new vector < double > { -8, -20, -2, 4 };
        double **eles = new double *[4];
        for (int i = 0;i < 4;i++)
            eles[i] = new double [4];
        for (int i = 0;i < 4;i++)
            for (int j = 0;j < 4;j++)
                eles[i][j] = a[i][j];
        Matrix *mat = new Matrix (4, 4, eles);
        CalculationResult res = EquationSolver :: SolveByGauss (mat, b);
        Array < double > *ans = static_cast < Array < double > * > (res.numeric.get ());
        vector < double > anss = ans->GetCopy ();
        for (int i = 0;i < anss.size ();i++)
            cout << anss[i] << ' ';
        cout << endl;
        for (int i = 0;i < 4;i++)
            delete[] eles[i];
        delete[] eles;
        delete mat;
        delete b;
    }
    return 0;
}
