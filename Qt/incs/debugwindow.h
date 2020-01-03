#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLabel>
#include <QDebug>
#include <QVBoxLayout>
#include <QLineEdit>

class DebugWindow : public QMainWindow
{
		Q_OBJECT
	public:
        ~DebugWindow();
        DebugWindow(QString fileName, QWidget *parent = nullptr);

	public slots:
		void			readOutput();
		void			writeInput();
        void            close_window();

	private:
        QProcess		*_process;
		QLabel			*_label;
		QString			_output;
		QVBoxLayout		*_layout;
		QLineEdit		*_input;
		QWidget			*_window;
};

#endif // DEBUGWINDOW_H
