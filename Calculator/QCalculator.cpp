#include "QCalculator.h"

QCalculator::QCalculator()
{
}

bool QCalculator::construct()
{
    m_ui = QCalculatorUI::NewInstance();    //��������ui������󣬵��ù��캯��NewInstance

    if( m_ui != NULL )
    {
        m_ui->setCalculator(&m_cal);
    }

    return (m_ui != NULL);      //�ж�ui������û�й���ɹ�
}

QCalculator* QCalculator::NewInstance()
{
    QCalculator* ret = new QCalculator();

    //����ret�ڶѿռ�����ռ�ɹ�����construct�ɹ��������������
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
