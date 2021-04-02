/**
 * \file DecorTypeVisitor.cpp
 *
 * \author Michael Dittman
 */

#include "pch.h"
#include "DecorTypeVisitor.h"
#include "Decor.h"

/**
 * Visit a Decor object.
 * \param decor Decor object we are visiting.
 */
void CDecorTypeVisitor::VisitDecor(CDecor* decor)
{

    mDecor = decor;
    mDecorId = decor->GetId();

}
