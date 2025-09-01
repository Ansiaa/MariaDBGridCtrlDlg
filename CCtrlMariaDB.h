#pragma once
#include "mysql.h"
#include ".\GridCtrl.h"
#include <vector>
#include <map>
#include "CMFCGridCtrl.h"
//#define DB_HOST "127.0.0.1"	// 서버 아이피
//#define DB_USER "root"	// DB 접속계정
//#define DB_PASS "luken2007"	// DB 계정암호
//#define DB_NAME "oled_ami_it_integrated"	// DB 이름
//#define DB_PORT 3306 // DB Port

class CCtrlMariaDB
{
public:

	struct MySql
	{
		MYSQL Conn;             // MySQL 정보를 담을 구조체
		MYSQL* ConnPtr = NULL;  // MySQL 핸들
		MYSQL_RES* Result;      // 쿼리성공시 결과를 담는 구조체 포인터
		MYSQL_ROW Row;          // 쿼리성공시 결과로 나온 행의 정보를 담는 구조체
		int Stat;               // 쿼리요청 후 결과(성공, 실패)

	}DB;

	struct DBSetData
	{
		CString DB_HOST = L"127.0.0.1";
		CString DB_USER = L"User";
		CString DB_PASS = L"Test123123";
		CString DB_NAME = L"oled_ami_it_integrated";
		CString DB_PORT = L"3306";
	}DB_Setting;
public:
	BOOL m_bConnect;
	
public:
	CCtrlMariaDB();
	~CCtrlMariaDB();
	void m_fnInitDB();
	void m_fnConnectDB();
	void m_fnCloseDB();
	void GetDBData(const char* query, std::vector<std::vector<CString>>& DBList, CGridCtrl& m_List);
	void GetDBData(const char* query, std::vector<std::vector<CString>>& DBList, CMFCGridCtrl& m_List);
	void SaveDBData(std::vector<std::vector<CString>>& DBList, int i, int num, CGridCtrl& m_List);
	void SaveDBData(std::vector<std::vector<CString>>& DBList, int i, int num, CMFCGridCtrl& m_List);
	bool ExecuteNonQuery(const char* query);
};

