/**
 * \file CarriedCargoVisitor.h
 *
 * \author Nikolai Tolmoff
 *
 * Visitor for finding the Cargo being carried by the Hero.
 */

#pragma once
#include "ItemVisitor.h"
#include <memory>


 /**
  * Visitor for finding the Cargo being carried by the Hero.
  */
class CCarriedCargoVisitor : public CItemVisitor
{
public:
    virtual void VisitCargo(CCargo* cargo) override;

    /** Returns cargo.
    * \returns The cargo being carried. */
    CCargo* GetCarriedCargo() { return mCarriedCargo; }

private:
    /// The cargo being carried.
    CCargo* mCarriedCargo = nullptr;
};

