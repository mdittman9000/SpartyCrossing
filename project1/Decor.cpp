/**
 * \file Decor.cpp
 *
 * \author Andrew Haakenson
 */

#include "pch.h"
#include "Decor.h"
#include "Game.h"

/// Number of pixels wide and tall a tile is.
const double TileToPixels = 64;

/**
 * Constructor for CDecor.
 * 
 * \param game Pointer to the game this decor is a part of
 * \param bitmap Bitmap of this item's image
 */
CDecor::CDecor(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap) :
	CItem(game, bitmap)
{
}

/**
 * Constructor for CDecor.
 *
 * \param game Pointer to the game this decor is a part of
 */
CDecor::CDecor(CGame* game) :
	CItem(game)
{
}

/**
 * Copy constructor
 * \param decor Decor being copied
 */
CDecor::CDecor(const CDecor& decor) : CItem(decor)
{
    mId = decor.mId;
	mRepeatX = decor.mRepeatX;
	mRepeatY = decor.mRepeatY;
}

/**
 * Draws a decor object onto the screen
 *
 * \param graphics Graphics device to draw on
 */
void CDecor::Draw(Gdiplus::Graphics* graphics)
{
	Gdiplus::Bitmap* itemImage = this->GetImage();
	double wid = itemImage->GetWidth();
	double hit = itemImage->GetHeight();

	// Repeats image in both directions 
	for (int x = 0; x < mRepeatX; x++)
	{
		for (int y = 0; y < mRepeatY; y++)
		{
			// POSSIBLY TEMPORARY
			// Multiplies coordinates by 64 until we have a concrete virtual pixel solution
			// EDIT: Ethan - moved conversion of mX and mY to pixels into CItem XmlLoad()
			graphics->DrawImage(itemImage,
				float(GetX() + x * TileToPixels), float(GetY() + y * TileToPixels),
				(float)itemImage->GetWidth() + 1, (float)itemImage->GetHeight() + 1);
		}
	}
}

/**
 * Load the attributes for a decor node.
 * 
 * \param node The Xml node we are loading the decor from
 */
void CDecor::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CItem::XmlLoad(node);

	// Save repeats in each direction
	int repeatX = node->GetAttributeIntValue(L"repeat-x", 1);
	int repeatY = node->GetAttributeIntValue(L"repeat-y", 1);
	std::wstring id = node->GetAttributeValue(L"id", L"");

	mId = id;
	mRepeatX = repeatX;
	mRepeatY = repeatY;
}


/**
 * Hittest for decor tile
 * \param x 
 * \param y 
 * \returns 
 */
bool CDecor::HitTest(double x, double y)
{

    //double wid = GetImage()->GetWidth();
    double hit = GetImage()->GetHeight() * (double)GetRepeatY();

    // Make x and y relative to the top-left corner of the bitmap image.
    // Subtracting the center makes x, y relative to the center of
    // the image. Adding half the size makes x, y relative to the top
    // corner of the image.
    //double testX = x - GetX() + wid / 2;
    double testY = y - GetY();

    // Test to see if x, y are in the image
    if (testY < 0 || testY >= hit)
    {
        // We are outside the image
        return false;
    }
    else return true;

}