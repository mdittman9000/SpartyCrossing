/**
 * \file Vehicle.cpp
 *
 * \author Nikolai Tolmoff
 */

#include "pch.h"
#include "Vehicle.h"

using namespace Gdiplus;

/// Number of pixels wide and tall a tile is.
const int TileToPixels = 64;

/**
 * Constructor
 * \param game Pointer to the game this decor is a part of
 * \param bitmap Bitmap of this item's image
 * \param speed Speed of the boat
 * \param yPos Y position
 * \param xPos X position
 * \param width Width of the river or road
 */
CVehicle::CVehicle(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, double speed, int yPos, int xPos, int width) : mSpeed(speed),
	mLaneWidth(width), CItem(game, bitmap, yPos, xPos)
{
    mLaneWidth = width;

}

/**
 * Constructor for CVehicle.
 *
 * \param game Pointer to the game this decor is a part of
 */
CVehicle::CVehicle(CGame* game) : CItem(game)
{
}



/**
 * Constructor
 * \param game Pointer to the game this decor is a part of
 * \param bitmap Bitmap of this item's image
 */
CVehicle::CVehicle(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap) : CItem(game, bitmap)
{
}

/**
 * Copy constructor
 * \param vehicle Vehicle being copied.
 */
CVehicle::CVehicle(const CVehicle& vehicle) : CItem(vehicle)
{
    mSpeed = vehicle.mSpeed;
    mLaneWidth = vehicle.mLaneWidth;
    mId = vehicle.mId;
}

/**
 * Update function for vehicle. Checks if a vehicle needs to be reset 
 * to the other side of the screen.
 * \param elapsed Time elapsed
 */
void CVehicle::Update(double elapsed)
{

    const int maxVehicleWidth = 256;

    // Width of the lane (in pixels)
    int laneWidth = mLaneWidth * TileToPixels;

    // If going off the left of the screen
    if (GetX() + (GetWidth() / 2) <= 0 && mSpeed < 0)
    {
        // Set the vehicle to the right boundary
        SetLocation(GetX() + laneWidth, GetY());
    }

    // If going off the right of the screen
    if (GetX() + maxVehicleWidth >= laneWidth + GetWidth() && mSpeed > 0)
    {
        // Set to the left boundary
        SetLocation(GetX() - laneWidth - maxVehicleWidth, GetY());
    }

	SetLocation(GetX() + mSpeed* elapsed, GetY());
}

/**
 * Load the attributes for a vehicle node.
 *
 * This is the  base class version that loads the attributes
 * common to all vehicles. Override this to load custom attributes
 * for specific vehicle.
 *
 * \param node The Xml node we are loading the vehicle from
 */
void CVehicle::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{

    std::wstring name = node->GetAttributeValue(L"id", L"Vehicle");
    mId = name;

}


/**
 * Draw the vehicle
 * \param graphics 
 */
void CVehicle::Draw(Gdiplus::Graphics* graphics)
{
    // Get the image item
    Gdiplus::Bitmap* itemImage = this->GetImage();

    // Height and Width of Image
    double wid = itemImage->GetWidth();
    double hit = itemImage->GetHeight();

    // Width of the window
    const double Width = 1024.0;

    // If the vehcile is starting to pass the left boundary
    if (GetX() - GetWidth() / 2 < 0)
    {
        // Draw the vehiclke
        CItem::Draw(graphics);

        // Create a solid black brush
        SolidBrush black(Color(0, 0, 0));

        // Fill a rectangle starting off the screen and going to the edge of the boundary
        graphics->FillRectangle(&black, float(-600), float(GetY() - hit / 2),
            (float)600, (float)800);

    }
    // If the vehicle is over the right boundary
    else if (GetWidth() / 2 + GetX() > Width)
    {

        // Draw the vehicle
        CItem::Draw(graphics);
        
        // Create a solid black brush
        SolidBrush black(Color(0, 0, 0));

        // Fill a recntangle starting at the width of the boundary to off screen
        graphics->FillRectangle(&black, float(Width), float(GetY() - hit / 2),
            (float)800, (float)800);
    }
    else
    {
        // Draw the vehcile normally
        CItem::Draw(graphics);
    }

}

/**
 * Checks to see if this Car hit the Hero.
 * \param x X location of the Hero
 * \param y Y location of the Hero
 * \returns True if Hero was hit, False otherwise
 */
bool CVehicle::HitTest(double x, double y)
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
