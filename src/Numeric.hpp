//
//  Numeric.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/1.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Numeric_hpp
#define Numeric_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

enum class NumericType
{
    DOUBLE,
    MATRIX,
    UNSURE,
    ARRAY
};

class Numeric
{
    protected :
    
    bool isValid;
    NumericType type;
    
    public :
    
    virtual ~Numeric ();
    
    const NumericType GetType () const;
    
    virtual const void *GetValue () const;
    
    bool GetValidity ();
    
    virtual Numeric *Clone ()
    {
        Numeric *ret = new Numeric ();
        ret->type = type;
        ret->isValid = isValid;
        return ret;
    }
};

#endif /* Numeric_hpp */
