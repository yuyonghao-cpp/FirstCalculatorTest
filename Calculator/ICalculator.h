//�ӿڣ�interface
#ifndef _ICALCULATOR_H_
#define _ICALCULATOR_H_

#include <QString>

class ICalculator
{
public:
    virtual bool expression(const QString& exp) = 0;    //������������û�������������
    virtual QString result() = 0;   //�����õ�������
};

#endif // _ICALCULATOR_H_
