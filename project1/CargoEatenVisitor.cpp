/**
 * \file CargoEatenVisitor.cpp
 *
 * \author Nikolai Tolmoff
 */

#include "pch.h"
#include "CargoEatenVisitor.h"
#include "Cargo.h"
#include <cmath>

/// Number of pixels wide and tall a tile is.
const double TileToPixels = 64;

 /**
  * Visit a Cargo object
  * \param cargo Cargo object we are visiting.
  */
void CCargoEatenVisitor::VisitCargo(CCargo* cargo)
{
	if (mSmallCargo == nullptr)
	{
		mSmallCargo = cargo;
	}
	else if (mMediumCargo == nullptr)
	{
		mMediumCargo = cargo;
	}
	else
	{
		mLargeCargo = cargo;
		if (mSmallCargo->GetY() == mMediumCargo->GetY() &&
			abs(mSmallCargo->GetY() - mHero->GetY()) > TileToPixels)
		{
			mSmallEaten = true;
		}
		if (mMediumCargo->GetY() == mLargeCargo->GetY() &&
			abs(mMediumCargo->GetY() - mHero->GetY()) > TileToPixels)
		{
			mMediumEaten = true;
		}
	}
}
