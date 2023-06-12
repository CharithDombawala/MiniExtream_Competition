#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <algorithm>

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '%' || c == '@' || c == '(');
}

bool isDigit(char c)
{
    return std::isdigit(c);
}

int evaluate(int operand1, int operand2, char op)
{
    if (op == '+')
        return operand1 + operand2;
    else if (op == '-')
    {
        if (operand1 > operand2)
        {
            return operand1 - operand2;
        }
        else
        {
            return operand2 - operand1;
        }
    }
    else if (op == '*')
        return operand1 * operand2;
    else if (op == '%')
        return std::min(operand1, operand2);
    else if (op == '@')
        return std::max(operand1, operand2);

    return 0;
}

int evaluateExpression(const std::string &expression)
{
    std::stack<int> values;
    std::stack<char> operators;

    for (size_t i = 0; i < expression.length(); i++)
    {
        if (expression[i] == '(')
        {
            operators.push('(');
        }

        else if (isDigit(expression[i]))
        {
            int num = 0;
            while (i < expression.length() && isDigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            values.push(num);
        }

        else if (isOperator(expression[i]))
        {
            while (!operators.empty() && operators.top() != '(' &&
                   ((expression[i] == '+' || expression[i] == '-') ||
                    ((expression[i] == '*' || expression[i] == '%') &&
                     (operators.top() == '*' || operators.top() == '%'))))
            {

                int operand2 = values.top();
                values.pop();
                int operand1 = values.top();
                values.pop();
                char op = operators.top();
                operators.pop();

                values.push(evaluate(operand1, operand2, op));
            }
            operators.push(expression[i]);
        }
        else if (expression[i] == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                if (values.empty())
                {
                    std::cerr << "invalid" << std::endl;
                    return -1;
                }
                int operand2 = values.top();
                values.pop();
                if (values.empty())
                {
                    std::cerr << "invalid" << std::endl;
                    return -1;
                }
                int operand1 = values.top();
                values.pop();
                if (operators.empty())
                {
                    std::cerr << "invalid" << std::endl;
                    return -1;
                }
                char op = operators.top();
                operators.pop();

                values.push(evaluate(operand1, operand2, op));
            }
            if (operators.empty() || operators.top() != '(')
            {
                std::cerr << "invalid" << std::endl;
                return -1;
            }
            operators.pop();
        }
    }

    while (!operators.empty())
    {
        if (values.empty())
        {
            std::cerr << "invalid" << std::endl;
            return -1;
        }
        int operand2 = values.top();
        values.pop();
        if (values.empty())
        {
            std::cerr << "invalid" << std::endl;
            return -1;
        }
        int operand1 = values.top();
        values.pop();
        if (operators.empty())
        {
            std::cerr << "invalid" << std::endl;
            return -1;
        }
        char op = operators.top();
        operators.pop();

        values.push(evaluate(operand1, operand2, op));
    }

    if (values.empty())
    {
        std::cerr << "invalid" << std::endl;
        return -1;
    }

    return values.top();
}

int main()
{
    int N;
    std::cin >> N;
    std::cin.ignore(); 

    for (int i = 0; i < N; i++)
    {
        std::string expression;
        std::getline(std::cin, expression);

        bool valid = true;
        for (size_t i = 0; i < expression.length(); i++)
        {
            if (!isOperator(expression[i]) && !isDigit(expression[i]) && expression[i] != '(' && expression[i] != ')')
            {
                valid = false;
                break;
            }
            if (i > 0 && isDigit(expression[i - 1]) && expression[i] == '(')
            {
                valid = false;
                break;
            }
        }

        if (!valid || expression.empty())
        {
            std::cout << "invalid" << std::endl;
        }
        else
        {
            int result = evaluateExpression(expression);
            if (result < 0)
            {
                std::cout << "invalid" << std::endl;
            }
            else
            {
                std::cout << result << std::endl;
            }
        }
    }

    return 0;
}