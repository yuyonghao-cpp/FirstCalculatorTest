//封装类
#ifndef _QCALCULATOR_H_
#define _QCALCULATOR_H_

#include "QCalculatorUI.h"
#include "QCalculatorDec.h"

//需要定义ui，和核心逻辑
class QCalculator
{
protected:
    QCalculatorUI* m_ui;    //QCalculatorUI是二阶构造
                            //如果成员变量有使用二阶构造的，整个类也需要使用二阶构造
    QCalculatorDec m_cal;

    QCalculator();
    bool construct();
public:
    static QCalculator* NewInstance();
    void show();
    ~QCalculator();

};

#endif // _QCALCULATOR_H_
