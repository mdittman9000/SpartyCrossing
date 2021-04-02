/**
 * \file ItemVisitor.h
 *
 * \author Nikolai Tolmoff
 *
 * Item visitor base class.
 */

#pragma once

// Forward reference to all item types
class CCargo;
class CVehicle;
class CCar;
class CHero;
class CDecor;
class CBoat;
class CSketchyBoat;

/** Item visitor base class */
class CItemVisitor
{
public:
	virtual ~CItemVisitor() {}

	/** Visit a CCargo object
	 * \param cargo Cargo we are visiting */
	virtual void VisitCargo(CCargo* cargo) {}

	/** Visit a CVehicle object
	 * \param vehicle Vehicle we are visiting */
	virtual void VisitVehicle(CVehicle* vehicle) {}

	/** Visit a CVehicle object
	* \param car car we are visiting */
	virtual void VisitCar(CCar* car) {}

	/** Visit a CHero object
	 * \param hero Hero we are visiting */
	virtual void VisitHero(CHero* hero) {}

	/** Visit a CDecor object
	 * \param decor Decor we are visiting */
	virtual void VisitDecor(CDecor* decor) {}

	/** Visit a CBoat object
	 * \param boat Boat we are visiting */
	virtual void VisitBoat(CBoat* boat) {}

	/** Visit a CSketchyBoat object
	* \param boat Boat we are visiting */
	virtual void VisitSketchy(CSketchyBoat* boat) {}
};

