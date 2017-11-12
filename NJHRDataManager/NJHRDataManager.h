#ifndef NJHRDataManager_h__
#define NJHRDataManager_h__

#include "njhrdatamanager_global.h"

#include <string>
#include <memory>
#include <vector>
//////////////////////////////////////////////////////////////////////////
///<summary> �������ݹ����� </summary>
///
///<remarks> ������,2017/11/2. </remarks>
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
	///<summary> ��ȡ������Ա���� </summary>
	///
	///<remarks> ������,2017/11/2. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	const SoldierBaseInfoVec &GetAllSoldiers()const;

	//////////////////////////////////////////////////////////////////////////
	///<summary> ��ȡ�����û������� </summary>
	///
	///<remarks> ������,2017/11/3. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	const UserPassWordTabVec &GetAllUserPassword()const;

	//////////////////////////////////////////////////////////////////////////
	///<summary>  </summary>
	///
	///<remarks> ������,2017/11/3. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	bool VerifyPassword(const std::string &userName,const std::string &passWord)const;
public:
	//<summary> ���ݿ���������������ύ���ع��� 2017/11/2--������ </summary> 
	bool BeginTransation();
	bool CommitData();
	bool RollBack();
public:
	//<summary> ��ʼ���������� 2017/11/2--������ </summary> 
	void InitData();

	//<summary> ������� 2017/11/2--������ </summary> 
	void ClearData();

public:
	static NJHRDataManager *Instance();
private:
	//////////////////////////////////////////////////////////////////////////
	///<summary> ���������ļ����������ݿ� </summary>
	///
	///<remarks> ������,2017/11/2. </remarks>
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
