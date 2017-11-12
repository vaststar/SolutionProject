#include "NJHRShootUtil.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>

#include <NJHRShootDataType/NJHRCommonTreeItem.h>
#include <NJHRShootDataType/NJHRShootDataType.h>

Q_DECLARE_METATYPE(SoldierBaseInfoPtr)

NJHRShootUtil::NJHRShootUtil(void)
{
}


NJHRShootUtil::~NJHRShootUtil(void)
{
}

void NJHRShootUtil::ConvertOrganizedSoldierToTreeItem( const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results )
{
	if(nullptr == Results)
	{
		Results = new NJHRCommonTreeItem(QVariant(),nullptr);
	}
	
	for (auto it = soldiers.begin();it != soldiers.end();++it)
	{
		if ((*it)->UperID.empty())
		{
			NJHRCommonTreeItem *Item = new NJHRCommonTreeItem(QVariant::fromValue<SoldierBaseInfoPtr>((*it)),Results);
			Results->appendChild(Item);
			CreateTreeItemFromParent(soldiers,Item);
		}
	}
}

void NJHRShootUtil::CreateTreeItemFromParent( const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results )
{
	if(!Results) return;
	SoldierBaseInfoPtr entity = Results->data().value<SoldierBaseInfoPtr>();
	if(!entity || entity->SubIDs.empty()) return;

	for (auto it = entity->SubIDs.begin();it != entity->SubIDs.end();++it)
	{
		SoldierBaseInfoPtr subordinate = nullptr;
		for (auto en = soldiers.begin();en != soldiers.end();++en)
		{
			if ((*en)->ID == (*it))
			{
				subordinate = *en;
				break;
			}
		}
		if (subordinate)
		{
			NJHRCommonTreeItem *Item = new NJHRCommonTreeItem(QVariant::fromValue<SoldierBaseInfoPtr>(subordinate),Results);
			Results->appendChild(Item);
			CreateTreeItemFromParent(soldiers,Item);
		}
	}

}

void NJHRShootUtil::ConvertSoldierVecToTreeItems( const SoldierBaseInfoVec &soldiers,NJHRCommonTreeItem *&Results ,const int SerialGap)
{
	if(nullptr == Results)
	{
		Results = new NJHRCommonTreeItem(QVariant(),nullptr);
	}
	//先给数据按照序号长度排序,从短到长
	SoldierBaseInfoVec sortedVec = soldiers;
	std::sort(sortedVec.begin(),sortedVec.end(),[](SoldierBaseInfoPtr first,SoldierBaseInfoPtr second)->bool{
		return first->Serial.length() < second->Serial.length();
	});
	//找到最顶层序号长度
	size_t topLength = 0;
	if (!sortedVec.empty())
	{
		topLength = sortedVec.front()->Serial.length();
	}
	//开始设置编组
	std::vector<NJHRCommonTreeItem*> createdItems;
	for (auto it = sortedVec.begin();it != sortedVec.end();++it)
	{
		NJHRCommonTreeItem *Item = new NJHRCommonTreeItem(QVariant::fromValue<SoldierBaseInfoPtr>((*it)));
		if ((*it)->Serial.length() == topLength)
		{
			//序号和顶层的一样则为顶层结构
			Item->SetParent(Results);
			Results->appendChild(Item);
			createdItems.push_back(Item);
		}
		else
		{
			//根据已经建立的item，寻找本次建立的节点的父亲
			for (auto itemIt = createdItems.begin();itemIt != createdItems.end();++itemIt)
			{
				SoldierBaseInfoPtr itemData = (*itemIt)->data().value<SoldierBaseInfoPtr>();
				if(itemData->Serial.length() == (*it)->Serial.length() ||
				   static_cast<int>((*it)->Serial.length()) - static_cast<int>(itemData->Serial.length()) > SerialGap) continue;
				if ((*it)->Serial.substr(0,itemData->Serial.length()).compare(itemData->Serial) == 0)
				{
					Item->SetParent(*itemIt);
					(*itemIt)->appendChild(Item);
					createdItems.push_back(Item);
					break;
				}
			}
		}
	}
}

void NJHRShootUtil::MakeUpOrganize( SoldierBaseInfoVec &Results,const int SerialGap)
{
	//先按序号从长到短排序
	std::stable_sort(Results.begin(),Results.end(),[](SoldierBaseInfoPtr first,SoldierBaseInfoPtr second)->bool{
		return first->Serial.length() > second->Serial.length();
	});
	//根据序号设置上下级
	for (auto it = Results.begin();it != Results.end();++it)
	{
		//序号为空，或者序号长度不足以支撑有上级的跳过
		if(static_cast<int>((*it)->Serial.empty()) || static_cast<int>((*it)->Serial.length()) <= SerialGap) continue;

		for (auto up = it+1;up != Results.end();++up)
		{
			//搜索的上级序号和基准序号相差不为标准间隔的跳过
			if(static_cast<int>((*it)->Serial.length()) - static_cast<int>((*up)->Serial.length()) != SerialGap) continue;
			//匹配到上下级
			if ((*it)->Serial.substr(0,(*it)->Serial.length()-SerialGap).compare((*up)->Serial) == 0)
			{
				(*it)->UperID = (*up)->ID;
				(*up)->SubIDs.push_back((*it)->ID);
				break;
			}
		}
	}
}

