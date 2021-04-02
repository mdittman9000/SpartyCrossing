/**
 * \file Cargo.h
 *
 * \author(s) Ethan Strain, Matthew Norris
 *
 * Class to handle cargo type items
 */

#pragma once

#include "Item.h"
#include "Hero.h"

#include <memory>
#include <string>

/**
 * Class to handle cargo items
 */
class CCargo :
    public CItem
{
public:

	/// Default contructor (disabled)
	CCargo() = delete;

	/// Copy constructor
	CCargo(const CCargo&);

	CCargo(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, std::shared_ptr<Gdiplus::Bitmap> mCarriedItemImage);

	CCargo(CGame* game);

	/** Returns whether or not Cargo is being carried by the Hero
	 * \return True if Cargo is being carried */
	bool GetCarryStatus() { return mCarriedByHero; }

	virtual void Draw(Gdiplus::Graphics* graphics);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	void PickUp();

	void Release();

	bool HitTest(double x, double y);

	void Update(double elapsed, std::shared_ptr<CHero> hero);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitCargo(this); }

	/** Clones a cargo item by invoking the copy constructor, returns an item pointer
	* \return pointer to a copied item
	*/
	virtual std::shared_ptr<CItem> Clone() const { return std::make_shared<CCargo>(*this); }

	/** Gets name of cargo
	* \return name of cargo
	*/
	std::wstring GetName() { return mName; }

private:

	/// Flag for if the cargo is currently being held by the hero
	bool mCarriedByHero = false;

	/// Flag for if the cargo object has been left alone for too long
	/// with the CCargo object that eats it
	bool mEaten = false;

	/// The carried image of this item
	std::shared_ptr<Gdiplus::Bitmap> mCarriedItemImage;
	/// The normal image of this item
	std::shared_ptr<Gdiplus::Bitmap> mImageNormal;

	/// name of the Cargo object that gets displayed on the Control Panel
	std::wstring mName;

	/// Cargo ID to identify object internally
	std::wstring mId;

	/// Image filename when object is in place
	std::wstring mImage;

	/// Image filename when object is being carried
	std::wstring mCarriedImage;

	/// Home x coordinate, for when it's not carried
	double mHomeX = 0.0;
};

