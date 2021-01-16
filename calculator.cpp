#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
//#include <ctime>
//#include <cstring>
//#include <sstream>

double evaluateEqu(std::string equ);
std::string findOperands(std::string equ, int index);
std::string findParen(std::string equ, int index);
double calculate(std::string leftNum, std::string rightNum, char operand);

// Given any math equation as a string without exponents or parenthesis
// this function can calculate the value and return it as a double.
int main()
{
    //double start = std::clock();
    double total = evaluateEqu("6+7/10*25+100-20/10+20-50-60+12/43*12/60-90+60*40+12-21+40/50");
    //double duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    //std::cout<<"Duration = "<<duration<<"\n";

    std::cout<<"The total is: "<<total<<"\n";

    return 0;
}

// Loops until the equation no longer has operators.
// Given a certain operator, it gives findOperands the equation and the index
// where the operator was found.
double evaluateEqu(std::string equ)
{
    std::size_t foundParen, foundExp, foundMD, foundAS;
    
    // These find the index of the string they are looking for.
    std::size_t found = equ.find_first_of("(^*/+-");
    
    // Continue the loop while we have operators inside the string.
    while (found != std::string::npos)
    {
        // These find the index of the string they are looking for.
        foundParen = equ.find("(");
        foundExp = equ.find("^");
        // Find the first instance of these operators since they are evaluated left to right.
        foundMD = equ.find_first_of("*/");
        foundAS = equ.find_first_of("+-");

        if (foundParen != std::string::npos)
        {
            equ = findParen(equ, foundParen);
            //std::cout<<"equ = "<<equ<<"\n\n";
        }
        else if (foundExp != std::string::npos)
        {
            equ = findOperands(equ, foundExp);
            //std::cout<<"equ = "<<equ<<"\n\n";
        }
        else if (foundMD != std::string::npos)
        {
            equ = findOperands(equ, foundMD);
            //std::cout<<"equ = "<<equ<<"\n\n";
        }
        else if (foundAS != std::string::npos)
        {
            equ = findOperands(equ, foundAS);
            //std::cout<<"equ = "<<equ<<"\n\n";
        }

        // After doing operation, check if there is any operators left.
        found =  equ.find_first_of("(^*/+-");
    }
    
    // Return the double of the equation.
    return stod(equ);
}

// Finds the operands of the operator so calculate() can use them.
// Returns the string equ with the current operation replaced with its value.
std::string findOperands(std::string equ, int index)
{
    std::string lOperand, rOperand, result;
    char operand = equ[index];
    int i, j;
    //std::cout<<"operand = "<<operand<<"\n";

    // Find the left operand.
    for (i = index - 1; i >= 0; i--)
    {
        if (equ[i] >= 48 || equ[i] == 46)
        {
            lOperand += equ[i];
        }
        else
        {
            break;
        }
    }
    // Since we approached the operand backwards, reverse the string.
    //std::cout<<"leftNum = "<<leftNum<<"\n";
    std::reverse(lOperand.begin(), lOperand.end());
    //std::cout<<"reversed leftNum = "<<leftNum<<"\n";

    // Find the right operand.
    for (j = index + 1; j < equ.length(); j++)
    {
        if (equ[j] >= 48 || equ[j] == 46)
        {
            rOperand += equ[j];
        }
        else
        {
            break;
        }
    }
    //std::cout<<"rightNum = "<<rightNum<<"\n";

    // Calculate the result of the operands.
    result = std::to_string(calculate(lOperand, rOperand, operand));
    //std::cout<<"result = "<<result<<"\n";
    //std::cout<<"equ[i + 1] = "<<equ[i + 1]<<"\n";
    //std::cout<<"equ[j - 2] = "<<equ[j - 2]<<"\n";

    // Replace the parts of the equation with the number we just calculated.
    // i + 1 and j - 2 because of inclusion rules and where values end.
    return equ.replace(i + 1, j - 2, result);
}

// Finds the parenthesis in the equation and figures out which 
std::string findParen(std::string equ, int index)
{
    return "";
}

// Calculates the value of the operands with the given operator and returns the result.
double calculate(std::string lOperand, std::string rOperand, char operand)
{
    double num1 = stod(lOperand);
    double num2 = stod(rOperand);
    double result;

    if (operand == '^')
    {
        result = pow(num1, num2);
    }
    else if (operand == '*')
    {
        result = num1 * num2;
    }
    else if (operand == '/')
    {
        result = num1 / num2;
    }
    else if (operand == '+')
    {
        result = num1 + num2;
    }
    else if (operand == '-')
    {
        result = num1 - num2;
    }

    return result;
}