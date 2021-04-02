/**
 * \file Hero.cpp
 *
 * \author Michael Dittman
 */

#include "pch.h"
#include "Hero.h"
#include "Game.h"
#include "Item.h"
#include <iostream>

using namespace Gdiplus;

/// The upper border of the screen
const int topBorder = 128;

/// The lower border of the screen
const int lowerBorder = 896;

/// Number of pixels wide and tall a tile is.
const double TileToPixels = 64;

/// Width of the window
const double Width = 1024.0;

/**
 * Constructor for the Hero
 * \param game The game this Hero is a part of
 * \param bitmap Bitmap of the default image of hero
 * \param swapped Bitmap of image of hero hit by car
 * \param mask Bitmap of hero's mask
 */
CHero::CHero(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, std::shared_ptr<Gdiplus::Bitmap> swapped, 
    std::shared_ptr<Gdiplus::Bitmap> mask) : CItem(game, bitmap)
{
    mSwappedItemImage = swapped;
    mItemMask = mask;
}

/**
 * Copy constructor
 * \param hero Hero being copied
 */
CHero::CHero(const CHero& hero) : CItem(hero)
{
    mName = hero.mName;
    mSwappedItemImage = hero.mSwappedItemImage;
    mItemMask = hero.mItemMask;
}

/**
 * Load the attributes for a decor node.
 *
 * \param node The Xml node we are loading the decor from
 */
void CHero::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    //CItem::XmlLoad(node);

    // Save repeats in each direction
    std::wstring name = node->GetAttributeValue(L"name", L"Sparty");
    mName = name;

}


/**
 * Save the hero node
 * \param node 
 * \returns 
 */
std::shared_ptr<xmlnode::CXmlNode> CHero::XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    auto heroNode = node->AddChild(L"hero");

    return heroNode;

}


/**
 * Function to make the Hero move forwards
 */
void CHero::moveForward()
{

    // Get the current position
    double currentY = this->GetY();
    double currentX = this->GetX();

    // Move the hero forward, unless at top of the screen
    if (currentY > topBorder)
    {
        this->SetLocation(currentX, currentY - TileToPixels);
    }
}


/**
 * Function to make the hero move backwards
 */
void CHero::moveBackward()
{

    // Get the current position
    double currentY = this->GetY();
    double currentX = this->GetX();

    // Move the hero forward, unless at bottom of the screen
    if (currentY < lowerBorder)
    {
        this->SetLocation(currentX, currentY + TileToPixels);
    }
}

/**
 * Function to make the hero move left
 */
void CHero::moveLeft()
{

    // Get the current position
    double currentY = this->GetY();
    double currentX = this->GetX();

    // Move the hero forward, this may have to be changed w/ Virtual pixels
    this->SetLocation(currentX - TileToPixels, currentY);

}

/**
 * Function to make the hero move right
 */
void CHero::moveRight()
{

    // Get the current position
    double currentY = this->GetY();
    double currentX = this->GetX();

    // Move the hero forward, this may have to be changed w/ Virtual pixels
    this->SetLocation(currentX + TileToPixels, currentY);

}

/**
 * Update function for vehicle. Checks if a vehicle needs to be reset
 * to the other side of the screen.
 * \param elapsed Time elapsed
 */
void CHero::Update(double elapsed)
{
    SetLocation(GetX() + mSpeed * elapsed, GetY());
}


/**
 * Responsible for drawing the hero on the screen. 
 * Overloaded from CItem. Handles what to do with hero 
 * if loss conditions occur.
 * \param graphics Graphics context to draw with
 */
void CHero::Draw(Gdiplus::Graphics* graphics)
{
    CGame* game = GetGame();

    // If hero got shmucked by a car
    if (game->GameLossCondition() == 1)
    {
        // draw the swapped image
        SetImage(mSwappedItemImage);
        CItem::Draw(graphics);
    }
    // If hero fell in the river
    else if (game->GameLossCondition() == 2)
    {
        CItem::Draw(graphics);

        // add the mask over the hero image
        double wid = mItemMask->GetWidth();
        double hit = mItemMask->GetHeight();

        graphics->DrawImage(mItemMask.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mItemMask->GetWidth(), (float)mItemMask->GetHeight());

        // If the vehcile is starting to pass the left boundary
        if (GetX() - GetWidth() / 2 < 0)
        {

            // Create a solid black brush
            SolidBrush black(Color(0, 0, 0));

            // Fill a rectangle starting off the screen and going to the edge of the boundary
            graphics->FillRectangle(&black, float(-600), float(GetY() - hit / 2),
                (float)600, (float)800);

        }
        // If the vehicle is over the right boundary
        else if (GetWidth() / 2 + GetX() > Width)
        {

            // Create a solid black brush
            SolidBrush black(Color(0, 0, 0));

            // Fill a recntangle starting at the width of the boundary to off screen
            graphics->FillRectangle(&black, float(Width), float(GetY() - hit / 2),
                (float)800, (float)800);
        }

    }
    // If hero drifted off screen
    else if (game->GameLossCondition() == 4)
    {
        // Don't draw hero for remainder of this run
    }
    else
    {
        // draw the image normally
        CItem::Draw(graphics);
    }
}
