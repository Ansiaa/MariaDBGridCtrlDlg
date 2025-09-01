#include "pch.h"
#include "CCtrlMariaDB.h"
#include "CMFCGridCtrl.h"
#include ".\GridCtrl.h"
#include <atlconv.h>
#include <map>


CCtrlMariaDB::CCtrlMariaDB()
	:m_bConnect(FALSE)
{
	

}

CCtrlMariaDB::~CCtrlMariaDB()
{
}

// MySQL ���� �ʱ�ȭ
void CCtrlMariaDB::m_fnInitDB()
{
	mysql_init(&DB.Conn);
}
void CCtrlMariaDB::m_fnCloseDB()
{
	mysql_free_result(DB.Result);
}
// MYSQL ����
void CCtrlMariaDB::m_fnConnectDB()
{
	// ConnPtr = mysql_real_connect(&Conn, "�����ͺ��̽������ּ�", "root", "��й�ȣ", "�����ҵ����ͺ��̽�", 3306, (char*)NULL, 0);
	DB.ConnPtr = mysql_real_connect(&DB.Conn, CT2A(DB_Setting.DB_HOST), CT2A(DB_Setting.DB_USER), CT2A(DB_Setting.DB_PASS), CT2A(DB_Setting.DB_NAME), _ttoi(DB_Setting.DB_PORT), (char*)NULL, 0);
	if (DB.ConnPtr == NULL)    
	{
		AfxMessageBox(L"ConnectDB X");
	}
	else {
		m_bConnect = TRUE;
	}
}
// 
void CCtrlMariaDB::GetDBData(const char* query, std::vector<std::vector<CString>>& DBList, CGridCtrl& m_List)
{
	DB.Stat = mysql_query(DB.ConnPtr, query);

	if (DB.Stat != 0)
	{
		AfxMessageBox(L"���� ���� ����");
		return;
	}

	DB.Result = mysql_store_result(DB.ConnPtr);

	if (DB.Result == NULL)
	{
		AfxMessageBox(L"��� ����");
		return;
	}

	unsigned int num_fields = mysql_num_fields(DB.Result);
	int rowIndex = 0;

	while ((DB.Row = mysql_fetch_row(DB.Result)) != NULL)
	{
		SaveDBData(DBList, rowIndex, num_fields, m_List);
		rowIndex++;
	}

	// m_fnCloseDB(); 
}
void CCtrlMariaDB::GetDBData(const char* query, std::vector<std::vector<CString>>& DBList, CMFCGridCtrl& m_List)
{
	DB.Stat = mysql_query(DB.ConnPtr, query);

	if (DB.Stat != 0)
	{
		AfxMessageBox(L"���� ���� ����");
		return;
	}

	DB.Result = mysql_store_result(DB.ConnPtr);

	if (DB.Result == NULL)
	{
		AfxMessageBox(L"��� ����");
		return;
	}

	unsigned int num_fields = mysql_num_fields(DB.Result);
	int rowIndex = 0;

	while ((DB.Row = mysql_fetch_row(DB.Result)) != NULL)
	{
		//ASSERT(::IsWindow(m_List.m_hWnd));
		SaveDBData(DBList, rowIndex, num_fields, m_List);
		rowIndex++;
	}

	// m_fnCloseDB(); 
}
void CCtrlMariaDB::SaveDBData(std::vector<std::vector<CString>>& DBList, int rowIndex, int numFields, CGridCtrl& m_List)
{
	if (DBList.size() <= rowIndex)
	{
		DBList.resize(rowIndex + 1);
	}


	for (int colIndex = 0; colIndex < numFields; colIndex++)
	{
		//CString value = (DB.Row[colIndex] != nullptr) ? CString(DB.Row[colIndex]) : L"";
		CString value = CString(DB.Row[colIndex]);
		DBList[rowIndex].push_back(value);

		if (m_List.GetRowCount() <= rowIndex)
			m_List.SetRowCount(rowIndex + 1);
		if (m_List.GetColumnCount() < numFields)
			m_List.SetColumnCount(numFields);


		//m_List.SetItemText(rowIndex, colIndex, value);
		int dataRow = rowIndex + 1; // 0���� ���
		m_List.SetRowCount(max(m_List.GetRowCount(), dataRow + 1));
		m_List.SetItemText(dataRow, colIndex, value);
		
	}
}
void CCtrlMariaDB::SaveDBData(std::vector<std::vector<CString>>& DBList, int rowIndex, int numFields, CMFCGridCtrl& m_List)
{
	
	if (DBList.size() <= rowIndex)
	{
		DBList.resize(rowIndex + 1);
	}


	for (int colIndex = 0; colIndex < numFields; colIndex++)
	{
		//CString value = (DB.Row[colIndex] != nullptr) ? CString(DB.Row[colIndex]) : L"";
		CString value = CString(DB.Row[colIndex]);
		DBList[rowIndex].push_back(value);

		if (m_List.GetRowCount() <= rowIndex)
			m_List.SetRowCount(rowIndex + 1);
		if (m_List.GetColumnCount() < numFields)
			m_List.SetColumnCount(numFields);

		//m_List.SetItemText(rowIndex, colIndex, value);
		int dataRow = rowIndex + 1; // 0���� ���
		m_List.SetRowCount(max(m_List.GetRowCount(), dataRow + 1));
		m_List.SetItemText(dataRow, colIndex, value);
		// -------------------------------
	 
		// �̹� ������ ������ Ȯ��
		/*
		auto editedIt = m_List.m_editedCells.find({ dataRow, colIndex });
		if (editedIt == m_List.m_editedCells.end())
		{
			// ������ ���� �ƴϸ� DB ������ ����
			m_List.SetItemText(dataRow, colIndex, value);
		}
		else
		{
			// ������ ���� ���� ������ ����
			m_List.SetItemText(dataRow, colIndex, editedIt->second);
		}*/
	}
}
bool CCtrlMariaDB::ExecuteNonQuery(const char* query)
{
	if (mysql_query(DB.ConnPtr, query) != 0)
	{
		CString msg;
		msg.Format(L"���� ���� ����: %S", mysql_error(DB.ConnPtr));
		AfxMessageBox(msg);
		return false;
	}

	// UPDATE/DELETE/INSERT �� ��� ���� ����
	my_ulonglong affected = mysql_affected_rows(DB.ConnPtr);

	CString msg;
	msg.Format(L"%llu ���� ����Ǿ����ϴ�.", affected);
	AfxMessageBox(msg);

	return (affected > 0);
}
