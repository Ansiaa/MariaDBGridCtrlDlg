#pragma once
#include ".\GridCtrl.h"
#define DT_CHECKBOX 0x0001
#include <map>

class CMFCGridCtrl : public CGridCtrl
{
private:
    CString m_strOldValue;


    CEdit* m_pEdit = nullptr;
public:
    int m_nSelectedRow = -1;
    int m_nSelectedCol = -1;
    int m_nEditRow = -1;
    int m_nEditCol = -1;
    bool m_bEditing = false;
    void OnEditCell(int nRow, int nCol, CPoint point, UINT nChar) override;
    void OnEndEditCell(int nRow, int nCol, CString str) override;
    
    void EndEditing() override;
    std::map<std::pair<int, int>, CString> m_editedCells;
    CString Recipe;
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    CString GetCStringData(UINT nFlags, CPoint point);
    void GetIntData(UINT nFlags, CPoint point);
    bool GetCellRectFromRowCol(int nRow, int nCol, CRect& rc);
    const std::map<std::pair<int, int>, CString>& GetEditedCells() const { return m_editedCells; }
    DECLARE_MESSAGE_MAP()
};

