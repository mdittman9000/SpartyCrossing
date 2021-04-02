
// ChildView.h : interface of the CChildView class
//


#pragma once

#include "Game.h"
#include "Item.h"


#include <memory>

/// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

private:
	/// Game object being played
	CGame mGame;

	/// Any cargo we currently clicked
	CCargo* mClickedCargo;

	/// True until the first time we draw
	bool mFirstDraw = true;

	long long mLastTime = 0;	///< Last time we read the timer
	double mTimeFreq = 0;		///< Rate the timer updates

// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

public:
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLevelmenuLevel0();
	afx_msg void OnLevelmenuLevel1();
	afx_msg void OnLevelmenuLevel2();
	afx_msg void OnLevelmenuLevel3();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCheatmenuRoadcheat();
	afx_msg void OnCheatmenuRivercheat();
};

