
// OmokDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Omok.h"
#include "OmokDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CDotSpace.h"

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
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// COmokDlg 대화 상자



COmokDlg::COmokDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OMOK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COmokDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COmokDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_START, &COmokDlg::OnBnClickedButtStart)
	ON_BN_CLICKED(IDC_BUTT_EXIT, &COmokDlg::OnBnClickedButtExit)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// COmokDlg 메시지 처리기

BOOL COmokDlg::OnInitDialog()
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

	CClientDC dc(this);
	m_MemDC.CreateCompatibleDC(&dc);
	m_MemBm.CreateCompatibleBitmap(&dc, 1920, 1080);
	m_MemDC.SelectObject(&m_MemBm);

	m_BoardBm.LoadBitmap(IDB_BOARD);
	m_BoardDC.CreateCompatibleDC(&dc);
	m_BoardDC.SelectObject(&m_BoardBm);

	m_StoneBm.LoadBitmap(IDB_STONE);
	m_StoneDC.CreateCompatibleDC(&dc);
	m_StoneDC.SelectObject(&m_StoneBm);


	m_PlayerTurn = 'B';

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COmokDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COmokDlg::OnPaint()
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
HCURSOR COmokDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void COmokDlg::OnBnClickedButtStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItem(IDC_STATIC_TITLE)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_TITLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_START)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_EXIT)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTT_EXIT)->EnableWindow(FALSE);


	MoveWindow(360, 100, 1200, 900);

	m_LinePen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	m_MemDC.StretchBlt(0, 0, 800, 800, &m_BoardDC, 0, 0, 400, 400, SRCCOPY);

	for (int i = 0, A = 40; i < 19; i++, A += 40)
	{
		m_MemDC.MoveTo(A, 40);
		m_MemDC.LineTo(A, 761);
		m_MemDC.MoveTo(40, A);
		m_MemDC.LineTo(761, A);
		if (i == 3 || i == 9 || i == 15)
		{
			m_MemDC.MoveTo(A, A);
			m_MemDC.LineTo(A, A);
		}
	}

	for (int i = 0, X = 22; i < 19; i++, X += 40)
	{
		for (int j = 0, Y = 22; j < 19; j++, Y += 40)
		{
			m_DotSpace[i][j].Setting(X, Y);
		}
	}
	CClientDC dc(this);

	dc.BitBlt(0, 0, 800, 800, &m_MemDC, 0, 0, SRCCOPY);
}


void COmokDlg::OnBnClickedButtExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}


void COmokDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnTimer(nIDEvent);
}


//BOOL CAboutDlg::PreTranslateMessage(MSG* pMsg)
//{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

//	return CDialogEx::PreTranslateMessage(pMsg);
//}


//void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	m_DotSpace.SetDetermine(point.x, point.y, m_PlayerTurn);
//	if (m_DotSpace.GetDetermine() == m_PlayerTurn)
//	{
//
//	}
//	CDialogEx::OnLButtonDown(nFlags, point);
//}


BOOL COmokDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void COmokDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	char Game = NULL;
	int X = 20;
	int Y = 20;
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			if (m_DotSpace[i][j].Determine(point.x, point.y, m_PlayerTurn))
			{
				X = j;
				Y = i;
				Game = GamePlay(Y, X);
				if (Game == 'F')
				{
					m_DotSpace[i][j].DeleteDetermin();
					MessageBox("33이라 안됨", "알림", NULL);
				}
				else if (m_PlayerTurn == 'B')
				{
					m_PlayerTurn = 'W';
					m_MemDC.SetStretchBltMode(HALFTONE);
					m_MemDC.StretchBlt(m_DotSpace[i][j].GetRect().left, m_DotSpace[i][j].GetRect().top, 36, 36, &m_StoneDC, 1000, 0, 500, 500, SRCAND);
					m_MemDC.StretchBlt(m_DotSpace[i][j].GetRect().left, m_DotSpace[i][j].GetRect().top, 36, 36, &m_StoneDC, 0, 0, 500, 500, SRCPAINT);
				}
				else if (m_PlayerTurn == 'W')
				{
					m_PlayerTurn = 'B';
					m_MemDC.SetStretchBltMode(HALFTONE);
					m_MemDC.StretchBlt(m_DotSpace[i][j].GetRect().left, m_DotSpace[i][j].GetRect().top, 36, 36, &m_StoneDC, 1000, 0, 500, 500, SRCAND);
					m_MemDC.StretchBlt(m_DotSpace[i][j].GetRect().left, m_DotSpace[i][j].GetRect().top, 36, 36, &m_StoneDC, 500, 0, 500, 500, SRCPAINT);
				}
			}
		}
	}

	dc.BitBlt(0, 0, 800, 800, &m_MemDC, 0, 0, SRCCOPY);


	if (Game == 'V')
	{
		if (m_PlayerTurn == 'W')
		{
			KillTimer(1);
			MessageBox("검은돌 승리!", "알림", NULL);
			OnOK();
		}
		else if (m_PlayerTurn == 'B')
		{
			KillTimer(1);
			MessageBox("횐돌 승리!", "알림", NULL);
			OnOK();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

char COmokDlg::GamePlay(int y, int x)
{
	// TODO: 여기에 구현 코드 추가.
	/*
	int eight_position[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };
	int eight_total[8] = { 0 };
	int xx, yy;
	char Color;
	int check = 0;
	for (int i = 0; i < 8; i++)
	{
		yy = y;
		xx = x;
		Color = m_DotSpace[y][x].GetAlive();
		check = 0;
		while (1)
		{
			yy += eight_position[i][0];
			xx += eight_position[i][1];
			if (Color == m_DotSpace[yy][xx].GetAlive())
			{
				eight_total[i] += 1;
			}
			else
				if (check == 0)
					check = 1;
				else
					break;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (eight_total[i] + eight_total[7 - i] == 4)
		{
		}
	}

	*/


	char Game = NULL;
	int StoneCount[8] = { 0 };
	bool Stone3x3[8] = { 0 };
	char Color = m_DotSpace[y][x].GetAlive();
	for (int i = -1, Number = 0; i < 2; i++)
	{
		int Check = 0;
		StoneCount[Number] = 0;
		Stone3x3[Number] = false;
		for (int k = -1; k < 2; k++, Number++)
		{
			if (i == 0 && k == 0)
			{
				Number--;
				continue;
			}
			else
			{
				for (int imsi = 1;; imsi++)
				{
					if (Color == m_DotSpace[y + i * imsi][x + k * imsi].GetAlive() && Check == 0)
					{
						StoneCount[Number] += 1;
					}
					else
					{
						if (Check == 0 && m_DotSpace[y + i * imsi][x + k * imsi].GetAlive() == 'A')
							Check = 1;
						else if (Check == 1)
							Stone3x3[Number] = true;
						else
							break;
					}
				}
			}
		}
	}

	int Count;
	int Rule = 0;
	for (int i = 0; i < 4; i++)
	{
		Count = StoneCount[i] + StoneCount[7 - i];
		if (Count == 4)
		{
			Game = 'V';
			break;
		}
		if (Count == 2 && Stone3x3[i] && Stone3x3[7 - i])
		{
			if (Rule == 0)
				Rule = 1;
			else if (Rule == 1)
				Game = 'F';
			else
				break;
		}
	}
	return Game;
}
