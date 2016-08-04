//
//  Array.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/4.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Array_hpp
#define Array_hpp

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#include "Numeric.hpp"

using namespace std;

template <class T>
class Array : public Numeric
{
    private :
    
    vector < T > array;
    int size;
    NumericType type;
    
    public :
    
    Array ();
    Array (int);
    Array (vector <T>);
    Array (int, T *);
    
    T operator [] (const int);
    
    void Push (T);
    void Erase (int);
    bool Find (T);
    
    vector < T > GetCopy ();
};

#endif /* Array_hpp */
