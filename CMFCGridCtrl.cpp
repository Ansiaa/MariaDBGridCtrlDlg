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
        pDlg->SetParamsData(Recipe); // 실제 화면 Grid에 데이터 채움
    }
    CGridCtrl::OnLButtonDown(nFlags, point);
  
}
CString CMFCGridCtrl::GetCStringData(UINT nFlags, CPoint point)
{
    //예외처리 필요
    CCellID cell = GetCellFromPt(point, TRUE);
    if (cell != CCellID(-1, -1))
    {
        /*CString str;
        str.Format(_T("클릭된 셀: Row=%d, Col=%d, Text=%s"),
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
