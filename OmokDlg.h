
// OmokDlg.h: 헤더 파일
//

#pragma once
#include "CDotSpace.h"

// COmokDlg 대화 상자
class COmokDlg : public CDialogEx
{
// 생성입니다.
public:
	COmokDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OMOK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtStart();
	afx_msg void OnBnClickedButtExit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private :
	CDC m_MemDC;
	CDC m_BoardDC;
	CDC m_StoneDC;
	CBitmap m_BoardBm;
	CBitmap m_StoneBm;
	CBitmap m_MemBm;
	CPen m_LinePen;
	CPen m_LineDotPen;
	CDotSpace m_DotSpace[19][19];
	char m_PlayerTurn = NULL;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	char GamePlay(int y, int x);
};
