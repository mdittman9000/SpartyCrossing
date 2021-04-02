/**
 * \file IsSketchyVisitor.cpp
 * 
 * \author Ethan Strain
 */
#include "pch.h"
#include "IsSketchyVisitor.h"


/** Visits a SketchyBoat and sets member variables accordingly
 * \param boat Pointer to boat we are visiting
 */
void CIsSketchyVisitor::VisitSketchy(CSketchyBoat* boat)
{
	mIsSketchy = true;
	mSketchyBoat = boat;
}
