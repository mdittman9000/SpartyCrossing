/**
 * \file Car.cpp
 *
 * \author Michael Dittman, Matthew Norris
 */

#include "pch.h"
#include "Car.h"


using namespace Gdiplus;

 /**
 * Constructor
 * \param game Game that car is in
 * \param bitmap1 Default image of car
 * \param bitmap2 Swapped image of car
 * \param speed Speed of car
 * \param yPos y position of car
 * \param xPos x position of car
 * \param width Width of road
 */
CCar::CCar(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap1, std::shared_ptr<Gdiplus::Bitmap> bitmap2, double speed, int yPos, int xPos, int width)
    : CVehicle(game, bitmap1, speed, yPos, xPos, width)
{
    
    mImage = bitmap1;
    mSwappedImage = bitmap2;
}

/**
 * Copy constructor
 * \param car Car being copied.
 */
CCar::CCar(const CCar& car) : CVehicle(car)
{
    mSwappedImage = car.mSwappedImage;
    mImage = car.mImage;
    mSwapTime = car.mSwapTime;
}

/**
 * 
 * \param node 
 */
void CCar::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{

    CVehicle::XmlLoad(node);

    double swapTime = node->GetAttributeDoubleValue(L"swap-time", 0);
    mSwapTime = swapTime;

}


/**
 * 
 * \param elapsed 
 */
void CCar::Update(double elapsed)
{
    // some logic to swap every time swap-time has passed

    CVehicle::Update(elapsed);

     mTimeCar += elapsed;

     // Convert to Seconds

     int seconds = ((int)mTimeCar) % 60;

      // Set  seconds

      mSeconds = seconds;

}

/**
* Draw this item
* \param graphics Graphics device to draw on
*/
void CCar::Draw(Gdiplus::Graphics* graphics)
{

    // Get the image item
    Gdiplus::Bitmap* itemImage = this->GetImage();
    // Height and Width of Image
    double wid = itemImage->GetWidth();
    double hit = itemImage->GetHeight();

    // Width of the window
    const double Width = 1024.0;
    const double mSwap = .5;

    
    if (mTimeCar > mSwap)
    {
       
        double wid = mSwappedImage->GetWidth();
        double hit = mSwappedImage->GetHeight();
        graphics->DrawImage(mSwappedImage.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)wid, (float)hit); 
        
        // If the image has been displayed for the length of its swap time
        // set the time back to 0
        if (mTimeCar > mSwap*2)
        {
            mTimeCar = 0;
        }
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
    else 
    {

        CItem::Draw(graphics);

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
}

/** Accept a visitor
* \param visitor The visitor we accept */
void CCar::Accept(CItemVisitor* visitor)
{ 
    // Do an upcall so the vehicle visitor still works
    CVehicle::Accept(visitor);
    visitor->VisitCar(this); 
}

