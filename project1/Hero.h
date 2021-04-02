/**
 * \file Hero.h
 *
 * \author(s) Michael Dittman,
 *
 * Class that describes the Hero
 */

#pragma once
#include "Item.h"


/**
 * Class that describes the Hero
 */
class CHero : public CItem
{

public:
    /// Default constructor (disabled)
    CHero() = delete;

    /// Copy constructor
    CHero(const CHero&);

    CHero::CHero(CGame* game, std::shared_ptr<Gdiplus::Bitmap> bitmap, std::shared_ptr<Gdiplus::Bitmap> swapped,
        std::shared_ptr<Gdiplus::Bitmap> mask);

    virtual std::shared_ptr<xmlnode::CXmlNode> 
        XmlSave(const std::shared_ptr<xmlnode::CXmlNode>& node) override;

    void moveForward();

    void moveBackward();

    void moveLeft();

    void moveRight();

    /** Accept a visitor
     * \param visitor The visitor we accept */
    virtual void Accept(CItemVisitor* visitor) override { visitor->VisitHero(this); }

    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node);

    /** Clones a hero by invoking the copy constructor, returns an item pointer
    * \return pointer to a copied object
    */
    virtual std::shared_ptr<CItem> Clone() const { return std::make_shared<CHero>(*this); }

    /** Clones a hero by invoking the copy constructor, returns a hero pointer
    * \return pointer to a copied hero
    */
    std::shared_ptr<CHero> CloneHero() const { return std::make_shared<CHero>(*this); }

    /** Gets whether hero is on boat
    * \return Whether hero is on a boat.
    */
    bool GetOnBoat() { return mOnBoat; }

    /** Sets whether hero is on boat
    * \param onBoat Whether hero is on a boat.
    */
    void SetOnBoat(bool onBoat) { mOnBoat = onBoat; }

    /// Setter for whether hero is on a sketchy boat
    /// \param onSketchy what to set mOnSketchy to
    void SetOnSketchy(bool onSketchy) { mOnSketchy = onSketchy; }

    /// Getter for whether hero is on a sketchy boat.
    /// \return whether hero is on a sketchy boat
    bool GetOnSketchy() const { return mOnSketchy; }

    /** Gets whether hero is carrying something.
    * \returns Whether hero is carrying something.
    */
    bool GetCarrying() { return mIsCarrying; }

    /** Sets whether hero is carrying something.
    * \param carrying Whether hero is carrying something.
    */
    void SetCarrying(bool carrying) { mIsCarrying = carrying; }

    /** Sets speed of hero
    * \param speed Speed of hero
    */
    void SetSpeed(double speed) { mSpeed = speed; }

    void Update(double elapsed);

    /** Return hero name
    * \return mName Name of the hero
    */
    std::wstring GetHeroName() { return mName; }

    virtual void Draw(Gdiplus::Graphics* graphics) override;

private:
    /// Name of hero
    std::wstring mName;

    /// Speed of hero (non zero when on boat)
    double mSpeed = 0.0;

    /// Whether the hero is floating on a boat
    bool mOnBoat = false;

    /// Whether the hero is floating on a sketchy boat
    bool mOnSketchy = false;

    /// Whether or not hero is carrying Cargo
    bool mIsCarrying = false;

    /// The swapped image of this item
    std::shared_ptr<Gdiplus::Bitmap> mSwappedItemImage;

    /// The mask for the hero when falling in river
    std::shared_ptr<Gdiplus::Bitmap> mItemMask;
};

