/**
 * \file IsSketchyVisitor.cpp
 *
 * \author Ethan Strain
 * Determines whether an item is a Sketchy boat
 */

#pragma once

#include "ItemVisitor.h"
#include "IsBoatVisitor.h"
#include "SketchyBoat.h"

/**
 * Visits an item and determines whether it is a SketchyBoat
 */
class CIsSketchyVisitor :
    public CItemVisitor
{
public:
    virtual void VisitSketchy(CSketchyBoat* boat) override;

    /** Returns whether or not the item is a boat.
    * \returns True if item is a boat, False otherwise. */
    bool GetIsSketchy() { return mIsSketchy; }

    /** Returns Vehicle.
    * \returns The vehicle that was visited. */
    CSketchyBoat* GetSketchy() { return mSketchyBoat; }

private:
    /// Whether this item is a SketchyBoat
    bool mIsSketchy = false;

    /// Pointer to SketchyBoat
    CSketchyBoat* mSketchyBoat = nullptr;
};

