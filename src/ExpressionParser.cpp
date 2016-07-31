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
    funcs.clear ();
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
    funcs.clear ();
    result = new CalculationResult ();
}

ExpressionParser :: ~ExpressionParser ()
{
    var_dic.clear ();
    func_dic.clear ();
    for (vector <Function *> :: iterator iter = funcs.begin ();iter != funcs.end ();iter++)
    {
        delete *iter;
    }
    funcs.clear ();
    delete result;
}

double ExpressionParser :: GetValue (int l, int r)
{
    double ans = 0;
    pair < int, int > operate = make_pair (INT_MAX, INT_MAX);
    int index = l;
    while (index < r)
    {
        index = GetChildExpressionPos (index);
        if (index == r - 1)
            break;
        int oprf = OperatorReflection (parsedExpr[++index]);
        if (index >= r) break;
        pair < int, int > tempOperate = make_pair (oprf, index);
        operate = min (operate, tempOperate);
        index++;
    }
    int op = operate.first;
    int splitPosition = operate.second;
    if (splitPosition != INT_MAX)
    {
        ans = GetThreeItemOperationValue (op, GetValue (l, splitPosition - 1), GetValue (splitPosition + 1, r));
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
                ans = GetFuncValue (parsedExpr.substr(l, functionName_size - 1), l + functionName_size, r - 1);
            }
            else
            {
                ans = GetSingleValue (l, r);
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
            if (var_dic.find (varName) != var_dic.end ())
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
        int l1 = (*params)[0].first, r1 = (*params)[0].second;
        int l2 = (*params)[1].first, r2 = (*params)[1].second;
        delete params;
        return max (GetValue (l1, r1), GetValue (l2, r2));
    }
    else ans = GetUserDefinedFuncValue (funcName, l, r);
    return ans;
}

