/**
 * \file IsCargoVisitor.cpp
 *
 * \author Nikolai Tolmoff
 */

#include "pch.h"
#include "IsCargoVisitor.h"


/**
 * Visit a Cargo object
 * \param cargo Cargo object we are visiting.
 */
void CIsCargoVisitor::VisitCargo(CCargo* cargo)
{
	mIsCargo = true;
	mCargo = cargo;
}
