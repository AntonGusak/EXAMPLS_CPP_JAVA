
// TestInfoDayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestInfoDay.h"
#include "TestInfoDayDlg.h"
#include "afxdialogex.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestInfoDayDlg dialog



CTestInfoDayDlg::CTestInfoDayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TESTINFODAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestInfoDayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	fg = true;
	SetWindowTextW(L"Дата народження - Характерне число");

	setlocale(LC_ALL, "rus");
	CStdioFile inf(L"reztest.txt", CFile::modeRead);
	if (!inf) return;
	for (k = 0; k < 9; k++)
	{
		inf.ReadString(EN[k].Numb);
		inf.ReadString(EN[k].Ops);
		inf.ReadString(EN[k].Str1);
		inf.ReadString(EN[k].Str2);
		inf.ReadString(EN[k].Str3);
		inf.ReadString(EN[k].Str4);
	}
	inf.Close();

	for (p = 0; p < 9; p++)
	{
		for (j = 0; j < 5; j++)
		{
			TAB[p][j] = 0;
		}
	}

	k = 1;
	for (p = 0; p < 9; p++)
	{
		for (j = 0; j < 5; j++)
		{
			if (j < 5 && k + 9 * j<32)
			{
				TAB[p][j] = k + 9 * j;
			}
			else
			{
				TAB[p][j] = 0;
			}
		}
		k++;
	}



}

