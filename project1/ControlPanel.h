/**
 * \file ControlPanel.h
 *
 * \author Matthew Norris
 *
 * 
 */

#pragma once

#include "Game.h"

class CGame;

/// Class describing control panel within a game
class CControlPanel
{
public: 

	/// Default constructor (disabled)
	CControlPanel() = delete;

	/// Copy constructor (disabled)
	CControlPanel(const CControlPanel&) = delete;

	CControlPanel(CGame* game);

	//Function that will draw our timer, and other control panel graphics
	virtual void Draw(Gdiplus::Graphics* graphics);

	//Function to constantly update timer
	void Update(double elapsed);

	/**
	* Set the level this control panel belongs to
	* \param level The level this control panel belongs to
	* \param levelNumber number of level this control panel belongs to
	*/
	void SetLevel(std::shared_ptr<CLevel> level, const int levelNumber) { mLevel = level, mLevelNumber = levelNumber; }

	/**
	* Adds a cargo name to the cargo name vector
	* \param cargoName name of cargo to add
	*/
	void SetCargoItem(std::wstring cargoName) { mCargoNames.push_back(cargoName); }

	void Clear();

	/**
	* Return the time on the timer
	* \return mTimerTime The time on the timer
	*/
	double GetTimerTime() { return mTimerTime; }

	/**
	* Set the time on the timer
	* \param time Time to set timer time to
	*/
	void SetTimerTime(double time) { mTimerTime = time; }

	/**
	* Gets current level number
	* \return current level number
	*/
	int GetLevelNumber() { return mLevelNumber; }

	/**
	* Set the name of the hero
	* \param hero The name of the hero
	*/
	void SetHeroName(std::wstring hero) { mHeroName = hero; }


	/**
	* Set the name of the car that hit sparty
	* \param car The name of the car
	*/
	void SetSpartyCar(std::wstring car) { mSpartyCar = car; }


private: 
	
	/// The game this control panel belongs to
	CGame* mGame;

	/// The level this control panel is a part of
	std::shared_ptr<CLevel> mLevel = nullptr;

	/// Names of the cargo items
	std::vector<std::wstring> mCargoNames;

	/// The level number
	int mLevelNumber = 0;

	/// Total time
	double mTime = 0;

	/// Minutes
	int mMinutes = 0;

	/// Seconds
	int mSeconds = 0;

	/// Time on the timer
	double mTimerTime = 0;
	
	/// The hero's name
	std::wstring mHeroName = L"Sparty";

	/// The vehicle that hit sparty
	std::wstring mSpartyCar = L"Vehicle";






	
};

