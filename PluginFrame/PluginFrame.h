#ifndef PLUGINFRAME_H
#define PLUGINFRAME_H

#include <QtWidgets/QMainWindow>
#include "ui_PluginFrame.h"

class QEvent;
class PluginFrame : public QMainWindow {
	Q_OBJECT

public:
	PluginFrame(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~PluginFrame();
private:
	void InitWindows();
	void InitPlugins();
	private slots:
	void pluginTriggered();
	void showHelp();
	void openImage();
	void enlargeSlot();
	void narrowSlot();
	void closeSlot();
protected:
	virtual bool eventFilter(QObject *obj, QEvent *event);
private:
	Ui::PluginFrameClass ui;
	class PluginFramePrivate;
	PluginFramePrivate *_p;
};

#endif // PLUGINFRAME_H
