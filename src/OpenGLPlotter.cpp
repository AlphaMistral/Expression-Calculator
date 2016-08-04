//
//  OpenGLPlotter.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/31.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "OpenGLPlotter.hpp"

ExpressionParser *OpenGLPlotter :: plottingParser = NULL;

OpenGLPlotter :: OpenGLPlotter ()
{
    refParser = NULL;
}

OpenGLPlotter :: OpenGLPlotter (ExpressionParser *parser, pair < int, int > interv, double f)
{
    refParser = parser;
    interval = interv;
    factor = f;
}

void OpenGLPlotter :: Plot ()
{
    if (refParser == NULL)
        return;
    
    plottingParser = refParser;
    
    glutInitDisplayMode (GLUT_RGB | GLUT_SINGLE);
    
    glutInitWindowPosition (100, 100);
    
    glutInitWindowSize (800, 800);
    
    glutCreateWindow ("第一个OpenGL程序");
    
    glutDisplayFunc (&(this->Display));
    
    glutMainLoop ();
}

void OpenGLPlotter :: Display ()
{
    GLfloat x;
    glClear (GL_COLOR_BUFFER_BIT);
    glBegin (GL_LINES);
    glVertex2f (-1.0f, 0.0f);
    glVertex2f (1.0f, 0.0f);         // 以上两个点可以画x轴
    glVertex2f (0.0f, -1.0f);
    glVertex2f (0.0f, 1.0f);         // 以上两个点可以画y轴
    glEnd ();
    glBegin (GL_LINE_STRIP);
    double factor = 0.1f;
    
    for(x = -1.0f / factor;x < 1.0f / factor;x += 0.1f)
    {
        plottingParser->SetVariable ("x", new Double (x));
        double res = plottingParser->ParseExpression ().result;
        glVertex2f (x * factor, res * factor);
    }
    glEnd ();
    glFlush ();
}