#ifndef FacilityUtil_h__
#define FacilityUtil_h__

#include "FacilityUtil_global.h"

#include <string>
#include <vector>
#include <map>

//////////////////////////////////////////////////////////////////////////
///<summary> ���������ࣨwindows�£� </summary>
///
///<remarks> ������,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class FACILITYUTIL_EXPORT FacilityUtil
{
public:
	//////////////////////////////////////////////////////////////////////////
	///<summary> ���ݽ������ƣ��رս��� </summary>
	///
	///<remarks> ������,2017/11/8. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	static void TerminateProcessByName(const std::string &processName);

	//////////////////////////////////////////////////////////////////////////
	///<summary> ����32λuuid </summary>
	///
	///<remarks> ������,2017/11/9. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	static const std::string GenerateUUID();

	//////////////////////////////////////////////////////////////////////////
	///<summary> ���ݾ���·����E:\test\gg\ss.txt���������ļ���Ŀ¼ </summary>
	///
	///<remarks> ������,2017/11/9. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	static bool CreateDirPath(const std::string &path, const std::string &splitCh = "\\",bool isDir = false);

	//////////////////////////////////////////////////////////////////////////
	///<summary>�滻ȫ�����ַ��� </summary>
	///<params>Դ�� ���滻���ַ����� �滻���ַ���</params>
	///<return></return>
	///<remarks> 11/9/2017 --������  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static void ReplaceStringAll(std::string &sourceStr,const std::string &oldStr,const std::string &newStr);

	//////////////////////////////////////////////////////////////////////////
	///<summary>��ȡ��ǰʱ�� </summary>
	///<params>�����ʽ(Y=4λ��ݣ�m�£�d�գ�Hʱ��M�֣�S��)������ʱ������(�룬�֣�ʱ���գ��£��꣬���ڼ�������ڼ��죬����ʱ)9������</params>
	///<return>���������ʽ��ʱ���ַ��������������ʽ���Բο�strftime�����ĸ�ʽ˵����</return>
	///<remarks> 11/9/2017 --������  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static const std::string GetDateTime(const std::string &dateStyle = "%Y-%m-%d %H:%M:%S",std::vector<int> &result = std::vector<int>());

	///////////////////////////////////////////////////////////////////////////
	///<summary> ���ӿڣ� ��json�ַ��������ļ�������map���޷�����Ƕ��json�� .</summary>/////////////////////////////////////////////
	///<params>	 �ַ��������ļ�·���� ���			</params>////
	///<return>	 �ɹ���������true�����򷵻�false				</return>////
	///<remarks>  �����죬2017/7/3.</remarks>/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static bool ParseJsonString(const std::string &jsonString, std::map<std::string, std::vector<std::string>> &Results);
	static bool ParseJsonFile(const std::string &filePath,std::map<std::string, std::vector<std::string>> &Results);

	/////////////////////////////////////////////////////////////////////////
	///<summary>��ԴĿ¼������Ŀ��Ŀ¼</summary>/////////////////////////////////
	///<params>Դ·����Ŀ��·�����Ƿ񸲸ǣ������ļ����� </params>///////////////////////////////////////
	///<return>�ɹ�����true�����򷵻�false </return>///////////////////////////////////////
	///<remarks>������,2017.11.29��</remarks>//////////////////
	//////////////////////////////////////////////////////////////////////////
	static bool CopyFileToTarget(const std::string &sourcePath,const std::string &dirPath,bool replace=true,const std::string &fileType="");
private:
	//////////////////////////////////////////////////////////////////////////
	///<summary>���ݽ������ƣ���ȡ����id </summary>
	///<params>�������ƣ�����id���</params>
	///<return>�ɹ�����true�����򷵻�false</return>
	///<remarks> 11/8/2017 --������  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static bool GetProcessIDByName(const std::string &processName, unsigned long &Results);

	/////////////////////////////////////////////////////////////////////////
	///<summary>����·�������ֽ���Ŀ¼�����ļ�</summary>/////////////////////////////////
	///<params>·������Ŀ¼�����ļ����Ƿ���Ŀ¼ </params>///////////////////////////////////////
	///<return>�ɹ�����true </return>///////////////////////////////////////
	///<remarks>������,2017.11.29��</remarks>//////////////////
	//////////////////////////////////////////////////////////////////////////
	static bool GetAllPath(const std::string &sourcePath, std::vector<std::string> &dirResult,
						   std::vector<std::string> &fileResult,bool isDir=true);
private:
	explicit FacilityUtil();
	FacilityUtil(const FacilityUtil &);
	FacilityUtil &operator=(const FacilityUtil &);
	~FacilityUtil();
};
#endif // FacilityUtil_h__

