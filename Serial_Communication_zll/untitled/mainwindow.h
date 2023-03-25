#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>     // 提供系统中存在的串口信息
#include <QString>
#include <QTimer>

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
    void SerialPortInit();// 串口初始化
    void SerialGet();// 获取计算机中的串口
    void SerialParameterConfiguration();// 串口参数设置
    void PermissionSetting();// 初始控件权限设置
    void CheckSerial(QString str);// 确保其他串口都已经关闭
    void PermissionUpdate(bool select);
    void ConnectFun();// connect 函数
    QByteArray QString2Hex(QString hexStr);// QString 类型转 QByteArray 类型（即 hex 类型）
    char ConvertHexChar(char c);
    void DataAnalysis(QString hexData);// 指令解析
    QString QStringList2QstringHex(QStringList strList);// 将 QStringList 转化为 hex 字符
    void WrongData2Text(QStringList strList);// 将错误指令写到 text 中
    void RightData2Table(QStringList strList);// 将正确指令写到 table 中

private slots:
    void on_PortBox_activated(const QString &arg1);// 串口切换

private:
    Ui::MainWindow *ui;

    // 串口变量
    QSerialPort *serial;// 定义全局的串口对象
    // 参数配置
    QStringList baudList;//波特率
    QStringList parityList;//校验位
    QStringList dataBitsList;//数据位
    QStringList stopBitsList;//停止位
    QStringList flowControlList;//控制流
    QStringList portName;// 记录串口名
    QStringList rawData;// 记录已经接收到的数据
};
#endif // MAINWINDOW_H
