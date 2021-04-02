/**
 * \file DecorTypeVisitor.h
 *
 * \author(s) Michael Dittman, Ethan Strain
 *
 * Class that describes the CDecorTypeVisitor
 */

#pragma once
#include "ItemVisitor.h"
#include <string>

/**
 * Class that describes the CDecorTypeVisitor
 */
class CDecorTypeVisitor : public CItemVisitor
{
public:
    virtual void VisitDecor(CDecor* decor) override;

    /** Returns Decor.
    * \returns The Decor that was visited. */
    CDecor* Decor() { return mDecor; }

    /** Returns Decor ID.
    * \returns The ID of the Decor that was visited. */
    std::wstring GetId() { return mDecorId; }

private:

    /// The pointer to the visited decor tile
    CDecor* mDecor = nullptr;

    /// The id of the visited decor tile
    std::wstring mDecorId;
};