const bool NJHRShootUtil::ParseJsonPluginFile( const std::string &filePath,std::map<std::string,std::vector<std::string>> &Result )
{
	if (FILE *pFile = fopen(filePath.c_str(),"r")){
		char buffer[65536];
		RAPIDJSON_NAMESPACE::FileReadStream is(pFile,buffer,sizeof(buffer));

		RAPIDJSON_NAMESPACE::Document document;
		if(document.ParseStream<0,RAPIDJSON_NAMESPACE::UTF8<>,RAPIDJSON_NAMESPACE::FileReadStream>(is).HasParseError()) return false;

		Result.clear();
		for (RAPIDJSON_NAMESPACE::Value::ConstMemberIterator it = document.MemberBegin();it != document.MemberEnd();++it){
			std::string key = it->name.GetString();
			std::vector<std::string> val;
			bool IsRecongnisable = true;
			switch (it->value.GetType())	{
			case RAPIDJSON_NAMESPACE::kNullType:
			case RAPIDJSON_NAMESPACE::kFalseType:
			case RAPIDJSON_NAMESPACE::kTrueType:
			case RAPIDJSON_NAMESPACE::kObjectType:
			case RAPIDJSON_NAMESPACE::kStringType:
			case RAPIDJSON_NAMESPACE::kNumberType:
				IsRecongnisable = false;
				break;
			case RAPIDJSON_NAMESPACE::kArrayType:
				for (RAPIDJSON_NAMESPACE::Value::ConstValueIterator arr = it->value.Begin();arr != it->value.End();++arr){
					if (arr->IsString())	{
						val.push_back(arr->GetString());
					}else if (arr->IsBool()){
						val.push_back(arr->GetBool()?"true":"false");
					}else if (arr->IsNull())	{
						val.push_back("");
					}else{
						val.push_back("");
					}
				}
				break;
			default:
				break;
			}
			if(!IsRecongnisable) continue;
			Result.insert(std::make_pair(key,val));
		}
		return true;
	}
	return false;
}

void NJHRShootUtil::StatisticSoldierEvaluateHistory( SoldierEvaluateDataVec &evaluateData )
{
	std::vector<std::pair<SoldierEvaluateDataPtr,float>> refVec;
	for (auto it = evaluateData.begin();it != evaluateData.end();++it)
	{
		(*it)->AverageScore = 0;
		for (auto his = (*it)->HistorySocre.begin();his != (*it)->HistorySocre.end();++his)
		{
			(*it)->AverageScore += (*his)->shootSocre;
		}
		if (!(*it)->HistorySocre.empty())
		{
			(*it)->AverageScore /= (*it)->HistorySocre.size();
		}
		refVec.push_back(std::make_pair((*it),(*it)->AverageScore));
	}
	
	std::stable_sort(evaluateData.begin(),evaluateData.end(),[](SoldierEvaluateDataPtr first,SoldierEvaluateDataPtr second)->bool{
		return first->AverageScore > second->AverageScore;
	});

	for (size_t i = 0;i < evaluateData.size();++i)
	{
		evaluateData[i]->Rank = i+1;
	}
}

#include <objbase.h>
#pragma comment(lib, "ole32.lib")
char* NJHRShootUtil::GenerateGUID()
{
	static char buf[64]={0};
	GUID guid;
	if (S_OK==::CoCreateGuid(&guid))
	{
		_snprintf(buf,sizeof(buf),"%08X%04X%04X%02X%02X%02X%02X%02X%02X%02X%02X"
			,guid.Data1,guid.Data2,guid.Data3\
			,guid.Data4[0],guid.Data4[1],guid.Data4[2],guid.Data4[3],guid.Data4[4]\
			,guid.Data4[5],guid.Data4[6],guid.Data4[7]);
	}
	return buf;
}

