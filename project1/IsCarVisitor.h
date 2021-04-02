/**
 * \file IsCarVisitor.h
 *
 * \author Andrew Haakenson
 * 
 * Class that describes a visitor for determining whether something is a car
 */

#pragma once
#include "ItemVisitor.h"
#include <string>

/** Visitor for checking if an item is a Car.
*/
class CIsCarVisitor : public CItemVisitor
{
public:
    virtual void VisitCar(CCar* car) override;

    /** Returns whether or not the item is a Vehicle.
    * \returns True if item is a Vehicle, False otherwise. */
    bool GetIsCar() { return mIsCar; }

    /** Returns Vehicle.
    * \returns The vehicle that was visited. */
    CCar* GetCar() { return mCar; }

    /** Returns Vehicle ID.
    * \returns The ID of the Vehicle that was visited. */
    std::wstring GetId() { return mCarId; }

private:
    /// Whether or not the item is a Vehicle.
    bool mIsCar = false;

    /// The vehicle that was visited.
    CCar* mCar = nullptr;

    /// The id of the Vehicle
    std::wstring mCarId;
};

