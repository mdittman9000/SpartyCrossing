/**
 * \file SketchyBoat.cpp
 *
 * \author Ethan Strain
 */


#include "pch.h"
#include "SketchyBoat.h"
#include "Hero.h"

using namespace Gdiplus;

/**
 * Constructor
 * \param game Pointer to game object
 * \param bitmap Bitmap image of the object to draw
 * \param bitmap1 Bitmap of broken boat image
 * \param speed Speed the object is moving in its lane
 * \param yPos Lane position
 * \param xPos Where in the lane the object gets initally drawn
 * \param width Width of the river lane which dictates when the boat wraps around
 */
CSketchyBoat::CSketchyBoat(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, std::shared_ptr<Gdiplus::Bitmap> bitmap1, double speed, int yPos, int xPos, int width) :
    CBoat(game, bitmap, speed, yPos, xPos, width)
{

    mBrokenItemImage = bitmap1;

}


/**
 * Draws the Sketchy Boat
 * \param graphics Graphics context to draw on
 */
void CSketchyBoat::Draw(Gdiplus::Graphics* graphics)
{
    CGame* game = GetGame();

    if (game->GetHero()->GetOnSketchy() && mTimeRidden > 2.0)
    {
        game->SetGameLost();
        // temorary loss condition
        game->SetLossCondtion(2);
        
        double wid = mBrokenItemImage->GetWidth();
        double hit = mBrokenItemImage->GetHeight();

        graphics->DrawImage(mBrokenItemImage.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mBrokenItemImage->GetWidth(), (float)mBrokenItemImage->GetHeight());

    }
    else
    {
        CVehicle::Draw(graphics);

    }

    

}


/**
 * Update function for the Sketchy Boat. 
 * Implements the functionality of this special item, which 
 * will dissapear after the hero stands on it for more than a second.
 * \param elapsed Time elapsed
 */
void CSketchyBoat::Update(double elapsed)
{
    CGame* game = GetGame();

    if (game->GetHero()->GetOnSketchy() && game->GetHero()->GetX() == GetX())
    {
        mTimeRidden += elapsed;
    }
    else
    {
        mTimeRidden = 0;
    }
    
    CVehicle::Update(elapsed);

}

/**
 * Copy constructor for Sketchy Boat
 * \param boat Reference to the Sketchy Boat object
 */
CSketchyBoat::CSketchyBoat(const CSketchyBoat& boat) : CBoat(boat)
{
    mBrokenItemImage = boat.mBrokenItemImage;
}

/** Accept a visitor to a Sketchy Boat object
 * \param visitor The visitor we accept */
void CSketchyBoat::Accept(CItemVisitor* visitor)
{
    visitor->VisitSketchy(this);
    visitor->VisitBoat(this);
    visitor->VisitVehicle(this);
}