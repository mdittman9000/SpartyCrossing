/**
 * \file Game.h
 *
 * \author(s) Ethan Strain, Michael Dittman, 
 *
 * Class that describes CGame
 *
 * Contains functionality to draw,
 */

#pragma once

#include<vector>
#include<memory>
#include<utility>
#include "Item.h"
#include "Hero.h"
#include "Cargo.h"
#include "Level.h"
#include "ControlPanel.h"

class CControlPanel;

/**
 * Class that describes a game of Sparty Crossing.
 */
class CGame
{
public:

	// need contructor etc.. and we should be able to get a black screen
	CGame::CGame();

	void OnDraw(Gdiplus::Graphics* graphics, int width, int height);

	std::pair<double, double> ScaleCoords(int x, int y);

	void Add(std::shared_ptr<CItem> item);
	void Add(std::shared_ptr<CLevel> level);

	void Save(const std::wstring& filename);

	void Load(const std::wstring& filename);
	void Load(const int level);

	void Clear();

	/** Setter for hero pointer
	 * \param hero pointer for hero of that level
	 */
	void SetHero(std::shared_ptr<CHero> hero) { mHero = hero; }

	void SetTime(double time);

	void moveHero(UINT nChar);

	void Update(double elapsed);

	void Accept(CItemVisitor* visitor);

	CCargo* HitTest(double x, double y);

	/// Get the width of the game window
	/// \returns Game window width
	int GetWidth() const { return Width; }

	/// Get the height of the game window
	/// \returns Game window height
	int GetHeight() const { return Height; }

	/// Get a pointer to the Hero
	/// \returns pointer to Hero
	std::shared_ptr<CHero> GetHero() const { return mHero; }

	void UpdateControlPanel(double elapsed);

	void DrawControlPanel(Gdiplus::Graphics* graphics);

	void CollisionTest(double x, double y);

	void BoatTest();

	void CheckWinState();

	/// Get if the game has been lost.
	/// \returns True if game has been lost, False otherwise.
	bool GetGameLost() { return mGameOver; }

	/// Sets game over condition to be true
	void SetGameLost() { mGameOver = true; }

	/// Get if the game has been won.
	/// \returns True if game has been won, False otherwise.
	bool GetGameWon() { return mGameWon; }

	/// Get if the Road Cheat is enabled.
	/// \returns True if Road Cheat enabled, False otherwise.
	bool GetRoadCheatState() { return mRoadCheatEnabled; }

	/// Get if the River Cheat is enabled.
	/// \returns True if River Cheat enabled, False otherwise.
	bool GetRiverCheatState() { return mRiverCheatEnabled; }

	/// Sets the Road Cheat state
	/// \param state State to set the Road Cheat to.
	void SetRoadCheatState(bool state) { mRoadCheatEnabled = state; }

	void SetRiverCheatState(bool state);

	/// Gets the condition of the game's loss
	/// \returns int representing condition of game's loss.
	int GameLossCondition() { return mGameLossCondition; }

	/// Sets game over condition to input
	/// \param loss Condition to set loss condition to
	void SetLossCondtion(int loss) { mGameLossCondition = loss; }

	/// Gets the game's get ready state
	/// \returns bool of get ready state
	bool GetReady() { return mGetReady; }

private:
	// game playing area constants:
	// leftmost 1024 x 1024 is the game grid
	// The control panel is the right 200 pixels

	/// Game area width in virtual pixels
	const static int Width = 1224;

	/// Game area height in virtual pixels
	const static int Height = 1024;

	/// Scale for virtual pixels
	float mScale = 0;

	/// X Offset for virtual pixels
	float mXOffset = 0;

	/// Y Offset for virtual pixels
	float mYOffset = 0;

	/// The items that will be contained in the current level
	std::vector<std::shared_ptr<CItem> > mItems;

	/// Levels which can be played
	std::vector<std::shared_ptr<CLevel>> mLevels;

	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node);

	/// Pointer for our hero
	std::shared_ptr<CHero> mHero = nullptr;

	/// Pointer for control panel
	std::shared_ptr<CControlPanel> mControlPanel;

	/// Bool to store if the game is over
	bool mGameOver = false;

	/// Bool to store if the game is won
	bool mGameWon = false;

	/// River Cheat
	bool mRiverCheatEnabled = false;

	/// Road cheat
	bool mRoadCheatEnabled = false;

	/// Game loss condition
	int mGameLossCondition = -1;

	/// Are we still in the get ready stage?
	bool mGetReady = true;

	/// Seconds until a new level is loaded or reloaded
	double mTimeToSwitchLevel = 3.0;

};

