#ifndef FacilityUtil_h__
#define FacilityUtil_h__

#include "FacilityUtil_global.h"

#include <string>
#include <vector>
#include <map>

//////////////////////////////////////////////////////////////////////////
///<summary> 基本工具类（windows下） </summary>
///
///<remarks> 朱正天,2017/11/9. </remarks>
///////////////////////////////////////////////////////////////////////////*/
class FACILITYUTIL_EXPORT FacilityUtil
{
public:
	//////////////////////////////////////////////////////////////////////////
	///<summary> 根据进程名称，关闭进程 </summary>
	///
	///<remarks> 朱正天,2017/11/8. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	static void TerminateProcessByName(const std::string &processName);

	//////////////////////////////////////////////////////////////////////////
	///<summary> 创建32位uuid </summary>
	///
	///<remarks> 朱正天,2017/11/9. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	static const std::string GenerateUUID();

	//////////////////////////////////////////////////////////////////////////
	///<summary> 根据绝对路径（E:\test\gg\ss.txt），创建文件夹目录 </summary>
	///
	///<remarks> 朱正天,2017/11/9. </remarks>
	///////////////////////////////////////////////////////////////////////////*/
	static bool CreateDirPath(const std::string &path, const std::string &splitCh = "\\");

	//////////////////////////////////////////////////////////////////////////
	///<summary>替换全部的字符串 </summary>
	///<params>源， 被替换的字符串， 替换的字符串</params>
	///<return></return>
	///<remarks> 11/9/2017 --朱正天  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static void ReplaceStringAll(std::string &sourceStr,const std::string &oldStr,const std::string &newStr);

	//////////////////////////////////////////////////////////////////////////
	///<summary>获取当前时间 </summary>
	///<params>输出格式(Y=4位年份，m月，d日，H时，M分，S秒)，具体时间内容(秒，分，时，日，月，年，星期几，当年第几天，夏令时)9项内容</params>
	///<return>符合输出格式的时间字符串（附：输出格式可以参看strftime函数的格式说明）</return>
	///<remarks> 11/9/2017 --朱正天  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static const std::string GetDateTime(const std::string &dateStyle = "%Y-%m-%d %H:%M:%S",std::vector<int> &result = std::vector<int>());

	///////////////////////////////////////////////////////////////////////////
	///<summary> （接口） 将json字符串或者文件解析成map（无法解析嵌套json） .</summary>/////////////////////////////////////////////
	///<params>	 字符串或者文件路径， 结果			</params>////
	///<return>	 成功解析返回true，否则返回false				</return>////
	///<remarks>  朱正天，2017/7/3.</remarks>/////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static bool ParseJsonString(const std::string &jsonString, std::map<std::string, std::vector<std::string>> &Results);
	static bool ParseJsonFile(const std::string &filePath,std::map<std::string, std::vector<std::string>> &Results);
private:
	//////////////////////////////////////////////////////////////////////////
	///<summary>根据进程名称，获取进程id </summary>
	///<params>进程名称，进程id结果</params>
	///<return>成功返回true，否则返回false</return>
	///<remarks> 11/8/2017 --朱正天  </remarks>/////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	static bool GetProcessIDByName(const std::string &processName, unsigned long &Results);
private:
	explicit FacilityUtil();
	FacilityUtil(const FacilityUtil &);
	FacilityUtil &operator=(const FacilityUtil &);
	~FacilityUtil();
};
#endif // FacilityUtil_h__

