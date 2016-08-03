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
    Double x1 (5.0);
    Double x2 (1.5);
    CalculationResult res = x1 * x2;
    cout << *(double *)res.numeric.GetValue () << endl;
    return 0;
}