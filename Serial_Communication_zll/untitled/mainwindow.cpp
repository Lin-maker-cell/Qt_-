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
    dataReceived.clear();// 清空字节数组
    serial = new QSerialPort;//申请内存,并设置父对象
    SerialGet();// 获取计算机中有效的端口号，然后将端口号的名称给端口选择控件
    SerialParameterConfiguration();// 参数配置
    PermissionSetting();//权限设置
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
    // 表格默认只读模式
}
// 所有控件的 connect 函数
void MainWindow::ConnectFun()
{
    connect(serial, &QSerialPort::readyRead, this, [&](){   // 接收数据
        QByteArray data = serial->readAll();           // 读取数据

        DataAnalysis(data.toHex(' ')); // 解析收到的指令
        if(!data.isEmpty()) // 接收到数据
        {
            QString str = ui->DataReceived->toPlainText();  // 返回纯文本
            if (!str.isEmpty()) {
                str.append('\n');
            }
            ui->DataReceived->setReadOnly(false);
            ui->DataReceived->append(data.toHex(' ')); // 将数据放入控件中
            ui->DataReceived->setReadOnly(true);
        }
    });
    connect(ui->SendEditBtn1, &QPushButton::clicked, this, [&](){
        QString EditText = ui->Edit1->toPlainText();       //获取发送框内容
        // 将发送数据转换为 16 进制数据
        QByteArray byte_data = QString2Hex(EditText);
        ui->DataSend->setReadOnly(false);
        ui->DataSend->append(byte_data.toHex(' '));    //将文本内容放在发送栏中
        ui->DataSend->setReadOnly(true);
        serial->write(byte_data);      // 串口发送数据
    });    // 发送数据
    connect(ui->ClearButton, &QPushButton::clicked, this, [&](){    // 清空发送窗口
        ui->DataSend->setReadOnly(false);
        ui->DataSend->setText("");
        ui->DataSend->setReadOnly(true);
    });
    connect(ui->ClearShowButton, &QPushButton::clicked, this, [&](){    // 清空接收窗口、正确指令信息表格和错误指令窗口
        // 清空接收窗口
        ui->DataReceived->setReadOnly(false);
        ui->DataReceived->setText("");
        ui->DataReceived->setReadOnly(true);
        // 清空表格
        // 清空错误指令窗口
        ui->m_errorInstruction->setReadOnly(false);
        ui->m_errorInstruction->setPlainText("");
        ui->m_errorInstruction->setReadOnly(true);
    });
    connect(ui->OpenSerialButton, &QPushButton::clicked, this, [&](){// 串口开关
        if(serial->isOpen()) {// 如果串口打开了，先给他关闭
            serial->clear();
            serial->close();
            qDebug() << serial->portName() << " 关闭成功";
            // 关闭状态，按钮显示“打开串口”
            ui->OpenSerialButton->setText("打开串口");

            // 关闭状态，允许用户操作
            ui->BaudBox->setDisabled(false);
            ui->ParityBox->setDisabled(false);
            ui->BitBox->setDisabled(false);
            ui->StopBox->setDisabled(false);
            ui->ControlBox->setDisabled(false);
            ui->SendEditBtn1->setDisabled(true);
            // 清空数据
            ui->DataReceived->setReadOnly(false);
            ui->DataSend->setReadOnly(false);

            ui->DataReceived->clear();
            ui->DataSend->clear();

            ui->DataReceived->setReadOnly(true);
            ui->DataSend->setReadOnly(true);
        }
        else    // 如果串口关闭了，先给他打开
        {
            //当前选择的串口名字
            serial->setPortName(ui->PortBox->currentText());
            //用ReadWrite 的模式尝试打开串口，无法收发数据时，发出警告

            for (int i = 0; i < portName.size(); i++) {
                if (QString::compare(ui->PortBox->currentText(),portName[i])) {
                    serial->setPortName(portName[i]);
                    if (serial->isOpen()) {
                        qDebug() << "有其他串口已经打开，先关闭其他串口";
                        serial->clear();
                        serial->close();
                    }
                }
            }

            //当前选择的串口名字
            serial->setPortName(ui->PortBox->currentText());
            //用ReadWrite 的模式尝试打开串口，无法收发数据时，发出警告

            if(!serial->open(QIODevice::ReadWrite))
            {
                QMessageBox::warning(this,tr("提示"),tr("串口打开失败!"),QMessageBox::Ok);
                return;
            }
            qDebug() << serial->portName() << " 打开成功";
            // 打开状态，按钮显示“关闭串口”
            ui->OpenSerialButton->setText("关闭串口");

            // 打开状态，禁止用户操作
            ui->BaudBox->setDisabled(true);
            ui->ParityBox->setDisabled(true);
            ui->BitBox->setDisabled(true);
            ui->StopBox->setDisabled(true);
            ui->ControlBox->setDisabled(true);
            ui->SendEditBtn1->setDisabled(false);
        }
    });
}
// ComboBox PortBox 的槽函数：激活串口
void MainWindow::on_PortBox_activated(const QString &arg1)
{
    qDebug() << "启动了activated" << arg1;
    serial->setPortName(arg1);
    if (serial->isOpen()) {
        // 打开状态，按钮显示“关闭串口”
        ui->OpenSerialButton->setText("关闭串口");
        // 打开状态，禁止用户操作
        ui->BaudBox->setDisabled(true);
        ui->ParityBox->setDisabled(true);
        ui->BitBox->setDisabled(true);
        ui->StopBox->setDisabled(true);
        ui->ControlBox->setDisabled(true);
        ui->SendEditBtn1->setDisabled(false);
    }
    else {
        // 关闭状态，按钮显示“打开串口”
        ui->OpenSerialButton->setText("打开串口");
        // 关闭状态，允许用户操作
        ui->BaudBox->setDisabled(false);
        ui->ParityBox->setDisabled(false);
        ui->BitBox->setDisabled(false);
        ui->StopBox->setDisabled(false);
        ui->ControlBox->setDisabled(false);
        ui->SendEditBtn1->setDisabled(true);
    }
}
// 字符串转Hex(QByteArray)类型
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
// 将单个字符串转换为hex
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
    qDebug() << "开始分析指令";
    QStringList rawData = hexData.split(' ');
    bool ok;
    if (QString::compare(rawData[0], "fe") == 0) {
        int dataLen = rawData[1].toUInt(&ok, 16);   // 指令长度
        if (dataLen + 3 != rawData.size()) {
            qDebug() << "指令长度出错，丢弃指令";
            WrongData2Text(hexData);   // 将本条指令写到错误指令 text 中
        }
        else {
            if (QString::compare(rawData[rawData.size() - 1], "ff") != 0) {
                qDebug() << "指令尾出错，丢弃指令";
                WrongData2Text(hexData);   // 将本条指令写到错误指令 text 中
            }
            else {
                qDebug() << "指令格式正确";
                RightData2Table(hexData);  // 将指令按照一定的格式写到表格中
            }
        }
    }
    else {
        qDebug() << "指令头出错，丢弃指令";
        WrongData2Text(hexData);   // 将本条指令写到错误指令 text 中
    }
}
// 出错指令写到 text 中
void MainWindow::WrongData2Text(QString hexData)
{

    QString beforeData = ui->m_errorInstruction->toPlainText();// 先读取之前的数据
    QString wrongData = hexData.append('\n');
    ui->m_errorInstruction->setReadOnly(false);
    ui->m_errorInstruction->setPlainText(beforeData.append(wrongData));
    ui->m_errorInstruction->setReadOnly(true);
}
// 正确指令信息写到 table 中
void MainWindow::RightData2Table(QString hexData)
{
    QStringList rawData = hexData.split(' ');
    bool ok;
    QString dataLen = QString::number(rawData[1].toUInt(&ok, 16));// 指令长度
    rawData.removeFirst();
    rawData.removeFirst();
    rawData.removeLast();// 指令内容
    // 向表格中增加新的行
    int row = ui->m_rightInstruction->rowCount();
    ui->m_rightInstruction->insertRow(row);
    ui->m_rightInstruction->setItem(row, 0, new QTableWidgetItem(dataLen));
    QString lastdata;
    for (int i = 0; i < rawData.size(); i++) {
        lastdata.append(rawData[i]);
        lastdata.append(' ');
    }
    ui->m_rightInstruction->setItem(row, 1, new QTableWidgetItem(lastdata));// 写进 table
}
