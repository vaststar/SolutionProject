#include "StdAfx.h"
#include "MyObserver.h"

#include <fstream>

#include <sstream>
#include <vector>
#include <iostream>

class MyObserver::ServerObserverPrivate{
public:
	ServerObserverPrivate(){

	}
public:

};
MyObserver::MyObserver(const SOCKET &sockConnect,const std::string &clientAddr)
	:WinBaseObserver(sockConnect,clientAddr)
	,_p(new ServerObserverPrivate()){
}

MyObserver::~MyObserver(void){
}
struct as
{
	int a;
	int b;
	double c;
};
void MyObserver::OnCommingMessage( const std::string &message ){
	if (message == "������.txt")	{
		std::ifstream file;
		file.open("E:\\C++\\Tcp\\Server\\������.txt",std::ios::binary);
		if (file.is_open()){
			std::stringstream ss;
			ss<<file.rdbuf();
			file.close();
			while (ss){
				char buf[100*1024]={};
				ss.get(buf,sizeof(buf));
				SendMessageToClient(buf);
			}
			
			//int record = file.tellg();
			//file.seekg(0,std::ios_base::end);
			//long siz = file.tellg();
			//while (!file.eof())
			//{
			//	file.seekg(record);
			//	std::string st;
			//	st.resize(100*1024);
			//	file.read(const_cast<char*>(st.c_str()),100*1024);
			//	record = file.tellg();
			//	SendMessageToClient(st);
			//}

			//	LogOutStream temp;
			//temp<<a.rdbuf();
			//std::string gg = temp.str();
			//SendMessageToClient(gg);
			//std::cout<<gg<<std::endl;
		}
	}else if(message == "int"){
		std::vector<int> hh;
		hh.push_back(123);
		hh.push_back(456);
		hh.push_back(56);
		int sh[] = {1,5,9};
 		std::ostringstream ss;
 		ss.write((char*)&sh,sizeof(sh));
 		std::string sd = ss.str();
// 		std::string ff = (char*)&sh;
// 
// 		ff.resize(sizeof(sh));
		SendMessageToClient(sd);
	}
	
}

void MyObserver::SendHolePack()
{

}

void MyObserver::SendSplitPack()
{

}

void MyObserver::SendPointPack()
{

}
