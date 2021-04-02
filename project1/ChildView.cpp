
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "project1.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "Level.h"


using namespace std;
using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Maximum amount of time to allow for elapsed
const double MaxElapsed = 0.050;

/**
 * Constructor
 */
CChildView::CChildView()
{
	srand((unsigned int)time(nullptr));
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_LEVELMENU_LEVEL0, &CChildView::OnLevelmenuLevel0)
	ON_COMMAND(ID_LEVELMENU_LEVEL1, &CChildView::OnLevelmenuLevel1)
	ON_COMMAND(ID_LEVELMENU_LEVEL2, &CChildView::OnLevelmenuLevel2)
	ON_COMMAND(ID_LEVELMENU_LEVEL3, &CChildView::OnLevelmenuLevel3)
	ON_WM_TIMER()
	ON_COMMAND(ID_CHEATMENU_ROADCHEAT, &CChildView::OnCheatmenuRoadcheat)
	ON_COMMAND(ID_CHEATMENU_RIVERCHEAT, &CChildView::OnCheatmenuRivercheat)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

/**
 * This function is called to draw in the window.
 *
 * This function is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 */
void CChildView::OnPaint() 
{
	CPaintDC paintDC(this);
	CDoubleBufferDC dc(&paintDC); // device context for painting

	Graphics graphics(dc.m_hDC);	// change paintDC back to dc once CDoubleBufferDC is implemented (to prevent flashing)

	CRect rect;
	GetClientRect(&rect);
	
	mGame.OnDraw(&graphics, rect.Width(), rect.Height());

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		 * Initialize the elapsed time system
		 */
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);

		wstring pathName = L".\\levels\\level";
		// Loads levels 0-3 and adds them to levels vector
		for (int i = 0; i < 4; i++)
		{
			wstring filename = pathName + to_wstring(i) + L".xml";
			shared_ptr<CLevel> levelPtr = make_shared<CLevel>(&mGame);
			levelPtr->Load(filename);
			mGame.Add(levelPtr);
		}
		// Load level 0 from level vector
		mGame.Load(1);
		Invalidate();
	}

	/*
	 * Compute the elapsed time since the last draw
	 */
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	// Prevent tunnelling
	while (elapsed > MaxElapsed)
	{
		mGame.Update(MaxElapsed);
		mGame.UpdateControlPanel(MaxElapsed);
		//mGame.CollisionTest()

		elapsed -= MaxElapsed;
	}

	// Consume any remaining time
	if (elapsed > 0)
	{
		mGame.Update(elapsed);
		mGame.UpdateControlPanel(elapsed);
	}
}


/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}


/**
 * Handle a click on the game area
 * \param nFlags Flags
 * \param point Position on the screen that was clicked
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	std::pair<double, double> coords = mGame.ScaleCoords(point.x, point.y);

	mClickedCargo = mGame.HitTest(coords.first, coords.second);

	if ((mClickedCargo != nullptr) && !mGame.GetReady())
	{
		if (mClickedCargo->GetCarryStatus())
		{
				mClickedCargo->Release();
		}
		else
		{
				mClickedCargo->PickUp();
		}

	}
}


/**
 * Handle a key press.
 * \param nChar Character that was pressed
 * \param nRepCnt Repeat count
 * \param nFlags Flags
 */
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// Move the hero
	mGame.moveHero(nChar);

}

/**
 * Menu handler for loading level 0
 */
void CChildView::OnLevelmenuLevel0()
{
	mGame.Load(0);
	Invalidate();
}

/**
 * Menu handler for loading level 1
 */
void CChildView::OnLevelmenuLevel1()
{
	// TODO: Add your command handler code here
	mGame.Load(1);
	Invalidate();
}

/**
 * Menu handler for loading level 2
 */
void CChildView::OnLevelmenuLevel2()
{
	// TODO: Add your command handler code here
	mGame.Load(2);
	Invalidate();
}

/**
 * Menu handler for loading level 3
 */
void CChildView::OnLevelmenuLevel3()
{
	// TODO: Add your command handler code here
	mGame.Load(3);
	Invalidate();
}

/**
 * Handle timer events
 * \param nIDEvent The timer event ID
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}


/**
 * Road Cheat event handler
 */
void CChildView::OnCheatmenuRoadcheat()
{
	CWnd* pParent = GetParent();
	CMenu* pMenu = pParent->GetMenu();

	// IF the cheat is on
	if (mGame.GetRoadCheatState())
	{
		// turn it off
		mGame.SetRoadCheatState(false);
		pMenu->CheckMenuItem(ID_CHEATMENU_ROADCHEAT, MF_UNCHECKED);
	}
	else
	{
		// turn it on
		mGame.SetRoadCheatState(true);
		pMenu->CheckMenuItem(ID_CHEATMENU_ROADCHEAT, MF_CHECKED);
	}
}


/**
 * River cheat event handler
 */
void CChildView::OnCheatmenuRivercheat()
{

	CWnd* pParent = GetParent();
	CMenu* pMenu = pParent->GetMenu();

	// if the cheat is on
	if (mGame.GetRiverCheatState())
	{
		// turn it off
		mGame.SetRiverCheatState(false);
		pMenu->CheckMenuItem(ID_CHEATMENU_RIVERCHEAT, MF_UNCHECKED);
	}
	else
	{
		// turn it on
		mGame.SetRiverCheatState(true);
		pMenu->CheckMenuItem(ID_CHEATMENU_RIVERCHEAT, MF_CHECKED);
	}
}
