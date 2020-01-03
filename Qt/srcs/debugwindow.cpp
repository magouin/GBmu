#include <debugwindow.h>

DebugWindow::DebugWindow(QString fileName, QWidget *parent)
    : QMainWindow(parent)
{
    _process = new QProcess(this);
    QStringList args = {"-d", fileName};

    _process->start(EXEC_PATH, args, QIODevice::ReadWrite | QIODevice::Text);
	_window = new QWidget(this);
    _layout = new QVBoxLayout(_window);
    _label = new QLabel(_output, _window);
    _input = new QLineEdit(_window);
	_layout->addWidget(_label);
	_layout->addWidget(_input);
	_output = "RAS";

    connect(_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
	connect(_input, SIGNAL(returnPressed()), this, SLOT(writeInput()));
    connect(_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(close_window()));

	setCentralWidget(_window);
	_window->setLayout(_layout);
    setAttribute(Qt::WA_DeleteOnClose);
}

void    DebugWindow::close_window()
{
    close();
}

DebugWindow::~DebugWindow()
{
    _process->kill();
}

void DebugWindow::readOutput()
{
	_label->setText(((QProcess *)sender())->readAllStandardOutput());
}

void DebugWindow::writeInput()
{
    _process->write((_input->text().toStdString() + "\n").c_str());
	_input->clear();
}
