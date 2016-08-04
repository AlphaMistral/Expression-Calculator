//
//  Numeric.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/1.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Numeric.hpp"

const NumericType Numeric :: GetType () const
{
    return type;
}

const void *Numeric :: GetValue () const
{
    return NULL;
}

bool Numeric :: GetValidity ()
{
    return isValid;
}

Numeric :: ~Numeric ()
{
    
}