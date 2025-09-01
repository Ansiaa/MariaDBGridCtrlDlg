#include "pch.h"
#include "CMFCGridCtrl.h"
#include ".\GridCtrl.h"
#include <MariaDBGridCtrlDlgDlg.h>

BEGIN_MESSAGE_MAP(CMFCGridCtrl, CGridCtrl)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CMFCGridCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    /*
    CString Recipe = GetCStringData(nFlags,point);
    
    CMariaDBGridCtrlDlgDlg* pDlg = dynamic_cast<CMariaDBGridCtrlDlgDlg*>(GetParent());
    if (pDlg)
    {
        pDlg->SetParamsData(Recipe); // 실제 화면 Grid에 데이터 채움
    }
    CGridCtrl::OnLButtonDown(nFlags, point);*/
    // 클릭한 셀 정보
    /*CCellID cell = GetCellFromPt(point, TRUE);

    if (!IsValid(cell))
    {
        CGridCtrl::OnLButtonDown(nFlags, point);
        return;
    }

    // 편집 중이면 데이터 덮어쓰지 않고 클릭만 처리
    if (m_bEditing)
    {
        CGridCtrl::OnLButtonDown(nFlags, point);
        return;
    }

    // 편집 중이 아니면 Recipe 데이터 가져와서 화면에 표시
    CString Recipe = GetCStringData(nFlags, point);

    CMariaDBGridCtrlDlgDlg* pDlg = dynamic_cast<CMariaDBGridCtrlDlgDlg*>(GetParent());
    if (pDlg)
    {
        pDlg->SetParamsData(Recipe); // 클릭 시 정상적으로 데이터 표시
    }

    CGridCtrl::OnLButtonDown(nFlags, point);*/
    // 클릭한 셀 정보
    CCellID cell = GetCellFromPt(point, TRUE);
    if (!IsValid(cell))
    {
        CGridCtrl::OnLButtonDown(nFlags, point);
        return;
    }

    CMariaDBGridCtrlDlgDlg* pDlg = dynamic_cast<CMariaDBGridCtrlDlgDlg*>(GetParent());
    if (pDlg)
    {
        if (this == &(pDlg->m_ctrlGrid)) // m_ctrlGrid에서만 SetParamsData 호출
        {
            if (!m_bEditing)
            {
                Recipe = GetCStringData(nFlags, point);
                pDlg->SetParamsData(Recipe);
            }
        }
        else if (this == &(pDlg->m_prmGrid))
        {
           // pDlg->SetParamsData(Recipe);
            GetIntData(nFlags, point);
        }
    }

    // 항상 마지막에 기본 처리 호출
    CGridCtrl::OnLButtonDown(nFlags, point);
  
}
CString CMFCGridCtrl::GetCStringData(UINT nFlags, CPoint point)
{
    CCellID cell = GetCellFromPt(point, TRUE);

    // 유효하지 않은 셀 체크
    if (!IsValid(cell))
        return _T("");  // 빈 문자열 반환

    // 첫 행(헤더) 클릭 시 제외
    if (cell.row == 0)
        return _T("");

    CGridCellBase* pCell = GetCell(cell.row, 1); // 1열 데이터 가져오기
    if (!pCell)
        return _T("");  // 셀 포인터가 없으면 빈 문자열

    return pCell->GetText(); // 안전하게 값 반환
}
void CMFCGridCtrl::GetIntData(UINT nFlags, CPoint point)
{
    CCellID cell = GetCellFromPt(point, TRUE);

    // 유효하지 않은 셀 체크
    if (!IsValid(cell))
    {
        AfxMessageBox(_T("삭제할 셀이 없습니다."));
        m_nSelectedRow = -1;
        m_nSelectedCol = -1;
        return;
    }
    m_nSelectedRow = cell.row;
    m_nSelectedCol = cell.col;
}
void CMFCGridCtrl::OnEditCell(int nRow, int nCol, CPoint point, UINT nChar)
{
    m_nEditRow = nRow;
    m_nEditCol = nCol;
    m_strOldValue = GetItemText(nRow, nCol);
    m_bEditing = true;

    CGridCtrl::OnEditCell(nRow, nCol, point, nChar);

    /*
    CString msg;
    msg.Format(_T("Editing started: Row=%d, Col=%d"), nRow, nCol);
    AfxMessageBox(msg);*/
}
bool CMFCGridCtrl::GetCellRectFromRowCol(int nRow, int nCol, CRect& rc)
{
    if (nRow < 0 || nRow >= GetRowCount() || nCol < 0 || nCol >= GetColumnCount())
        return false;

    int left = 0;
    for (int c = 0; c < nCol; c++)
        left += GetColumnWidth(c);

    int top = 0;
    for (int r = 0; r < nRow; r++)
        top += GetRowHeight(r);

    rc.left = left;
    rc.top = top;
    rc.right = left + GetColumnWidth(nCol);
    rc.bottom = top + GetRowHeight(nRow);

    return true;
}
void CMFCGridCtrl::OnEndEditCell(int nRow, int nCol, CString str)
{
    m_bEditing = false;
    CGridCtrl::OnEndEditCell(nRow, nCol, str);

    if (str == m_strOldValue)
        return; // 변경 없으면 리턴

    CGridCellBase* pCell = GetCell(nRow, nCol);
    if (!pCell)
        return;

    DWORD fmt = pCell->GetFormat();
    CString msg;

    if (str != m_strOldValue)
    {
        SetItemText(nRow, nCol, str);                    // 그리드에 새 값 반영
        m_editedCells[{nRow, nCol}] = str;              // 편집 기록 저장
    }


    if (fmt & DT_CHECKBOX)
    {
        msg.Format(_T("[CHECK] Row=%d, Col=%d, New=%s"), nRow, nCol, str);
    }
    else if (fmt & DT_EDITCONTROL)
    {
        msg.Format(_T("[EDIT] Row=%d, Col=%d, Old=%s, New=%s"), nRow, nCol, m_strOldValue, str);
    }
    else
    {
        msg.Format(_T("[NORMAL] Row=%d, Col=%d, Old=%s, New=%s"), nRow, nCol, m_strOldValue, str);
    }

    //AfxMessageBox(msg);
    m_strOldValue = str;

    m_bEditing = false;
}

void CMFCGridCtrl::EndEditing()
{
    //CGridCtrl::EndEditing();

    // 강제로 편집 종료 시 할 작업
    //AfxMessageBox(_T("편집 종료됨"));
    if (!m_pEdit)
        return; // 편집 컨트롤이 아예 없으면 그냥 종료

    CString str;
    m_pEdit->GetWindowText(str);

    // 값이 변경된 경우만 기록
    if (m_nEditRow >= 0 && m_nEditCol >= 0)
    {
        OnEndEditCell(m_nEditRow, m_nEditCol, str);
    }

    m_pEdit->DestroyWindow();
    m_pEdit = nullptr;
    m_bEditing = false;
    m_nEditRow = m_nEditCol = -1; // 초기화
}