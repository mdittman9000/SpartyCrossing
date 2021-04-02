/**
 * \file Boat.cpp
 *
 * \author Michael Dittman, Matthew Norris
 */

#include "pch.h"
#include "Boat.h"


/**
 * Constructor
 * \param game Game that boat is in
 * \param bitmap Image of boat
 * \param speed Speed of boat
 * \param yPos y position of boat
 * \param xPos x position of boat
 * \param width width of the river
 */
CBoat::CBoat(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, double speed, int yPos, int xPos, int width) : 
    CVehicle(game, bitmap, speed, yPos, xPos, width)
{
}

/**
 * Copy constructor
 * \param boat Boat being copied.
 */
CBoat::CBoat(const CBoat& boat) : CVehicle(boat)
{
    mSwapTime = boat.mSwapTime;
}

/**
 * Function to load the boat
 * \param node Node to load
 */
void CBoat::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{

   // CVehicle::XmlLoad(node);

}

/** Accept a visitor
 * \param visitor The visitor we accept */
void CBoat::Accept(CItemVisitor* visitor) 
{ 
    visitor->VisitBoat(this); 
    visitor->VisitVehicle(this);
}


