/**
 * \file Vehicle.h
 *
 * \author Nikolai Tolmoff
 *
 * Base class for vehicles, including cars and boats.
 */

#pragma once

#include <memory>
#include "Item.h"
#include "XmlNode.h"
#include "Game.h"


/**
 * Base class for vehicles, including cars and boats.
 */
class CVehicle : public CItem
{
public:
    /// Default constructor (disabled)
    CVehicle() = delete;

    /// Copy constructor
    CVehicle(const CVehicle&);

    CVehicle(CGame* game);

    CVehicle(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap);

    CVehicle(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, double speed, int yPos, int xPos, int width);

    /// Set the speed
    /// \param speed Speed
    void SetSpeed(double speed) { mSpeed = speed; }

    /** Get the speed
    * \return speed of vehicle
    */
    double GetSpeed() { return mSpeed; }

    virtual void Update(double elapsed);

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitVehicle(this); }

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    bool HitTest(double x, double y);

    /** Clones a vehicle by invoking the copy constructor, returns an item pointer
    * \return pointer to a copied object
    */
    virtual std::shared_ptr<CItem> Clone() const { return std::make_shared<CVehicle>(*this); }

    /** Get car name
    * \return Name
    */
    std::wstring GetId() { return mId; }

private:
    /// Vehicle speed
    double mSpeed = 1;

    /// Width of the lane this vehicle travels on
    int mLaneWidth = 0;

    /// Name
    std::wstring mId;
};

