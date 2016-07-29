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

using namespace std;

class Function
{
    private :
    
    string name_func;
    int num_func;
    string expr_func;
    
    public :
    
    Function ();
    Function (string, int, string);
    
    void SetName (string);
    void SetNum (int);
    void SetExpression (string);
    
    string GetName ();
    string GetExpression ();
    int GetVarNum ();
};
#endif /* Function_hpp */