BEGIN_MESSAGE_MAP(CTestInfoDayDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CTestInfoDayDlg message handlers

BOOL CTestInfoDayDlg::OnInitDialog()
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

void CTestInfoDayDlg::OnPaint()
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
		
		CClientDC dc(this);
		GetClientRect(&rc);

		dc.FillSolidRect(&rc, 0x00D5EFFF);

		RH = abs(rc.left - rc.right);
		RW = abs(rc.top - rc.bottom);
		dx = RH / 5;
		dy = RW / 9;
		p = 0;
		for (k = 0; k < 9; k++)
		{
			j = 0;
			for (i = 0; i < 5; i++)
			{
				w.top = k * dy;
				w.bottom = (k + 1)*dy;
				w.left = i * dx;
				w.right = (i + 1)*dx;

				kw[p][j] = w;
				j++;
			}
			p++;
		}
		

		for (p = 0; p < 9; p++)
		{
			for (j = 0; j < 5; j++)
			{
				if (j<4)
					cf = 0x00BEFFC6;
				else
					cf = 0x00D5B281;
				m = CreateSolidBrush(cf);
				oldm = (HBRUSH)dc.SelectObject(m);
				dc.FillSolidRect(&kw[p][j], cf);
				DeleteObject(m);
				SelectObject(dc, oldm);
			}
		}

		x1 = kw[0][0].left;
		y1 = kw[0][0].top;
		x2 = kw[8][4].right;
		y2 = kw[8][4].bottom;

		cf = 0x00800080;
		hPenOxy = CreatePen(PS_SOLID, 3, cf);
		hOldPen = (HPEN)SelectObject(dc, hPenOxy);

		for (k = 0; k < 9; k++)
		{
			if (k < 5)
			{
				dc.MoveTo(x1 + k * dx, y1);
				dc.LineTo(x1 + k * dx, y2);
			}
			dc.MoveTo(x1, y1 + k * dy);
			dc.LineTo(x2, y1 + k * dy);
		}

		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y1);
		dc.LineTo(x2, y2);
		dc.LineTo(x1, y2);
		dc.LineTo(x1, y1);

		SelectObject(dc, hOldPen);
		DeleteObject(hPenOxy);


		hbk = (HFONT)::GetStockObject(SYSTEM_FONT);
		hNew = CreateFont(44, 0, 0, 0,
			FW_BOLD,
			0, 0, 0,
			ANSI_CHARSET,
			OUT_DEFAULT_PRECIS,
			CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			L"Trebuchet Ms");
		hold = (HFONT)SelectObject(dc, hNew);

		x1 = kw[0][0].left;
		y1 = kw[0][0].top;

		k = 1; i = 1;
		for (p = 0; p < 5; p++)
		{
			for (j = 0; j < 9; j++)
			{
				if (k < 32)
				{
					dc.SetTextColor(0x00D5B281);
					dc.SetBkColor(0x00BEFFC6);
					t.Format(L"%i", k);
					dc.TextOutW(x1 + p * dx + dx / 3, y1 + j * dy + dy / 5, t, t.GetLength());
				}
				if (k > 36)
				{
					dc.SetTextColor(0x00BEFFC6);
					dc.SetBkColor(0x00D5B281);
					t.Format(L"%i", i);
					dc.TextOutW(x1 + p * dx + dx / 3, y1 + j * dy + dy / 5, t, t.GetLength());
					i++;
				}
				k++;
			}
		}

		hold = (HFONT)SelectObject(dc, hbk);




		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestInfoDayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestInfoDayDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	GetClientRect(&rc);

	//dc.FillSolidRect(&rc, 0x00D5EFFF);

	RH = abs(rc.left - rc.right);
	RW = abs(rc.top - rc.bottom);
	dx = RH / 5;
	dy = RW / 9;
	p = 0;
	for (k = 0; k < 9; k++)
	{
		j = 0;
		for (i = 0; i < 5; i++)
		{
			w.top = k * dy;
			w.bottom = (k + 1)*dy;
			w.left = i * dx;
			w.right = (i + 1)*dx;

			kw[p][j] = w;
			j++;
		}
		p++;
	}

	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < 4; i++)
		{
			if (PtInRect(&kw[k][i], point))
			{
				pfix = k; jfix = i;
			}
		}
	}

	x1 = kw[pfix][jfix].left;
	y1 = kw[pfix][jfix].top;
	x2 = kw[pfix][jfix].right;
	y2 = kw[pfix][jfix].bottom;


	w.left = kw[pfix][jfix].left + 7;
	w.top = kw[pfix][jfix].top + 7;
	w.right = kw[pfix][jfix].right - 7;
	w.bottom = kw[pfix][jfix].bottom - 7;

	if (PtInRect(&w, point))
	{
		ckw = 0x004763FD;
		hPenOxy = CreatePen(PS_SOLID, 3, ckw);
		hOldPen = (HPEN)SelectObject(dc, hPenOxy);

		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y1);
		dc.LineTo(x2, y2);
		dc.LineTo(x1, y2);
		dc.LineTo(x1, y1);

		SelectObject(dc, hOldPen);
		DeleteObject(hPenOxy);
	}
	else
	{
		ckw = 0x00800080;
		hPenOxy = CreatePen(PS_SOLID, 3, ckw);
		hOldPen = (HPEN)SelectObject(dc, hPenOxy);

		dc.MoveTo(x1, y1);
		dc.LineTo(x2, y1);
		dc.LineTo(x2, y2);
		dc.LineTo(x1, y2);
		dc.LineTo(x1, y1);

		SelectObject(dc, hOldPen);
		DeleteObject(hPenOxy);
	}

	CDialog::OnMouseMove(nFlags, point);
}


void CTestInfoDayDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	GetClientRect(&rc);

	dc.FillSolidRect(&rc, 0x00D5EFFF);

	RH = abs(rc.left - rc.right);
	RW = abs(rc.top - rc.bottom);
	dx = RH / 5;
	dy = RW / 9;
	p = 0;
	for (k = 0; k < 9; k++)
	{
		j = 0;
		for (i = 0; i < 5; i++)
		{
			w.top = k * dy;
			w.bottom = (k + 1)*dy;
			w.left = i * dx;
			w.right = (i + 1)*dx;

			kw[p][j] = w;
			j++;
		}
		p++;
	}


	for (p = 0; p < 9; p++)
	{
		for (j = 0; j < 5; j++)
		{
			if (j<4)
				cf = 0x00BEFFC6;
			else
				cf = 0x00D5B281;
			m = CreateSolidBrush(cf);
			oldm = (HBRUSH)dc.SelectObject(m);
			dc.FillSolidRect(&kw[p][j], cf);
			DeleteObject(m);
			SelectObject(dc, oldm);
		}
	}

	x1 = kw[0][0].left;
	y1 = kw[0][0].top;
	x2 = kw[8][4].right;
	y2 = kw[8][4].bottom;

	cf = 0x00800080;
	hPenOxy = CreatePen(PS_SOLID, 3, cf);
	hOldPen = (HPEN)SelectObject(dc, hPenOxy);

	for (k = 0; k < 9; k++)
	{
		if (k < 5)
		{
			dc.MoveTo(x1 + k * dx, y1);
			dc.LineTo(x1 + k * dx, y2);
		}
		dc.MoveTo(x1, y1 + k * dy);
		dc.LineTo(x2, y1 + k * dy);
	}

	dc.MoveTo(x1, y1);
	dc.LineTo(x2, y1);
	dc.LineTo(x2, y2);
	dc.LineTo(x1, y2);
	dc.LineTo(x1, y1);

	SelectObject(dc, hOldPen);
	DeleteObject(hPenOxy);


	hbk = (HFONT)::GetStockObject(SYSTEM_FONT);
	hNew = CreateFont(44, 0, 0, 0,
		FW_BOLD,
		0, 0, 0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Trebuchet Ms");
	hold = (HFONT)SelectObject(dc, hNew);

	x1 = kw[0][0].left;
	y1 = kw[0][0].top;

	k = 1; i = 1;
	for (p = 0; p < 5; p++)
	{
		for (j = 0; j < 9; j++)
		{
			if (k < 32)
			{
				dc.SetTextColor(0x00D5B281);
				dc.SetBkColor(0x00BEFFC6);
				t.Format(L"%i", k);
				dc.TextOutW(x1 + p * dx + dx / 3, y1 + j * dy + dy / 5, t, t.GetLength());
			}
			if (k > 36)
			{
				dc.SetTextColor(0x00BEFFC6);
				dc.SetBkColor(0x00D5B281);
				t.Format(L"%i", i);
				dc.TextOutW(x1 + p * dx + dx / 3, y1 + j * dy + dy / 5, t, t.GetLength());
				i++;
			}
			k++;
		}
	}

	hold = (HFONT)SelectObject(dc, hbk);


	for (k = 0; k < 9; k++)
	{
		for (i = 0; i < 4; i++)
		{
			if (PtInRect(&kw[k][i], point))
			{
				pfix = k; jfix = i;
			}
		}
	}

	w.left = kw[pfix][jfix].left + 7;
	w.top = kw[pfix][jfix].top + 7;
	w.right = kw[pfix][jfix].right - 7;
	w.bottom = kw[pfix][jfix].bottom - 7;

	if (PtInRect(&w, point))
	{
		if (TAB[pfix][jfix] > 0)
		{
			//t.Format(L"Натиснуто %i", TAB[pfix][jfix]);

			t.Empty();
			ms.Empty();
			switch (TAB[pfix][jfix])
			{
			case 1:
				ms = EN[0].Numb;
				ms += "\n";
				ms += EN[0].Ops;
				ms += "\n";
				ms += EN[0].Str1;
			break;
			case 10:
				ms = EN[0].Numb;
				ms += "\n";
				ms += EN[0].Ops;
				ms += "\n";
				ms += EN[0].Str2;
				break;
			case 19:
				ms = EN[0].Numb;
				ms += "\n";
				ms += EN[0].Ops;
				ms += "\n";
				ms += EN[0].Str3;
				break;
			case 28:
				ms = EN[0].Numb;
				ms += "\n";
				ms += EN[0].Ops;
				ms += "\n";
				ms += EN[0].Str4;
				break;



			case 2:
				ms = EN[1].Numb;
				ms += "\n";
				ms += EN[1].Ops;
				ms += "\n";
				ms += EN[1].Str1;
				break;
			case 11:
				ms = EN[1].Numb;
				ms += "\n";
				ms += EN[1].Ops;
				ms += "\n";
				ms += EN[1].Str2;
				break;
			case 20:
				ms = EN[1].Numb;
				ms += "\n";
				ms += EN[1].Ops;
				ms += "\n";
				ms += EN[1].Str3;
				break;
			case 29:
				ms = EN[1].Numb;
				ms += "\n";
				ms += EN[1].Ops;
				ms += "\n";
				ms += EN[1].Str4;
				break;


			case 3:
				ms = EN[2].Numb;
				ms += "\n";
				ms += EN[2].Ops;
				ms += "\n";
				ms += EN[2].Str1;
				break;
			case 12:
				ms = EN[2].Numb;
				ms += "\n";
				ms += EN[2].Ops;
				ms += "\n";
				ms += EN[2].Str2;
				break;
			case 21:
				ms = EN[2].Numb;
				ms += "\n";
				ms += EN[2].Ops;
				ms += "\n";
				ms += EN[2].Str3;
				break;
			case 30:
				ms = EN[2].Numb;
				ms += "\n";
				ms += EN[2].Ops;
				ms += "\n";
				ms += EN[2].Str4;
				break;



			case 4:
				ms = EN[3].Numb;
				ms += "\n";
				ms += EN[3].Ops;
				ms += "\n";
				ms += EN[3].Str1;
				break;
			case 13:
				ms = EN[3].Numb;
				ms += "\n";
				ms += EN[3].Ops;
				ms += "\n";
				ms += EN[3].Str2;
				break;
			case 22:
				ms = EN[3].Numb;
				ms += "\n";
				ms += EN[3].Ops;
				ms += "\n";
				ms += EN[3].Str3;
				break;
			case 31:
				ms = EN[3].Numb;
				ms += "\n";
				ms += EN[3].Ops;
				ms += "\n";
				ms += EN[3].Str4;
				break;


			case 5:
				ms = EN[4].Numb;
				ms += "\n";
				ms += EN[4].Ops;
				ms += "\n";
				ms += EN[4].Str1;
				break;
			case 14:
				ms = EN[4].Numb;
				ms += "\n";
				ms += EN[4].Ops;
				ms += "\n";
				ms += EN[4].Str2;
				break;
			case 23:
				ms = EN[4].Numb;
				ms += "\n";
				ms += EN[4].Ops;
				ms += "\n";
				ms += EN[4].Str3;
				break;

			case 6:
				ms = EN[5].Numb;
				ms += "\n";
				ms += EN[5].Ops;
				ms += "\n";
				ms += EN[5].Str1;
				break;
			case 15:
				ms = EN[5].Numb;
				ms += "\n";
				ms += EN[5].Ops;
				ms += "\n";
				ms += EN[5].Str2;
				break;
			case 24:
				ms = EN[5].Numb;
				ms += "\n";
				ms += EN[5].Ops;
				ms += "\n";
				ms += EN[5].Str3;
				break;

			case 7:
				ms = EN[6].Numb;
				ms += "\n";
				ms += EN[6].Ops;
				ms += "\n";
				ms += EN[6].Str1;
				break;
			case 16:
				ms = EN[6].Numb;
				ms += "\n";
				ms += EN[6].Ops;
				ms += "\n";
				ms += EN[6].Str2;
				break;
			case 25:
				ms = EN[6].Numb;
				ms += "\n";
				ms += EN[6].Ops;
				ms += "\n";
				ms += EN[6].Str3;
				break;

			case 8:
				ms = EN[7].Numb;
				ms += "\n";
				ms += EN[7].Ops;
				ms += "\n";
				ms += EN[7].Str1;
				break;
			case 17:
				ms = EN[7].Numb;
				ms += "\n";
				ms += EN[7].Ops;
				ms += "\n";
				ms += EN[7].Str2;
				break;
			case 26:
				ms = EN[7].Numb;
				ms += "\n";
				ms += EN[7].Ops;
				ms += "\n";
				ms += EN[7].Str3;
				break;

			case 9:
				ms = EN[8].Numb;
				ms += "\n";
				ms += EN[8].Ops;
				ms += "\n";
				ms += EN[8].Str1;
				break;
			case 18:
				ms = EN[8].Numb;
				ms += "\n";
				ms += EN[8].Ops;
				ms += "\n";
				ms += EN[8].Str2;
				break;
			case 27:
				ms = EN[8].Numb;
				ms += "\n";
				ms += EN[8].Ops;
				ms += "\n";
				ms += EN[8].Str3;
				break;

			}

			t += ms;
			

			MessageBox(t, L"На сьогодні Вами обрано", MB_OK | MB_ICONINFORMATION);

		}
		else
		{
			t.Format(L"Тут порожньо!");
			MessageBox(t, L"На сьогодні Вами обрано", MB_OK | MB_ICONINFORMATION);
		}
	}


	CDialog::OnLButtonDown(nFlags, point);
}
