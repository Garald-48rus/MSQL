#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "login.h"
#include "ui_login.h"

#include "addobject.h"
#include "ui_addobject.h"

#include "izmenenie.h"
#include "ui_izmenenie.h"

#include <QSqlTableModel>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public:
    login* logwin;
    addobject* maadobj;
    izmenenie* mizmenenie;


    int globid{};
    bool fl;

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void obr_ref_tab();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void CustomMenuReg(QPoint);

    void del_zap();

    void izm_zap();



signals:
   void sendID(int);

private:
    Ui::MainWindow *ui;
    QSqlQueryModel* model;
   // QSqlTableModel* model;
};
#endif // MAINWINDOW_H
