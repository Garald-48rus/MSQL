#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QtSql>
#include <QMessageBox>


namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

public:
    QMessageBox* mss;

private slots:
    void on_pushButton_clicked();

private:
    QSqlDatabase db;

private:
    Ui::login *ui;


};

#endif // LOGIN_H
