//
//  EquationSolver.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/30.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "EquationSolver.hpp"

int EquationSolver :: MAX_ITER_TIMES = 500;
double EquationSolver :: EPS = 1e-5;

void EquationSolver :: SetMaxIterTimes (int times)
{
    MAX_ITER_TIMES = times;
}

bool dcmp (double a, double b, double EPS = 1e-5)
{
    return abs (a - b) <= EPS;
}

EquationSolver :: EquationSolver ()
{
    expression = NULL;
    status = UnSolved;
    var_name = "";
    result = NULL;
    parser = NULL;
}

EquationSolver :: ~EquationSolver ()
{
    //delete result;
}

EquationSolver :: EquationSolver (Expression *expr, ExpressionParser *p, string name)
{
    expression = expr;
    status = UnSolved;
    var_name = name;
    parser = p;
    p->SetToNewExpression (expression);
}

void EquationSolver :: SetVarName(string name)
{
    var_name = name;
}

CalculationResult EquationSolver :: SetExpression(Expression *expr)
{
    expression = expr;
    CalculationResult checkResult = parser->SetToNewExpression (expr);
    return checkResult;
}

CalculationResult EquationSolver :: SetParser (ExpressionParser *p)
{
    parser = p;
    return parser->SetToNewExpression (expression);
}

void EquationSolver :: SetEPS(double eps)
{
    EPS = eps;
}

CalculationResult EquationSolver :: SolveByBinarySearch (double l,  double r)
{
    CalculationResult ret = CalculationResult ();
    double mid = (l + r) / 2.0;
    shared_ptr <Numeric> v1 (new Double (l));
    shared_ptr <Numeric> v2 (new Double (r));
    shared_ptr <Numeric> v3;
    parser->SetVariable (var_name, v1.get ());
    double t1 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
    parser->SetVariable (var_name, v2.get ());
    double t2 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
    if (t1 == 0)
    {
        v1.reset (new Double (l));
        ret.SetAllParams(v1.get ()->Clone (), true, "The left end point is the solution. \n");
        return ret;
    }
    else if (t2 == 0)
    {
        v2.reset (new Double (r));
        ret.SetAllParams(v2.get ()->Clone (), true, "The right end point is the solution. \n");
        return ret;
    }
    else if (t1 * t2 > 0)
    {
        v1.reset (new Numeric ());
        ret.SetAllParams(v1.get ()->Clone (), false, "The indicated interval may not include a solution since the function has values of the same sign on the two end points. Please check. \n");
        return ret;
    }
    while (abs (l - r) > EPS)
    {
        mid = (l + r) / 2.0;
        v1.reset (new Double (l));
        v2.reset (new Double (r));
        v3.reset (new Double (mid));
        parser->SetVariable (var_name, v1.get ());
        double c1 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
        parser->SetVariable (var_name, v3.get ());
        double c2 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
        parser->SetVariable (var_name, v2.get ());
        double c3 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
        if (c1 * c2 < 0)
        {
            r = mid;
        }
        else if (c1 * c2 > 0)
            l = mid;
        else
        {
            if (c1 == 0)
                mid = l;
            else if (c3 == 0)
                mid = r;
            break;
        }
    }
    v3.reset (new Double (mid));
    ret.SetAllParams(v3.get ()->Clone (), true, "A solution is found in the interval. However it may not be the only solution to the equation. \n");
    return ret;
}

CalculationResult EquationSolver :: SolveByNewton(Expression *expr, double prediction = 0)
{
    CalculationResult ret = CalculationResult ();
    double last = prediction;
    bool isMaxIterReached = true;
    shared_ptr <Numeric> var;
    for (int iter = 0;iter < MAX_ITER_TIMES;iter++)
    {
        var.reset (new Double (last));
        parser->SetVariable (var_name, var.get ());
        double current = static_cast <Double *> (parser->ParseExpression (expression).numeric.get ())->GetValue ();
        current /= static_cast <Double *> (parser->ParseExpression (expr).numeric.get ())->GetValue ();
        current = -current + last;
        if (abs (last - current) < EPS)
        {
            isMaxIterReached = false;
            last = current;
            break;
        }
        last = current;
    }
    var.reset (new Double (last));
    if (isMaxIterReached)
        ret.SetAllParams(var.get ()->Clone (), true, "The answer may not be accurate because the max iteration time is reached and the itertaion is broken in the middle way. \n");
    else ret.SetAllParams(var.get ()->Clone (), true, "The answer has reached the indicated accuracy. \n");
    return ret;
}

