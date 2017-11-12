#ifndef BaseItemData_h__
#define BaseItemData_h__

#include "DataStructType_global.h"
#include <string>
#include <memory>
#include <vector>
//////////////////////////////////////////////////////////////////////////
///<summary> 通用树结构 </summary>
///
///<remarks> 朱正天,2017/11/2. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class DATASTRUCTTYPE_LIB_EXPORT BaseItemData
{
public:
	//<summary> 名称 2017/11/9--朱正天 </summary> 
	void SetName(const std::string &name);
	const std::string &GetName()const;

	//<summary> id标识 2017/11/9--朱正天 </summary> 
	void SetUUID(const std::string &uuid);
	const std::string &GetUUID()const;

	//<summary> 上级id 2017/11/9--朱正天 </summary> 
	void SetSuperiorID(const std::string &uuid);
	const std::string &GetSuperiorID()const;

	//<summary> 下级id 2017/11/9--朱正天 </summary> 
	void SetSubordinateIDs(const std::vector<std::string> &ids);
	bool AppendSubordinate(const std::string &id);
	const std::vector<std::string> &GetSubordinateIDs()const;
public:
	BaseItemData();
	BaseItemData(const BaseItemData &r);
	BaseItemData &operator=(const BaseItemData &r);
	virtual ~BaseItemData();
private:
	class BaseItemDataPrivate;
	BaseItemDataPrivate *_p;
};
typedef std::shared_ptr<BaseItemData> BaseItemDataPtr;
#endif // BaseItemData_h__

