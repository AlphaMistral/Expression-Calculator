//
//  ExpressionParser.cpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#include "ExpressionParser.hpp"

ExpressionParser :: ExpressionParser ()
{
    originalExpr = NULL;
    parsedExpr = "";
    p_expr_size = 0;
    var_dic.clear ();
    func_dic.clear ();
    result = NULL;
}

ExpressionParser :: ExpressionParser (Expression *e)
{
    originalExpr = e;
    parsedExpr = "";
    string temp_e = e->GetExpression ();
    for (string :: iterator iter = temp_e.begin ();iter != temp_e.end ();iter++)
    {
        if (*iter != ' ')
            parsedExpr += *iter;
    }
    p_expr_size = (int)parsedExpr.size ();
    var_dic.clear ();
    func_dic.clear ();
    result = new CalculationResult ();
}

double ExpressionParser :: GetValue (int l, int r)
{
    double ans = 0;
    pair < int, int > operate = make_pair (INT_MAX, INT_MAX);
    int index = l;
    while (index < r)
    {
        index = GetChildExpressionPos (index);
        if (index == p_expr_size - 1)
            break;
        int oprf = OperatorReflection(parsedExpr[++index]);
        if (index >= r) break;
        pair < int, int > tempOperate = make_pair (oprf, index);
        operate = min (operate, tempOperate);
        index++;
    }
    int op = operate.first;
    int splitPosition = operate.second;
    if (splitPosition != INT_MAX)
    {
        ans = GetThreeItemOperationValue(op, GetValue (l, splitPosition - 1), GetValue (splitPosition + 1, r));
    }
    else
    {
        if (parsedExpr[l] == '(' && parsedExpr[r] == ')')
        {
            int ll = l + 1, rr = r - 1;
            while (parsedExpr[ll] == '(' && parsedExpr[rr] == ')')
            {
                ll++;
                rr--;
            }
            ans = GetValue (ll, rr);
        }
        else
        {
            bool isFunction = false;
            int functionName_size = 0;
            string temp_e = parsedExpr.substr (l, r - l + 1);
            for (string :: iterator iter = temp_e.begin ();iter != temp_e.end ();iter++)
            {
                functionName_size++;
                if (*iter == '(')
                {
                    isFunction = true;
                    break;
                }
            }
            if (isFunction)
            {
                ans = GetFuncValue(parsedExpr.substr(l, functionName_size - 1), l + functionName_size, r - 1);
            }
            else
            {
                ans = GetSingleValue(l, r);
            }
        }
    }
    return ans;
}

double ExpressionParser :: GetSingleValue (int l, int r)
{
    double ans = 0;
    int index = l;
    double sign = ((parsedExpr[l] == '-') ? -1 : 1);
    if (sign < 0)index++;
    if (isdigit (parsedExpr[index]))
    {
        double integer = 0, decimal = 0;
        int decimalIndex = 0;
        bool isDecimal = false;
        string temp_e = parsedExpr.substr (index, r - index + 1);
        for (string :: iterator iter = temp_e.begin ();iter != temp_e.end ();iter++)
        {
            char c = *iter;
            if (isdigit (c))
            {
                if (!isDecimal)
                {
                    integer = integer * 10 + c - '0';
                }
                else
                {
                    decimal = decimal * 10 + c - '0';
                    decimalIndex++;
                }
            }
            else if (c == '.')
            {
                isDecimal = true;
                continue;
            }
        }
        ans += integer + pow (0.1, decimalIndex) * decimal;
    }
    else
    {
        string varName = parsedExpr.substr (l, r - l + 1);
        if (varName == "pi")
            ans = acos (-1.0);
        else if (varName == "e")
            ans = 2.71828;
        else
        {
            if (var_dic[varName])
            {
                ans = var_dic[varName];
            }
        }
    }
    return sign * ans;
}

