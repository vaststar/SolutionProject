#ifndef NJHRCOMMONTREEVIEW_H
#define NJHRCOMMONTREEVIEW_H

#include "njhrshootcommonui_global.h"
#include <QtWidgets/QTreeView>
#include <memory>

//////////////////////////////////////////////////////////////////////////
///<summary> 通用编组树view </summary>
///
///<remarks> 朱正天,2017/10/10. </remarks>
///////////////////////////////////////////////////////////////////////////
class SoldierBaseInfo;
typedef std::shared_ptr<SoldierBaseInfo> SoldierBaseInfoPtr;
typedef std::vector<SoldierBaseInfoPtr> SoldierBaseInfoVec;

class NJHRSHOOTCOMMONUI_EXPORT NJHRCommonTreeView : public QTreeView
{
	Q_OBJECT

public:
	explicit NJHRCommonTreeView(QWidget *parent = 0);
	virtual ~NJHRCommonTreeView();
public:
	void SetViewData(const SoldierBaseInfoVec &data);
private:
	void InitView();
private:
	class NJHRCommonTreeViewPrivate;
	NJHRCommonTreeViewPrivate *_p;
};

#endif // NJHRCOMMONTREEVIEW_H
