//
//  Double.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/1.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Double.hpp"

Double :: Double ()
{
    type = NumericType :: DOUBLE;
}

Double :: Double (double x)
{
    type = NumericType :: DOUBLE;
    value = x;
}

const double Double :: GetValue ()
{
    return value;
}

const NumericType Double :: GetType () const
{
    return NumericType :: DOUBLE;
}

void Double :: SetValue (double x)
{
    value = x;
}