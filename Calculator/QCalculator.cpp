#include "QCalculator.h"

QCalculator::QCalculator()
{
}

bool QCalculator::construct()
{
    m_ui = QCalculatorUI::NewInstance();    //首先生成ui界面对象，调用构造函数NewInstance

    if( m_ui != NULL )
    {
        m_ui->setCalculator(&m_cal);
    }

    return (m_ui != NULL);      //判断ui对象有没有构造成功
}

QCalculator* QCalculator::NewInstance()
{
    QCalculator* ret = new QCalculator();

    //必须ret在堆空间申请空间成功，且construct成功，对象才能生成
    if( (ret == NULL) || !ret->construct() )
    {
        delete ret;

        ret = NULL;
    }

    return ret;
}

void QCalculator::show()
{
    m_ui->show();
}

QCalculator::~QCalculator()
{
    delete m_ui;
}
