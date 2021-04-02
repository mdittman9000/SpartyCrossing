/**
 * \file Cargo.cpp
 *
 * \author(s) Ethan Strain, Matthew Norris
 */

#include "pch.h"
#include "Cargo.h"
#include "Game.h"
#include "IsCargoVisitor.h"
#include "CarriedCargoVisitor.h"

/// Number of pixels wide and tall a tile is.
const double TileToPixels = 64;

/**
 * Constructor for CCargo
 * 
 * \param game Pointer to game object
 * \param bitmap Bitmap of item's image
 * \param carried Bitmap of item's carried image
 */
CCargo::CCargo(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, std::shared_ptr<Gdiplus::Bitmap> carried) :
	CItem(game, bitmap)
{
	mCarriedItemImage = carried;
	mImageNormal = bitmap;
}

/**
 * Constructor for CCargo
 *
 * \param game Pointer to the game this decor is a part of
 */
CCargo::CCargo(CGame* game) : CItem(game)
{
}

CCargo::CCargo(const CCargo& cargo) : CItem(cargo)
{
	mCarriedByHero = cargo.mCarriedByHero;
	mEaten = cargo.mEaten;
	mCarriedItemImage = cargo.mCarriedItemImage;
	mName = cargo.mName;
	mId = cargo.mId;
	mImageNormal = cargo.mImageNormal;
	mCarriedImage = cargo.mCarriedImage;
	mHomeX = cargo.mHomeX;
}

/** Draws a cargo object
 * \param graphics Pointer to where to draw cargo
 */
void CCargo::Draw(Gdiplus::Graphics* graphics)
{
	CGame* game = GetGame();
	

	// if cargo is being carried, draw the cargo at the hero's position
	if (mCarriedByHero && !(game->GetGameLost()))
	{
		double wid = mCarriedItemImage->GetWidth();
		double hit = mCarriedItemImage->GetHeight();

		graphics->DrawImage(mCarriedItemImage.get(),
			float(game->GetHero()->GetX() - wid / 2), float(game->GetHero()->GetY() - hit / 2),
			(float)mCarriedItemImage->GetWidth(), (float)mCarriedItemImage->GetHeight());
	}
	else if (!mCarriedByHero)
	{
		double wid = mImageNormal->GetWidth();
		double hit = mImageNormal->GetHeight();

		graphics->DrawImage(mImageNormal.get(),
			float(GetX() - wid / 2), float(GetY() - hit / 2),
			(float)GetWidth(), (float)GetHeight());
	}

}

/**
 * Load the attributes that are universal to Cargo
 * 
 * \param node The Xml node to load Cargo attributes from
 */
void CCargo::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CItem::XmlLoad(node);

	// Set home x coordinate as starting x coordinate
	mHomeX = GetX();

	// load cargo specific xml info
	mId = node->GetAttributeValue(L"cargo id", L"");
	mName = node->GetAttributeValue(L"name", L"");

	mImage = node->GetAttributeValue(L"image", L"");
	mCarriedImage = node->GetAttributeValue(L"carried-image", L"");
}

/** Picks up cargo by hero
 */
void CCargo::PickUp()
{
	double heroY = GetGame()->GetHero()->GetY();

	if (GetGame()->GetHero()->GetCarrying())
	{
		CCarriedCargoVisitor visitor;
		GetGame()->Accept(&visitor);
		if (heroY - GetY() <= TileToPixels && heroY - GetY() >= -TileToPixels)
		{
			visitor.GetCarriedCargo()->Release();
		}
	}

	if (heroY - GetY() <= TileToPixels && heroY - GetY() >= -TileToPixels)
	{
		mCarriedByHero = true;
		GetGame()->GetHero()->SetCarrying(true);
	}

}

/** Releases cargo.
 */
void CCargo::Release()
{
	double heroY = GetGame()->GetHero()->GetY();

	if (heroY <= TileToPixels * 2 || heroY >= TileToPixels * 14)
	{
		mCarriedByHero = false;

			if (heroY <= TileToPixels * 2)
			{
				SetLocation(mHomeX, TileToPixels * 0.5);
			}
			if (heroY >= TileToPixels * 14)
			{
				SetLocation(mHomeX, TileToPixels * 15.5);
			}
			GetGame()->GetHero()->SetCarrying(false);
	}

	GetGame()->CheckWinState();
}

/** Checks if this cargo was hit by a mouse click.
 * \param x X coordinate of mouse click
 * \param y Y coordinate of mouse click
 * \return True if cargo was clicked by mouse, false otherwise
 */
bool CCargo::HitTest(double x, double y)
{
	
	double wid = GetImage()->GetWidth();
	double hit = GetImage()->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image.
	// Subtracting the center makes x, y relative to the center of
	// the image. Adding half the size makes x, y relative to the top
	// corner of the image.
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}
	else return true;

}

/**
 * Update function for vehicle
 * \param elapsed Time elapsed
 * \param hero Pointer to the hero
 */
void CCargo::Update(double elapsed, std::shared_ptr<CHero> hero)
{
	if (mCarriedByHero)
	{
		SetLocation(hero->GetX(), hero->GetY());
	} 

	
}