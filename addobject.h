#ifndef ADDOBJECT_H
#define ADDOBJECT_H

#include <QWidget>

#include <QMessageBox>
#include <QSqlQuery>

#include <QFileDialog>

namespace Ui {
class addobject;
}

class addobject : public QWidget
{
    Q_OBJECT

public:
    explicit addobject(QWidget *parent = nullptr);
    ~addobject();

    QString imgadr{};
    int postcombo{};

private slots:
    void on_pushButton_clicked();

    void on_toolButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

signals:
    void refresh_table();

private:
    Ui::addobject *ui;
};

#endif // ADDOBJECT_H
