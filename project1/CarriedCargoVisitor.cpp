/**
 * \file CarriedCargoVisitor.cpp
 *
 * \author Nikolai Tolmoff
 */

#include "pch.h"
#include "CarriedCargoVisitor.h"
#include "Cargo.h"


 /**
  * Visit a Cargo object
  * \param cargo Cargo object we are visiting.
  */
void CCarriedCargoVisitor::VisitCargo(CCargo* cargo)
{
	if (cargo->GetCarryStatus())
	{
		mCarriedCargo = cargo;
	}
}
