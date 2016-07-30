//
//  Expression.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Expression_hpp
#define Expression_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>

#include "Calculation.hpp"
using namespace std;

enum class ExpressionStatus { valid, invalid, uncertain };

class Expression
{
    private :
    
    string expr; // The expression is stored here.
    int expr_size; // In order to decrease the frequency of calling for expr.size () which is relatively inefficient.
    ExpressionStatus status; // Whether the expression is valid itself.
    
    public :
    
    //Constructors
    Expression ();
    Expression (Expression *);
    Expression (string);
    
    //Methods
    void SetToNewExpression (string);
    bool IsValid ();
    void SetStatus (ExpressionStatus);
    
    string GetExpression ();
};
#endif /* Expression_hpp */
