/**
 * \file IsCargoVisitor.h
 *
 * \author Nikolai Tolmoff
 *
 * Visitor for checking if an item is Cargo.
 */

#pragma once
#include "ItemVisitor.h"


/**
 * Visitor for checking if an item is Cargo.
 */
class CIsCargoVisitor : public CItemVisitor
{
public:
	virtual void VisitCargo(CCargo* cargo) override;

    /** Returns whether or not the item is Cargo.
    * \returns True if item is Cargo, False otherwise. */
    bool GetIsCargo() { return mIsCargo; }

    /** Returns cargo.
    * \returns The cargo that was visited. */
    CCargo* GetCargo() { return mCargo; }

private:
    /// Whether or not the item is Cargo.
    bool mIsCargo = false;

    /// The cargo that was visited.
    CCargo* mCargo = nullptr;
};