double ExpressionParser :: GetUserDefinedFuncValue (string funcName, int l, int r)
{
    double ans = 0;
    Function *function = func_dic[funcName];
    Expression *expr = function->GetExpression ();
    vector < pair < int, int > > *params = GetParameters (l, r);
    vector < double > *values = new vector < double > ();
    for (vector < pair < int, int > > :: iterator iter = params->begin (); iter != params->end ();iter++)
    {
        pair < int, int> p = *iter;
        values->push_back(GetValue(p.first, p.second));
    }
    ExpressionParser *newParser = new ExpressionParser (expr);
    newParser->InitializeFunctionLib (func_dic);
    char c = 'a' - 1;
    for (vector < double > :: iterator iter = values->begin ();iter != values->end ();iter++)
    {
        double v = *iter;
        newParser->SetVariable(string (1, ++c), v);
    }
    newParser->ParseExpression ();
    CalculationResult *tempAns = newParser->GetResult ();
    ans = tempAns->GetResult ();
    delete values;
    delete tempAns;
    delete newParser;
    delete params;
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
            if (r == 0.0)
            {
                result->SetValidity (false);
                result->AttachInformation("A divide by zero Exception is caught during the calculation. \n");
            }
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
            else if (backBracket > frontBracket)
            {
                index--;
                break;
            }
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

CalculationResult *ExpressionParser :: ParseExpression ()
{
    CalculationResult *checkResult = CheckExpression ();
    if (!checkResult->GetValidity ())
    {
        result->SetAllParams(0.0, false, "The Expression is not parsed and calculated because following error(s) is (are) detected: \n" + checkResult->GetInformation ());
    }
    else
        result->SetAllParams(GetValue (0, p_expr_size - 1), true, "The result is valid \n");
    delete checkResult;
    return new CalculationResult (*result);
}

CalculationResult *ExpressionParser :: ParseExpression (Expression *expr)
{
    Expression *oldExpr = originalExpr;
    int oldSize = p_expr_size;
    string oldPExpr = parsedExpr;
    CalculationResult *oldResult = new CalculationResult (*result);
    originalExpr = expr;
    parsedExpr = "";
    string temp_e = expr->GetExpression ();
    for (string :: iterator iter = temp_e.begin ();iter != temp_e.end ();iter++)
    {
        if (*iter != ' ')
            parsedExpr += *iter;
    }
    p_expr_size = (int)parsedExpr.size ();
    ParseExpression ();
    CalculationResult *ret = new CalculationResult (*result);
    originalExpr = oldExpr;
    p_expr_size = oldSize;
    parsedExpr = oldPExpr;
    result->SetAllParams (oldResult->GetResult (), oldResult->GetValidity (), oldResult->GetInformation ());
    delete oldResult;
    return ret;

}

CalculationResult *ExpressionParser :: GetResult ()
{
    CalculationResult *ret = new CalculationResult (*result);
    return ret;
}

void ExpressionParser :: SetVariable(string varName, double value)
{
    var_dic[varName] = value;
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

CalculationResult *ExpressionParser :: AddNewFunction (Function *func)
{
    CalculationResult *ret = new CalculationResult (1, true, "aff");
    Function *newFunc = new Function (func);
    funcs.push_back (newFunc);
    if (func_dic.find (newFunc->GetName ()) != func_dic.end ())
    {
        ret->SetAllParams(0.0, false, "The function has already been defined! \n");
    }
    else
    {
        CalculationResult *function_anal = CheckFunctionValidity (newFunc);
        if (!function_anal->GetValidity ())
        {
            ret->SetAllParams(0.0, false, "The expression of the function has some errors: \n" + function_anal->GetInformation () + "Hence the Function is not added into the parser! ");
        }
        else
        {
            func_dic[newFunc->GetName ()] = newFunc;
            ret->SetAllParams(1.0, true, "The function has been inserted into the parser! \n");
        }
        delete function_anal;
    }
    return ret;
}

CalculationResult *ExpressionParser :: DeleteFunction (string name)
{
    CalculationResult *ret = new CalculationResult ();
    if (func_dic.find (name) == func_dic.end ())
    {
        ret->SetAllParams(0.0, false, "The indicated function does not exist at all. \n");
    }
    else
    {
        for (vector <Function *> :: iterator iter = funcs.begin ();iter != funcs.end ();iter++)
        {
            Function *func = *iter;
            if (func->GetName ()== name)
            {
                funcs.erase (iter);
                break;
            }
        }
        func_dic[name] = NULL;
        ret->SetAllParams(1.0, true, "The indicated function has been removed from the parser! \n");
    }
    return ret;
}

void ExpressionParser :: InitializeFunctionLib (map<string, Function *> lib)
{
    func_dic = lib;
}

CalculationResult *ExpressionParser :: CheckExpression ()
{
    CalculationResult *ret = new CalculationResult (1.0, true, "");
    for (string :: iterator iter = parsedExpr.begin ();iter != parsedExpr.end ();iter++)
    {
        char c = *iter;
        if (isdigit (c) || isalpha(c))
            continue;
        if (c == '(' || c == ')')
            continue;
        if (c == '.' || c == ',')
            continue;
        if (OperatorReflection (c) != NONEXIST)
            continue;
        ret->AttachInformation("Invalid Character \'" + string (1, c) + "\' detected. \n");
    }
    CheckThreeItemExpression(ret, 0, p_expr_size - 1);
    if (ret->GetInformation () != "")
    {
        ret->SetResult (0.0);
        ret->SetValidity (false);
    }
    return ret;
}

void ExpressionParser :: CheckThreeItemExpression (CalculationResult *ret, int l, int r)
{
    pair < int, int > invalidInterval = make_pair (-1, -1);
    int currentIndex = l;
    bool isErrorDetected = false;
    bool isOperatorDetected = false;
    while (currentIndex < r)
    {
        char c = parsedExpr[currentIndex];
        if (!isalpha (c) && !isdigit (c) && c != '(' && c != '.')
        {
            if (invalidInterval.first == -1)
                invalidInterval.first = currentIndex;
            invalidInterval.second = currentIndex;
            isErrorDetected = true;
        }
        else
        {
            if (isErrorDetected)
            {
                ret->AttachInformation ("Invalid Sequence \'" + parsedExpr.substr(invalidInterval.first, invalidInterval.second) + "\' is detected. \n");
            }
            isErrorDetected = false;
            invalidInterval = make_pair (-1, -1);
            int tempIndex = GetChildExpressionPos (currentIndex);
            if (tempIndex == r)
            {
                currentIndex = tempIndex;
                continue;
            }
            else
                CheckThreeItemExpression(ret, currentIndex, tempIndex);
            currentIndex = tempIndex;
            string so_calledOperator = ""; //The operator may be wrong. So it is referred to as "So-called operator" HAHA!
            while (OperatorReflection (parsedExpr[++currentIndex]) != NONEXIST && currentIndex < r)
            {
                so_calledOperator += parsedExpr[currentIndex];
            }
            if (so_calledOperator.size () == 0)
            {
                ret->AttachInformation ("Operator Missing Error Detected at position " + to_string (currentIndex) + ". \n");
            }
            else if (so_calledOperator.size () != 1)
            {
                ret->AttachInformation ("Invalid Operator \'" + so_calledOperator + "\' Detected. \n");
            }
            else isOperatorDetected = true;
            currentIndex--;
        }
        currentIndex++;
    }
    if (!isOperatorDetected)
    {
        int ll = l, rr = r;
        while (parsedExpr[ll] == '(' && parsedExpr[rr] == ')')
        {
            ll++;
            rr--;
        }
        int idx = ll;
        string tempString = parsedExpr.substr (ll, rr - l + 1);
        for (string :: iterator iter = tempString.begin ();iter != tempString.end ();iter++)
        {
            char c = *iter;
            if (c == '(')
            {
                CheckFunctionExpression (ret, parsedExpr.substr (ll, idx - ll), idx, rr);
                return;
            }
            idx++;
        }
        CheckSingleExpression(ret, ll ,rr);
    }
}

void ExpressionParser :: CheckFunctionExpression (CalculationResult *ret, string funcName, int l, int r)
{
    if (funcName == "sin" || funcName == "cos" || funcName == "arcsin" || funcName == "arccos" || funcName == "tan" || funcName == "cot" || funcName == "arctan" || funcName == "arccot" || funcName == "abs")
    {
        CheckThreeItemExpression(ret, l, r);
        return;
    }
    else if (funcName == "max")
    {
        vector < pair < int, int > > *params = GetParameters (l + 1, r - 1);
        if (params->size () != 2)
        {
            ret->AttachInformation ("Function \'" + string("max") + "\' Requires" + to_string (2) + " Parameter(s), while " + to_string (params->size ()) + " Provided. \n");
            return;
        }
        for (vector < pair < int, int > > :: iterator iter = params->begin ();iter != params->end ();iter++)
        {
            pair < int, int > interval = *iter;
            CheckThreeItemExpression (ret, interval.first, interval.second);
        }
        delete params;
        return;
    }
    if (func_dic.find (funcName) == func_dic.end ())
    {
        ret->AttachInformation("Invalid Function \'" + funcName + "\' Detected! \n");
    }
    else
    {
        vector < pair < int, int > > *params = GetParameters (l + 1, r - 1);
        Function *func = func_dic[funcName];
        int num = func->GetVarNum ();
        if (params->size () != num)
        {
            ret->AttachInformation ("Function \'" + funcName + "\' Requires" + to_string (num) + " Parameter(s), while " + to_string (params->size ()) + " Provided. \n");
        }
        for (vector < pair < int, int > > :: iterator iter = params->begin ();iter != params->end ();iter++)
        {
            pair < int, int > interval = *iter;
            CheckThreeItemExpression (ret, interval.first, interval.second);
        }
        delete params;
    }
}

void ExpressionParser :: CheckSingleExpression (CalculationResult *ret, int l, int r)
{
    bool isDecimal = false;
    string str = parsedExpr.substr (l, r - l + 1);
    if (isalpha (str[0]))
    {
        if (var_dic.find (str) == var_dic.end ())
        {
            ret->AttachInformation("Variable \'" + str + "\' does not exist. \n");
        }
        return;
    }
    for (string :: iterator iter = str.begin ();iter != str.end ();iter++)
    {
        char c = *iter;
        if (c == '.')
        {
            if (!isDecimal)
                isDecimal = true;
            else
            {
                ret->AttachInformation("Number \'" + str + "\' is invalid. \n");
                return;
            }
        }
        else if (!isdigit (c))
        {
            ret->AttachInformation ("Number \'" + str + "\' is invalid. \n");
            return;
        }
    }
}

CalculationResult *ExpressionParser :: CheckExpression (Expression *expr)
{
    Expression *oldExpr = originalExpr;
    int oldSize = p_expr_size;
    string oldPExpr = parsedExpr;
    CalculationResult *oldResult = new CalculationResult (*result);
    originalExpr = expr;
    parsedExpr = "";
    string temp_e = expr->GetExpression ();
    for (string :: iterator iter = temp_e.begin ();iter != temp_e.end ();iter++)
    {
        if (*iter != ' ')
            parsedExpr += *iter;
    }
    p_expr_size = (int)parsedExpr.size ();
    CheckExpression ();
    CalculationResult *ret = new CalculationResult (*result);
    originalExpr = oldExpr;
    p_expr_size = oldSize;
    parsedExpr = oldPExpr;
    result = oldResult;
    return ret;
}

CalculationResult *ExpressionParser :: SetToNewExpression (Expression *expr)
{
    originalExpr = expr;
    parsedExpr = "";
    string temp_e = expr->GetExpression ();
    for (string :: iterator iter = temp_e.begin ();iter != temp_e.end ();iter++)
    {
        if (*iter != ' ')
            parsedExpr += *iter;
    }
    p_expr_size = (int)parsedExpr.size ();
    return CheckExpression ();
}

CalculationResult *ExpressionParser :: CheckFunctionValidity (Function *func)
{
    int varNum = func->GetVarNum ();
    Expression *expr = func->GetExpression ();
    ExpressionParser *newParser = new ExpressionParser (expr);
    newParser->InitializeFunctionLib (func_dic);
    char c = 'a' - 1;
    for (int i = 0;i < varNum;i++)
    {
        newParser->SetVariable(string (1, ++c), 1.0);
    }
    CalculationResult *checkResult = newParser->CheckExpression ();
    CalculationResult *ret = new CalculationResult (*checkResult);
    delete newParser;
    delete checkResult;
    return ret;
}

vector <Function *> ExpressionParser :: GetFunctionList ()
{
    return funcs;
}