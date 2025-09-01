
// MariaDBGridCtrlDlgDlg.h: 헤더 파일
//

#pragma once
#include <vector>
#include <map>
#include "CMFCGridCtrl.h"
#include "CCtrlMariaDB.h"


// CMariaDBGridCtrlDlgDlg 대화 상자
class CMariaDBGridCtrlDlgDlg : public CDialogEx
{
// 생성입니다.
public:
	CMariaDBGridCtrlDlgDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MARIADBGRIDCTRLDLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	enum ModelColIndex
	{
		sRecipeName,      
		sFrontalPattern,    
		ModelColMAX
	};

	enum ParamsColIndex
	{
		sInspType,
		sRecipe,
		sPattern,
		sSubPattern,
		sFilterName,
		sFilterType,
		bItemUsage,
		ParamsColMAX
	};

	CString comboItems[ParamsColMAX] = {
		_T("sInspType"),
		_T("sRecipe"),
		_T("sPattern"),
		_T("sSubPattern"),
		_T("sFilterName"),
		_T("sFilterType"),
		_T("bItemUsage")
	};
	CGridCtrl m_dbGrid;
	CMFCGridCtrl m_ctrlGrid;
	CMFCGridCtrl m_prmGrid;

	CString m_SearchString;
	CString Searchcol = _T("sFilterName");
	std::vector<std::vector<CString>> tbl_setmodel;
	std::vector<std::vector<CString>> tbl_setparams;

	CCtrlMariaDB MariaDB;
	CGridCtrl GridCtrl;
	CMFCGridCtrl MFCGridCtrl;

	std::map<std::pair<int, int>, CString>& m_SaveCell = m_ctrlGrid.m_editedCells;

	void InitGrid();
	void DBGridInit();
	void ModelGridInit();
	void ParamsGridInit();
	void ComboBoxInit();

	void SetParamsData(CString sRecipe);
	void UpDaateParamsData(int nCol, int nRow, CString value);
	void DeleteParamsData(int nCol, int nRow);
	void FindDeleteParamsData(int nCol, int nRow, CString value);
	afx_msg void OnBnClickedDbCon();
	CEdit m_EditSearch;
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedDbSave();
	afx_msg void OnBnClickedDelete();
	CComboBox pCombo;
	afx_msg void OnSelchangeCombo1();
};
