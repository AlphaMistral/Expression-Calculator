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
    result = CalculationResult ();
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
    result = CalculationResult ();
}

ExpressionParser :: ~ExpressionParser ()
{
    var_dic.clear ();
    func_dic.clear ();
    for (vector <Function *> :: iterator iter = funcs.begin ();iter != funcs.end ();iter++)
    {
        delete *iter;
    }
    for (vector <Numeric *> :: iterator iter = nums.begin ();iter != nums.end ();iter++)
    {
        delete *iter;
    }
    funcs.clear ();
    nums.clear ();
}

Numeric *ExpressionParser :: GetValue (int l, int r)
{
    shared_ptr <Numeric> ans (new Numeric ());
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
        Numeric *a1 = GetValue (l, splitPosition - 1);
        Numeric *a2 = GetValue (splitPosition + 1, r);
        Numeric *test = GetThreeItemOperationValue (op, a1, a2);
        ans.reset (test);
        delete a1;
        delete a2;
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
            ans.reset (GetValue (ll, rr));
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
                ans.reset (GetFuncValue (parsedExpr.substr(l, functionName_size - 1), l + functionName_size, r - 1));
            }
            else
            {
                Numeric *a = GetSingleValue (l, r);
                ans.reset (a);
            }
        }
    }
    Numeric *ret = ans.get ()->Clone ();
    return ret;
}

Numeric *ExpressionParser :: GetSingleValue (int l, int r)
{
    shared_ptr <Numeric> ans (new Numeric ());
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
        ans.reset (new Double (integer + pow (0.1, decimalIndex) * decimal));
    }
    else
    {
        string varName = parsedExpr.substr (l, r - l + 1);
        if (varName == "pi")
            ans.reset (new Double (acos (-1.0)));
        else if (varName == "e")
            ans.reset (new Double (2.71828));
        else
        {
            if (var_dic.find (varName) != var_dic.end ())
            {
                ans.reset (var_dic[varName]->Clone ());
            }
        }
    }
    Numeric *ret = ans.get ()->Clone ();
    return ret;
}

