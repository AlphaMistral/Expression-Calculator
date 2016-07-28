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
> * Value : The actual result of the operation.
> * IsValid : Is the operation actually valid.
> * StatusInformation : The concise information about the operation. Whether the operations are manipulated well or some problems encountered. 
* Here you may simply call **double numericalResult = result->GetValue ();**. 

##Releasing Notes
======
* I have to commit that currently the project is **A PILE OF SHIT**. It works, and works ONLY. I am working on the re-construct the essential codes to make it stronger and more stable. 