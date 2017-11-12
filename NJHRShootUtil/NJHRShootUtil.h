#ifndef NJHRShootUtil_h__
#define NJHRShootUtil_h__

#include "NJHRShootUtil_global.h"
#include <memory>
#include <vector>
#include <map>
//////////////////////////////////////////////////////////////////////////
///<summary> ������ </summary>
///
///<remarks> ������,2017/10/10. </remarks>
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
	//<summary> ���ݱ������¼���������ת��Ϊ������ 2017/10/12--������ </summary> 
	static void ConvertOrganizedSoldierToTreeItem(const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results);

	//<summary> ������ţ�������ת�������� 2017/10/11--������ </summary> 
	static void ConvertSoldierVecToTreeItems(const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results,const int SerialGap = 2);
public:
	//<summary> ��ȫ������Ϣ 2017/10/11--������ </summary> 
	static void MakeUpOrganize(SoldierBaseInfoVec &Results,const int SerialGap = 2);
private:
	static void CreateTreeItemFromParent(const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results);
public:
	///////////////////////////////////////////////////////////////////////////
	///<summary> ��json�ĵ�,�������ַ������飨ֻ�����ַ��������Ҳ���������֮������ݣ������ڶ�ȡ�����ļ�֮��ģ�.</summary>/////////////////////////////////////////////
	///<params>		json�ĵ�·���� ���map			</params>////
	///<return>		�ɹ���������true�����򷵻�false			</return>////
	///<remarks>  �����죬2017/10/11.</remarks>/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static const bool ParseJsonPluginFile(const std::string &filePath,std::map<std::string,std::vector<std::string>> &Result);
public:
	///////////////////////////////////////////////////////////////////////////
	///<summary> ���ӿڣ� ��json�ַ���������map���޷�����Ƕ��json,�����飩 .</summary>/////////////////////////////////////////////
	///<params>	 �ַ��������ļ�·���� ���			</params>////
	///<return>	 �ɹ���������true�����򷵻�false				</return>////
	///<remarks>  �����죬2017/10/15.</remarks>/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static const bool ParseJsonDataString(const std::string &jsonString,std::map<std::string,std::string> &Result);
public:
	//<summary> ͳ�Ƶ�����ʷ��¼�ɼ� 2017/10/12--������ </summary> 
	static void StatisticSoldierEvaluateHistory(SoldierEvaluateDataVec &evaluateData);
public:
	//<summary> ����32λuuid 2017/10/12--������ </summary> 
	static char* GenerateGUID();
public:
	//<summary> ����item�����������(������ ��Ų�) 2017/10/13--������ </summary> 
	static void CalSelfSeriesFromItem(NJHRCommonTreeItem *&Results,const int SerialGap = 2);

private:
	//<summary> ������ת��Ϊָ�����ȵ��ַ������������0���� 2017/10/16--������ </summary> 
	static const std::string ConvertIntToStringWithLength(const int number,const size_t length = 2);

public:
	//<summary> ����������������ҳ���һ����ȱ�� 2017/10/16--������ </summary>
	static const int FindVacancy(const std::vector<unsigned int> data,const unsigned int maxNumber = 10);
private:
	NJHRShootUtil(void);
	~NJHRShootUtil(void);
};
#endif // NJHRShootUtil_h__

