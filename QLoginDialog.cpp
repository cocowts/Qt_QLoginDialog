#include "QLoginDialog.h"
#include <QPainter>
#include <QFont>
#include <QTime>
#include <QMessageBox>

QLoginDialog::QLoginDialog(QWidget* parent) : QDialog (parent, Qt::Drawer | Qt::Desktop)
{
    initControl();
    initSlots();

    qsrand(static_cast<uint>((QTime::currentTime().second() * 1000 + QTime::currentTime().msec())));

    m_colors = getColor();
    m_captcha = getCaptcha();

    m_timer.setParent(this);
    m_timer.start(100);
}

void QLoginDialog::initControl()
{
    m_userLbl.setParent(this);
    m_userLbl.setText("用户名：");
    m_userLbl.move(8, 9);
    m_userLbl.resize(57, 16);

    m_userEdit.setParent(this);
    m_userEdit.move(73, 7);
    m_userEdit.resize(148, 20);
    m_userEdit.setMaxLength(12);

    m_passwordLbl.setParent(this);
    m_passwordLbl.setText("密 码：");
    m_passwordLbl.move(8, 39);
    m_passwordLbl.resize(57, 16);

    m_passwordEdit.setParent(this);
    m_passwordEdit.move(73, 37);
    m_passwordEdit.resize(148, 20);
    m_passwordEdit.setEchoMode(QLineEdit::Password);
    m_passwordEdit.setMaxLength(8);

    m_captchaLbl.setParent(this);
    m_captchaLbl.setText("验证码：");
    m_captchaLbl.move(8, 69);
    m_captchaLbl.resize(57, 16);

    m_captchaEdit.setParent(this);
    m_captchaEdit.move(73, 67);
    m_captchaEdit.resize(57, 20);
    m_captchaEdit.setMaxLength(4);

    m_cancelBtn.setParent(this);
    m_cancelBtn.setText("取消");
    m_cancelBtn.move(8, 113);
    m_cancelBtn.resize(80, 22);

    m_loginBtn.setParent(this);
    m_loginBtn.setText("登陆");
    m_loginBtn.move(141, 113);
    m_loginBtn.resize(80, 22);

    setFixedSize(231, 145);
    setWindowTitle("登陆");
}

void QLoginDialog::initSlots()
{
    connect(&m_cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelBtnClicked()));
    connect(&m_loginBtn, SIGNAL(clicked()), this, SLOT(onLoginBtnClicked()));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(Timer_TimeOut()));
}

QString QLoginDialog::getUser()
{
    return m_user;
}

QString QLoginDialog::getPassword()
{
    return m_password;
}

QString QLoginDialog::getCaptcha()
{
    QString ret = "";

    for(int i=0; i<4; i++)
    {
        int c = (qrand() % 2) ? 'a' : 'A';
        ret += static_cast<QChar>(c + qrand() % 26);
    }

    return ret;
}

Qt::GlobalColor* QLoginDialog::getColor()
{
    static Qt::GlobalColor color[4];

    for(int i=0; i<4; i++)
    {
        color[i] = static_cast<Qt::GlobalColor>((2 + qrand() % 16));
    }

    return color;
}

//------------------------------------
void QLoginDialog::onCancelBtnClicked()
{
    done(QDialog::Rejected);
}

void QLoginDialog::onLoginBtnClicked()
{
    if( m_captcha.toLower() == m_captchaEdit.text().toLower() )
    {
        m_user = m_userEdit.text().trimmed();
        m_password = m_passwordEdit.text();

        if( m_user != "" && m_password != "")
        {
            done(QDialog::Accepted);
        }
        else
        {
            QMessageBox(QMessageBox::Critical, "错误", "用户名或密码输入有误", QMessageBox::Ok, this, Qt::Drawer).exec();
        }
    }
    else
    {
        QMessageBox(QMessageBox::Critical, "错误", "验证码输入有误", QMessageBox::Ok, this, Qt::Drawer).exec();

        qsrand(static_cast<uint>((QTime::currentTime().second() * 1000 + QTime::currentTime().msec())));

        m_captcha = getCaptcha();
    }
}

void QLoginDialog::Timer_TimeOut()
{
    m_colors = getColor();

    update();
}

//---------------------------------------
void QLoginDialog::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setFont(QFont("consolas", 12));
    painter.fillRect(151, 67, 70, 20, Qt::white);

    for(int i=0; i<150; i++)
    {
        painter.setPen(m_colors[i % 4]);
        painter.drawPoint(151 + qrand() % 70, 67 + qrand() % 20);
    }

    for(int i=0; i<4; i++)
    {
        painter.setPen(m_colors[i]);
        painter.drawText(151 + i*17, 67, 17, 20, Qt::AlignCenter, m_captcha.at(i));
    }
}
