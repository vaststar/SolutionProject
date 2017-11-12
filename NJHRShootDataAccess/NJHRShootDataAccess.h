#ifndef NJHRShootDataAccess_h__
#define NJHRShootDataAccess_h__

#include "njhrshootdataaccess_global.h"

#include <memory>
#include <vector>
#include <map>
//////////////////////////////////////////////////////////////////////////
///<summary> ���ݿ��ѯ������ </summary>
///
///<remarks> ������,2017/11/1. </remarks>
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
	///<summary> �������ݿ� </summary>
	///
	///<remarks> ������,2017/11/1. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	bool ConncetToDB(const std::vector<std::string> &DBConfig);

public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>��ѯ���б�����Ա. </summary>
	///
	/// <remarks>	ʯ��, 2017/10/12. </remarks>
	////////////////////////////////////////////////////////////////////////////////////////////////////
	bool GetAllSoldiers(SoldierBaseInfoVec &results);
	
	//////////////////////////////////////////////////////////////////////////
	///<summary> ��ѯ����� </summary>
	///
	///<remarks> ������,2017/11/3. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	bool GetAllPassWord(UserPassWordTabVec &results);
private:
	//////////////////////////////////////////////////////////////////////////
	///<summary>����ѯ�����ת��Ϊʿ����Ϣ </summary>
	///<params>һ����ѯ��Ϣ��ʿ��������Ϣ</params>
	///<return></return>
	///<remarks> 11/1/2017 --������  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	void ParseMapToSoldierBaseInfo(const std::map<std::string,std::string> &parseMap,SoldierBaseInfoPtr &info);

	//////////////////////////////////////////////////////////////////////////
	///<summary>����ѯ���ת��Ϊ����� </summary>
	///<params>һ����ѯ��Ϣ�������ṹ</params>
	///<return></return>
	///<remarks> 11/3/2017 --������  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	void ParseMapToUserPassWordInfo(const std::map<std::string, std::string> &parseMap, UserPassWordTabPtr &info);
public:
	//<summary> һЩ���ݿ��������������ع����ύ�� 2017/11/2--������ </summary> 
	bool beginTransation();
	bool rollBack();
	bool commitData();
private:
	class NJHRShootDataAccessPrivate;
	NJHRShootDataAccessPrivate *_p;
	static NJHRShootDataAccess *_instance;
};
#endif // NJHRShootDataAccess_h__