CalculationResult EquationSolver :: SolveBySecant (double p1, double p2)
{
    CalculationResult ret = CalculationResult ();
    double last1 = p1;
    double last2 = p2;
    shared_ptr <Numeric> var1, var2;
    bool isMaxIterReached = true;
    for (int iter = 0;iter < MAX_ITER_TIMES;iter++)
    {
        var1.reset (new Double (last1));
        var2.reset (new Double (last2));
        parser->SetVariable (var_name, var1.get ());
        double t1 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
        parser->SetVariable (var_name, var2.get ());
        double t2 = static_cast <Double *> (parser->ParseExpression ().numeric.get ())->GetValue ();
        double current = last2 - (last2 - last1) / (t2 - t1) * t2;
        if (abs (current - last2) <= EPS)
        {
            last2 = current;
            isMaxIterReached = false;
            break;
        }
        last1 = last2;
        last2 = current;
    }
    var1.reset (new Double (last2));
    if (isMaxIterReached)
        ret.SetAllParams(var1.get ()->Clone (), true, "The answer may not be accurate because the max iteration time is reached and the itertaion is broken in the middle way. \n");
    else ret.SetAllParams(var2.get ()->Clone (), true, "The answer has reached the indicated accuracy. \n");
    return ret;
}

CalculationResult EquationSolver :: SolveByGauss (Matrix *mat, vector < double > *b)
{
    CalculationResult ret;
    CalculationResult test = TestMatrixSolvable (mat, b);
    if (!test.isValid)
        return test;
    Matrix *cal = new Matrix (*static_cast < Matrix *> (test.numeric.get ()));
    int size = (int)b->size ();
    for (int i = 0;i < size;i++)
    {
        if ((*cal)(i, i) == 0)
        {
            bool isFound = false;
            for (int j = i + 1;j < size;j++)
            {
                if ((*cal)(j, i) != 0)
                {
                    cal->SwapRow (i, j);
                    isFound = true;
                    break;
                }
            }
            if (!isFound)
            {
                ret.isValid = false;
                ret.statusInformation += "The linera equation has various solutions. \n";
                return ret;
            }
        }
        double cp = (*cal)(i, i);
        for (int j = i + 1;j < size;j++)
        {
            double ap = (*cal)(j, i);
            double mul = ap / -cp;
            cal->AddRow (i, j, mul);
        }
    }
    ret.isValid = true;
    CalculationResult diaRet = SolveDiagonalMatrix(cal, true);
    ret.numeric.reset (diaRet.numeric.get ()->Clone ());
    delete cal;
    return ret;
}

CalculationResult EquationSolver :: SolveDiagonalMatrix (Matrix *mat, bool isUpper)
{
    CalculationResult ret;
    vector < double > tempVec;
    vector < double > retVec;
    int rsize = mat->GetRowNum ();
    for (int i = 0;i < rsize;i++)
    {
        tempVec.push_back ((*mat)(i, rsize));
        retVec.push_back ((*mat)(i, rsize));
    }
    if (isUpper)
    {
        for (int i = rsize - 1;i >= 0;i--)
        {
            retVec[i] = tempVec[i] / (*mat)(i, i);
            for (int j = i - 1;j >= 0;j--)
                tempVec[j] -= retVec[i] * (*mat)(j, i);
        }
    }
    else
    {
        for (int i = 0;i < rsize;i++)
        {
            retVec[i] = tempVec[i] / (*mat)(i, i);
            for (int j = i + 1;j < rsize;j++)
                tempVec[j] -= retVec[i] * (*mat)(j, i);
        }
    }
    Array < double > *array = new Array < double > (retVec);
    ret.isValid = true;
    ret.numeric.reset (array);
    return ret;
}

