#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <functional>
#include <QResource>
#include <QFile>
#include <QTemporaryFile>
#include <QRegularExpression>
#include <QTextEdit>
#include <QThread>

#include <hexspinbox.h>

class DebugWindow : public QMainWindow
{
		Q_OBJECT
	public:
        ~DebugWindow();
        DebugWindow(QString fileName, QWidget *parent = nullptr);
        void reg_update(int, QString, int, int, int);

	public slots:
		void			readOutput();
		void			writeInput();
        void            close_window();

	private:
        QProcess             *_process;
        QTextEdit            *_label;
        QVBoxLayout          *_vlayout;
        QGridLayout          *_gridlayout;
        QLineEdit            *_input;
        QWidget              *_window;
        QWidget              *_registers;
        QList<QSpinBox *>    _regs_values;
        QLabel               *_next_instr;
};

#endif // DEBUGWINDOW_H
