#include "calculate.h"

#include <Qstack>
#include <Qvector>
#include <Qstring>
#include <cmath>
#include <QChar>
#include <iostream>
using namespace std;

enum ABS_ODEVITY {
    ABS_ODD = 1,
    ABS_EVEN = 2,
};

enum PRIO_LV {
    PRIO_LV0 = 0,
    PRIO_LV1 = 1,
    PRIO_LV2 = 2,
    PRIO_LV3 = 3,
    PRIO_LV4 = 4,
};

Calculate::Calculate(QString input) {
    infix = input;
    result = 0.0;
}


void Calculate::getFormat() {

    stdInfix = infix;
    for (int i = 0; i < stdInfix.size(); i++) {
        if (stdInfix[i] == '-' || stdInfix[i] == '+') {
            if (i == 0) {
                stdInfix.insert(0, '0');
            }
            else if (stdInfix[i - 1] == '(') {
                stdInfix.insert(i, '0');
            }
        }
    }
    cout << "std:" << stdInfix.toStdString() << endl;
}

int Calculate::getPrior(QChar c) {

    if (c == '+' || c == '-') {
        return PRIO_LV1;
    }
    else if (c == '*' || c == '/') {
        return PRIO_LV2;
    }
    else if (c == '%' || c == '^') {
        return PRIO_LV3;
    }
    else if (c == '!' || c == 's') {
        return PRIO_LV4;
}
else {
    return PRIO_LV0;
}
}

void Calculate::getPostfix() {
    int absNumeber = ABS_ODD;
    QString tmp;
    for (size_t i = 0; i < stdInfix.size(); i++) {
        tmp = "";
        switch (stdInfix[i].toLatin1()) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case '!':
        case 's':
                if (symStack.empty() || symStack.top() == '(' || symStack.top() == '[' || symStack.top() == '{' || (symStack.top() == '|' && absNumeber == ABS_ODD)) {
                    symStack.push(stdInfix[i]);
                }
                else {
                    while (!symStack.empty() && (getPrior(symStack.top()) >= getPrior(stdInfix[i]))) {
                        tmp += symStack.top();
                        postfix.push_back(tmp);
                        symStack.pop();
                        tmp = "";
                    }
                    symStack.push(stdInfix[i]);
                }
                break;
        case '|':
                if (absNumeber == ABS_ODD) {
                    symStack.push(stdInfix[i]);
                    absNumeber = ABS_EVEN;
                }
                else{
                    while (!symStack.empty() && symStack.top() != '|') {
                        tmp += symStack.top();
                        postfix.push_back(tmp);
                        symStack.pop();
                        tmp = "";
                    }
                    if (!symStack.empty() && symStack.top() == '|') {
                        tmp += symStack.top();
                        postfix.push_back(tmp);
                        symStack.pop();
                        absNumeber = ABS_ODD;
                    }
                }
                break;
        case '(':
        case '[':
        case '{':
                symStack.push(stdInfix[i]);
                break;
        case ')':
                while (!symStack.empty() && symStack.top() != '(') {
                    tmp += symStack.top();
                    postfix.push_back(tmp);
                    symStack.pop();
                    tmp = "";
                }
                if (!symStack.empty() && symStack.top() == '(') {
                    symStack.pop();
                }
                break;
        case ']':
                while (!symStack.empty() && symStack.top() != '[') {
                    tmp += symStack.top();
                    postfix.push_back(tmp);
                    symStack.pop();
                    tmp = "";
                }
                if (!symStack.empty() && symStack.top() == '[') {
                    symStack.pop();
                }
                break;
        case '}':
                while (!symStack.empty() && symStack.top() != '{') {
                    tmp += symStack.top();
                    postfix.push_back(tmp);
                    symStack.pop();
                    tmp = "";
                }
                if (!symStack.empty() && symStack.top() == '{') {
                    symStack.pop();
                }
                break;
        default:
                if ((stdInfix[i] >= '0' && stdInfix[i] <= '9')) {
                    tmp += stdInfix[i];
                    while (i + 1 < stdInfix.length() && (stdInfix[i + 1] >= '0' && stdInfix[i + 1] <= '9' || stdInfix[i + 1] == '.')) {

                        tmp += stdInfix[i + 1];
                        i++;
                    }
                    if (tmp[tmp.length() - 1] == '.') {
                        tmp += '0';
                    }
                    postfix.push_back(tmp);
                }
                break;
        }
    }
    while (!symStack.empty()) {
        tmp = "";
        tmp += symStack.top();
        postfix.push_back(tmp);
        symStack.pop();
    }
}

void Calculate::calResult() {

    QString tmp;
    double number = 0;
    double op1 = 0, op2 = 0;

    for (int i = 0; i < postfix.size(); i++) {
        tmp = postfix[i];
        cout << "tmp:" << tmp.toStdString() << endl;
        if (tmp[0] >= '0' && tmp[0] <= '9') {
            number = tmp.toDouble();
            figStack.push(number);
            cout << number << "was pushed" << endl;
        }
        else if (postfix[i] == "+") {
            std::cout << "!\n";
            if (!figStack.empty()) {
                op2 = figStack.top();
                figStack.pop();
            }
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            cout << op1 << ' ' << op2 << endl;
            figStack.push(op1 + op2);
        }
        else if (postfix[i] == "-") {
            if (!figStack.empty()) {
                op2 = figStack.top();
                figStack.pop();
            }
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            figStack.push(op1 - op2);
        }
        else if (postfix[i] == "*") {
            if (!figStack.empty()) {
                op2 = figStack.top();
                figStack.pop();
            }
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            figStack.push(op1* op2);
        }
        else if (postfix[i] == "/") {
            if (!figStack.empty()) {
                op2 = figStack.top();
                figStack.pop();
            }
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            if (op2 != 0) {
            }
            figStack.push(op1 / op2);
        }
        else if (postfix[i] == "%") {
            if (!figStack.empty()) {
                op2 = figStack.top();
                figStack.pop();
            }
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            figStack.push(fmod(op1, op2));
        }
        else if (postfix[i] == "^") {
            if (!figStack.empty()) {
                op2 = figStack.top();
                figStack.pop();
            }
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            figStack.push(pow(op1, op2));
        }
        else if (postfix[i] == "|") {
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            figStack.push(abs(op1));
        }
        else if (postfix[i] == "!") {
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            if (op1 > 0) {
                double factorial = 1;
                for (int i = 1; i <= op1; ++i)
                {
                    factorial *= i;
                }
                op1 = factorial;
            }
            figStack.push(op1);
        } else if (postfix[i] == "s") {
            if (!figStack.empty()) {
                op1 = figStack.top();
                figStack.pop();
            }
            if (op1 > 0) {
                op1 = sqrt(op1);
            }
            figStack.push(op1);
       }
    }
    if (!figStack.empty()) {
        result = figStack.top();
    }
}

void Calculate::calculate() {

    getFormat();
    getPostfix();
    calResult();
}

double Calculate::getResult() {
    return result;
}
