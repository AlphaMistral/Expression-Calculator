//
//  Double.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/1.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Double.hpp"

Double :: Double (double x)
{
    value = x;
}

const void *Double :: GetValue () const
{
    return &value;
}

const NumericType Double :: GetType () const
{
    return NumericType :: DOUBLE;
}