double ExpressionParser :: GetFuncValue(string funcName, int l, int r)
{
    double ans = 0;
    int index = l;
    double sign = ((parsedExpr[index] == '-') ? -1 : 1);
    if (sign < 0)index++;
    if (funcName == "sin")
    {
        double operatingNum = GetValue (l, r);
        ans = sin (operatingNum);
    }
    else if (funcName == "cos")
    {
        double operatingNum = GetValue (l, r);
        ans = cos (operatingNum);
    }
    else if (funcName == "tan")
    {
        double operatingNum = GetValue (l, r);
        ans = tan (operatingNum);
    }
    else if (funcName == "cot")
    {
        double operatingNum = GetValue (l, r);
        ans = 1.0 / tan (operatingNum);
    }
    else if (funcName == "arcsin")
    {
        double operatingNum = GetValue (l, r);
        ans = asin(operatingNum);
    }
    else if (funcName == "arccos")
    {
        double operatingNum = GetValue (l, r);
        ans = acos(operatingNum);
    }
    else if (funcName == "arctan")
    {
        double operatingNum = GetValue (l, r);
        ans = atan(operatingNum);
    }
    else if (funcName == "arccot")
    {
        double operatingNum = GetValue (l, r);
        ans = atan(1.0 / operatingNum);
    }
    else if (funcName == "abs")
    {
        double operatingNum = GetValue (l, r);
        ans = abs (operatingNum);
    }
    else if (funcName == "max")
    {
        vector < pair < int, int > > *params = GetParameters(l, r);
        return max (GetValue ((*params)[0].first, (*params)[0].second), GetValue ((*params)[1].first, (*params)[1].second));
    }
    else ans = GetUserDefinedFuncValue (funcName, l, r);
    return ans;
}

double ExpressionParser :: GetUserDefinedFuncValue (string funcName, int l, int r)
{
    double ans = 0;
    Function *function = func_dic[funcName];
    string expr = function->GetExpression ();
    vector < pair < int, int > > *params = GetParameters (l, r);
    vector < double > *values = new vector < double > ();
    for (vector < pair < int, int > > :: iterator iter = params->begin (); iter != params->end ();iter++)
    {
        pair < int, int> p = *iter;
        values->push_back(GetValue(p.first, p.second));
    }
    Expression *expression = new Expression (expr);
    ExpressionParser *newParser = new ExpressionParser (expression);
    newParser->InitializeFunctionLib (&func_dic);
    string currentVar = "";
    for (vector < double > :: iterator iter = values->begin ();iter != values->end ();iter++)
    {
        double v = *iter;
        currentVar += "x";
        newParser->SetVariable(currentVar, v);
    }
    newParser->ParseExpression ();
    CalculationResult *tempAns = newParser->GetResult ();
    ans = tempAns->GetResult ();
    return ans;
}

double ExpressionParser :: GetThreeItemOperationValue(int op, double l, double r)
{
    switch (op)
    {
        case ADD :
            return l + r;
            break;
        case SUB :
            return l - r;
            break;
        case MUL :
            return l * r;
            break;
        case DIV :
            return l / r;
            break;
        case EXP :
            return pow (l, r);
            break;
        default :
            return 0;
    }
}

int ExpressionParser :: GetChildExpressionPos (int start)
{
    int index = start;
    if (parsedExpr[index] == '-')
        index++;
    int frontBracket = 0, backBracket = 0;
    bool isStillInBracket = false;
    for (;index < p_expr_size;index++)
    {
        char c = parsedExpr[index];
        if (isdigit (c) | isalpha (c) || c == '.')
            continue;
        if (c == '(')
        {
            frontBracket++;
            isStillInBracket = true;
        }
        else if (c == ')')
        {
            backBracket++;
            if (frontBracket == backBracket)
                break;
        }
        else if (!isStillInBracket)
        {
            index--;
            break;
        }
    }
    if (index == p_expr_size)
        index--;
    return index;
}

