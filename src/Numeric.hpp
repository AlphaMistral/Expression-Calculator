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
    UNSURE
};

class Numeric
{
    private :
    
    bool isValid;
    
    public :
    
    virtual const NumericType GetType () const;
    
    virtual const void *GetValue () const;
    
    bool GetValidity ();
};
#endif /* Numeric_hpp */
