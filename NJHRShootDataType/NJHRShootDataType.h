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
	SoldierLevel_Normal = 1 << 0, //普通小兵
	SoldierLevel_Monitor = 1 << 1, //班长
	SoldierLevel_Principal = 1 << 2 //首长
};

//////////////////////////////////////////////////////////////////////////
///<summary> 密码表 </summary>
///
///<remarks> 朱正天,2017/10/11. </remarks>
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
///<summary> 士兵基本信息 </summary>
///
///<remarks> 朱正天,2017/10/10. </remarks>
///////////////////////////////////////////////////////////////////////////
class SoldierBaseInfo
{
public:
	SoldierBaseInfo()
		:Level(SoldierLevel_Normal)
	{

	}
public:
	std::string ID;//编组内码
	std::string Name;//士兵名称
	std::string Serial;//士兵序号（用于判定编组）
	SoldierLevel Level;//士兵等级
	std::string UperID;//上级id
	std::vector<std::string> SubIDs;//所有直属下级id
};
typedef std::shared_ptr<SoldierBaseInfo> SoldierBaseInfoPtr;
typedef std::vector<SoldierBaseInfoPtr> SoldierBaseInfoVec;

//////////////////////////////////////////////////////////////////////////
///<summary> 士兵射击信息 </summary>
///
///<remarks> 朱正天,2017/10/10. </remarks>
///////////////////////////////////////////////////////////////////////////
class SoldierShootData
{
public:
	SoldierShootData()
		:SoldierInfo(nullptr)
	{

	}
public:
	SoldierBaseInfoPtr SoldierInfo;//士兵信息
	std::vector<std::tuple<float, float,float>> ShootRecord;//射击分数+射击横纵比（以靶心为原点，向右为x正轴，向下为y正轴）
};
typedef std::shared_ptr<SoldierShootData> SoldierShootDataPtr;
typedef std::vector<SoldierShootDataPtr> SoldierShootDataVec;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	场次成绩上传信息.  </summary>
///
/// <remarks>	石威, 2017/10/12. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
class ShootUploadData
{
public:
	std::string ID;	//场次编码
	std::string Name;	//场次名称
	std::string UploadTime;//上传
	SoldierShootDataVec SoldierShootRecord;	//士兵成绩
};
typedef std::shared_ptr<ShootUploadData> ShootUploadDataPtr;
typedef std::vector<ShootUploadDataPtr> ShootUploadDataVec;

//////////////////////////////////////////////////////////////////////////
///<summary> 分数信息 </summary>
///
///<remarks> 朱正天,2017/10/11. </remarks>
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
	std::string ID;	//场次编码
	std::string Name;	//场次名称
	std::string shootTime;//射击时间
	float shootSocre;//射击平均环数
	std::vector<std::tuple<float, float,float>> shootPosPer;//射击分数+射击横纵比（以靶心为原点，向右为x正轴，向下为y正轴）
};
typedef std::shared_ptr<ShootScoreData> ShootScoreDataPtr;
typedef std::vector<ShootScoreDataPtr> ShootScoreDataVec;

//////////////////////////////////////////////////////////////////////////
///<summary> 单个士兵的历史评分记录 </summary>
///
///<remarks> 朱正天,2017/10/10. </remarks>
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
	SoldierBaseInfoPtr SoldierInfo;//士兵信息
	ShootScoreDataVec HistorySocre;//所有历史成绩
	int Rank;//排名
	float AverageScore;//平均分数
};
typedef std::shared_ptr<SoldierEvaluateData> SoldierEvaluateDataPtr;
typedef std::vector<SoldierEvaluateDataPtr> SoldierEvaluateDataVec;
typedef std::pair<SoldierBaseInfoPtr,ShootScoreDataPtr> SingleHistoryInfo;

//////////////////////////////////////////////////////////////////////////
///<summary> 首长视角下的记录 </summary>
///
///<remarks> 朱正天,2017/10/11. </remarks>
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