CalculationResult EquationSolver :: SolveDiagonalMatrix (Matrix *mat, vector < double > *b, bool isUpper)
{
    CalculationResult ret;
    CalculationResult test = TestMatrixSolvable (mat, b);
    if (!test.isValid)
        return test;
    int rsize = mat->GetRowNum ();
    Matrix *ano = new Matrix (rsize, rsize + 1, mat->GetValue ());
    for (int i = 0;i < rsize;i++)
        ano->SetValue (i, rsize, (*b)[i]);
    CalculationResult res = SolveDiagonalMatrix(ano, isUpper);
    ret.numeric.reset (static_cast < Matrix * >  (res.numeric.get ()->Clone ()));
    ret.isValid = true;
    delete ano;
    return ret;
}

CalculationResult EquationSolver :: TestMatrixSolvable (Matrix *mat, vector < double > *b)
{
    CalculationResult ret;
    if (!Matrix :: TestEquationSolvable (mat, b))
    {
        ret.isValid = false;
        ret.statusInformation += "The size of the matrix and the array don't meet the requirement of linear equation solving. \n";
        return ret;
    }
    int size = (int)b->size ();
    double **eles = new double *[size];
    for (int i = 0;i < size;i++)
    {
        eles[i] = new double [size + 1];
        for (int j = 0;j < size;j++)
            eles[i][j] = (*mat) (i, j);
        eles[i][size] = (*b)[i];
    }
    Matrix *cal = new Matrix (size, size + 1, eles);
    DELETE_ARRAY(size, eles);
    ret.numeric.reset (cal);
    ret.isValid = true;
    return ret;
}

CalculationResult EquationSolver :: SolveByCholesky (Matrix *mat, vector<double> *b)
{
    CalculationResult test = TestMatrixSolvable (mat, b);
    if (!test.isValid)
        return test;
    int size = (int)b->size ();
    double **eles = new double *[size];
    for (int i = 0;i < size;i++)
    {
        eles[i] = new double [size];
        for (int j = 0;j < size;j++)
            eles[i][j] = 0;
    }
    eles[0][0] = sqrt ((*mat)(0, 0));
    for (int k = 0;k < size;k++)
    {
        double num = 0;
        for (int i = 0;i < k;i++)
        {
            num = 0;
            for (int j = 0;j < i;j++)
                num += eles[i][j] * eles[k][j];
            eles[k][i] = ((*mat)(k, i) - num) / eles[i][i];
        }
        num = 0;
        for (int j = 0;j < k;j++)
            num += eles[k][j] * eles[k][j];
        eles[k][k] = sqrt ((*mat)(k, k) - num);
    }
    shared_ptr < Matrix > mat1 (new Matrix (size, size, eles));
    shared_ptr < Matrix > mat2 (new Matrix (mat1.get ()->Transpose ()));
    CalculationResult xResult = SolveDiagonalMatrix(mat1.get (), b, false);
    vector < double > xValues = static_cast < Array < double > * > (xResult.numeric.get ())->GetCopy ();
    CalculationResult yResult = SolveDiagonalMatrix(mat2.get (), &xValues, true);
    yResult.isValid = true;
    DELETE_ARRAY(size, eles);
    return yResult;
}

