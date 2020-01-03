#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QProcess>
#include <QLabel>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QObject>
#include <string>
#include <debugwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DebugWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
public slots:
	void change_file();
	void run_emu();
private:
	QList<QPushButton *>	buttons;
	QString					fileName;
    QList<QProcess *>		processes;
    QLabel                  *label;
    QCheckBox *				debug;
    QHBoxLayout *			layout;
	QWidget					*window;
};
#endif // MAINWINDOW_H
