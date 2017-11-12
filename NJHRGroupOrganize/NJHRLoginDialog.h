#ifndef NJHRLoginDialog_h__
#define NJHRLoginDialog_h__

#include <QtWidgets/QDialog>
namespace Ui { class NJHRLoginDialog; };
//////////////////////////////////////////////////////////////////////////
///<summary> 登录界面 </summary>
///
///<remarks> 朱正天,2017/11/3. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class NJHRLoginDialog : public QDialog
{
	Q_OBJECT

public:
	NJHRLoginDialog(QWidget *parent = Q_NULLPTR);
	~NJHRLoginDialog();
private slots:
	void OnConfirm();
	void OnCancel();
public:
	void InitWidget();
private:
	class NJHRLoginDialogPrivate;
	NJHRLoginDialogPrivate *_p;
private:
	Ui::NJHRLoginDialog *ui;
};
#endif // NJHRLoginDialog_h__
