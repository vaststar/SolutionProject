#ifndef NJHRShootUtil_h__
#define NJHRShootUtil_h__

#include "NJHRShootUtil_global.h"
#include <memory>
#include <vector>
#include <map>
//////////////////////////////////////////////////////////////////////////
///<summary> 工具类 </summary>
///
///<remarks> 朱正天,2017/10/10. </remarks>
///////////////////////////////////////////////////////////////////////////
class SoldierBaseInfo;
typedef std::shared_ptr<SoldierBaseInfo> SoldierBaseInfoPtr;
typedef std::vector<SoldierBaseInfoPtr> SoldierBaseInfoVec;

class SoldierEvaluateData;
typedef std::shared_ptr<SoldierEvaluateData> SoldierEvaluateDataPtr;
typedef std::vector<SoldierEvaluateDataPtr> SoldierEvaluateDataVec;

class NJHRCommonTreeItem;
class NJHRSHOOTUTIL_EXPORT NJHRShootUtil
{
public:
	//<summary> 根据编组上下级，将编组转换为树链表 2017/10/12--朱正天 </summary> 
	static void ConvertOrganizedSoldierToTreeItem(const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results);

	//<summary> 根据序号，将编组转换成链表 2017/10/11--朱正天 </summary> 
	static void ConvertSoldierVecToTreeItems(const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results,const int SerialGap = 2);
public:
	//<summary> 补全编组信息 2017/10/11--朱正天 </summary> 
	static void MakeUpOrganize(SoldierBaseInfoVec &Results,const int SerialGap = 2);
private:
	static void CreateTreeItemFromParent(const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results);
public:
	///////////////////////////////////////////////////////////////////////////
	///<summary> 将json文档,解析成字符串数组（只解析字符串，并且不解析数组之外的内容）（用于读取配置文件之类的）.</summary>/////////////////////////////////////////////
	///<params>		json文档路径， 结果map			</params>////
	///<return>		成功解析返回true，否则返回false			</return>////
	///<remarks>  朱正天，2017/10/11.</remarks>/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static const bool ParseJsonPluginFile(const std::string &filePath,std::map<std::string,std::vector<std::string>> &Result);
public:
	///////////////////////////////////////////////////////////////////////////
	///<summary> （接口） 将json字符串解析成map（无法解析嵌套json,无数组） .</summary>/////////////////////////////////////////////
	///<params>	 字符串或者文件路径， 结果			</params>////
	///<return>	 成功解析返回true，否则返回false				</return>////
	///<remarks>  朱正天，2017/10/15.</remarks>/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static const bool ParseJsonDataString(const std::string &jsonString,std::map<std::string,std::string> &Result);
public:
	//<summary> 统计单兵历史记录成绩 2017/10/12--朱正天 </summary> 
	static void StatisticSoldierEvaluateHistory(SoldierEvaluateDataVec &evaluateData);
public:
	//<summary> 产生32位uuid 2017/10/12--朱正天 </summary> 
	static char* GenerateGUID();
public:
	//<summary> 根据item调整自身序号(树链表， 序号差) 2017/10/13--朱正天 </summary> 
	static void CalSelfSeriesFromItem(NJHRCommonTreeItem *&Results,const int SerialGap = 2);

private:
	//<summary> 将整数转换为指定长度的字符串，不足的用0补齐 2017/10/16--朱正天 </summary> 
	static const std::string ConvertIntToStringWithLength(const int number,const size_t length = 2);

public:
	//<summary> 在已排序的数组中找出第一个空缺的 2017/10/16--朱正天 </summary>
	static const int FindVacancy(const std::vector<unsigned int> data,const unsigned int maxNumber = 10);
private:
	NJHRShootUtil(void);
	~NJHRShootUtil(void);
};
#endif // NJHRShootUtil_h__

