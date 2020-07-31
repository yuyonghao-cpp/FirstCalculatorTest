//接口，interface
#ifndef _ICALCULATOR_H_
#define _ICALCULATOR_H_

#include <QString>

class ICalculator
{
public:
    virtual bool expression(const QString& exp) = 0;    //用来代表接收用户输入四则运算
    virtual QString result() = 0;   //用来得到计算结果
};

#endif // _ICALCULATOR_H_