int ExpressionParser :: OperatorReflection (char c)
{
    switch (c)
    {
        case '+' :
            return ADD;
            break;
        case '-' :
            return SUB;
            break;
        case '*' :
            return MUL;
            break;
        case '/' :
            return DIV;
            break;
        case '^' :
            return EXP;
            break;
        default :
            return NONEXIST;
    }
}

void ExpressionParser :: ParseExpression ()
{
    result->SetAllParams(GetValue (0, p_expr_size - 1), true, "HAHA");
}

CalculationResult *ExpressionParser :: GetResult ()
{
    CalculationResult *ret = new CalculationResult (*result);
    return ret;
}

CalculationResult *ExpressionParser :: SetVariable(string varName, double value)
{
    CalculationResult *ret = new CalculationResult ();
    if (var_dic[varName])
    {
        var_dic[varName] = value;
        ret->SetAllParams(1.0, true, "Altered!");
    }
    else
    {
        var_dic[varName] = value;
        ret->SetAllParams(1.0, true, "Added!");
    }
    return ret;
}

vector< pair < int, int > > *ExpressionParser :: GetParameters (int l, int r)
{
    vector< pair < int, int > > *ret = new vector < pair < int, int > > ();
    int ll = l, rr = r;
    int lindex = ll, rindex = ll;
    while (rindex <= rr)
    {
        if (parsedExpr[rindex] == ',')
        {
            ret->push_back (make_pair (lindex, rindex - 1));
            lindex = rindex + 1;
            if (lindex > rr)
                break;
        }
        if (rindex == rr)
            ret->push_back(make_pair (lindex, rindex));
        rindex++;
    }
    return ret;
}

void ExpressionParser :: CheckExpression ()
{
    bool isErrorDeteced = false;
    result->SetAllParams (1.0, true, "");
    if (originalExpr == NULL || p_expr_size == 0)
    {
        isErrorDeteced = true;
        result->SetAllParams(0.0, false, "The expression doesn't exist or is empty. Pleaes check your input!");
        return;
    }
    for (string :: iterator iter = parsedExpr.begin ();iter != parsedExpr.end ();iter++)
    {
        char c = *iter;
        if (!isdigit (c) && !isalpha (c))
        {
            if (c != '(' && c != ')')
            {
                if (OperatorReflection (c) == NONEXIST)
                {
                    int pos = (int)(iter - parsedExpr.begin ()) + 1;
                    isErrorDeteced = true;
                    result->AttachInformation (string ("Invalid character \'") + c + "\' is detected at the" + to_string (pos) + "one.");
                }
            }
        }
    }
    if (isErrorDeteced)
    {
        result->SetResult (0.0);
        result->SetValidity (false);
        return;
    }
    CheckExpression(0, p_expr_size - 1);
    if (!isErrorDeteced)
    {
        result->SetAllParams(1.0, true, "The expression is valid. However the variables have not been checked yet.");
    }
    else
    {
        result->SetResult (0.0);
        result->SetValidity (false);
    }
}

void ExpressionParser :: CheckExpression(int l, int r)
{
    
}

CalculationResult *ExpressionParser :: AddNewFunction (string name, int num, string expr)
{
    CalculationResult *ret = new CalculationResult ();
    if (func_dic[name] != NULL)
    {
        ret->SetAllParams(0.0, false, "The function has already been defined!");
    }
    else
    {
        Function *newFunc = new Function (name, num, expr);
        func_dic[name] = newFunc;
        ret->SetAllParams(1.0, true, "The function has been inserted into the parser!");
    }
    return ret;
}

CalculationResult *ExpressionParser :: DeleteFunction (string name)
{
    CalculationResult *ret = new CalculationResult ();
    if (func_dic[name] == NULL)
    {
        ret->SetAllParams(0.0, false, "The indicated function does not exist at all.");
    }
    else
    {
        func_dic[name] = NULL;
        ret->SetAllParams(1.0, true, "The indicated function has been removed from the parser!");
    }
    return ret;
}

void ExpressionParser :: InitializeFunctionLib (map<string, Function *> *lib)
{
    func_dic = *lib;
}