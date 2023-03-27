#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mCommandHead = "fe";
    mCommandTail = "ff";
    SerialPortInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}
// 初始化
void MainWindow::SerialPortInit()
{
    serial = new QSerialPort;// 申请内存,并设置父对象
    ui->SerialSwitchButton->setText("打开串口");
    SerialGet();// 获取计算机中有效的端口号，然后将端口号的名称给端口选择控件
    SerialParameterConfiguration();// 参数配置
    PermissionSetting();// 权限设置
    ConnectFun();// 信号
}
// 获取串口
void MainWindow::SerialGet()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        serial->setPort(info);// 在对象中设置串口
        ui->PortBox->addItem(info.portName());// 添加计算机中的端口
        portName.append(info.portName());// 将可用串口放到 portName list 中
        if (serial->isOpen()) {// 如果串口已经打开，则关闭串口
            serial->clear();
            serial->close();
        }
    }
}
// 串口参数配置
void MainWindow::SerialParameterConfiguration()
{
    // 波特率，波特率默认选择 19200
    ui->BaudBox->addItem("19200");
    serial->setBaudRate(QSerialPort::Baud19200);
    // 校验，校验默认选择 无
    ui->ParityBox->addItem("无");
    serial->setParity(QSerialPort::NoParity);
    // 数据位，数据位默认选择 8 位
    ui->BitBox->addItem("8");
    serial->setDataBits(QSerialPort::Data8);
    // 停止位，停止位默认选择 1 位
    ui->StopBox->addItem("1");
    serial->setStopBits(QSerialPort::OneStop);
    // 控制流，默认选择 无
    ui->ControlBox->addItem("无");
    serial->setFlowControl(QSerialPort::NoFlowControl);
}
// 初始权限设置
void MainWindow::PermissionSetting()
{
    ui->SendButton->setDisabled(true);// 发送按钮初始不可按
    ui->SendWindow->setReadOnly(true);// 发送窗口默认只读权限
    ui->ReceivingWindow->setReadOnly(true);// 接收窗口默认只读权限
    ui->WrongDataInfo->setReadOnly(true);// 错误指令存储窗口默认只读模式
    ui->RightDataInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格默认只读模式
}
// 确保其他串口都已经关闭
void MainWindow::CheckSerial(QString str)
{
    for (int i = 0; i < portName.size(); i++) {
        if (portName[i] != str) {
            serial->setPortName(portName[i]);
            if (serial->isOpen()) {
                serial->clear();
                serial->close();
            }
        }
    }
}
// 权限更新
void MainWindow::PermissionUpdate(bool select)
{
    ui->BaudBox->setDisabled(select);
    ui->ParityBox->setDisabled(select);
    ui->BitBox->setDisabled(select);
    ui->StopBox->setDisabled(select);
    ui->ControlBox->setDisabled(select);
    ui->SendButton->setDisabled(!select);
    if (select) {
        ui->SerialSwitchButton->setText("关闭串口");
    }
    else {
        ui->SerialSwitchButton->setText("打开串口");
    }
}
// 所有控件的 connect 函数
void MainWindow::ConnectFun()
{
    connect(serial, &QSerialPort::readyRead, this, [&](){// 接收数据
        QByteArray data = serial->readAll();// 读取数据
        if(!data.isEmpty())// 接收到数据
        {
            QString str = ui->ReceivingWindow->toPlainText();// 返回纯文本
            if (!str.isEmpty()) {
                str.append('\n');
            }
            ui->ReceivingWindow->setReadOnly(false);
            ui->ReceivingWindow->append(data.toHex(' '));// 将数据放入接收窗口
            ui->ReceivingWindow->setReadOnly(true);
        }
        mByteArray.append(data.toHex(' ')).append(' ');
        while (true) {
            int headIndex = mByteArray.indexOf(mCommandHead);// 帧头
            if (headIndex >= 0) {// 存在帧头
                mByteArray.remove(0, headIndex);// 去除帧头之前的无效数据
                int tailIndex = mByteArray.indexOf(mCommandTail);// 帧尾
                if (tailIndex > 0) {// 存在帧尾
                    int lastHeadIndex = mByteArray.left(tailIndex).lastIndexOf(mCommandHead);// 最后一个帧头的索引位置
                    DataAnalysis(mByteArray.mid(lastHeadIndex, tailIndex - lastHeadIndex + 2));
                    mByteArray.remove(0, tailIndex + 2);
                }
                else {// 不存在帧尾
                    break;
                }
            }
            else {// 不存在帧头
                break;
            }
        }
    });
    connect(ui->SendButton, &QPushButton::clicked, this, [&](){// 发送数据
        QString EditText = ui->EditWindow->toPlainText();       //获取发送框内容
        QByteArray byte_data = QString2Hex(EditText);
        ui->SendWindow->setReadOnly(false);
        ui->SendWindow->append(byte_data.toHex(' '));//将文本内容放在发送栏中
        ui->SendWindow->setReadOnly(true);
        serial->write(byte_data);// 串口发送数据
    });
    connect(ui->ClearSendButton, &QPushButton::clicked, this, [&](){// 清空发送窗口
        ui->SendWindow->setReadOnly(false);
        ui->SendWindow->setText("");
        ui->SendWindow->setReadOnly(true);
    });
    connect(ui->ClearReceiveButton, &QPushButton::clicked, this, [&](){// 清空接收窗口、正确指令信息表格和错误指令窗口
        // 清空接收窗口
        ui->ReceivingWindow->setReadOnly(false);
        ui->ReceivingWindow->setText("");
        ui->ReceivingWindow->setReadOnly(true);
        // 清空表格
        ui->RightDataInfo->clearContents();
        ui->RightDataInfo->setRowCount(0);
        ui->RightDataInfo->setColumnCount(2);
        // 清空错误指令窗口
        ui->WrongDataInfo->setReadOnly(false);
        ui->WrongDataInfo->setPlainText("");
        ui->WrongDataInfo->setReadOnly(true);
    });
    connect(ui->SerialSwitchButton, &QPushButton::clicked, this, [&](){// 串口开关
        QString str = ui->SerialSwitchButton->text();
        if (QString::compare(str, "打开串口") == 0) {
            CheckSerial(ui->PortBox->currentText());
            serial->setPortName(ui->PortBox->currentText());
            serial->open(QIODevice::ReadWrite);
            if (serial->isOpen()) {// 串口打开成功
                QMessageBox::information(this, "提示", "串口打开成功");
                PermissionUpdate(true);
            }
            else {// 串口打开失败
                QMessageBox::information(this, "提示", "串口打开失败");
            }
        }
        else {// 串口关闭成功
            serial->setPortName(ui->PortBox->currentText());
            serial->clear();
            serial->close();
            if (!serial->isOpen()) {
                // MessageBox 提示
                QMessageBox::information(this, "提示", "串口关闭成功");
                PermissionUpdate(false);
            }
            else {// 串口关闭失败
                QMessageBox::information(this, "提示", "串口关闭失败");
            }
        }
    });
}
// 串口切换
void MainWindow::on_PortBox_activated(const QString &arg1)
{
    serial->setPortName(arg1);
    if (serial->isOpen()) {
        PermissionUpdate(false);
    }
    else {
        PermissionUpdate(true);
    }
}
// 字符串转 Hex(QByteArray) 类型
QByteArray MainWindow::QString2Hex(QString hexStr)
{
    QByteArray senddata;
    int hexdata, lowhexdata;
    int hexdatalen = 0;
    int len = hexStr.length();
    senddata.resize(len/2);
    char lstr, hstr;
    for(int i = 0; i < len; )
    {
        //将第一个不为' '的字符赋给hstr;
        hstr = hexStr[i].toLatin1();
        if(hstr == ' ')
        {
            i++;
            continue;
        }
        i++;
        //当i >= len时，跳出循环
        if(i >= len)
            break;
        //当i < len时，将下一个字符赋值给lstr;
        lstr = hexStr[i].toLatin1();
        //将hstr和lstr转换为0-15的对应数值
        hexdata = ConvertHexChar(hstr);
        lowhexdata = ConvertHexChar(lstr);
        //
        if((hexdata == 16) || (lowhexdata == 16))
            break;
        else
            hexdata = hexdata * 16 + lowhexdata;
        i++;
        senddata[hexdatalen] = (char)hexdata;
        hexdatalen++;
    }
    senddata.resize(hexdatalen);
    return senddata;
}
// 将单个字符串转换为 hex
char MainWindow::ConvertHexChar(char c)
{
    if((c >= '0') && (c <= '9'))
        return c - 0x30;
    else if((c >= 'A') && (c <= 'F'))
        return c - 'A' + 10;//'A' = 65;
    else if((c >= 'a') && (c <= 'f'))
        return c - 'a' + 10;
    else
        return -1;
}
// 解析一条完整的指令
void MainWindow::DataAnalysis(QByteArray hexData)
{
    QString str = hexData;
    QStringList rawData = str.split(' ');
    if (rawData.size() <= 3) {
        WrongData2Text(rawData);
    }
    else {
        bool ok;
        int dataLen = rawData[1].toUInt(&ok, 16);// 指令长度
        if (dataLen + 3 == rawData.size()) {
            RightData2Table(rawData);
        }
        else {
            WrongData2Text(rawData);
        }
    }
}
// 将 QStringList 转化为 hex 字符
QString MainWindow::QStringList2QstringHex(QStringList strList)
{
    QString str;
    for (int i = 0; i < strList.size(); i++) {
        str.append(strList[i]);
        str.append(' ');
    }
    return str;
}
// 出错指令写到 text 中
void MainWindow::WrongData2Text(QStringList strList)
{
    QString beforeData = ui->WrongDataInfo->toPlainText();// 先读取之前的数据
    QString wrongData = QStringList2QstringHex(strList).append('\n');
    ui->WrongDataInfo->setReadOnly(false);
    ui->WrongDataInfo->setPlainText(beforeData.append(wrongData));
    ui->WrongDataInfo->setReadOnly(true);
}
// 正确指令信息写到 table 中
void MainWindow::RightData2Table(QStringList strList)
{
    bool ok;
    QString dataLen = QString::number(strList[1].toUInt(&ok, 16));// 指令长度
    strList.removeFirst();
    strList.removeFirst();
    strList.removeLast();// 指令内容
    // 向表格中增加新的行
    int row = ui->RightDataInfo->rowCount();
    ui->RightDataInfo->insertRow(row);
    ui->RightDataInfo->setItem(row, 0, new QTableWidgetItem(dataLen));
    QString lastdata;
    for (int i = 0; i < strList.size(); i++) {
        lastdata.append(strList[i]);
        lastdata.append(' ');
    }
    ui->RightDataInfo->setItem(row, 1, new QTableWidgetItem(lastdata));// 写进 table
}
