/**
 * \file Car.h
 *
 * \author Michael Dittman
 *
 * Class that describes the car
 */


#pragma once
#include "Vehicle.h"


/**
 * Class that describes the car
 */
class CCar : public CVehicle
{
public:
    /// Default contructor (disabled)
    CCar() = delete;

    /// Copy constructor
    CCar(const CCar&);

    CCar::CCar(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap1, std::shared_ptr<Gdiplus::Bitmap> bitmap2, double speed, int yPos, int xPos, int width);

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    virtual void Update(double elapsed) override;

    virtual void Draw(Gdiplus::Graphics* graphics) override;

    /** 
    * Clones a car by invoking the copy constructor, returns an item pointer
    * \return pointer to a copied item
    */
    virtual std::shared_ptr<CItem> Clone() const { return std::make_shared<CCar>(*this); }

    /**
    * Gets hit status
    * \returns Hit status
    */
    bool GetHitStatus() { return mHitCar; }

    /** Accept a visitor
    * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override;



private:
    /// Image swap time
    double mSwapTime = .5;

    /// Swapped image
    std::shared_ptr<Gdiplus::Bitmap> mSwappedImage;

    /// Normal image
    std::shared_ptr<Gdiplus::Bitmap> mImage;

    /// Flag if Sparty hit a car
    bool mHitCar = false;

    /// Timer for Image Swap Animation
    double mTimeCar = 0.0;
    /// keeps track of seconds
    double mSeconds = 0.0;
    
  


   


};

