#ifndef _QCALCULATORDEC_H_
#define _QCALCULATORDEC_H_

#include <QString>
#include <QStack>
#include <QQueue>

#include "ICalculator.h"

class QCalculatorDec : public ICalculator
{
protected:
    QString m_exp;
    QString m_result;

    bool isDigitOrDot(QChar c);
    bool isSymbol(QChar c);
    bool isSign(QChar c);
    bool isNumber(QString s);
    bool isOperator(QString s);
    bool isRight(QString s);
    bool isLeft(QString s);
    int priority(QString s);
    bool match(QQueue<QString>& exp);   //匹配算法
    QString calculator(QQueue<QString>& exp);
    QString calculator(QString lp, QString op, QString rp);
    bool transform(QQueue<QString>& exp, QQueue<QString>& output);                   //中缀转后缀算法
    QQueue<QString> split(const QString& exp);
public:
    QCalculatorDec();
    ~QCalculatorDec();
    bool expression(const QString& exp);
    QString expression();
    QString result();
};

#endif // QCALCULATORDEC_H
