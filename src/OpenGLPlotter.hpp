//
//  OpenGLPlotter.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/31.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef OpenGLPlotter_hpp
#define OpenGLPlotter_hpp

#include <stdio.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>

#include "ExpressionParser.hpp"

using namespace std;

class OpenGLPlotter
{
    private :
    
    pair < int, int > interval;
    static ExpressionParser *refParser;
    double factor;
    
    static void Display (void);
    public :
    
    OpenGLPlotter ();
    OpenGLPlotter (ExpressionParser *, pair < int, int >, double);
    
    void Plot ();
};
#endif /* OpenGLPlotter_hpp */
