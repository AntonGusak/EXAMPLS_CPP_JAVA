
// ProgramDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Program.h"
#include "ProgramDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>

using namespace std;

fstream inf, otf;
string ms, t;
int k;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CProgramDlg dialog

CProgramDlg::CProgramDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PROGRAM_DIALOG, pParent)
	, A(_T("OS_W.txt"))
	, B(_T("sol.txt"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgramDlg::DoDataExchange(CDataExchange* pDX)
{
	SetWindowTextW(L"Обробка даних у файлах. ");

	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, A);
	DDX_Text(pDX, IDC_EDIT2, B);
}

BEGIN_MESSAGE_MAP(CProgramDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProgramDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CProgramDlg message handlers

BOOL CProgramDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProgramDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProgramDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CProgramDlg::OnBnClickedButton1()
{
	CString temp;
	
	UpdateData(true);
	ms = A;
	t = B;
	UpdateData(false);
	
	ShellExecute(m_hWnd, L"open", ms, NULL, NULL, SW_SHOWDEFAULT);

	CStdioFile inf(ms, CFile::modeRead);
	CStdioFile otf(t, CFile::modeCreate | CFile::modeWrite);

	while (inf.ReadString(z))
	{
		for (k = z.GetLength() - 1; k >= 0; k--)
		{
			temp += z[k];
		}
		temp += "\n";
	}
	otf.WriteString(temp);
	otf.Flush();
	otf.Close();
	
	inf.Close();

	ShellExecute(m_hWnd, L"open", t, NULL, NULL, SW_SHOWDEFAULT);
}
