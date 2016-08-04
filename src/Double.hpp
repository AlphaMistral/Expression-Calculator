//
//  Double.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/1.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Double_hpp
#define Double_hpp

#include <stdio.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Numeric.hpp"

using namespace std;

class Double : public Numeric
{
    private :
    
    double value;
    
    public :
    
    Double ();
    ~Double ();
    Double (double);
    
    virtual Numeric *Clone ();
    
    const double GetValue ();
    
    const NumericType GetType () const;
    
    void SetValue (double);
};

#endif /* Double_hpp */
