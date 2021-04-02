/**
 * \file Level.h
 *
 * \author Andrew Haakenson
 *
 * Class representing a level.
 */

#pragma once
#include <memory>
#include <map>
#include <vector>
#include <string>
#include "Item.h"
#include "Hero.h"


 /**
 Class representing a rectangle like a stripe on the road. 
  */
class CLevel
{
public:
	/// default constructor (disabled)
	CLevel() = delete;
	CLevel(CGame* game);

	void Load(const std::wstring& filename);
	void XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node, const double speed = 0.0, const int width = 0, const int yPos = 0);
	void Add(std::shared_ptr<CItem> item);
	void AddCargo(std::shared_ptr<CItem> item);
	/** Getter for item vector
	 * 
	 * \return item vector
	 */
	std::vector<std::shared_ptr<CItem>> GetItems() { return mBelowHero; }

	/**
	 * Getter for hero pointer for this level
	 * 
	 * \return hero pointer
	 */
	std::shared_ptr<CHero> GetHero() { return mHero; }
	/** Getter for cargo vector
	 * \return vector of cargo items for this level
	 */
	std::vector<std::shared_ptr<CItem>> GetCargo() { return mAboveHero; }
private:
	/// Map holding the bitmaps associated with IDs
	std::map<std::wstring, std::vector<std::shared_ptr<Gdiplus::Bitmap>>> mImageMap; 
	/// Vector holding all items drawn above hero for this level (everything except hero and cargo)
	std::vector<std::shared_ptr<CItem>> mBelowHero; 
	/// Pointer to game
	CGame* mGame; 
	/// Pointer to hero of this level
	std::shared_ptr<CHero> mHero; 
	/// Vector holding things drawn above the hero (cargo)
	std::vector<std::shared_ptr<CItem>> mAboveHero;
};

