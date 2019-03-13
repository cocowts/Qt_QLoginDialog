#ifndef QLOGINDIALOG_H
#define QLOGINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include <QString>
#include <QTimer>

class QLoginDialog : public QDialog
{
    Q_OBJECT

private:
    QLabel m_userLbl;
    QLabel m_passwordLbl;
    QLabel m_captchaLbl;
    QLineEdit m_userEdit;
    QLineEdit m_passwordEdit;
    QLineEdit m_captchaEdit;
    QPushButton m_cancelBtn;
    QPushButton m_loginBtn;

    QString m_user;
    QString m_password;

    QTimer m_timer;

    QString m_captcha;
    Qt::GlobalColor* m_colors;

    void initControl();
    void initSlots();

    QString getCaptcha();
    Qt::GlobalColor* getColor();

protected:
    void paintEvent(QPaintEvent*);

private slots:
    void onCancelBtnClicked();
    void onLoginBtnClicked();
    void Timer_TimeOut();

public:
    QLoginDialog(QWidget* parent);
    QString getUser();
    QString getPassword();
};

#endif // QLOGINDIALOG_H
