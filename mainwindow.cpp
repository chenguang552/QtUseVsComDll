#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pGetRes = new SecCtrlLib::ICACtrlCom();
    regsvr32Dll(QString::fromUtf8("npSecCtrl.dll"));
    bool ret = m_pGetRes->setControl(QString::fromUtf8("{17F8D3CF-857C-4D7C-9355-7A2398930B6A}"));
    if(!ret)
    {
        qDebug()<< "err: com dll is not find";
        if(m_pGetRes)
        {
            m_pGetRes->clear();
            m_pGetRes->destroyed();
            m_pGetRes = nullptr ;
        }
        delete ui;
    }
    if (this->isMinimized())
    {
        this->showNormal();
    }
    //设置窗口置顶
    ::SetWindowPos(HWND(this->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
    ::SetWindowPos(HWND(this->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
}

MainWindow::~MainWindow()
{
    if(m_pGetRes)
    {
        m_pGetRes->clear();
        m_pGetRes->destroyed();
        m_pGetRes = nullptr ;
    }
    delete ui;
}

void MainWindow::regsvr32Dll(QString dll)
{
    QString path = "E:\\liChenG\\审查_国办\\审查_国办\\SecCtrl\\Debug\\";
//    path = QCoreApplication::applicationDirPath();//获取程序运行路径
    QString cmdStr = "Regsvr32 " + path +"/"+ dll;
    QProcess p(nullptr);
    p.start("cmd", QStringList() << "/c" << cmdStr);
    p.waitForStarted();
    p.waitForFinished();
}
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    comboBoxItem = index ;
}

void MainWindow::on_pushButton_clicked()
{
    m_pGetRes->KS_SetProv("XACA", 0, "C:\\CONT?");
    int uRet = m_pGetRes->TestFunction(comboBoxItem);
    qDebug()<<"functionRet:"+QString::number(uRet)<<endl;
    if(!uRet)
    {
        QMessageBox::information(this,"information","success",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::warning(this,"information","err",QMessageBox::Ok | QMessageBox::Cancel,QMessageBox::Cancel);
    }
}
