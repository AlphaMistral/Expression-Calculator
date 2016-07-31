//
//  Calculation.hpp
//  Numerical Analysis
//
//  Created by 于京平 on 16/7/22.
//  Copyright © 2016年 于京平. All rights reserved.
//

#ifndef Calculation_hpp
#define Calculation_hpp

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

/*class CalculationResult
{
    private :
    
    double result; // Stores the result generated by the calculating process
    bool isValid; // Whether the result is valid or not.
    string statusInformation; // The text information of the result. It indicates how the result is generated.
    
    public :
    
    //Constructors
    CalculationResult ();
    CalculationResult (double, bool, string);
    CalculationResult (CalculationResult &);
    
    void SetAllParams (double, bool, string);
    
    // It is not recommened to set the params individually. Unless you are very sure about what you are doing.
    void SetResult (double);
    void SetValidity (bool);
    void SetInformation (string);
    void AttachInformation (string);
    
    double GetResult ();
    bool GetValidity ();
    string GetInformation ();
    
    //Debugging Functions
    void OutputResult ();
};
*/

struct CalculationResult
{
    double result;
    bool isValid;
    string statusInformation;
    
    CalculationResult ()
    {
        result = 0.0;
        isValid = false;
        statusInformation = "";
    }
    
    CalculationResult (double r, bool i, string s)
    {
        result = r;
        isValid = i;
        statusInformation = s;
    }
    
    void SetAllParams (double r, bool i, string s)
    {
        result = r;
        isValid = i;
        statusInformation = s;
    }
    void OutputResult ()
    {
        cerr << endl << "******The Output Result for the indicated operation is as follows******" << endl;
        cerr << "The numerical result is: " << result << endl;
        cerr << "The result is ";
        if (!isValid) cerr << "in";
        cerr << "valid." << endl;
        cerr << "The Status Information is: " << statusInformation << endl;
        cerr << "******This is the end of the result of the indicated operation******" << endl << endl;
    }
};

#endif /* Calculation_hpp */