CalculationResult EquationSolver :: SolveByDoolittle(Matrix *mat, vector < double > *b)
{
    CalculationResult ret;
    CalculationResult test = TestMatrixSolvable (mat, b);
    if (!test.isValid)
        return test;
    int size = (int)b->size ();
    CREATE_ARRAY(size, size, double, ele1);
    CREATE_ARRAY(size, size, double, ele2);
    for (int i = 0;i < size;i++)
        ele1[i][i] = 1;
    for (int i = 0;i < size;i++)
        ele2[0][i] = (*mat)(0, i);
    for (int i = 1;i < size;i++)
        ele1[i][0] = (*mat)(i, 0) / (*mat)(0, 0);
    for (int i = 1;i < size;i++)
    {
        for (int j = i;j < size;j++)
        {
            double num = (*mat)(i, j);
            for (int k = 0;k < i;k++)
                num -= ele1[i][k] * ele2[k][j];
            ele2[i][j] = num;
        }
        for (int j = i + 1;j < size;j++)
        {
            double num = (*mat)(j, i);
            for (int k = 0; k< i;k++)
                num -= ele1[j][k] * ele2[k][i];
            ele1[j][i] = num / ele2[i][i];
        }
    }
    Matrix *lu = new Matrix (size, size, ele1);
    for (int i = 0;i < size;i++)
        lu->SetValue(i, i, 1);
    vector < double > y = (static_cast < Array < double > * > (SolveDiagonalMatrix(lu, b, false).numeric.get ()))->GetCopy ();
    delete lu;
    lu = new Matrix (size, size, ele2);
    y = (static_cast< Array < double > * > (SolveDiagonalMatrix (lu, &y, true).numeric.get ()))->GetCopy ();
    delete lu;
    DELETE_ARRAY(size, ele1);
    DELETE_ARRAY(size, ele2);
    ret.numeric.reset (new Array < double > (y));
    ret.isValid = true;
    return ret;
}

double EquationSolver :: GetDifference(vector < double > *vec1, vector < double > *vec2)
{
    double ret = 0;
    for (int i = 0, imax = (int)vec1->size ();i < imax;i++)
    {
        ret += abs ((*vec1)[i] - (*vec2)[i]);
    }
    return ret;
}

CalculationResult EquationSolver :: SolveByJacobi(Matrix *mat, vector < double > * b, int maxIterTime = MAX_ITER_TIMES)
{
    CalculationResult ret;
    CalculationResult test = TestMatrixSolvable (mat, b);
    if (!test.isValid)
        return test;
    vector < double > vec1, vec2, *cur, *pre;
    cur = &vec1;
    pre = &vec2;
    int size = (int)b->size ();
    for (int i = 0;i < size;i++)
    {
        pre->push_back (0);
        cur->push_back (0x3f3f3f3f);
    }
    int iterTime = 0;
    while (iterTime < maxIterTime && GetDifference (cur, pre) > EPS)
    {
        iterTime++;
        for (int i = 0;i < size;i++)
        {
            double num = 0;
            for (int j = 0;j < size;j++)
            {
                if (i == j)
                    continue;
                num += (*mat)(i, j) * (*pre)[j];
            }
            (*cur)[i] = ((*b)[i] - num) / (*mat)(i, i);
        }
        swap (cur, pre);
    }
    Array < double > *array = new Array < double > (*cur);
    ret.isValid = true;
    ret.numeric.reset (array);
    return ret;
}

CalculationResult EquationSolver :: SolveByGaussSeidel (Matrix *mat, vector < double > *b, int maxIterTime = MAX_ITER_TIMES)
{
    CalculationResult ret;
    CalculationResult test = TestMatrixSolvable (mat, b);
    if (!test.isValid)
        return test;
    vector < double > vec1, vec2, *cur, *pre;
    cur = &vec1;
    pre = &vec2;
    int size = (int)b->size ();
    for (int i = 0;i < size;i++)
    {
        pre->push_back (0);
        cur->push_back (0);
    }
    int iterTime = 0;
    while (iterTime == 0 || (iterTime < maxIterTime && GetDifference (cur, pre) > EPS))
    {
        iterTime++;
        for (int i = 0;i < size;i++)
        {
            double num = 0;
            for (int j = 0;j < i;j++)
                num += (*mat)(i, j) * (*cur)[j];
            for (int j = i + 1;j < size;j++)
                num += (*mat)(i, j) * (*pre)[j];
            (*cur)[i] = ((*b)[i] - num) / (*mat)(i, i);
        }
        swap (cur, pre);
    }
    Array < double > *array = new Array < double > (*cur);
    ret.isValid = true;
    ret.numeric.reset (array);
    return ret;
}

