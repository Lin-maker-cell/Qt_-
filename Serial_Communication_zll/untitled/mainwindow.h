#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// 引入串口通信的两个头文件
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include <QDateTime>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 串口功能
    void SerialPortInit();                      // 串口初始化（参数配置）
    void SerialGet();
    void PermissionSetting();
    void ConnectFun();
    void RefreshSerialPort(int index);          // 刷新串口
    QByteArray QString2Hex(QString hexStr);
    char ConvertHexChar(char c);
    void DataAnalysis(QString hexData);
    void WrongData2Text(QString hexData);
    void RightData2Table(QString hexData);
    void SerialParameterConfiguration();



private slots:
    void on_PortBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;

    // 串口变量
    QSerialPort     *serial;                            // 定义全局的串口对象（第三步）
    // 参数配置
    QStringList     baudList;                           //波特率
    QStringList     parityList;                         //校验位
    QStringList     dataBitsList;                       //数据位
    QStringList     stopBitsList;                       //停止位
    QStringList     flowControlList;                    //控制流
    QStringList     portName;
    QByteArray      dataReceived;
};
#endif // MAINWINDOW_H
