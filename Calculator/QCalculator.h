//��װ��
#ifndef _QCALCULATOR_H_
#define _QCALCULATOR_H_

#include "QCalculatorUI.h"
#include "QCalculatorDec.h"

//��Ҫ����ui���ͺ����߼�
class QCalculator
{
protected:
    QCalculatorUI* m_ui;    //QCalculatorUI�Ƕ��׹���
                            //�����Ա������ʹ�ö��׹���ģ�������Ҳ��Ҫʹ�ö��׹���
    QCalculatorDec m_cal;

    QCalculator();
    bool construct();
public:
    static QCalculator* NewInstance();
    void show();
    ~QCalculator();

};

#endif // _QCALCULATOR_H_
