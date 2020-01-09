#include <debugwindow.h>

DebugWindow::DebugWindow(QString fileName, QWidget *parent)
    : QMainWindow(parent)
{
    QList<QString> regs = {"a ", "f ", "af ", "b ", "c ", "bc ", "d ", "e ", "de ", "h ", "l ", "hl ", "pc ", "sp "};

    _process = new QProcess(this);
    QStringList args = {"-d", fileName};
    QResource::registerResource("resources.rcc");

    QFile f(":/bin");
    int x;
    char tmp[8192];
    QTemporaryFile file;

    if (file.open() && f.open(QIODevice::ReadOnly))
    {
        file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ReadOther | QFileDevice::ReadGroup |
                            QFileDevice::ExeOwner | QFileDevice::ExeOther | QFileDevice::ExeGroup);
        while ((x = f.read(tmp, 8192)))
            file.write(tmp, x);
    }
    file.close();
    _process->start(file.fileName(), args, QIODevice::ReadWrite | QIODevice::Text);
    _window = new QWidget(this);
    _registers = new QWidget(_window);
    _vlayout = new QVBoxLayout(_window);
    _gridlayout = new QGridLayout(_registers);

    for (int x = 0; x < 14; x++)
    {
        _regs_values.append(new HexSpinBox(_registers));
        _regs_values[x]->setRange(0, 256 * ((x % 3 == 2 || x > 11) ? 256 : 1) - 1);
        connect(
            _regs_values[x],
            QOverload<int>::of(&HexSpinBox::valueChanged),
            [=]( int i ) { reg_update( i , regs[x], ((x % 3 == 2 || x > 11) ? 2 : 1)); }
        );
    }
    _gridlayout->addWidget(new QLabel(tr("A:"), _registers), 0, 0);
    _gridlayout->addWidget(_regs_values[0], 0, 1);
    _gridlayout->addWidget(new QLabel(tr("F:"), _registers), 0, 2);
    _gridlayout->addWidget(_regs_values[1], 0, 3);
    _gridlayout->addWidget(new QLabel(tr("AF:"), _registers), 0, 4);
    _gridlayout->addWidget(_regs_values[2], 0, 5);
    _gridlayout->addWidget(new QLabel(tr("B:"), _registers), 1, 0);
    _gridlayout->addWidget(_regs_values[3], 1, 1);
    _gridlayout->addWidget(new QLabel(tr("C:"), _registers), 1, 2);
    _gridlayout->addWidget(_regs_values[4], 1, 3);
    _gridlayout->addWidget(new QLabel(tr("BC:"), _registers), 1, 4);
    _gridlayout->addWidget(_regs_values[5], 1, 5);
    _gridlayout->addWidget(new QLabel(tr("D:"), _registers), 2, 0);
    _gridlayout->addWidget(_regs_values[6], 2, 1);
    _gridlayout->addWidget(new QLabel(tr("E:"), _registers), 2, 2);
    _gridlayout->addWidget(_regs_values[7], 2, 3);
    _gridlayout->addWidget(new QLabel(tr("DE:"), _registers), 2, 4);
    _gridlayout->addWidget(_regs_values[8], 2, 5);
    _gridlayout->addWidget(new QLabel(tr("H:"), _registers), 3, 0);
    _gridlayout->addWidget(_regs_values[9], 3, 1);
    _gridlayout->addWidget(new QLabel(tr("L:"), _registers), 3, 2);
    _gridlayout->addWidget(_regs_values[10], 3, 3);
    _gridlayout->addWidget(new QLabel(tr("HL:"), _registers), 3, 4);
    _gridlayout->addWidget(_regs_values[11], 3, 5);
    _gridlayout->addWidget(new QLabel(tr("PC:"), _registers), 4, 0);
    _gridlayout->addWidget(_regs_values[12], 4, 1);
    _gridlayout->addWidget(new QLabel(tr("SP:"), _registers), 4, 2);
    _gridlayout->addWidget(_regs_values[13], 4, 3);



    _input = new QLineEdit(_window);
    _vlayout->addWidget(_registers);
    _vlayout->addWidget(_input);

    connect(_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
	connect(_input, SIGNAL(returnPressed()), this, SLOT(writeInput()));
    connect(_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(close_window()));

	setCentralWidget(_window);
    _window->setLayout(_vlayout);
    setAttribute(Qt::WA_DeleteOnClose);
    _process->waitForStarted(30000);
}

void    DebugWindow::close_window()
{
    close();
}

void    DebugWindow::reg_update(int val, QString reg, int size)
{
    qDebug() << QString("w/" + QString::number(size) + " ") + reg + QString::number(val);
    _process->write((QString("w/" + QString::number(size) + " ") + reg + QString::number(val) + '\n').toStdString().c_str());
}

