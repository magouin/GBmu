#include <debugwindow.h>
#include <QDir>

DebugWindow::DebugWindow(QString fileName, QWidget *parent)
	: QMainWindow(parent)
{
	QList<QString> regs = {"a ", "f ", "af ", "b ", "c ", "bc ", "d ", "e ", "de ", "h ", "l ", "hl ", "pc ", "sp "};

	_process = new QProcess(this);
	QStringList args = {"-d", fileName};
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
	_process->start(filename, args, QIODevice::ReadWrite | QIODevice::Text);
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
			[=]( int i ) { reg_update( i , regs[x], ((x % 3 == 2 || x > 11) ? 2 : 1), x / 3 * 3 + 2); }
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
	_next_instr = new QLabel(_window);
	_label = new QTextEdit(_window);
	_label->setFont({ "Courier" });
	_label->setReadOnly(true);
	_vlayout->addWidget(_registers);
	_vlayout->addWidget(_next_instr);
	_vlayout->addWidget(_label);
	_vlayout->addWidget(_input);

	connect(_process, SIGNAL(readyReadStandardOutput()), this, SLOT(readOutput()));
	connect(_input, SIGNAL(returnPressed()), this, SLOT(writeInput()));
	connect(_process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(close_window()));

	_next_instr->setText("Next Instruction :\n");
	setCentralWidget(_window);
	_window->setLayout(_vlayout);
	setAttribute(Qt::WA_DeleteOnClose);
	_process->waitForStarted(30000);
}

void    DebugWindow::close_window()
{
	close();
}

void    DebugWindow::reg_update(int val, QString reg, int size, int reg_id)
{
	if (size == 2)
	{
		_regs_values[reg_id - 1]->blockSignals(true);
		_regs_values[reg_id - 2]->blockSignals(true);
		_regs_values[reg_id - 1]->setValue(val & 0xff);
		_regs_values[reg_id - 2]->setValue(val >> 8);
		_regs_values[reg_id - 1]->blockSignals(false);
		_regs_values[reg_id - 2]->blockSignals(false);
	}
	else if (size == 1)
	{
		_regs_values[reg_id]->blockSignals(true);
		_regs_values[reg_id]->setValue(_regs_values[reg_id - 1]->value() | (_regs_values[reg_id - 2]->value() << 8));
		_regs_values[reg_id]->blockSignals(false);
	}
	qDebug() << QString("w/" + QString::number(size) + " ") + reg + QString::number(val);
	_process->write((QString("w/" + QString::number(size) + " ") + reg + QString::number(val) + '\n').toStdString().c_str());
}

DebugWindow::~DebugWindow()
{
	_process->kill();
}

void DebugWindow::readOutput()
{
	QByteArray output = _process->readAllStandardOutput();
	uint16_t            parsedValue;
	bool                ok;
	QList<QRegularExpression> res = {   QRegularExpression("A: (?<A>[A-F0-9]{2})"),
										QRegularExpression("F: (?<F>[A-F0-9]{2})"),
										QRegularExpression("B: (?<B>[A-F0-9]{2})"),
										QRegularExpression("C: (?<C>[A-F0-9]{2})"),
										QRegularExpression("D: (?<D>[A-F0-9]{2})"),
										QRegularExpression("E: (?<E>[A-F0-9]{2})"),
										QRegularExpression("H: (?<H>[A-F0-9]{2})"),
										QRegularExpression("L: (?<L>[A-F0-9]{2})"),
										QRegularExpression("PC: (?<PC>[A-F0-9]{4})"),
										QRegularExpression("SP: (?<SP>[A-F0-9]{4})")};
	QRegularExpression next("(?<NEXT>[A-F0-9]{2}:[A-F0-9]{4}:  [A-F0-9]{2}.*)$");
	QList<const char*> regs = {"A", "F", "B", "C", "D", "E", "H", "L", "PC", "SP"};
	int x = 0;

	_label->setText(output);
	QRegularExpressionMatch mnext = next.match(output);
	_next_instr->setText("Next Instruction :\n" + mnext.captured("NEXT"));

	while (x < 10)
	{
		QRegularExpressionMatch match = res[x].match(output);
		if (match.hasMatch()) {
			_regs_values[x + x / 2]->blockSignals(true);
			QString qstr = match.captured(regs[x]);
			_regs_values[x + x / 2]->setValue(qstr.toUInt(&ok, 16));
			_regs_values[x + x / 2]->blockSignals(false);
			if (x < 8)
			{
				_regs_values[x + x / 2 + 2 - x % 2]->blockSignals(true);
				parsedValue = _regs_values[x + x / 2 + 2 - x % 2]->value();
				parsedValue = (x % 2 == 0) ? (parsedValue & 0xff) | (qstr.toUInt(&ok, 16) << 8) :
					(parsedValue & 0xff00) | (qstr.toUInt(&ok, 16));
				_regs_values[x + x / 2 + 2 - x % 2]->setValue(parsedValue);
				_regs_values[x + x / 2 + 2 - x % 2]->blockSignals(false);

			}
		}
		x++;
	}
} 

void DebugWindow::writeInput()
{
	_process->write((_input->text().toStdString() + '\n').c_str());
	QThread::msleep(50);
	_input->clear();
}
