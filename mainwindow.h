#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "secctrllib.h"
#include <QDebug>
#include <objbase.h>
#include <iostream>
#include <QTreeView>
#include <QMessageBox>
#include <QProcess>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void regsvr32Dll(QString uuid);
private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();


private:
    Ui::MainWindow *ui;
    SecCtrlLib::ICACtrlCom *m_pGetRes;
    int comboBoxItem = 0;
};

#endif // MAINWINDOW_H
