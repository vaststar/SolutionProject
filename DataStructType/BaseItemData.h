#ifndef BaseItemData_h__
#define BaseItemData_h__

#include "DataStructType_global.h"
#include <string>
#include <memory>
#include <vector>
//////////////////////////////////////////////////////////////////////////
///<summary> ͨ�����ṹ </summary>
///
///<remarks> ������,2017/11/2. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class DATASTRUCTTYPE_LIB_EXPORT BaseItemData
{
public:
	//<summary> ���� 2017/11/9--������ </summary> 
	void SetName(const std::string &name);
	const std::string &GetName()const;

	//<summary> id��ʶ 2017/11/9--������ </summary> 
	void SetUUID(const std::string &uuid);
	const std::string &GetUUID()const;

	//<summary> �ϼ�id 2017/11/9--������ </summary> 
	void SetSuperiorID(const std::string &uuid);
	const std::string &GetSuperiorID()const;

	//<summary> �¼�id 2017/11/9--������ </summary> 
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

