###This is an expression calculator which enables the users to naturally input expressions and define variables and functions.

* Author : Jingping Yu

## Features
======
* Easy-plugin
* Supports handling with wrong expressions and generate corresponding warnings
* Supports user-defined functions and variables

## Documentation
======
* *From now on I will update the document in the online project and make sure it bounds with the codes. Currently you may refer to the docs bellow or have a glance at the codes.*

####Setup and Installation
* Currently the project is still ongoing and due to the fact that I have never planned to make it a fully functional library (It is a homework only actually) the structure is in chaos. However, all you need to do is to **#include "ExpressionParser.hpp"** in your own project. 

####Create an Expression
* In order to work as an expression calculator, an expression is definitely required. You may Create an expression by **Expression \*expression = new Expression ("5 * x + 7 x sin (SHIT (1, 11.24 ^ x))");**

####Create a parser
* With your expression defined, you may create a parser by **ExpressionParser \*parser = new ExpressionParser (expression);**

####Define variables
* As you can see there is an 'x' variable in the expression above. In order to make the parser know this, you need to call the method like this : **parser->SetVariable ("x", 1.1);**.

####Define Functions
* There is a "SHIT" function left undefined in the expression above. There is an *AddNewFunction* method in the ExpressionParser Class with three parameters : string func_name, int var_num, string expression. And you may define the function like this: **parser->AddNewFunction ("SHIT", 2, "max (a + b) * sin (a / b)");**.

####Calculating Results
* Now that you have given an expression and defined the variables and functions, the parser is ready to work now! Simply call **parser->ParseExpression ();** and the result would be stored in the parser. In order to get the result, please call **Calculation \*result = parser->GetResult ();**. Please note that you are not getting a *double value* but rather a *Calculation Result*. There are three elements stored in a *CalculationResult*:
> * Numeric : The actual result of the operation.
> * IsValid : Is the operation actually valid.
> * StatusInformation : The concise information about the operation. Whether the operations are manipulated well or some problems encountered. 
* Since now the Expression Calculator must store **Double**, **Matrix** and **Array** as its result, all these value types inherit from a class called as **Numeric**. Meanwhile in order to make sure that memory leak is avoided, numeric is stored in a **shared_ptr**. Hence, in order to get the result, you may simply code like this: **Numeric \*res = parser->ParseExpression ().numeric.get ();**
* After that, you can cast your **Numeric \*** to other types by using **staic_cast** or **dynamic_cast** depending on the situation. If you are not sure what exactly is stored in the result, you may use **res->GetType () == NumericType :: (COMPARE_TYPE)** to check. Once you are pretty sure about what is stored, **static_cast** is encouraged to use since it is approximately three times faster than **dynamic_cast**.

##Releasing Notes
======
* Now the expression calculator and the numerical analyzer is pretty functional. However the document is still ongoing. I will continue on documenting to make sure that all the users could get the first-hand doc at any time for use. 
* GL & HF!