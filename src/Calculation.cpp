//
//  Calculation.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "Calculation.hpp"

CalculationResult Add (const Numeric *a1, const Numeric *a2)
{
    CalculationResult ret;
    if (a1->GetType () == a2->GetType () && a1->GetType () == NumericType :: DOUBLE)
    {
        Double d1 = *static_cast<const Double *> (a1);
        Double d2 = *static_cast<const Double *> (a2);
        ret.numeric.reset (new Double (d1.GetValue () + d2.GetValue ()));
    }
    else if (a1->GetType () == a2->GetType () && a1->GetType () == NumericType :: MATRIX)
    {
        const Matrix *m1 = static_cast<const Matrix *> (a1);
        const Matrix *m2 = static_cast<const Matrix *> (a2);
        if (!m1->TestAddable (m2))
        {
            ret.statusInformation += "The two Matrices could not be added together because they have different sizes! \n";
        }
        else
        {
            ret.numeric.reset (new Matrix (*m1 + *m2));
        }
    }
    else
    {
        ret.statusInformation += "The two elements are of different types, and thus it is totally illegal to add them together! \n";
    }
    return ret;
}

CalculationResult Sub (const Numeric *a1, const Numeric *a2)
{
    CalculationResult ret;
    if (a1->GetType () == a2->GetType () && a1->GetType () == NumericType :: DOUBLE)
    {
        Double d1 = *static_cast<const Double *> (a1);
        Double d2 = *static_cast<const Double *> (a2);
        ret.numeric.reset (new Double (d1.GetValue () - d2.GetValue ()));
    }
    else if (a1->GetType () == a2->GetType () && a1->GetType () == NumericType :: MATRIX)
    {
        const Matrix *m1 = static_cast<const Matrix *> (a1);
        const Matrix *m2 = static_cast<const Matrix *> (a2);
        if (!m1->TestAddable (m2))
        {
            ret.statusInformation += "The two Matrices could not be added together because they have different sizes! \n";
        }
        else
        {
            ret.numeric.reset (new Matrix (*m1 - *m2));
        }
    }
    else
    {
        ret.statusInformation += "The two elements are of different types, and thus it is totally illegal to add them together! \n";
    }
    return ret;
}

CalculationResult Mul (const Numeric *a1, const Numeric *a2)
{
    CalculationResult ret;
    if (a1->GetType () == a2->GetType () && a1->GetType () == NumericType :: DOUBLE)
    {
        Double d1 = *static_cast<const Double *> (a1);
        Double d2 = *static_cast<const Double *> (a2);
        ret.numeric.reset (new Double (d1.GetValue () * d2.GetValue ()));
    }
    else if (a1->GetType () == a2->GetType () && a1->GetType () == NumericType :: MATRIX)
    {
        const Matrix *m1 = static_cast<const Matrix *> (a1);
        const Matrix *m2 = static_cast<const Matrix *> (a2);
        if (!m1->TestTimable (m2))
        {
            ret.statusInformation += "The two Matrices could not be multiplied together due to wrong size matching! \n";
        }
        else
        {
            ret.numeric.reset (new Matrix (*m1 * *m2));
        }
    }
    else
    {
        if (a1->GetType () == NumericType :: DOUBLE)
        {
            Matrix mat = *static_cast<const Matrix *> (a2);
            Double dou = *static_cast<const Double *> (a1);
            ret.numeric.reset (new Matrix (mat * dou.GetValue ()));
        }
        else
        {
            Matrix mat = *static_cast<const Matrix *> (a1);
            Double dou = *static_cast<const Double *> (a2);
            ret.numeric.reset (new Matrix (mat * dou.GetValue ()));
        }
    }
    return ret;
}

CalculationResult Div (const Numeric *a1, const Numeric *a2)
{
    CalculationResult ret;
    if (a2->GetType () != NumericType :: DOUBLE)
    {
        ret.statusInformation += "The / operator requires that the second operand is of Type Double. \n";
    }
    else
    {
        Double dou = *static_cast<const Double *> (a2);
        if (a1->GetType () == NumericType :: DOUBLE)
        {
            Double d1 = *static_cast<const Double *> (a1);
            ret.numeric.reset (new Double (d1.GetValue () / dou.GetValue ()));
        }
        else if (a1->GetType () == NumericType :: MATRIX)
        {
            Matrix mat = *static_cast<const Matrix *> (a1);
            Double *d = new Double (1.0 / dou.GetValue ());
            ret.numeric.reset (new Matrix (mat * (1.0 / d->GetValue ())));
        }
    }
    return ret;
}

CalculationResult Exp (const Numeric *a1, const Numeric *a2)
{
    CalculationResult ret;
    if (a2->GetType () != NumericType :: DOUBLE)
    {
        ret.statusInformation += "The second operand must be a double! \n";
    }
    else
    {
        Double d2 = *static_cast <const Double *> (a2);
        if (a1->GetType () == NumericType :: DOUBLE)
        {
            Double d1 = *static_cast<const Double *> (a1);
            ret.numeric.reset (new Double (pow (d1.GetValue (), d2.GetValue ())));
        }
        else
        {
            Matrix mat = *static_cast<const Matrix *> (a1);
            Matrix res = mat;
            const int times = (int)d2.GetValue ();
            for (int i = 0;i < times;i++)
            {
                res *= mat;
            }
            ret.numeric.reset (new Matrix (res));
        }
    }
    return ret;
}

