/**
 * \file IsCarVisitor.cpp
 *
 * \author Andrew Haakenson
 */

#include "pch.h"
#include "IsCarVisitor.h"
#include "car.h"


 /**
  * Visit a Car object
  * \param car Car object we are visiting.
  */
void CIsCarVisitor::VisitCar(CCar* car)
{
	mIsCar = true;
	mCar = car;
	mCarId = car->GetId();
}