#ifndef NJHRGroupTreeView_h__
#define NJHRGroupTreeView_h__

#include <NJHRShootCommonUI/NJHRCommonTreeView.h>
//////////////////////////////////////////////////////////////////////////
///<summary> ���������view </summary>
///
///<remarks> ������,2017/11/2. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class QPoint;

class NJHRGroupTreeView : public NJHRCommonTreeView
{
	Q_OBJECT

public:
	NJHRGroupTreeView(QWidget *parent = 0);
	~NJHRGroupTreeView();
private slots:
	//////////////////////////////////////////////////////////////////////////
	///<summary> �Ҽ��� </summary>
	///
	///<remarks> ������,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	void OnCustomContextMenuRequested(const QPoint &pos);

	void AddSoldierSlot(bool checked );
	void DelSoldierSlot(bool checked);
	void EditSoldierSlot(bool checked);
private:
	//////////////////////////////////////////////////////////////////////////
	///<summary> ��ʼ�������������� </summary>
	///
	///<remarks> ������,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	void InitView();

	//////////////////////////////////////////////////////////////////////////
	///<summary> ��ʼ���Ҽ��˵� </summary>
	///
	///<remarks> ������,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	void InitMenu();
private:
	class NJHRGroupTreeViewPrivate;
	NJHRGroupTreeViewPrivate *_p;
};
#endif // NJHRGroupTreeView_h__
