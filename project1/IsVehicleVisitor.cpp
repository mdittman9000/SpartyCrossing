/**
 * \file IsVehicleVisitor.cpp
 *
 * \author Nikolai Tolmoff
 */

#include "pch.h"
#include "IsVehicleVisitor.h"
#include "Vehicle.h"


 /**
  * Visit a Vehicle object
  * \param vehicle Vehicle object we are visiting.
  */
void CIsVehicleVisitor::VisitVehicle(CVehicle* vehicle)
{
	mIsVehicle = true;
	mVehicle = vehicle;
    mVehicleId = vehicle->GetId();
}
