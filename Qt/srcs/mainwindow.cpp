#include <mainwindow.h>
#include <ui_mainwindow.h>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    this->setFixedSize(400,100);
    window = new QWidget(this);
    window->setGeometry(0, 8, 400, 50);
    setWindowTitle("Gbmu by Vsteffen and Magouin");
    layout = new QHBoxLayout();
    buttons.append(new QPushButton("Choose ROM", window));
    buttons.append(new QPushButton("Play", window));
    debug = new QCheckBox("Debug", window);

    layout->addWidget(buttons[0]);
    layout->addWidget(buttons[1]);
    layout->addWidget(debug);

    window->setLayout(layout);
    label = new QLabel(this);
    label->setText("File :");
    label->setGeometry(20, 50, 380, 40);
    connect(buttons[0], SIGNAL(clicked(bool)), this, SLOT(change_file()));
	connect(buttons[1], SIGNAL(clicked(bool)), this, SLOT(run_emu()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::change_file()
{
	fileName = QFileDialog::getOpenFileName(this, "Choose your game", ROM_PATH, "*.gb *.gbc");
    std::string std_str = fileName.toStdString();
    std::size_t tmp = std_str.find_last_of("/\\");
    label->setText("File : " + QString::fromStdString(std_str.substr(tmp + 1)));
}

void MainWindow::run_emu()
{
    if (debug->checkState())
    {
        DebugWindow * debugger = new DebugWindow(fileName, this);
        debugger->show();
    }
    else
    {
        QProcess *process = new QProcess(this);
        QStringList args = {fileName};
        QResource::registerResource("resources.rcc");

        int x;
        char tmp[8192];

    #ifdef WINDOS
        QFile src_dll(":/dll");
        QFile target_dll(QDir::tempPath() + "/SDL2.dll");
        QTemporaryFile *file = new QTemporaryFile(QDir::tempPath() + "/GBmu-XXXXXX.exe");

        src_dll.open(QIODevice::ReadOnly);
        target_dll.open(QIODevice::WriteOnly);

        while ((x = src_dll.read(tmp, 8192)))
            target_dll.write(tmp, x);

        target_dll.close();
        src_dll.close();
        QFile f(":/bin_win");
    #endif

    #ifndef WINDOS
        QTemporaryFile *file = new QTemporaryFile(QDir::tempPath() + "/GBmu-XXXXXX");
        QFile f(":/bin_unix");
    #endif
    file->setAutoRemove(false);
    if (!f.exists())
    {
        printf("Exiting 2\n");
        exit(2);
    }
    if (file->open() && f.open(QIODevice::ReadOnly))
    {
        file->setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ReadOther | QFileDevice::ReadGroup |
                            QFileDevice::ExeOwner | QFileDevice::ExeOther | QFileDevice::ExeGroup);
        while ((x = f.read(tmp, 8192)))
            file->write(tmp, x);
    }
    file->close();
    QString filename = file->fileName();
    delete file;
    f.close();
    process->start(filename, args, QIODevice::ReadWrite | QIODevice::Text);
    process->waitForStarted(30000);
    }
}
