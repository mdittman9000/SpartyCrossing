/**
 * \file CargoEatenVisitor.h
 *
 * \author Nikolai Tolmoff
 *
 * Visitor for checking if any Cargo has been eaten.
 */

#pragma once
#include "ItemVisitor.h"
#include <memory>


 /**
  * Visitor for checking if any Cargo has been eaten.
  */
class CCargoEatenVisitor : public CItemVisitor
{
public:
    /** Constructor
     * \param hero The game's hero.
     */
    CCargoEatenVisitor(std::shared_ptr<CHero> hero) { mHero = hero; }

    virtual void VisitCargo(CCargo* cargo) override;

    /** Returns whether or not the small Cargo has been eaten.
    * \returns True if small Cargo eaten, False otherwise. */
    bool GetSmallEaten() { return mSmallEaten; }

    /** Returns whether or not the small Cargo has been eaten.
    * \returns True if small Cargo eaten, False otherwise. */
    bool GetMediumEaten() { return mMediumEaten; }

    /**
     * Gets a pointer to the small cargo object
     * \returns CCargo pointer
     */
    CCargo* GetSmallCargo() { return mSmallCargo; }

    /**
     * Gets a pointer to the medium cargo object
     * \returns CCargo pointer
     */
    CCargo* GetMediumCargo() { return mMediumCargo; }

    /**
     * Gets a pointer to the large cargo object
     * \returns CCargo pointer
     */
    CCargo* GetLargeCargo() { return mLargeCargo; }

private:
    /// Whether or not the small Cargo has been eaten.
    bool mSmallEaten = false;

    /// Whether or not the small Cargo has been eaten.
    bool mMediumEaten = false;

    /// The game's small cargo.
    CCargo* mSmallCargo = nullptr;

    /// The game's medium cargo.
    CCargo* mMediumCargo = nullptr;

    /// The game's large cargo.
    CCargo* mLargeCargo = nullptr;

    /// The game's Hero.
    std::shared_ptr<CHero> mHero;
};
