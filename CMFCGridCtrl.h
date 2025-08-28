#pragma once
#include ".\GridCtrl.h"
class CMFCGridCtrl : public CGridCtrl
{
private:
    
public:
    
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    CString GetCStringData(UINT nFlags, CPoint point);
    DECLARE_MESSAGE_MAP()
};

