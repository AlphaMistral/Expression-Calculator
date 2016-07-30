//
//  Function.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/27.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Function_hpp
#define Function_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>

#include "Expression.hpp"

using namespace std;

class Function
{
    private :
    
    string name_func;
    int num_func;
    Expression *expr_func;
    
    public :
    
    Function ();
    Function (Function *);
    Function (string, int, Expression *);
    
    void SetName (string);
    void SetNum (int);
    void SetExpression (Expression *);
    
    string GetName ();
    Expression *GetExpression ();
    int GetVarNum ();
};
#endif /* Function_hpp */
