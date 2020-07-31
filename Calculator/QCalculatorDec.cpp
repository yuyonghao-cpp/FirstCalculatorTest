#include "QCalculatorDec.h"

QCalculatorDec::QCalculatorDec()
{
    m_exp = "";
    m_result = "";
}

QCalculatorDec::~QCalculatorDec()
{

}

bool QCalculatorDec::isDigitOrDot(QChar c)
{
    return ((('0' <= c) && (c <= '9')) || (c == '.'));    //判断是否为0-9或者小数点
}

bool QCalculatorDec::isSymbol(QChar c)
{
    return isOperator(c) || (c == '(') || (c == ')');   //判断是否为操作符，是否为( )；
}

bool QCalculatorDec::isSign(QChar c)
{
    return (c == '+') || (c == '-');    //判断是否为 + - 符号
}

bool QCalculatorDec::isNumber(QString s)
{
    bool ret = false;

    s.toDouble(&ret);   //将s转换为double，传唤成功ret为ture，转换失败ret为false

    return ret;
}

bool QCalculatorDec::isOperator(QString s)
{
    return (s == "+") || (s == "-") || (s == "*") || (s == "/");
}

bool QCalculatorDec::isRight(QString s)
{
    return (s == ")");
}

bool QCalculatorDec::isLeft(QString s)
{
    return (s == "(");
}

int QCalculatorDec::priority(QString s)
{
    int ret = 0;

    if((s == "+") || (s == "-"))
    {
        ret = 1;
    }
    if((s == "*") || (s == "/"))
    {
        ret = 2;
    }

    return ret;
}

bool QCalculatorDec::expression(const QString& exp)
{
    bool ret = false;
    QQueue<QString> spExp = split(exp);
    QQueue<QString> postExp;
    m_exp = exp;

    if( transform(spExp, postExp))
    {
        m_result = calculator(postExp);

        ret = (m_result != "Error");
    }
    else
    {
        m_result = "Error";
    }


    return ret;
}
//QString QCalculatorDec::expression();
QString QCalculatorDec::result()
{
    return m_result;
}

//分离算法
QQueue<QString> QCalculatorDec::split(const QString& exp)
{
    QQueue<QString> ret;
    QString num = "";   //用于保存数字，小数点，以及正负号
    QString pre = "";   //用于保存前一个字符

    for(int i=0; i<exp.length(); i++)
    {
        if( isDigitOrDot(exp[i]) )
        {
            num += exp[i];  //当exp[i]为数字或者小数点时，就把字符组合
            pre = exp[i];   //保存前一个字符
        }
        else if( isSymbol(exp[i]))
        {
            if( !num.isEmpty())
            {
                ret.enqueue(num);

                num.clear();
            }

            if( isSign(exp[i]) && ((pre == "") || (pre == "(") || isOperator(pre)) )
            {
                num += exp[i];
            }
            else
            {
                ret.enqueue(exp[i]);
            }

            pre = exp[i];
        }
    }

    if( !num.isEmpty())
    {
        ret.enqueue(num);
    }

    return ret;
}

bool QCalculatorDec::match(QQueue<QString>& exp)
{
    bool ret = true;
    int len = exp.length();
    QStack<QString> stack;

    for(int i=0; i<len; i++)
    {
        if( isLeft(exp[i]) )
        {
            stack.push(exp[i]);
        }
        else if( isRight(exp[i]) )
        {
            if( !stack.isEmpty() && isLeft(stack.top()) )
            {
                stack.pop();
            }
            else
            {
                ret = false;
                break;
            }
        }

    }

    return ret;
}

bool QCalculatorDec::transform(QQueue<QString>& exp, QQueue<QString>& output)
{
    bool ret = match(exp);
    QStack<QString> stack;

    output.clear();

    while(ret && !exp.isEmpty())
    {
        QString e = exp.dequeue();

        if(isNumber(e))
        {
            output.enqueue(e);
        }
        else if(isOperator(e))
        {
            while( !stack.isEmpty() && (priority(e) <= priority(stack.top())))
            {
                output.enqueue(stack.pop());
            }

            stack.push(e);
        }
        else if( isLeft(e))
        {
            stack.push(e);
        }
        else if(isRight(e))
        {
            while( !stack.isEmpty() && !isLeft(stack.top()) )
            {
                output.enqueue(stack.pop());
            }

            if( !stack.isEmpty() )
            {
                stack.pop();
            }
        }
        else
        {
            ret = false;
        }
    }

    while( !stack.isEmpty() )
    {
        output.enqueue(stack.pop());
    }

    if( !ret )
    {
        output.clear();
    }

    return ret;
}

QString QCalculatorDec::calculator(QString l, QString op, QString r)
{
    QString ret = "Error";

    if( isNumber(l) && isNumber(r) )
    {
        double lp = l.toDouble();
        double rp = r.toDouble();

        if( op == "+")
        {
            ret.sprintf("%f", lp + rp);
        }
        else if(op == "-")
        {
            ret.sprintf("%f", lp - rp);
        }
        else if(op == "*")
        {
            ret.sprintf("%f", lp * rp);
        }
        else if(op == "/")
        {
            const double p = 0.0000000000001;
            if( ( -p < rp ) && ( rp < p ) )
            {
                ret = "Error";
            }
            else
            {
                ret.sprintf("%f", lp / rp);
            }
        }
        else
        {
            ret = "Error";
        }
    }

    return ret;
}

QString QCalculatorDec::calculator(QQueue<QString>& exp)
{
    QString ret = "Error";
    QStack<QString> stack;

    while( !exp.isEmpty() )
    {
        QString e = exp.dequeue();

        if( isNumber(e) )
        {
            stack.push(e);
        }
        else if( isOperator(e) )
        {
            QString rp = !stack.isEmpty() ? stack.pop() : "";
            QString lp = !stack.isEmpty() ? stack.pop() : "";
            QString result = calculator(lp, e, rp);

            if( result != "Error" )
            {
                stack.push(result);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }

    if( exp.isEmpty() && (stack.size() == 1) && isNumber(stack.top()) )
    {
        ret = stack.pop();
    }

    return ret;
}
