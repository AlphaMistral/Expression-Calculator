//
//  Calculation.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Calculation.hpp"

CalculationResult operator + (const Numeric &a1, const Numeric &a2)
{
    CalculationResult ret;
    if (a1.GetType () == a2.GetType () && a1.GetType () == NumericType :: DOUBLE)
    {
        ret.numeric = Double (*(double *)a1.GetValue () + *(double *)a2.GetValue ());
    }
    else if (a1.GetType () == a2.GetType () && a1.GetType () == NumericType :: MATRIX)
    {
        const Matrix *m1 = static_cast<const Matrix *> (&a1);
        const Matrix *m2 = static_cast<const Matrix *> (&a2);
        if (!m1->TestAddable (m2))
        {
            ret.statusInformation += "The two Matrices could not be added together because they have different sizes! \n";
        }
        else
        {
            ret.numeric = *m1 + *m2;
        }
    }
    else
    {
        ret.statusInformation += "The two elements are of different types, and thus it is totally illegal to add them together! \n";
    }
    return ret;
}

CalculationResult operator * (const Numeric &a1, const Numeric &a2)
{
    CalculationResult ret;
    if (a1.GetType () == a2.GetType () && a1.GetType () == NumericType :: DOUBLE)
    {
        ret.numeric = Double (*(double *)a1.GetValue () * *(double *)a2.GetValue ());
    }
    else if (a1.GetType () == a2.GetType () && a1.GetType () == NumericType :: MATRIX)
    {
        const Matrix *m1 = static_cast<const Matrix *> (&a1);
        const Matrix *m2 = static_cast<const Matrix *> (&a2);
        if (!m1->TestTimable (m2))
        {
            ret.statusInformation += "The two Matrices could not be multiplied together due to wrong size matching! \n";
        }
        else
        {
            ret.numeric = *m1 * *m2;
        }
    }
    else
    {
        
    }
    return ret;
}
