#include "QCalculatorUI.h"
#include <QDebug>
#include <QString>

QCalculatorUI::QCalculatorUI() : QWidget(NULL, Qt::WindowCloseButtonHint)
{
    m_cal = NULL;
//    QLineEdit* le = new QLineEdit(this);   //生成QLineEdit对象，其父组件为QWidget
}

bool QCalculatorUI::construct()
{
    bool ret = true;
    const char* btnText[20] =
    {
        "7","8","9","+","(",
        "4","5","6","-",")",
        "1","2","3","*","<-",
        "0",".","=","/","C",
    };

    m_edit = new QLineEdit(this);

    if(m_edit != NULL)
    {
        m_edit->move(10, 10);
        m_edit->resize(240, 30);
        m_edit->setAlignment(Qt::AlignRight);   //AlignRight 将文本框内容放置于右边
        //m_edit->setAlignment(Qt::AlignLeft);   //AlignLeft 将文本框内容放置于左边
        m_edit->setReadOnly(true);
    }
    else
    {
        ret = false;
    }

    for(int i=0; i<4 && ret; i++)
    {
        for(int j=0; j<5 && ret; j++)
        {
            m_button[i*5 + j] = new QPushButton(this);   //每一行生成五个按钮

            if(m_button[i*5 + j] != NULL)
            {
                m_button[i*5 + j]->resize(40, 40);        //设置按钮的大小
                m_button[i*5 + j]->move(10 +(10 + 40)*j, 50 + (10 + 40)*i);          //设置按钮的位置
                m_button[i*5 + j]->setText(btnText[i*5 + j]);
                connect(m_button[i*5 + j], SIGNAL(clicked()), this, SLOT(onButtonClicked()));

            }
            else
            {
                ret = false;
            }
        }
    }

    return ret;
}

QCalculatorUI* QCalculatorUI::NewInstance()// 入口函数，必须为静态的。
{
    QCalculatorUI* ret = new QCalculatorUI();

    if((ret == NULL) || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void QCalculatorUI::show()
{
    QWidget::show();
    setFixedSize(width(),height());    //setFixedSize设置窗口大小后不可改变
}

void QCalculatorUI::onButtonClicked()
{
    QPushButton* btn = dynamic_cast<QPushButton*>(sender());

    if( btn != NULL)
    {
        QString clickText = btn->text();    //text()获取字符串内容

        if(clickText == "<-")
        {
            QString text = m_edit->text();
            if(text.length() > 0)
            {
                text.remove(text.length() - 1, 1);
                m_edit->setText(text);
            }
        }
        else if(clickText == "C")
        {
            m_edit->setText("");
        }
        else if(clickText == "=")
        {
            if(m_cal != NULL)
            {
                m_cal->expression(m_edit->text());
                m_edit->setText(m_cal->result());
            }
        }
        else
        {
            m_edit->setText(m_edit->text() + clickText);
        }
    }
}

void QCalculatorUI::setCalculator(ICalculator* cal)
{
    m_cal = cal;
}

ICalculator* QCalculatorUI::getCalculator()
{
    return m_cal;
}

QCalculatorUI::~QCalculatorUI()
{

}
