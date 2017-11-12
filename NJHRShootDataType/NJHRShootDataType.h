#ifndef NJHRShootDataType_h__
#define NJHRShootDataType_h__

#include "njhrshootdatatype_global.h"

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <memory>

class NJHRShootDataType
{
public:
	NJHRShootDataType(void);
	~NJHRShootDataType(void);
};

enum SoldierLevel
{
	SoldierLevel_Normal = 1 << 0, //��ͨС��
	SoldierLevel_Monitor = 1 << 1, //�೤
	SoldierLevel_Principal = 1 << 2 //�׳�
};

//////////////////////////////////////////////////////////////////////////
///<summary> ����� </summary>
///
///<remarks> ������,2017/10/11. </remarks>
///////////////////////////////////////////////////////////////////////////
class UserPassWordTab
{
public:
	UserPassWordTab()
		:SoldierID(""),UserName(""),PassWord("")
	{
	
	}
public:
	std::string SoldierID;
	std::string UserName;
	std::string PassWord;
};
typedef std::shared_ptr<UserPassWordTab> UserPassWordTabPtr;
typedef std::vector<UserPassWordTabPtr> UserPassWordTabVec;

//////////////////////////////////////////////////////////////////////////
///<summary> ʿ��������Ϣ </summary>
///
///<remarks> ������,2017/10/10. </remarks>
///////////////////////////////////////////////////////////////////////////
class SoldierBaseInfo
{
public:
	SoldierBaseInfo()
		:Level(SoldierLevel_Normal)
	{

	}
public:
	std::string ID;//��������
	std::string Name;//ʿ������
	std::string Serial;//ʿ����ţ������ж����飩
	SoldierLevel Level;//ʿ���ȼ�
	std::string UperID;//�ϼ�id
	std::vector<std::string> SubIDs;//����ֱ���¼�id
};
typedef std::shared_ptr<SoldierBaseInfo> SoldierBaseInfoPtr;
typedef std::vector<SoldierBaseInfoPtr> SoldierBaseInfoVec;

//////////////////////////////////////////////////////////////////////////
///<summary> ʿ�������Ϣ </summary>
///
///<remarks> ������,2017/10/10. </remarks>
///////////////////////////////////////////////////////////////////////////
class SoldierShootData
{
public:
	SoldierShootData()
		:SoldierInfo(nullptr)
	{

	}
public:
	SoldierBaseInfoPtr SoldierInfo;//ʿ����Ϣ
	std::vector<std::tuple<float, float,float>> ShootRecord;//�������+������ݱȣ��԰���Ϊԭ�㣬����Ϊx���ᣬ����Ϊy���ᣩ
};
typedef std::shared_ptr<SoldierShootData> SoldierShootDataPtr;
typedef std::vector<SoldierShootDataPtr> SoldierShootDataVec;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	���γɼ��ϴ���Ϣ.  </summary>
///
/// <remarks>	ʯ��, 2017/10/12. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ShootUploadData
{
public:
	std::string ID;	//���α���
	std::string Name;	//��������
	std::string UploadTime;//�ϴ�
	SoldierShootDataVec SoldierShootRecord;	//ʿ���ɼ�
};
typedef std::shared_ptr<ShootUploadData> ShootUploadDataPtr;
typedef std::vector<ShootUploadDataPtr> ShootUploadDataVec;

//////////////////////////////////////////////////////////////////////////
///<summary> ������Ϣ </summary>
///
///<remarks> ������,2017/10/11. </remarks>
///////////////////////////////////////////////////////////////////////////
class ShootScoreData
{
public:
	ShootScoreData()
		:shootTime("")
		,shootSocre(0)
	{

	}
public:
	std::string ID;	//���α���
	std::string Name;	//��������
	std::string shootTime;//���ʱ��
	float shootSocre;//���ƽ������
	std::vector<std::tuple<float, float,float>> shootPosPer;//�������+������ݱȣ��԰���Ϊԭ�㣬����Ϊx���ᣬ����Ϊy���ᣩ
};
typedef std::shared_ptr<ShootScoreData> ShootScoreDataPtr;
typedef std::vector<ShootScoreDataPtr> ShootScoreDataVec;

//////////////////////////////////////////////////////////////////////////
///<summary> ����ʿ������ʷ���ּ�¼ </summary>
///
///<remarks> ������,2017/10/10. </remarks>
///////////////////////////////////////////////////////////////////////////
class SoldierEvaluateData
{
public:
	SoldierEvaluateData()
		:SoldierInfo(nullptr)
		,Rank(0)
		,AverageScore(0)
	{

	}
public:
	SoldierBaseInfoPtr SoldierInfo;//ʿ����Ϣ
	ShootScoreDataVec HistorySocre;//������ʷ�ɼ�
	int Rank;//����
	float AverageScore;//ƽ������
};
typedef std::shared_ptr<SoldierEvaluateData> SoldierEvaluateDataPtr;
typedef std::vector<SoldierEvaluateDataPtr> SoldierEvaluateDataVec;
typedef std::pair<SoldierBaseInfoPtr,ShootScoreDataPtr> SingleHistoryInfo;

//////////////////////////////////////////////////////////////////////////
///<summary> �׳��ӽ��µļ�¼ </summary>
///
///<remarks> ������,2017/10/11. </remarks>
///////////////////////////////////////////////////////////////////////////
class SubSoldierEvaluateData
{
public:
	SubSoldierEvaluateData()
		:Name(""),AverageScore(0),Rank(0)
	{
	
	}
public:
	std::string Name;
	float AverageScore;
	int Rank;
};
typedef std::shared_ptr<SubSoldierEvaluateData> SubSoldierEvaluateDataPtr;
typedef std::vector<SubSoldierEvaluateDataPtr> SubSoldierEvaluateDataVec;
#endif // NJHRShootDataType_h__

