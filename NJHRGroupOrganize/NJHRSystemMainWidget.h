#ifndef NJHRSystemMainWidget_h__
#define NJHRSystemMainWidget_h__

#include <QtWidgets/QWidget>
namespace Ui { class NJHRSystemMainWidget; };
//////////////////////////////////////////////////////////////////////////
///<summary> 主界面 </summary>
///
///<remarks> 朱正天,2017/11/3. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class NJHRSystemMainWidget : public QWidget
{
	Q_OBJECT

public:
	NJHRSystemMainWidget(QWidget *parent = Q_NULLPTR);
	~NJHRSystemMainWidget();

private slots:
	void OnExit();
private:
	void InitWidget();
private:
	class NJHRSystemMainWidgetPrivate;
	NJHRSystemMainWidgetPrivate *_p;
private:
	Ui::NJHRSystemMainWidget *ui;
};
#endif // NJHRSystemMainWidget_h__
