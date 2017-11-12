#ifndef NJHRGroupTreeView_h__
#define NJHRGroupTreeView_h__

#include <NJHRShootCommonUI/NJHRCommonTreeView.h>
//////////////////////////////////////////////////////////////////////////
///<summary> 编组管理树view </summary>
///
///<remarks> 朱正天,2017/11/2. </remarks>
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
	///<summary> 右键槽 </summary>
	///
	///<remarks> 朱正天,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	void OnCustomContextMenuRequested(const QPoint &pos);

	void AddSoldierSlot(bool checked );
	void DelSoldierSlot(bool checked);
	void EditSoldierSlot(bool checked);
private:
	//////////////////////////////////////////////////////////////////////////
	///<summary> 初始化编组树等设置 </summary>
	///
	///<remarks> 朱正天,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	void InitView();

	//////////////////////////////////////////////////////////////////////////
	///<summary> 初始化右键菜单 </summary>
	///
	///<remarks> 朱正天,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	void InitMenu();
private:
	class NJHRGroupTreeViewPrivate;
	NJHRGroupTreeViewPrivate *_p;
};
#endif // NJHRGroupTreeView_h__
