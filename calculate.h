
#include <Qstack>
#include <Qvector>
#include <Qstring>
using namespace std;

class Calculate {
public:
    Calculate(QString input);
    void getFormat();
    int getPrior(QChar c);
    void getPostfix();
    void calResult();
    void calculate();
    double getResult();
    double fact(int s) {
        if (s == 0 || s == 1)
            return 1;
        else
            return s * fact(s - 1);
    }

    double C(int n, int m) {
        return fact(n) / fact(m) / fact(n - m);
    }

    double A(int n, int m) {
        return fact(n) / fact(n - m);
    }

    QString operatorSym;
    QString infix;

private:
    QVector<QString> postfix;
    QStack<QChar> symStack;
    QStack<double> figStack;
    QString stdInfix;
    double result;
};
