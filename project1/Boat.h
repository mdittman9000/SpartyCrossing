/**
 * \file Boat.h
 *
 * \author Michael Dittman , Matthew Norris
 *
 * Class that describes the boat
 */

#pragma once
#include "Vehicle.h"

/**
 * Class that describes the boat
 */
class CBoat : public CVehicle
{
public:
    /// Default constructor (disabled)
    CBoat() = delete;

    /// Copy constructor
    CBoat(const CBoat&);

    CBoat::CBoat(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, double speed, int yPos, int xPos, int width);

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    /** Clones a boat by invoking the copy constructor, returns an item pointer
    * \return pointer to a copied item
    */
    virtual std::shared_ptr<CItem> Clone() const { return std::make_shared<CBoat>(*this); }

    virtual void Accept(CItemVisitor* visitor) override;


private:
    /// Image swap time for boat
    double mSwapTime = 0;

};

