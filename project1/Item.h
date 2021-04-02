/**
 * \file Item.h
 *
 * \author Nikolai Tolmoff
 *
 * Base class for all game items.
 */

#pragma once

#include <string>
#include <memory>
#include "XmlNode.h"
#include "ItemVisitor.h"

class CGame;

/**
 * Base class for all game items.
 */
class CItem
{
public:
	/// Default contructor (disabled)
	CItem() = delete;

	/// Copy constructor
	CItem(const CItem& item);

	virtual ~CItem();

	/** The X location of the item
	 * \returns X location in pixels */
	double GetX() const { return mX; }

	/** The Y location of the item
	 * \returns Y location in pixels */
	double GetY() const { return mY; }

	/** The width of the item
	 * \returns width in pixels */
	double GetWidth() const { return mItemImage->GetWidth(); }

	/** The height of the item
	 * \returns height in pixels */
	double GetHeight() const { return mItemImage->GetHeight(); }

	/** Gets a pointer to the image bitmap
	 * \returns height in pixels */
	Gdiplus::Bitmap* GetImage() const { return mItemImage.get(); }

	/// Sets the image to draw of the hero
	/// \param image The bitmap pointer image to set
	void SetImage(std::shared_ptr<Gdiplus::Bitmap> image) { mItemImage = image;}

	/// Set the item location
	/// \param x X location
	/// \param y Y location
	void SetLocation(double x, double y) { mX = x; mY = y; }

	/// Get the game this item is in
	/// \returns Game pointer
	CGame* GetGame() { return mGame; }

	virtual void Draw(Gdiplus::Graphics* graphics);

	virtual std::shared_ptr<xmlnode::CXmlNode> XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node);

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

	double Distance(std::shared_ptr<CItem> other);

	/** Accept a visitor
	 * \param visitor The visitor we accept */
	virtual void Accept(CItemVisitor* visitor) {};

	/** Pure virtual function which clones an item by invoking copy constructor
	* \return pointer to a copied item
	*/
	virtual std::shared_ptr<CItem> Clone() const = 0;

protected:
	CItem(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, int yPos, int xPos);
	CItem(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap);
	CItem(CGame* game);

private:
	/// The game this item is a part of
	CGame* mGame;

	// Item location on the playing field
	double mX = 0;			///< X location for the center of the item
	double mY = 0;			///< Y location for the center of the item

	/// The image of this item
	std::shared_ptr<Gdiplus::Bitmap> mItemImage;
};

