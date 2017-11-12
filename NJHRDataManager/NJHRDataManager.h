#ifndef NJHRDataManager_h__
#define NJHRDataManager_h__

#include "njhrdatamanager_global.h"

#include <string>
#include <memory>
#include <vector>
//////////////////////////////////////////////////////////////////////////
///<summary> 工程数据管理类 </summary>
///
///<remarks> 朱正天,2017/11/2. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class SoldierBaseInfo;
typedef std::shared_ptr<SoldierBaseInfo> SoldierBaseInfoPtr;
typedef std::vector<SoldierBaseInfoPtr> SoldierBaseInfoVec;

class UserPassWordTab;
typedef std::shared_ptr<UserPassWordTab> UserPassWordTabPtr;
typedef std::vector<UserPassWordTabPtr> UserPassWordTabVec;

class NJHRDATAMANAGER_EXPORT NJHRDataManager
{
public:
	//////////////////////////////////////////////////////////////////////////
	///<summary> 获取所有人员编组 </summary>
	///
	///<remarks> 朱正天,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	const SoldierBaseInfoVec &GetAllSoldiers()const;

	//////////////////////////////////////////////////////////////////////////
	///<summary> 获取所有用户名密码 </summary>
	///
	///<remarks> 朱正天,2017/11/3. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	const UserPassWordTabVec &GetAllUserPassword()const;

	//////////////////////////////////////////////////////////////////////////
	///<summary>  </summary>
	///
	///<remarks> 朱正天,2017/11/3. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	bool VerifyPassword(const std::string &userName,const std::string &passWord)const;
public:
	//<summary> 数据库基本操作（事务、提交、回滚） 2017/11/2--朱正天 </summary> 
	bool BeginTransation();
	bool CommitData();
	bool RollBack();
public:
	//<summary> 初始化所有数据 2017/11/2--朱正天 </summary> 
	void InitData();

	//<summary> 清空数据 2017/11/2--朱正天 </summary> 
	void ClearData();

public:
	static NJHRDataManager *Instance();
private:
	//////////////////////////////////////////////////////////////////////////
	///<summary> 根据配置文件，连接数据库 </summary>
	///
	///<remarks> 朱正天,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	bool StartDataBase();
private:
	NJHRDataManager();
	virtual ~NJHRDataManager();
	NJHRDataManager(const NJHRDataManager&);
	NJHRDataManager &operator=(const NJHRDataManager&);
private:
	class NJHRDataManagerPrivate;
	NJHRDataManagerPrivate *_p;
	static NJHRDataManager *_instance;
};
#endif // NJHRDataManager_h__
