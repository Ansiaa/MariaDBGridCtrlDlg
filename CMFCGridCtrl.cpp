#include "pch.h"
#include "CMFCGridCtrl.h"
#include ".\GridCtrl.h"
#include <MariaDBGridCtrlDlgDlg.h>

BEGIN_MESSAGE_MAP(CMFCGridCtrl, CGridCtrl)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CMFCGridCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
    
    CString Recipe = GetCStringData(nFlags,point);
    
    CMariaDBGridCtrlDlgDlg* pDlg = dynamic_cast<CMariaDBGridCtrlDlgDlg*>(GetParent());
    if (pDlg)
    {
        pDlg->SetParamsData(Recipe); // ���� ȭ�� Grid�� ������ ä��
    }
    CGridCtrl::OnLButtonDown(nFlags, point);
  
}
CString CMFCGridCtrl::GetCStringData(UINT nFlags, CPoint point)
{
    //����ó�� �ʿ�
    CCellID cell = GetCellFromPt(point, TRUE);
    if (cell != CCellID(-1, -1))
    {
        /*CString str;
        str.Format(_T("Ŭ���� ��: Row=%d, Col=%d, Text=%s"),
            cell.row, cell.col,
            GetCell(cell.row,1)->GetText());
        AfxMessageBox(str);*/
        CString Text;
        Text = GetCell(cell.row, 1)->GetText();
        return Text;
       // vector.tbl_setmodel
    }
    else {
        return 0;
    }
}
