#ifndef _QCALCULATORUI_H_
#define _QCALCULATORUI_H_

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include "ICalculator.h"

class QCalculatorUI : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* m_edit;
    QPushButton* m_button[20];
    ICalculator* m_cal;

    QCalculatorUI();
    bool construct();   //二阶构造
private slots:
    void onButtonClicked();
public:

    static QCalculatorUI* NewInstance();// 入口函数，必须为静态的。
    void show();

    void setCalculator(ICalculator* cal);
    ICalculator* getCalculator();
    ~QCalculatorUI();
    
};

#endif // QCALCULATORUI_H