Numeric *ExpressionParser :: GetFuncValue(string funcName, int l, int r)
{
    shared_ptr <Numeric> ans (new Numeric ());
    int index = l;
    double sign = ((parsedExpr[index] == '-') ? -1 : 1);
    if (sign < 0)index++;
    if (funcName == "sin")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (sin (dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "cos")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (cos (dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "tan")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (tan (dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "cot")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (1.0 / tan (dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "arcsin")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (asin (dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "arccos")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (acos (dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "arctan")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (atan (dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "arccot")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (atan (1.0 / dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "abs")
    {
        Numeric *operand = GetValue (l, r);
        if (operand->GetType () == NumericType :: DOUBLE)
        {
            Double dou = *static_cast<Double *> (operand);
            ans.reset (new Double (abs (dou.GetValue ())));
        }
        delete operand;
    }
    else if (funcName == "max")
    {
        vector < pair < int, int > > *params = GetParameters(l, r);
        int l1 = (*params)[0].first, r1 = (*params)[0].second;
        int l2 = (*params)[1].first, r2 = (*params)[1].second;
        delete params;
        shared_ptr<Double> d1 (static_cast<Double *> (GetValue (l1, r1)));
        shared_ptr<Double> d2 (static_cast<Double *> (GetValue (l2, r2)));
        ans.reset (new Double (max (d1.get ()->GetValue (), d2.get ()->GetValue ())));
    }
    else
    {
        Numeric *ano = GetUserDefinedFuncValue (funcName, l, r);
        ans.reset (ano);
    }
    Numeric *ret = ans.get ()->Clone ();
    return ret;
}

Numeric *ExpressionParser :: GetUserDefinedFuncValue (string funcName, int l, int r)
{
    Function *function = func_dic[funcName];
    Expression *expr = function->GetExpression ();
    vector < pair < int, int > > *params = GetParameters (l, r);
    vector < Numeric * > *values = new vector < Numeric * > ();
    for (vector < pair < int, int > > :: iterator iter = params->begin (); iter != params->end ();iter++)
    {
        pair < int, int> p = *iter;
        values->push_back (GetValue (p.first, p.second));
    }
    ExpressionParser *newParser = new ExpressionParser (expr);
    newParser->InitializeFunctionLib (func_dic);
    char c = 'a' - 1;
    for (vector < Numeric * > :: iterator iter = values->begin ();iter != values->end ();iter++)
    {
        newParser->SetVariable (string (1, ++c), *iter);
    }
    CalculationResult tempAns = newParser->ParseExpression ();
    for (vector < Numeric * > :: iterator iter = values->begin ();iter != values->end ();iter++)
    {
        delete *iter;
    }
    delete values;
    delete newParser;
    delete params;
    Numeric *ret = tempAns.numeric.get ()->Clone ();
    return ret;
}

Numeric *ExpressionParser :: GetThreeItemOperationValue(int op, Numeric *l, Numeric *r)
{
    shared_ptr <Numeric> ans (new Numeric ());
    switch (op)
    {
        case ADD :
            ans.reset (Add (l, r).numeric->Clone ());
            break;
        case SUB :
            ans.reset (Sub (l, r).numeric->Clone ());
            break;
        case MUL :
            ans.reset (Mul (l, r).numeric->Clone ());
            break;
        case DIV :
            ans.reset (Div (l, r).numeric->Clone ());
            break;
        case EXP :
            ans.reset (Exp (l, r).numeric->Clone ());
            break;
        default :
            break;
    }
    Numeric *ret = ans.get ()->Clone ();
    return ret;
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

CalculationResult ExpressionParser :: ParseExpression ()
{
    CalculationResult checkResult = CheckExpression ();
    if (!checkResult.isValid)
    {
        result.SetAllParams(new Numeric (), false, "The Expression is not parsed and calculated because following error(s) is (are) detected: \n" + checkResult.statusInformation);
    }
    else
    {
        result.SetAllParams(GetValue (0, p_expr_size - 1), true, "The result is valid \n");
    }
    return result;
}

CalculationResult ExpressionParser :: ParseExpression (Expression *expr)
{
    Expression *oldExpr = originalExpr;
    int oldSize = p_expr_size;
    string oldPExpr = parsedExpr;
    CalculationResult oldResult = result;
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
    CalculationResult ret = result;
    originalExpr = oldExpr;
    p_expr_size = oldSize;
    parsedExpr = oldPExpr;
    result = oldResult;
    return ret;

}

CalculationResult ExpressionParser :: GetResult ()
{
    return result;
}

void ExpressionParser :: SetVariable(string varName, Numeric *value)
{
    nums.push_back (value->Clone ());
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

CalculationResult ExpressionParser :: AddNewFunction (Function *func)
{
    CalculationResult ret = CalculationResult (1, true, "");
    Function *newFunc = new Function (func);
    funcs.push_back (newFunc);
    if (func_dic.find (newFunc->GetName ()) != func_dic.end ())
    {
        ret.SetAllParams(new Numeric (), false, "The function has already been defined! \n");
    }
    else
    {
        CalculationResult function_anal = CheckFunctionValidity (newFunc);
        if (!function_anal.isValid)
        {
            ret.SetAllParams(new Numeric (), false, "The expression of the function has some errors: \n" + function_anal.statusInformation + "Hence the Function is not added into the parser! ");
        }
        else
        {
            func_dic[newFunc->GetName ()] = newFunc;
            ret.SetAllParams(new Numeric (), true, "The function has been inserted into the parser! \n");
        }
    }
    return ret;
}

CalculationResult ExpressionParser :: DeleteFunction (string name)
{
    CalculationResult ret = CalculationResult ();
    if (func_dic.find (name) == func_dic.end ())
    {
        ret.SetAllParams(new Numeric (), false, "The indicated function does not exist at all. \n");
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
        ret.SetAllParams(new Numeric (), true, "The indicated function has been removed from the parser! \n");
    }
    return ret;
}

void ExpressionParser :: InitializeFunctionLib (map<string, Function *> lib)
{
    func_dic = lib;
}

CalculationResult ExpressionParser :: CheckExpression ()
{
    CalculationResult ret = CalculationResult (1.0, true, "");
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
        ret.statusInformation += string("Invalid Character \'" + string (1, c) + "\' detected. \n");
    }
    CheckThreeItemExpression(&ret, 0, p_expr_size - 1);
    if (ret.statusInformation != "")
    {
        ret.result = 0.0;
        ret.isValid = false;
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
                ret->statusInformation += string("Invalid Sequence \'" + parsedExpr.substr(invalidInterval.first, invalidInterval.second) + "\' is detected. \n");
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
                ret->statusInformation += string("Operator Missing Error Detected at position " + to_string (currentIndex) + ". \n");
            }
            else if (so_calledOperator.size () != 1)
            {
                ret->statusInformation += string("Invalid Operator \'" + so_calledOperator + "\' Detected. \n");
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
            ret->statusInformation += string("Function \'" + string("max") + "\' Requires" + to_string (2) + " Parameter(s), while " + to_string (params->size ()) + " Provided. \n");
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
        ret->statusInformation += string("Invalid Function \'" + funcName + "\' Detected! \n");
    }
    else
    {
        vector < pair < int, int > > *params = GetParameters (l + 1, r - 1);
        Function *func = func_dic[funcName];
        int num = func->GetVarNum ();
        if (params->size () != num)
        {
            ret->statusInformation += string("Function \'" + funcName + "\' Requires" + to_string (num) + " Parameter(s), while " + to_string (params->size ()) + " Provided. \n");
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
        if (str == "pi" || str == "e")return;
        if (var_dic.find (str) == var_dic.end ())
        {
            ret->statusInformation += string("Variable \'" + str + "\' does not exist. \n");
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
                ret->statusInformation += string("Number \'" + str + "\' is invalid. \n");
                return;
            }
        }
        else if (!isdigit (c))
        {
            ret->statusInformation += string ("Number \'" + str + "\' is invalid. \n");
            return;
        }
    }
}

CalculationResult ExpressionParser :: CheckExpression (Expression *expr)
{
    Expression *oldExpr = originalExpr;
    int oldSize = p_expr_size;
    string oldPExpr = parsedExpr;
    CalculationResult oldResult = result;
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
    CalculationResult ret = result;
    originalExpr = oldExpr;
    p_expr_size = oldSize;
    parsedExpr = oldPExpr;
    result = oldResult;
    return ret;
}

CalculationResult ExpressionParser :: SetToNewExpression (Expression *expr)
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

CalculationResult ExpressionParser :: CheckFunctionValidity (Function *func)
{
    int varNum = func->GetVarNum ();
    Expression *expr = func->GetExpression ();
    ExpressionParser *newParser = new ExpressionParser (expr);
    newParser->InitializeFunctionLib (func_dic);
    char c = 'a' - 1;
    for (int i = 0;i < varNum;i++)
    {
        Numeric *temp = new Numeric ();
        newParser->SetVariable(string (1, ++c), temp);
        delete temp;
    }
    CalculationResult checkResult = newParser->CheckExpression ();
    delete newParser;
    return checkResult;
}

vector <Function *> ExpressionParser :: GetFunctionList ()
{
    return funcs;
}

