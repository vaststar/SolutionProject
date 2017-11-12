#ifndef NJHRShootDataAccess_h__
#define NJHRShootDataAccess_h__

#include "njhrshootdataaccess_global.h"

#include <memory>
#include <vector>
#include <map>
//////////////////////////////////////////////////////////////////////////
///<summary> 数据库查询操作类 </summary>
///
///<remarks> 朱正天,2017/11/1. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class SoldierBaseInfo;
typedef std::shared_ptr<SoldierBaseInfo> SoldierBaseInfoPtr;
typedef std::vector<SoldierBaseInfoPtr> SoldierBaseInfoVec;

class UserPassWordTab;
typedef std::shared_ptr<UserPassWordTab> UserPassWordTabPtr;
typedef std::vector<UserPassWordTabPtr> UserPassWordTabVec;

class NJHRSHOOTDATAACCESS_EXPORT NJHRShootDataAccess
{
public:
	explicit NJHRShootDataAccess();
	~NJHRShootDataAccess();
public:
	//////////////////////////////////////////////////////////////////////////
	///<summary> 连接数据库 </summary>
	///
	///<remarks> 朱正天,2017/11/1. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	bool ConncetToDB(const std::vector<std::string> &DBConfig);

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>查询所有编组人员. </summary>
	///
	/// <remarks>	石威, 2017/10/12. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool GetAllSoldiers(SoldierBaseInfoVec &results);
	
	//////////////////////////////////////////////////////////////////////////
	///<summary> 查询密码表 </summary>
	///
	///<remarks> 朱正天,2017/11/3. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	bool GetAllPassWord(UserPassWordTabVec &results);
private:
	//////////////////////////////////////////////////////////////////////////
	///<summary>将查询结果，转换为士兵信息 </summary>
	///<params>一条查询信息，士兵基本信息</params>
	///<return></return>
	///<remarks> 11/1/2017 --朱正天  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	void ParseMapToSoldierBaseInfo(const std::map<std::string,std::string> &parseMap,SoldierBaseInfoPtr &info);

	//////////////////////////////////////////////////////////////////////////
	///<summary>将查询结果转换为密码表 </summary>
	///<params>一条查询信息，密码表结构</params>
	///<return></return>
	///<remarks> 11/3/2017 --朱正天  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	void ParseMapToUserPassWordInfo(const std::map<std::string, std::string> &parseMap, UserPassWordTabPtr &info);
public:
	//<summary> 一些数据库基本操作（事物、回滚、提交） 2017/11/2--朱正天 </summary> 
	bool beginTransation();
	bool rollBack();
	bool commitData();
private:
	class NJHRShootDataAccessPrivate;
	NJHRShootDataAccessPrivate *_p;
	static NJHRShootDataAccess *_instance;
};
#endif // NJHRShootDataAccess_h__
