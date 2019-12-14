#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Gbmu by Vsteffen and Magouin");
    buttons.append(new QPushButton("Choose ROM", this));
    connect(*buttons.begin(), SIGNAL(clicked(bool)), this, SLOT(change_file()));
    buttons.append(new QPushButton("Play", this));
    (*(buttons.begin() + 1))->move(0, 30);
    connect(*(buttons.begin() + 1), SIGNAL(clicked(bool)), this, SLOT(run_emu()));
    QLabel(str, this);
}

MainWindow::~MainWindow()
{

}

void MainWindow::change_file()
{
    fileName = QFileDialog::getOpenFileName(this, "Choose your game", "/Users/magouin/Project/GBmu/roms", "*.gb *.gbc");
}

void MainWindow::run_emu()
{
    QProcess *process = new QProcess(this);
    DebugWindow *debug = new DebugWindow(*process, this);

    process->start("/Users/magouin/Project/GBmu/MacosX/GBmu",
                  QStringList() << "-d" << fileName,
                  QIODevice::ReadWrite | QIODevice::Text);
    processes.append(process);
    debug->show();
}
