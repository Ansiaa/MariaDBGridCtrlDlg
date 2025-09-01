#pragma once
#include "mysql.h"
#include ".\GridCtrl.h"
#include <vector>
#include <map>
#include "CMFCGridCtrl.h"
//#define DB_HOST "127.0.0.1"	// ���� ������
//#define DB_USER "root"	// DB ���Ӱ���
//#define DB_PASS "luken2007"	// DB ������ȣ
//#define DB_NAME "oled_ami_it_integrated"	// DB �̸�
//#define DB_PORT 3306 // DB Port

class CCtrlMariaDB
{
public:

	struct MySql
	{
		MYSQL Conn;             // MySQL ������ ���� ����ü
		MYSQL* ConnPtr = NULL;  // MySQL �ڵ�
		MYSQL_RES* Result;      // ���������� ����� ��� ����ü ������
		MYSQL_ROW Row;          // ���������� ����� ���� ���� ������ ��� ����ü
		int Stat;               // ������û �� ���(����, ����)

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

