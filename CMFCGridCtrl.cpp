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
        pDlg->SetParamsData(Recipe); // ���� ȭ�� Grid�� ������ ä��
    }
    CGridCtrl::OnLButtonDown(nFlags, point);*/
    // Ŭ���� �� ����
    /*CCellID cell = GetCellFromPt(point, TRUE);

    if (!IsValid(cell))
    {
        CGridCtrl::OnLButtonDown(nFlags, point);
        return;
    }

    // ���� ���̸� ������ ����� �ʰ� Ŭ���� ó��
    if (m_bEditing)
    {
        CGridCtrl::OnLButtonDown(nFlags, point);
        return;
    }

    // ���� ���� �ƴϸ� Recipe ������ �����ͼ� ȭ�鿡 ǥ��
    CString Recipe = GetCStringData(nFlags, point);

    CMariaDBGridCtrlDlgDlg* pDlg = dynamic_cast<CMariaDBGridCtrlDlgDlg*>(GetParent());
    if (pDlg)
    {
        pDlg->SetParamsData(Recipe); // Ŭ�� �� ���������� ������ ǥ��
    }

    CGridCtrl::OnLButtonDown(nFlags, point);*/
    // Ŭ���� �� ����
    CCellID cell = GetCellFromPt(point, TRUE);
    if (!IsValid(cell))
    {
        CGridCtrl::OnLButtonDown(nFlags, point);
        return;
    }

    CMariaDBGridCtrlDlgDlg* pDlg = dynamic_cast<CMariaDBGridCtrlDlgDlg*>(GetParent());
    if (pDlg)
    {
        if (this == &(pDlg->m_ctrlGrid)) // m_ctrlGrid������ SetParamsData ȣ��
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

    // �׻� �������� �⺻ ó�� ȣ��
    CGridCtrl::OnLButtonDown(nFlags, point);
  
}
CString CMFCGridCtrl::GetCStringData(UINT nFlags, CPoint point)
{
    CCellID cell = GetCellFromPt(point, TRUE);

    // ��ȿ���� ���� �� üũ
    if (!IsValid(cell))
        return _T("");  // �� ���ڿ� ��ȯ

    // ù ��(���) Ŭ�� �� ����
    if (cell.row == 0)
        return _T("");

    CGridCellBase* pCell = GetCell(cell.row, 1); // 1�� ������ ��������
    if (!pCell)
        return _T("");  // �� �����Ͱ� ������ �� ���ڿ�

    return pCell->GetText(); // �����ϰ� �� ��ȯ
}
void CMFCGridCtrl::GetIntData(UINT nFlags, CPoint point)
{
    CCellID cell = GetCellFromPt(point, TRUE);

    // ��ȿ���� ���� �� üũ
    if (!IsValid(cell))
    {
        AfxMessageBox(_T("������ ���� �����ϴ�."));
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
        return; // ���� ������ ����

    CGridCellBase* pCell = GetCell(nRow, nCol);
    if (!pCell)
        return;

    DWORD fmt = pCell->GetFormat();
    CString msg;

    if (str != m_strOldValue)
    {
        SetItemText(nRow, nCol, str);                    // �׸��忡 �� �� �ݿ�
        m_editedCells[{nRow, nCol}] = str;              // ���� ��� ����
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

    // ������ ���� ���� �� �� �۾�
    //AfxMessageBox(_T("���� �����"));
    if (!m_pEdit)
        return; // ���� ��Ʈ���� �ƿ� ������ �׳� ����

    CString str;
    m_pEdit->GetWindowText(str);

    // ���� ����� ��츸 ���
    if (m_nEditRow >= 0 && m_nEditCol >= 0)
    {
        OnEndEditCell(m_nEditRow, m_nEditCol, str);
    }

    m_pEdit->DestroyWindow();
    m_pEdit = nullptr;
    m_bEditing = false;
    m_nEditRow = m_nEditCol = -1; // �ʱ�ȭ
}