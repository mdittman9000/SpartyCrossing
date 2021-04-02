/**
 * \file Item.cpp
 *
 * \author Nikolai Tolmoff
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"
#include "XmlNode.h"

using namespace Gdiplus;
using namespace std;

/// Number of pixels wide and tall a tile is.
const double TileToPixels = 64;


/**
 * Constructor
 * \param game The game this item is a part of.
 * \param bitmap Bitmap of this item's image.
 * \param yPos Y position 
 * \param xPos X position
 */
CItem::CItem(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, int yPos, int xPos)
    : mGame(game), mItemImage(bitmap), mY(yPos), mX(xPos)
{
}

/**
 * Constructor
 * \param game The game this item is a part of.
 * \param bitmap Bitmap of this item's image.
 */
CItem::CItem(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap) : mGame(game), mItemImage(bitmap)
{
}

/**
 * Constructor
 * \param game The game this item is a part of.
 */
CItem::CItem(CGame* game) : mGame(game)
{
}

/**
 * Copy constructor
 * \param item Copy of this item being created.
 */
CItem::CItem(const CItem& item)
{
    mX = item.GetX();
    mY = item.GetY();
    mItemImage = item.mItemImage;
    mGame = item.mGame;
}

/**
 * Destructor
 */
CItem::~CItem()
{
}

/**
 * Draw the game item
 * \param graphics Graphics device to draw on
 */
void CItem::Draw(Gdiplus::Graphics* graphics)
{
    double wid = mItemImage->GetWidth();
    double hit = mItemImage->GetHeight();

    graphics->DrawImage(mItemImage.get(),
        float(GetX() - wid / 2), float(GetY() - hit / 2),
        (float)mItemImage->GetWidth(), (float)mItemImage->GetHeight());

}


/**
 * Function to save items
 * \param node Node to save in file
 * \returns pointer to the node
 */
std::shared_ptr<xmlnode::CXmlNode> CItem::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    return std::shared_ptr<xmlnode::CXmlNode>();
}




/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * \param node The Xml node we are loading the item from
 */
void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    double x, y = 0.0;
    x = node->GetAttributeDoubleValue(L"x", 0);
    y = node->GetAttributeDoubleValue(L"y", 15.5);

    // tile values multiplied by 64 to convert to pixels
    mX = x * TileToPixels;
    mY = y * TileToPixels;

}


/**
 * Determine the distance from this item to some other item.
 * \param other Other item we are testing
 * \return Distance in pixels
 */
double CItem::Distance(std::shared_ptr<CItem> other)
{
    // Create a vector in the direction we are from the nudger
    double dx = mX - other->mX;
    double dy = mY - other->mY;

    // Determine how far away we are
    return sqrt(dx * dx + dy * dy);
}