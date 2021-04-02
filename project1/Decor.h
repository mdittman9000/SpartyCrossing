/**
 * \file Decor.h
 *
 * \author Andrew Haakenson
 *
 * Base class for roads and rivers.  Represents background of game.
 */

#pragma once
#include <memory>
#include "Item.h"
#include "XmlNode.h"
#include "Game.h"

 /**
  * Base class for roads and rivers.  Represents background of game.
  */
class CDecor : public CItem
{
public:
	/// Default contructor (disabled)
	CDecor() = delete;

	/// Copy constructor
	CDecor(const CDecor&);

	CDecor(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap);
	CDecor(CGame* game);

	/** Gets repeat in x direction
	* \returns how many times to repeat in x direction */
	int GetRepeatX() { return mRepeatX; }

	/** Gets repeat in y direction
	 * \returns how many times to repeat in y direction */
	int GetRepeatY() { return mRepeatY; }

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	bool HitTest(double x, double y);

	virtual void Draw(Gdiplus::Graphics* graphics);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitDecor(this); }

	/** Clones a decor item by invoking the copy constructor, returns an item pointer
	* \return pointer to a copied item
	*/
	virtual std::shared_ptr<CItem> Clone() const { return std::make_shared<CDecor>(*this); }

	/** Get the decor's id
	* \return mId
	*/
	std::wstring GetId() { return mId; }

private:
	
	/// The id of the decor
	std::wstring mId;

	/// How many times decor repeats in x direction
	int mRepeatX = 1;

	/// How many times decor repeats in y direction
	int mRepeatY = 1;

};

