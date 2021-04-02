/**
 * \file IsVehicleVisitor.h
 *
 * \author Nikolai Tolmoff
 *
 * Visitor for checking if an item is a Vehicle.
 */

#pragma once
#include "ItemVisitor.h"
#include <string>


 /**
  * Visitor for checking if an item is a Vehicle.
  */
class CIsVehicleVisitor : public CItemVisitor
{
public:
    virtual void VisitVehicle(CVehicle* vehicle) override;

    /** Returns whether or not the item is a Vehicle.
    * \returns True if item is a Vehicle, False otherwise. */
    bool GetIsVehicle() { return mIsVehicle; }

    /** Returns Vehicle.
    * \returns The vehicle that was visited. */
    CVehicle* GetVehicle() { return mVehicle; }

    /** Returns Vehicle ID.
    * \returns The ID of the Vehicle that was visited. */
    std::wstring GetId() { return mVehicleId; }

private:
    /// Whether or not the item is a Vehicle.
    bool mIsVehicle = false;

    /// The vehicle that was visited.
    CVehicle* mVehicle = nullptr;

    /// The id of the Vehicle
    std::wstring mVehicleId;
};

