
// PlanimetriaDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CPlanimetriaDlg dialog
class CPlanimetriaDlg : public CDialog
{
// Construction
public:
	CPlanimetriaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLANIMETRIA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:

	CBitmap pic, pic1, pic2, pic3, pic4;
	CRect rc, w, w1, w2, w3, w4;

	int p;


public:
	CStatic mpic1;
	CStatic mpic2;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
