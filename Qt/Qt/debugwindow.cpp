#include "debugwindow.h"

DebugWindow::DebugWindow(QProcess &process, QWidget *parent)
    : QMainWindow(parent),
      _process(process)
{
    _window = new QWidget(this);
    _layout = new QVBoxLayout(this);
    _label = new QLabel(_output, _window);
    _input = new QLineEdit(_window);
//    _input->setSizePolicy(MINI)
    _layout->addWidget(_label);
    _layout->addWidget(_input);
    _output = "RAS";
    connect(&_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
    connect(_input, SIGNAL(returnPressed()), this, SLOT(writeInput()));
    setCentralWidget(_window);
    _window->setLayout(_layout);
}

void DebugWindow::readOutput()
{
    _label->setText(((QProcess *)sender())->readAllStandardOutput());
}

void DebugWindow::writeInput()
{
    _process.write((_input->text().toStdString() + "\n").c_str());
    _input->clear();
}
