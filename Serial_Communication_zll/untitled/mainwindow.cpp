#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SerialPortInit();// 串口初始化（参数配置）
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SerialPortInit()
{
    rawData.clear();// 清空 QStringList 对象中的内容
    serial = new QSerialPort;// 申请内存,并设置父对象
    SerialGet();// 获取计算机中有效的端口号，然后将端口号的名称给端口选择控件
    ui->OpenSerialButton->setText("打开串口");
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
    ui->SendEditBtn1->setDisabled(true);// 发送按钮初始不可按
    ui->DataSend->setReadOnly(true);// 发送窗口默认只读权限
    ui->DataReceived->setReadOnly(true);// 接收窗口默认只读权限
    ui->m_errorInstruction->setReadOnly(true);// 错误指令存储窗口默认只读模式
    ui->m_rightInstruction->setEditTriggers(QAbstractItemView::NoEditTriggers);// 表格默认只读模式
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

void MainWindow::PermissionUpdate(bool select)
{
    ui->BaudBox->setDisabled(select);
    ui->ParityBox->setDisabled(select);
    ui->BitBox->setDisabled(select);
    ui->StopBox->setDisabled(select);
    ui->ControlBox->setDisabled(select);
    ui->SendEditBtn1->setDisabled(!select);
    if (select) {
        ui->OpenSerialButton->setText("关闭串口");
    }
    else {
        ui->OpenSerialButton->setText("打开串口");
    }
}
// 所有控件的 connect 函数
void MainWindow::ConnectFun()
{
    connect(serial, &QSerialPort::readyRead, this, [&](){// 接收数据
        QByteArray data = serial->readAll();// 读取数据
        DataAnalysis(data.toHex(' '));// 解析收到的指令
        if(!data.isEmpty())// 接收到数据
        {
            QString str = ui->DataReceived->toPlainText();// 返回纯文本
            if (!str.isEmpty()) {
                str.append('\n');
            }
            ui->DataReceived->setReadOnly(false);
            ui->DataReceived->append(data.toHex(' '));// 将数据放入接收窗口
            ui->DataReceived->setReadOnly(true);
        }
    });
    connect(ui->SendEditBtn1, &QPushButton::clicked, this, [&](){// 发送数据
        QString EditText = ui->Edit1->toPlainText();       //获取发送框内容
        // 将发送数据转换为 16 进制数据
        QByteArray byte_data = QString2Hex(EditText);
        ui->DataSend->setReadOnly(false);
        ui->DataSend->append(byte_data.toHex(' '));    //将文本内容放在发送栏中
        ui->DataSend->setReadOnly(true);
        serial->write(byte_data);      // 串口发送数据
    });
    connect(ui->ClearButton, &QPushButton::clicked, this, [&](){// 清空发送窗口
        ui->DataSend->setReadOnly(false);
        ui->DataSend->setText("");
        ui->DataSend->setReadOnly(true);
    });
    connect(ui->ClearShowButton, &QPushButton::clicked, this, [&](){// 清空接收窗口、正确指令信息表格和错误指令窗口
        // 清空接收窗口
        ui->DataReceived->setReadOnly(false);
        ui->DataReceived->setText("");
        ui->DataReceived->setReadOnly(true);
        // 清空表格
        ui->m_rightInstruction->clearContents();
        ui->m_rightInstruction->setRowCount(0);
        ui->m_rightInstruction->setColumnCount(2);
        // 清空错误指令窗口
        ui->m_errorInstruction->setReadOnly(false);
        ui->m_errorInstruction->setPlainText("");
        ui->m_errorInstruction->setReadOnly(true);
    });
    connect(ui->OpenSerialButton, &QPushButton::clicked, this, [&](){// 串口开关
        QString str = ui->OpenSerialButton->text();
        //当前选择的串口名字
        serial->setPortName(ui->PortBox->currentText());
        if (QString::compare(str, "打开串口") == 0) {
            CheckSerial(ui->PortBox->currentText());
            serial->open(QIODevice::ReadWrite);
            PermissionUpdate(true);
        }
        else {
            serial->clear();
            serial->close();
            PermissionUpdate(false);
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
// 数据解析
void MainWindow::DataAnalysis(QString hexData)
{
    // 一条指令可能要分多次才可能收全，但是一次只会发一条指令的数据
    // 假设指令头、指令长度和指令尾三个字节只会有一个出错
    // 指令尾出错，此情况最为复杂

    rawData.append(hexData.split(' '));// 记录已经接收到的数据
    if (QString::compare(rawData[0], "fe") == 0) {// 指令头正确
        if (rawData.size() >= 2) {// 判断指令长度是否接收到
            bool ok;
            int dataLen = rawData[1].toUInt(&ok, 16);// 指令长度
            if (dataLen + 3 < rawData.size()) {// 长度字段必出错
                if (QString::compare(rawData.back(), "ff") == 0) {// 指令收集全了
                    qDebug() << "指令长度出错";
                    WrongData2Text(rawData);// 错误指令写到 text 中
                }
            }
            else if(dataLen + 3 == rawData.size()) {
                if (QString::compare(rawData.back(), "ff") == 0) {// 指令正确
                    qDebug() << "指令正确";
                    RightData2Table(rawData);// 正确指令写到 table 中
                }
                else {// 此时可能出现两种情况：1.指令内容出错；2.指令尾出错
                    // 让程序暂停一段时间，若一直没有收到新的数据，则认为指令尾出错
                    QTimer::singleShot(3000, this, [this]{// 暂停 3 秒，只会暂停 1 次
                        // 执行需要暂停的代码
                        qDebug() << "指令尾出错";
                        WrongData2Text(rawData);// 错误指令写到 text 中
                    });
                }
            }
            else {
                if (QString::compare(rawData.back(), "ff") == 0) {// 指令长度必出错
                    qDebug() << "指令长度出错";
                    WrongData2Text(rawData);// 错误指令写到 text 中
                }
            }
        }
    }
    else {// 指令头出错
        if (QString::compare(rawData.back(), "ff") == 0) {// 指令收集全了
            qDebug() << "指令头出错";
            WrongData2Text(rawData);// 错误指令写到 text 中
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
    QString beforeData = ui->m_errorInstruction->toPlainText();// 先读取之前的数据
    QString wrongData = QStringList2QstringHex(strList).append('\n');
    ui->m_errorInstruction->setReadOnly(false);
    ui->m_errorInstruction->setPlainText(beforeData.append(wrongData));
    ui->m_errorInstruction->setReadOnly(true);
    rawData.clear();// 清空 rawData
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
    int row = ui->m_rightInstruction->rowCount();
    ui->m_rightInstruction->insertRow(row);
    ui->m_rightInstruction->setItem(row, 0, new QTableWidgetItem(dataLen));
    QString lastdata;
    for (int i = 0; i < strList.size(); i++) {
        lastdata.append(strList[i]);
        lastdata.append(' ');
    }
    ui->m_rightInstruction->setItem(row, 1, new QTableWidgetItem(lastdata));// 写进 table
    rawData.clear();// 清空 rawData
}
