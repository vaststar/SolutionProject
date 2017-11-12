#include "BaseItemData.h"

class BaseItemData::BaseItemDataPrivate
{
public:
	BaseItemDataPrivate()
		:_name(""), _uuid(""), _superiorID("")
	{

	}
public:
	//<summary> 名称 2017/11/9--朱正天 </summary> 
	std::string _name;

	//<summary> 自己的id 2017/11/9--朱正天 </summary> 
	std::string _uuid;

	//<summary> 上级id 2017/11/9--朱正天 </summary> 
	std::string _superiorID;

	//<summary> 下级id 2017/11/9--朱正天 </summary> 
	std::vector<std::string> _subordinateID;
};

BaseItemData::BaseItemData()
	:_p(new BaseItemDataPrivate())
{
}

BaseItemData::BaseItemData(const BaseItemData &r)
{
	_p = new BaseItemDataPrivate(*r._p);
}

BaseItemData::~BaseItemData()
{
	delete _p;
}

BaseItemData & BaseItemData::operator=(const BaseItemData &r)
{
	if (this != &r)
	{
		delete _p;
		_p = new BaseItemDataPrivate(*r._p);
	}
	return *this;
}

void BaseItemData::SetName(const std::string &name)
{
	_p->_name = name;
}

const std::string & BaseItemData::GetName() const
{
	return _p->_name;
}

void BaseItemData::SetUUID(const std::string &uuid)
{
	_p->_uuid = uuid;
}

const std::string & BaseItemData::GetUUID() const
{
	return _p->_uuid;
}

void BaseItemData::SetSuperiorID(const std::string &uuid)
{
	_p->_superiorID = uuid;
}

const std::string & BaseItemData::GetSuperiorID() const
{
	return _p->_superiorID;
}

void BaseItemData::SetSubordinateIDs(const std::vector<std::string> &ids)
{
	_p->_subordinateID = ids;
}

bool BaseItemData::AppendSubordinate(const std::string &id)
{
	if (std::find(_p->_subordinateID.begin(),_p->_subordinateID.end(),id) == _p->_subordinateID.end())
	{
		_p->_subordinateID.push_back(id);
		return true;
	}
	return false;
}

const std::vector<std::string> & BaseItemData::GetSubordinateIDs() const
{
	return _p->_subordinateID;
}