DebugWindow::~DebugWindow()
{
    _process->kill();
}

/*uint16_t get_hex_from_string(string str)
{
    uint16_t parsedValue;

    if (str[0] >= '0' && str[0] <= '9')
        parsedValue = (str[0] - '0') * 0x10;
    else if (str[0] >= 'F' && str[0] <= 'F')
        parsedValue = (str[0] - 'A' + 10) * 0x10;
    else if (str[0] >= 'a' && str[0] <= 'f')
        parsedValue = (str[0] - 'a' + 10) * 0x10;
    else
        parsedValue = 0;
    printf("parsedValue = %x\n", parsedValue);
    if (str[1] >= '0' && str[1] <= '9')
        parsedValue += (str[1] - '0');
    else if (str[1] >= 'A' && str[1] <= 'F')
        parsedValue += (str[1] - 'A' + 10);
    else if (str[1] >= 'a' && str[1] <= 'f')
        parsedValue += (str[1] - 'a' + 10);
    else
        parsedValue = 0;
    printf("parsedValue = %x\n", parsedValue);
    return (parsedValue);
}*/

void DebugWindow::readOutput()
{
    QByteArray output = _process->readAllStandardOutput();
    uint16_t            parsedValue;
    bool                ok;

    printf("search\n");
    qDebug() << "Received: [" << output << "]";
    QRegularExpression re("A: (?<A>[A-F0-9]{2})  F: (?<F>[A-F0-9]{2})  \\(AF: [A-F0-9]{4}\\)");
    QRegularExpressionMatch match = re.match(output);
    if (match.hasMatch()) {
        QString qstr = match.captured("A");
        parsedValue = qstr.toUInt(&ok, 16);
        _regs_values[0]->setValue(parsedValue);
        qstr = match.captured("F");
        parsedValue = parsedValue * 256 + qstr.toUInt(&ok, 16);
        _regs_values[1]->setValue(qstr.toUInt(&ok, 16));
        _regs_values[2]->setValue(parsedValue);    
    }
    re = QRegularExpression("B: (?<B>[A-F0-9]{2})  C: (?<C>[A-F0-9]{2})  \\(BC: [A-F0-9]{4}\\)");
    match = re.match(output);
    if (match.hasMatch()) {
        QString qstr = match.captured("B");
        parsedValue = qstr.toUInt(&ok, 16);
        _regs_values[3]->setValue(parsedValue);
        qstr = match.captured("C");
        parsedValue = parsedValue * 256 + qstr.toUInt(&ok, 16);
        _regs_values[4]->setValue(qstr.toUInt(&ok, 16));
        _regs_values[5]->setValue(parsedValue);    
    }
    re = QRegularExpression("D: (?<D>[A-F0-9]{2})  E: (?<E>[A-F0-9]{2})  \\(DE: [A-F0-9]{4}\\)");
    match = re.match(output);
    if (match.hasMatch()) {
        QString qstr = match.captured("D");
        parsedValue = qstr.toUInt(&ok, 16);
        _regs_values[6]->setValue(parsedValue);
        qstr = match.captured("E");
        parsedValue = parsedValue * 256 + qstr.toUInt(&ok, 16);
        _regs_values[7]->setValue(qstr.toUInt(&ok, 16));
        _regs_values[8]->setValue(parsedValue);    
    }
    re = QRegularExpression("H: (?<H>[A-F0-9]{2})  L: (?<L>[A-F0-9]{2})  \\(HL: [A-F0-9]{4}\\)");
    match = re.match(output);
    if (match.hasMatch()) {
        QString qstr = match.captured("H");
        parsedValue = qstr.toUInt(&ok, 16);
        _regs_values[9]->setValue(parsedValue);
        qstr = match.captured("L");
        parsedValue = parsedValue * 256 + qstr.toUInt(&ok, 16);
        _regs_values[10]->setValue(qstr.toUInt(&ok, 16));
        _regs_values[11]->setValue(parsedValue);    
    }
    re = QRegularExpression("PC: (?<PC>[A-F0-9]{4})  SP: (?<SP>[A-F0-9]{4})");
    match = re.match(output);
    if (match.hasMatch()) {
        printf("ici\n");
        QString qstr = match.captured("PC");
        _regs_values[12]->setValue(qstr.toUInt(&ok, 16));
        qstr = match.captured("SP");
        _regs_values[13]->setValue(qstr.toUInt(&ok, 16));
    }
}

void DebugWindow::writeInput()
{
    printf("writting: %s", (_input->text().toStdString() + '\n').c_str());
    if (_input->text().toStdString().empty())
        printf("nb = %lld\n", _process->write("n\n"));
    else
        printf("nb = %lld\n", _process->write((_input->text().toStdString() + '\n').c_str()));
	_input->clear();
}
