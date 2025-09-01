
// MariaDBGridCtrlDlgDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MariaDBGridCtrlDlg.h"
#include "MariaDBGridCtrlDlgDlg.h"
#include "CCtrlMariaDB.h"
#include ".\GridCtrl.h"
#include <map>
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMariaDBGridCtrlDlgDlg 대화 상자

CMariaDBGridCtrlDlgDlg::CMariaDBGridCtrlDlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MARIADBGRIDCTRLDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMariaDBGridCtrlDlgDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MODEL_GRID, m_ctrlGrid);
    DDX_Control(pDX, IDC_PARAMS_GRID, m_prmGrid);
    DDX_Control(pDX, IDC_DB_GRID, m_dbGrid);
    DDX_Control(pDX, IDC_EDIT_SEARCH, m_EditSearch);
    DDX_Control(pDX, IDC_COMBO1, pCombo);
}

BEGIN_MESSAGE_MAP(CMariaDBGridCtrlDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_DB_CON, &CMariaDBGridCtrlDlgDlg::OnBnClickedDbCon)
    ON_BN_CLICKED(IDC_SEARCH, &CMariaDBGridCtrlDlgDlg::OnBnClickedSearch)
    ON_BN_CLICKED(IDC_DB_SAVE, &CMariaDBGridCtrlDlgDlg::OnBnClickedDbSave)
    ON_BN_CLICKED(IDC_DELETE, &CMariaDBGridCtrlDlgDlg::OnBnClickedDelete)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CMariaDBGridCtrlDlgDlg::OnSelchangeCombo1)
END_MESSAGE_MAP()


// CMariaDBGridCtrlDlgDlg 메시지 처리기

BOOL CMariaDBGridCtrlDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
    InitGrid();
    ComboBoxInit();
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMariaDBGridCtrlDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMariaDBGridCtrlDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMariaDBGridCtrlDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMariaDBGridCtrlDlgDlg::InitGrid()
{
    DBGridInit();
    //ModelGridInit();
    //ParamsGridInit();
 
   //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
}
void CMariaDBGridCtrlDlgDlg::DBGridInit()
{
    if (m_dbGrid.m_hWnd == NULL)
    {
        m_dbGrid.SubclassDlgItem(IDC_DB_GRID, this);
    }
    m_dbGrid.SetEditable(TRUE); // 수정 가능  
    //m_dbGrid.SetListMode(TRUE); //List Mode 설정(Cell 클릭 시 한 줄(Row) 전체 선택)
    m_dbGrid.EnableDragAndDrop(FALSE); // Drag And Drop 기능 비활성화

    // 행/열 설정
    m_dbGrid.SetRowCount(6);
    m_dbGrid.SetColumnCount(ModelColIndex::ModelColMAX);
    m_dbGrid.SetFixedRowCount(1); // 첫 행은 헤더
    m_dbGrid.SetColumnWidth(1, 320);

    m_dbGrid.SetItemText(0, 0, _T("Name"));
    m_dbGrid.SetItemText(0, 1, _T("Value"));

    CCtrlMariaDB::DBSetData DB;
    CString names[] = { _T("DB_HOST"), _T("DB_USER"), _T("DB_PASS"), _T("DB_NAME"), _T("DB_PORT") };
    CString values[] = { DB.DB_HOST, DB.DB_USER, DB.DB_PASS, DB.DB_NAME, DB.DB_PORT };

    int nTargetCol = 0;
    for (int i = 0; i < 5; i++)
    {
        m_dbGrid.SetItemText(i + 1, 0, names[i]);
        m_dbGrid.SetItemText(i + 1, 1, values[i]);

        UINT state = m_dbGrid.GetItemState(i + 1, nTargetCol);
        state |= GVIS_READONLY;
        m_dbGrid.SetItemState(i + 1, nTargetCol, state);
    }
}
void CMariaDBGridCtrlDlgDlg::ModelGridInit()
{
    if (m_ctrlGrid.m_hWnd == NULL)
    {
        m_ctrlGrid.SubclassDlgItem(IDC_MODEL_GRID, this);
    }
    // grid 설정

    m_ctrlGrid.SetEditable(TRUE); // 수정 가능  
    //m_ctrlGrid.SetListMode(TRUE); //List Mode 설정(Cell 클릭 시 한 줄(Row) 전체 선택)
    m_ctrlGrid.EnableDragAndDrop(FALSE); // Drag And Drop 기능 비활성화
    m_ctrlGrid.SetRowCount(1);             // 최소 1행 확보
    m_ctrlGrid.SetFixedRowCount(1);        // <== 헤더 행 만들기
    m_ctrlGrid.SetColumnCount(ModelColIndex::ModelColMAX); // 기본으로 생성할 Column의 개수
    m_ctrlGrid.SetColumnWidth(0, 320);
    m_ctrlGrid.SetColumnWidth(1, 320);

    m_ctrlGrid.SetItemText(0, 0, _T("sRecipeName"));
    m_ctrlGrid.SetItemText(0, 1, _T("sFrontalPattern"));
    // Grid Color Setting
    m_ctrlGrid.SetTextBkColor(RGB(240, 240, 240));   // 기본 Cell 배경색
    //m_ctrlGrid.SetTextColor(RGB(25, 180, 70));       // 기본 Cell 텍스트색
    m_ctrlGrid.SetBkColor(RGB(100, 100, 100));       // 기본 배경색 (TextBkColor에도 영향을 줍니다.)
    //m_ctrlGrid.SetGridColor(RGB(255, 0, 0));         // Grid의 Line 색
}
void CMariaDBGridCtrlDlgDlg::ParamsGridInit()
{
  
    if (m_prmGrid.m_hWnd == NULL)
    {
       m_prmGrid.SubclassDlgItem(IDC_PARAMS_GRID, this);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    m_prmGrid.SetEditable(TRUE);
    //m_prmGrid.SetListMode(TRUE);
  
    m_prmGrid.EnableDragAndDrop(FALSE);

    m_prmGrid.SetRowCount(1);             // 최소 1행 확보
    m_prmGrid.SetFixedRowCount(1);        // <== 헤더 행 만들기
    m_prmGrid.SetColumnCount(ParamsColIndex::ParamsColMAX); // 기본으로 생성할 Column의 개수
    m_prmGrid.SetColumnWidth(1, 220);
    m_prmGrid.SetColumnWidth(4, 220);

    int i = 0;

    m_prmGrid.SetItemText(0, i++, _T("sInspType"));
    m_prmGrid.SetItemText(0, i++, _T("sRecipe"));
    m_prmGrid.SetItemText(0, i++, _T("sPattern"));
    m_prmGrid.SetItemText(0, i++, _T("sSubPattern"));
    m_prmGrid.SetItemText(0, i++, _T("sFilterName"));
    m_prmGrid.SetItemText(0, i++, _T("sFilterType"));
    m_prmGrid.SetItemText(0, i++, _T("bItemUsage"));

    m_prmGrid.SetTextBkColor(RGB(240, 240, 240));   // 기본 Cell 배경색
    //m_prmGrid.SetTextColor(RGB(25, 180, 70));       // 기본 Cell 텍스트색
    m_prmGrid.SetBkColor(RGB(100, 100, 100));       // 기본 배경색 (TextBkColor에도 영향을 줍니다.)
    m_prmGrid.SetGridColor(RGB(255, 0, 0));         // Grid의 Line 색
}
void CMariaDBGridCtrlDlgDlg::ComboBoxInit()
{
    for (int i = ParamsColMAX-1; i > 0; i--)
    {
        pCombo.InsertString(0, comboItems[i]); // 항상 맨 위에 추가
    }

    pCombo.SetCurSel(3);

}
void CMariaDBGridCtrlDlgDlg::OnBnClickedDbCon()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    MariaDB.m_fnInitDB();
    MariaDB.m_fnConnectDB();
    m_ctrlGrid.DeleteAllItems();
    ModelGridInit();
    CString SELECT_query;
    SELECT_query.Format(L"SELECT sRecipeName,sFrontalParam FROM %s.tbl_setmodel;", MariaDB.DB_Setting.DB_NAME);
    
    MariaDB.GetDBData(CT2A(SELECT_query), tbl_setmodel, m_ctrlGrid); 
    MariaDB.m_fnCloseDB();
}
void CMariaDBGridCtrlDlgDlg::SetParamsData(CString sRecipe)
{
    MariaDB.m_fnInitDB();
    MariaDB.m_fnConnectDB();
    ParamsGridInit();
    CString SELECT_query;
    SELECT_query.Format(L"SELECT sInspType, sRecipe, sPattern, sSubPattern, sFilterName, sFilterType, bItemUsage FROM %s.tbl_setparams WHERE sRecipe = '%s' AND sInspType = 'Frontal';", MariaDB.DB_Setting.DB_NAME, sRecipe);

    MariaDB.GetDBData(CT2A(SELECT_query), tbl_setparams, m_prmGrid);
    
}
void CMariaDBGridCtrlDlgDlg::UpDaateParamsData(int nCol, int nRow,CString value)
{
    // nRow, nCol 유효 범위 체크 필요
    if (nRow < 0 || nCol < 0 || nRow >= tbl_setparams.size())
        return;

    CString UPDATE_query;
    nRow -= 1;

    switch (nCol)
    {
    case ParamsColIndex::sInspType:
        UPDATE_query.Format(
            L"UPDATE `oled_ami_it_integrated`.`tbl_setparams` "
            L"SET `sInspType`='%s' "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            value,
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sRecipe:
        UPDATE_query.Format(
            L"UPDATE `oled_ami_it_integrated`.`tbl_setparams` "
            L"SET `sRecipe`='%s' "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            value,
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sPattern:
        UPDATE_query.Format(
            L"UPDATE `oled_ami_it_integrated`.`tbl_setparams` "
            L"SET `sPattern`='%s' "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            value,
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sSubPattern:
        UPDATE_query.Format(
            L"UPDATE `oled_ami_it_integrated`.`tbl_setparams` "
            L"SET `sSubPattern`='%s' "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            value,
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sFilterName:
        UPDATE_query.Format(
            L"UPDATE `oled_ami_it_integrated`.`tbl_setparams` "
            L"SET `sFilterName`='%s' "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            value,
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sFilterType:
        UPDATE_query.Format(
            L"UPDATE `oled_ami_it_integrated`.`tbl_setparams` "
            L"SET `sFilterType`='%s' "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            value,
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::bItemUsage:
        UPDATE_query.Format(
            L"UPDATE `oled_ami_it_integrated`.`tbl_setparams` "
            L"SET `bItemUsage`='%s' "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            value,
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;
    }
    MariaDB.ExecuteNonQuery(CT2A(UPDATE_query));
    
    tbl_setparams.clear();
    SetParamsData(m_ctrlGrid.Recipe);
 
    MariaDB.m_fnCloseDB();
}

void CMariaDBGridCtrlDlgDlg::OnBnClickedDbSave()
{

    m_prmGrid.EndEditing();
    auto m_SaveCell = m_prmGrid.GetEditedCells();
    if (m_SaveCell.empty())
    {
        AfxMessageBox(_T("편집된 셀이 없습니다."));
        return;
    }
    // 모든 편집된 셀 순회
    for (const auto& cell : m_SaveCell)
    {
        int nCol = cell.first.second;
        int nRow = cell.first.first;
        CString value = cell.second;   

       
        UpDaateParamsData(nCol, nRow, value);
    }

}
void CMariaDBGridCtrlDlgDlg::DeleteParamsData(int nCol, int nRow)
{
    // nRow, nCol 유효 범위 체크 필요
    if (nRow < 0 || nCol < 0 || nRow >= tbl_setparams.size())
        return;

    CString DELETE_query;
    nRow -= 1;

    switch (nCol)
    {
    case ParamsColIndex::sInspType:
        DELETE_query.Format(
            L"DELETE FROM `oled_ami_it_integrated`.`tbl_setparams` "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sRecipe:
        DELETE_query.Format(
            L"DELETE FROM `oled_ami_it_integrated`.`tbl_setparams` "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sPattern:
        DELETE_query.Format(
            L"DELETE FROM `oled_ami_it_integrated`.`tbl_setparams` "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sSubPattern:
        DELETE_query.Format(
            L"DELETE FROM `oled_ami_it_integrated`.`tbl_setparams` "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sFilterName:
        DELETE_query.Format(
            L"DELETE FROM `oled_ami_it_integrated`.`tbl_setparams` "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::sFilterType:
        DELETE_query.Format(
            L"DELETE FROM `oled_ami_it_integrated`.`tbl_setparams` "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;

    case ParamsColIndex::bItemUsage:
        DELETE_query.Format(
            L"DELETE FROM `oled_ami_it_integrated`.`tbl_setparams` "
            L"WHERE `sInspType`='%s' AND `sRecipe`='%s' AND `sPattern`='%s' "
            L"AND `sSubPattern`='%s' AND `sFilterName`='%s' AND `sFilterType`='%s';",
            tbl_setparams[nRow][ParamsColIndex::sInspType],
            tbl_setparams[nRow][ParamsColIndex::sRecipe],
            tbl_setparams[nRow][ParamsColIndex::sPattern],
            tbl_setparams[nRow][ParamsColIndex::sSubPattern],
            tbl_setparams[nRow][ParamsColIndex::sFilterName],
            tbl_setparams[nRow][ParamsColIndex::sFilterType]
        );
        break;
    }
    MariaDB.ExecuteNonQuery(CT2A(DELETE_query));
   
    tbl_setparams.clear();
    SetParamsData(m_ctrlGrid.Recipe);

    MariaDB.m_fnCloseDB();
}
void CMariaDBGridCtrlDlgDlg::FindDeleteParamsData(int nCol, int nRow, CString value)
{
    

}
void CMariaDBGridCtrlDlgDlg::OnBnClickedSearch()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    MariaDB.m_fnInitDB();
    MariaDB.m_fnConnectDB();

    m_EditSearch.GetWindowText(m_SearchString);
    CString FILTER_query;
    FILTER_query.Format(L"SELECT sInspType, sRecipe, sPattern, sSubPattern, sFilterName, sFilterType, bItemUsage "
        L"FROM %s.tbl_setparams "
        L"WHERE sRecipe = '%s' AND sInspType = 'Frontal' AND `%s` LIKE '%%%s%%';",
        MariaDB.DB_Setting.DB_NAME, m_ctrlGrid.Recipe, Searchcol, m_SearchString
    );

    tbl_setparams.clear();
    ParamsGridInit();

    MariaDB.GetDBData(CT2A(FILTER_query), tbl_setparams, m_prmGrid);

    MariaDB.m_fnCloseDB();
}

void CMariaDBGridCtrlDlgDlg::OnBnClickedDelete()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
 
    if (m_prmGrid.m_nSelectedRow >= 0)
    {
        DeleteParamsData(m_prmGrid.m_nSelectedCol, m_prmGrid.m_nSelectedRow);
    }
    else
    {
        AfxMessageBox(_T("선택된 셀이 없습니다."));
    }
}


void CMariaDBGridCtrlDlgDlg::OnSelchangeCombo1()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    int Sel = pCombo.GetCurSel(); 
    if (Sel != CB_ERR)
    {
        pCombo.GetLBText(Sel, Searchcol); 
        //AfxMessageBox(_T("선택된 값: ") + Searchcol);
    }
    
}
