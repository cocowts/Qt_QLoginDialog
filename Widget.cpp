#include "Widget.h"
#include "QLoginDialog.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_button.setParent(this);
    m_button.setText("button");
    m_button.move(10, 10);

    connect(&m_button, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

void Widget::onButtonClicked()
{
    QLoginDialog dlg(this);

    if( dlg.exec() == QDialog::Accepted )
    {
        qDebug() << "用户名： " << dlg.getUser();
        qDebug() << "密码 " << dlg.getPassword();
    }
}

Widget::~Widget()
{

}
