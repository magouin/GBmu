#include <debugwindow.h>

DebugWindow::DebugWindow(QString fileName, QWidget *parent)
    : QMainWindow(parent)
{
    QList<QString> regs = {"a ", "f ", "af ", "b ", "c ", "bc ", "d ", "e ", "de ", "h ", "l ", "hl ", "pc ", "sp "};

    _process = new QProcess(this);
    QStringList args = {"-d", fileName};
    QResource::registerResource("resources.rcc");

    QFile f(":/bin");
    if (f.exists())
        printf("Trouver\n");
    else
        printf("Pas trouver\n");
    int x;
    char tmp[8192];
    QTemporaryFile file;

    if (file.open() && f.open(QIODevice::ReadOnly))
    {
        qDebug() << "ici" << endl;
        file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ReadOther | QFileDevice::ReadGroup |
                            QFileDevice::ExeOwner | QFileDevice::ExeOther | QFileDevice::ExeGroup);
        while ((x = f.read(tmp, 8192)))
        {
            file.write(tmp, x);
            printf("%d ", x);
        }
    }
    printf("filename = %s\n", file.fileName().toStdString().c_str());
    printf("filename = %s\n", fileName.toStdString().c_str());
    file.close();
    file.setAutoRemove(false);
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
}

void    DebugWindow::close_window()
{
    close();
}

void    DebugWindow::reg_update(int val, QString reg, int size)
{
    qDebug() << QString("w/"+ QString::number(size) +" ") + reg + QString::number(val);
    _process->write((QString("w/"+ QString::number(size) +" ") + reg + QString::number(val)).toStdString().c_str());
}

DebugWindow::~DebugWindow()
{
    _process->kill();
}

void DebugWindow::readOutput()
{
//	_label->setText(((QProcess *)sender())->readAllStandardOutput());
}

void DebugWindow::writeInput()
{
    _process->write((_input->text().toStdString() + "\n").c_str());
	_input->clear();
}
