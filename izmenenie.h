#ifndef IZMENENIE_H
#define IZMENENIE_H

#include <QWidget>
#include <QSqlQuery>



namespace Ui {
class izmenenie;
}

class izmenenie : public QWidget
{
    Q_OBJECT

public:
    explicit izmenenie(QWidget *parent = nullptr);
    ~izmenenie();

private:
    Ui::izmenenie *ui;

public slots:

    void obrSendID(int);

private slots:
    void on_pushButton_clicked();

signals:

    void ref();
};

#endif // IZMENENIE_H
