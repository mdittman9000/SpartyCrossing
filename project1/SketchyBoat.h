/**
 * \file SketchyBoat.h
 *
 * \author Ethan Strain
 *
 * Class that describes our team item, a boat that sinks
 * after a period of the hero standing on it.
 */

#pragma once
#include "Vehicle.h"
#include "Boat.h"


/**
 * Class that describes the sketchy boat
 */
class CSketchyBoat :
    public CBoat
{
public:
    /// Default constructor (disabled)
    CSketchyBoat() = delete;

    /// Copy constructor
    CSketchyBoat(const CSketchyBoat&);

    CSketchyBoat::CSketchyBoat(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, std::shared_ptr<Gdiplus::Bitmap> bitmap1, double speed, int yPos, int xPos, int width);

    virtual void Update(double elapsed) override;

    /** Clones a SketchyBoat by invoking the copy constructor, returns an item pointer
    * \return pointer to a copied item
    */
    virtual std::shared_ptr<CItem> Clone() const { return std::make_shared<CSketchyBoat>(*this); }

    virtual void Accept(CItemVisitor* visitor) override;

    virtual void Draw(Gdiplus::Graphics* graphics) override;
    /** Gets time hero has been on the boat
    * \return time hero has been on the boat
    */
    double GetTimeRidden() const { return mTimeRidden; }

    /** Sets if this boat has hero on it
    * \param rid whether hero is on this boat
    */
    void SetIsRidden(bool rid) { mIsRidden = rid; }

private:
    /// If the boat is occupied by the hero
    bool mIsRidden = false;
    
    /// Time since hero stepped onto this boat
    double mTimeRidden = 0;

    /// The swapped image of this item
    std::shared_ptr<Gdiplus::Bitmap> mBrokenItemImage;
};

