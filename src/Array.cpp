//
//  Array.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/8/4.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Array.hpp"

template <class T>
Array<T> :: Array ()
{
    type = NumericType :: ARRAY;
    size = 0;
}

template <class T>
Array<T> :: Array (int x)
{
    type = NumericType :: ARRAY;
    size = x;
    array.reserve (x);
}

template <class T>
Array<T> :: Array (vector<T> t)
{
    type = NumericType :: ARRAY;
    size = t.size ();
    array = t;
}

template <class T>
Array<T> :: Array (int x, T *a)
{
    type = NumericType :: ARRAY;
    size = x;
    for (int i = 0;i < x;i++)
        array.push_back (a[i]);
}

template <class T>
T Array<T> :: operator [] (const int index)
{
    return array[index];
}

template <class T>
void Array<T> :: Push (T value)
{
    array.push_back (value);
}

template <class T>
void Array<T> :: Erase (int index)
{
    typename vector <T> :: iterator iter = array.begin ()+ index;
    array.erase (iter);
}

template <class T>
bool Array<T> :: Find (T toFind)
{
    bool isFound = false;
    for (typename vector <T> :: iterator iter = array.begin ();iter != array.end ();iter++)
    {
        if (*iter == toFind)
        {
            isFound = true;
            break;
        }
    }
    return isFound;
}

template <class T>
vector <T> Array<T> :: GetCopy ()
{
    return array;
}