void NJHRShootUtil::CalSelfSeriesFromItem( NJHRCommonTreeItem *&Results ,const int SerialGap)
{
	if(!Results) return;
	SoldierBaseInfoPtr soldierInfo = Results->data().value<SoldierBaseInfoPtr>();
	if(!soldierInfo) return;

	NJHRCommonTreeItem *parentItem = Results->GetParent();
	if (!parentItem) return;

	if (parentItem->childCount() <= 1)
	{
		SoldierBaseInfoPtr parentData = parentItem->data().value<SoldierBaseInfoPtr>();
		
		if(!parentData)
		{
			soldierInfo->Serial = "01";
		}
		else
		{
			soldierInfo->Serial = parentData->Serial.append("01");
		}
	}
	//有兄弟时，根据兄弟序号，给定自己序号
	std::vector<std::string> serialVec;
	std::vector<int> numberVec;
	std::string head = "";
	for (int i =0 ;i < parentItem->childCount();++i)
	{
		std::string tempSerial = parentItem->GetChild(i)->data().value<SoldierBaseInfoPtr>()->Serial;
		if(tempSerial.empty() || tempSerial.length() < static_cast<size_t>(SerialGap)) continue;
		serialVec.push_back(tempSerial);
		if (head.empty())
		{
			head = tempSerial.substr(0,tempSerial.length()-SerialGap);
		}
		numberVec.push_back(atoi(tempSerial.substr(tempSerial.length()-SerialGap).c_str()));
	}

	int ResultNumber = 0;
	std::sort(numberVec.begin(),numberVec.end());
	for (auto it = numberVec.begin();it != numberVec.end();++it)
	{
		if (ResultNumber == *it)
		{
			++ResultNumber;
		}
		else
		{
			break;
		}
	}
	
	soldierInfo->Serial = head + NJHRShootUtil::ConvertIntToStringWithLength(ResultNumber,2);
}

const std::string NJHRShootUtil::ConvertIntToStringWithLength( const int number,const size_t length )
{
	std::string reslut = std::to_string(static_cast<long long>(number));
	size_t resultLen = reslut.length();
	if (resultLen < length)
	{
		reslut.insert(reslut.begin(),length-resultLen,'0');
	}
	else if (resultLen > length)
	{
		reslut = std::to_string(static_cast<long long>(number / pow(static_cast<double>(10),static_cast<int>(resultLen-length))));
	}
	return reslut;
}

///////////////////////////////////////////////////////////////////////////
///<summary> 将json文档，解析成map（key=string,value=string）(无法解析kObjectType)(数组去除首尾空白后通过下划线连接) .</summary>/////////////////////////////////////////////
///<params>		json字符串， 结果map			</params>////
///<return>		成功解析返回true，否则返回false			</return>////
///<remarks>  朱正天，2017/6/27.</remarks>/////////////////////////////////
///////////////////////////////////////////////////////////////////////////
const bool ParseJsonDoc( const RAPIDJSON_NAMESPACE::Document &document,std::map<std::string,std::string> &Result )
{
	Result.clear();
	for (RAPIDJSON_NAMESPACE::Value::ConstMemberIterator it = document.MemberBegin();it != document.MemberEnd();++it)
	{
		std::string key = it->name.GetString();
		std::string val ="";
		bool IsRecongnisable = true;
		switch (it->value.GetType())
		{
		case RAPIDJSON_NAMESPACE::kNullType:
			val = "";
			break;
		case RAPIDJSON_NAMESPACE::kFalseType:
			val = "false";
			break;
		case RAPIDJSON_NAMESPACE::kTrueType:
			val = "true";
			break;
		case RAPIDJSON_NAMESPACE::kObjectType:
			IsRecongnisable = false;
			break;
		case RAPIDJSON_NAMESPACE::kArrayType:
			for (RAPIDJSON_NAMESPACE::Value::ConstValueIterator arr = it->value.Begin();arr != it->value.End();++arr)
			{
				if (arr->IsString())
				{
					val += "_" + QString::fromStdString(arr->GetString()).trimmed().toStdString();
				}
				else if (arr->IsInt())
				{
					val += "_" + QString::number(arr->GetInt()).toStdString();
				}
				else if (arr->IsDouble())
				{
					val += "_" + QString::number(arr->GetDouble()).toStdString();
				}
			}
			if (!val.empty())
			{
				val = val.substr(1,val.length()-1);
			}
			break;
		case RAPIDJSON_NAMESPACE::kStringType:
			val = it->value.GetString();
			break;
		case RAPIDJSON_NAMESPACE::kNumberType:
			if (it->value.IsInt())
			{
				val = QString::number(it->value.GetInt()).toStdString();
			}
			else if (it->value.IsDouble())
			{
				val = QString::number(it->value.GetDouble()).toStdString();
			}
		default:
			break;
		}
		if(!IsRecongnisable) continue;
		Result.insert(std::make_pair(key,val));
	}

	return true;
}

const bool NJHRShootUtil::ParseJsonDataString( const std::string &jsonString,std::map<std::string,std::string> &Result )
{
	if(jsonString.empty()) return false;
	RAPIDJSON_NAMESPACE::Document document;
	if(document.Parse(jsonString.c_str()).HasParseError()) return false;

	return ParseJsonDoc(document,Result);
}

const int NJHRShootUtil::FindVacancy( const std::vector<unsigned int> data,const unsigned int maxNumber /*= 10*/ )
{
	if(data.size() > static_cast<size_t>(maxNumber)) return 0;
	for (size_t i = 0;i < data.size();++i)
	{
		if (data[i] != static_cast<unsigned >(i+1))
		{
			return (i+1)%maxNumber;
		}
	}
	return 0;
}
