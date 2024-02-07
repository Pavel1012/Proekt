#include <iostream>
#include <stack>
#include <cmath>
#include <cctype>
using namespace std;
class Expression {
private:
    string inf;

public:
    Expression(const string& expression) : inf(expression) {}

    bool isOperator(char ch) {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
    }

    int getOperatorPrecedence(char op) {
        if (op == '^')
            return 3;
        else if (op == '*' || op == '/')
            return 2;
        else if (op == '+' || op == '-')
            return 1;
        else
            return -1;
    }

    double calculate(double operand1, double operand2, char op) {
        switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            return operand1 / operand2;
        case '^':
            return pow(operand1, operand2);
        default:
            return 0;
        }
    }

    double evaluate() {
        stack<double> operands;
        stack<char> operators;

        for (size_t i = 0; i < inf.length(); i++) {
            if (inf[i] == ' ')
                continue;

            if (isdigit(inf[i])) {
                double operand = 0;
                while (i < inf.length() && isdigit(inf[i])) {
                    operand = operand * 10 + (inf[i] - '0');
                    i++;
                }
                i--;

                operands.push(operand);
            }
            else if (inf[i] == '(') {
                operators.push(inf[i]);
            }
            else if (inf[i] == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    double operand2 = operands.top();
                    operands.pop();

                    double operand1 = operands.top();
                    operands.pop();

                    char op = operators.top();
                    operators.pop();

                    double result = calculate(operand1, operand2, op);
                    operands.push(result);
                }

                if (!operators.empty())
                    operators.pop(); 
            }
            else if (isOperator(inf[i])) {
                while (!operators.empty() && getOperatorPrecedence(inf[i]) <= getOperatorPrecedence(operators.top())) {
                    double operand2 = operands.top();
                    operands.pop();

                    double operand1 = operands.top();
                    operands.pop();

                    char op = operators.top();
                    operators.pop();

                    double result = calculate(operand1, operand2, op);
                    operands.push(result);
                }

                operators.push(inf[i]);
            }
        }

        while (!operators.empty()) {
            double operand2 = operands.top();
            operands.pop();

            double operand1 = operands.top();
            operands.pop();

            char op = operators.top();
            operators.pop();

            double result = calculate(operand1, operand2, op);
            operands.push(result);
        }

        return operands.top();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    string expression;
    cout << "---Программа для вычисления математических выражений---" << endl;
    cout << "   Введите математическое выражение: ";
    cin >> expression;
    Expression mathExpression(expression);
    double result = mathExpression.evaluate();
    cout << "   Результат вычисления: " << result << endl;
    cout << "-------------------------------------------------------" << endl;
    return 0;
}