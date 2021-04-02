/**
 * \file IsBoatVisitor.cpp
 *
 * \author Andrew Haakenson
 */

#include "pch.h"
#include "IsBoatVisitor.h"

/** Visits item and determines whether it's a boat and sets pointer to it
 * \param boat Boat we are visiting
 */
void CIsBoatVisitor::VisitBoat(CBoat* boat)
{
	mIsBoat = true;
	mBoat = boat;
}