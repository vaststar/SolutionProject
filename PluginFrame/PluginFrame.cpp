#include "PluginFrame.h"

#include <PluginCore/PluginManager.h>
#include <PluginCore/PluginBase.h>

#include <QAction>
#include <QMessageBox>
#include <QEvent>
#include <QWheelEvent>
#include <QtWidgets/QFileDialog>

class PluginFrame::PluginFramePrivate {
public:
	PluginFramePrivate()
		:img(new QImage()), sizeCount(1) {
		PluginManager::Instance()->startManager();
	}
public:
	std::map<std::string, std::pair<QAction*, PluginBase*>> plugins;

	QImage* img;//ͼƬ
	double sizeCount;//�Ŵ���С��¼
};
PluginFrame::PluginFrame(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags), _p(new PluginFramePrivate()) {
	ui.setupUi(this);
	InitWindows();
}

PluginFrame::~PluginFrame() {
	delete _p;
}

void PluginFrame::InitWindows() {
	setWindowTitle(QStringLiteral("������Ĳ��"));
	statusBar()->addWidget(new QLabel(QStringLiteral("  Copyright @ 2017--2020  �����ѧʿ  ")));
	//ui.statusBar->showMessage("Copyright @ 2017--2020  �����ѧʿ");
	QAction *helpAction = ui.menuBar->addAction(QStringLiteral("����"));
	connect(helpAction, SIGNAL(triggered()), this, SLOT(showHelp()));
	connect(ui.action_Help, SIGNAL(triggered()), this, SLOT(showHelp()));
	connect(ui.action_open, SIGNAL(triggered()), this, SLOT(openImage()));

	connect(ui.action_large, SIGNAL(triggered()), this, SLOT(enlargeSlot()));
	connect(ui.action_small, SIGNAL(triggered()), this, SLOT(narrowSlot()));
	connect(ui.action_close, SIGNAL(triggered()), this, SLOT(closeSlot()));
	InitPlugins();

	ui.label_image->installEventFilter(this);
}

void PluginFrame::pluginTriggered() {
	if (QAction *action = dynamic_cast<QAction*>(QObject::sender())) {
		auto it = _p->plugins.find(action->text().toStdString());
		if (it != _p->plugins.end()) {
			(*it).second.second->InitialLize();
		}
	}
}

void PluginFrame::InitPlugins() {
	std::vector<PluginBase*> allPlugins = PluginManager::Instance()->GetAllPlugins();
	for (auto it = allPlugins.begin(); it != allPlugins.end(); ++it) {
		QAction *action = new QAction((*it)->getName().c_str(), this);
		ui.menu_Plugin->addAction(action);
		action->setIcon((*it)->getIcon());
		_p->plugins[(*it)->getName()] = std::make_pair(action, *it);
		connect(action, SIGNAL(triggered()), this, SLOT(pluginTriggered()));
	}
}

void PluginFrame::showHelp() {
	QMessageBox::information(this, QStringLiteral("���˵��"), QStringLiteral("������������Ƶ�C++������������"));
}

void PluginFrame::openImage() {
	QString fileName = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ����Ҫ�򿪵�ͼ��"), "", "Images(*.png *.bmp *.jpg *.tif *.GIF)");
	if (fileName.isEmpty()) return;

	_p->img->load(fileName);
	ui.label_image->setPixmap(QPixmap::fromImage(*_p->img));
	ui.label_image->resize(QSize(_p->img->width(), _p->img->height()));
	ui.label_image->setAlignment(Qt::AlignCenter);
}

void PluginFrame::enlargeSlot() {
	if (!_p->img) return;
	_p->sizeCount *= 1.1;
	ui.label_image->setPixmap(QPixmap::fromImage(_p->img->scaled(_p->img->size()*_p->sizeCount, Qt::KeepAspectRatio, Qt::FastTransformation)));
}

void PluginFrame::narrowSlot() {
	if (!_p->img) return;
	_p->sizeCount *= 0.9;
	ui.label_image->setPixmap(QPixmap::fromImage(_p->img->scaled(_p->img->size()*_p->sizeCount, Qt::KeepAspectRatio, Qt::FastTransformation)));
}

void PluginFrame::closeSlot() {
	close();
}

bool PluginFrame::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui.label_image) {
		if (event->type() == QEvent::Wheel) {
			if (QWheelEvent *wheel = dynamic_cast<QWheelEvent*>(event)) {
				if (wheel->delta() > 0) {
					enlargeSlot();
				}
				else {
					narrowSlot();
				}
			}
		}
	}
	return obj->eventFilter(obj, event);
}
