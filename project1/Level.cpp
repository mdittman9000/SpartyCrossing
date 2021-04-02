/**
 * \file Level.cpp
 *
 * \author Andrew Haakenson
 */

#include "pch.h"
#include "Level.h"
#include "Item.h"
#include "XmlNode.h"
#include "Vehicle.h"
#include "Decor.h"
#include "Rectangle.h"
#include "Cargo.h"
#include "Boat.h"
#include "SketchyBoat.h"
#include "Car.h"
#include <memory>
#include <map>
#include <vector>
#include <string>

using namespace std;
using namespace Gdiplus;
using namespace xmlnode;

/// Number of pixels wide and tall a tile is.
const double TileToPixels = 64;

/**
 * Constructor
 * 
 * \param game Pointer to game this level is a part of
 */
CLevel::CLevel(CGame* game) : mGame(game)
{
}

/**
 * Loads an image from a file
 * 
 * \param filename file to load image from
 * \return bitmap of image from file
 */
shared_ptr<Bitmap> LoadImage(wstring& filename)
{
    shared_ptr<Bitmap> image = shared_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
    if (image->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += filename;
        AfxMessageBox(msg.c_str());
    }
    return image;
}

/**
 * Function to load in the contents of each level
 *
 * Load will be called inititally to Add the contents of an
 * XML file to the vector of items. It will be used again
 * when conditions for a new level to be loaded are met,
 * (clear will erase the contents of the old level)
 *
 * \param filename the Filename to load from
 */
void CLevel::Load(const std::wstring& filename)
{
    
    // We surround with a try/catch to handle errors
    try
    {
        // Open the document to read
        shared_ptr<CXmlNode> root = CXmlNode::OpenDocument(filename);

        //
        // Traverse the children of the root
        // node of the XML document in memory!!!!
        //
        for (auto section : root->GetChildren())
        {

            // Types section of xml document
            if (section->GetType() == NODE_ELEMENT && section->GetName() == L"types")
            {
                // Go through each node in types section
                for (auto node : section->GetChildren())
                {
                    // If the type was decor or boat or sketchy boat
                    if (node->GetType() == NODE_ELEMENT && (node->GetName() == L"decor" || node->GetName() == L"boat"))
                    {
                        wstring imageName = L".\\images\\" + node->GetAttributeValue(L"image", L"");
                        wstring id = node->GetAttributeValue(L"id", L"");
                        mImageMap[id].push_back(LoadImage(imageName));
                    }

                    // If the type was car
                    if (node->GetType() == NODE_ELEMENT && (node->GetName() == L"car" || node->GetName() == L"sketchy"))
                    {
                        wstring imageName1 = L".\\images\\" + node->GetAttributeValue(L"image1", L"");
                        wstring imageName2 = L".\\images\\" + node->GetAttributeValue(L"image2", L"");
                        wstring id = node->GetAttributeValue(L"id", L"");
                        mImageMap[id].push_back(LoadImage(imageName1));
                        mImageMap[id].push_back(LoadImage(imageName2));
                    }
                }
            }

            // Background section of xml document
            else if (section->GetType() == NODE_ELEMENT && section->GetName() == L"background")
            {
                // Go through each node in background section
                for (auto node : section->GetChildren())
                {
                    // Decor or rectangle node
                    if (node->GetType() == NODE_ELEMENT && (node->GetName() == L"decor" || node->GetName() == L"rect"))
                    {
                        XmlItem(node);
                    }
                }
            }

            // Hero or cargo tag
            else if (section->GetType() == NODE_ELEMENT && (section->GetName() == L"hero" || section->GetName() == L"cargo"))
            {
                wstring imageName = L".\\images\\" + section->GetAttributeValue(L"image", L"");
                // Hero will have no id
                wstring id = section->GetAttributeValue(L"id", L"");
                mImageMap[id].push_back(LoadImage(imageName));

                // Load hit image and mask for hero
                if (section->GetName() == L"hero")
                {
                    wstring hitImageName = L".\\images\\" + section->GetAttributeValue(L"hit-image", L"");
                    wstring maskImageName = L".\\images\\" + section->GetAttributeValue(L"mask", L"");
                    mImageMap[id].push_back(LoadImage(hitImageName));
                    if (maskImageName != L".\\images\\")
                    {
                        mImageMap[id].push_back(LoadImage(maskImageName));
                    }
                    // Makes mask image the same as default hero image for level 0 to prevent crash
                    else
                    {
                        mImageMap[id].push_back(LoadImage(imageName));
                    }

                }
                // Load carried image for cargo
                else if (section->GetName() == L"cargo")
                {
                    wstring carriedImageName = L".\\images\\" + section->GetAttributeValue(L"carried-image", L"");
                    mImageMap[id].push_back(LoadImage(carriedImageName));
                }
                XmlItem(section);
            }
            // Road or river tag
            else if (section->GetType() == NODE_ELEMENT && (section->GetName() == L"road" || section->GetName() == L"river"))
            {
                // Get speed and width of the road/river
                double speed = section->GetAttributeDoubleValue(L"speed", 1.0);
                int width = section->GetAttributeIntValue(L"width", 1);
                int yPos = section->GetAttributeIntValue(L"y", 0); 

                // Iterate through the cars and boats and create objects from them
                for (auto node : section->GetChildren())
                {
                    XmlItem(node, speed, width, yPos);
                }
            }

        }

        /*
        // Copy over hero and cargo items to item vector
        for (auto& item : mTempHeroCargoVec)
        {
            Add(item);
        }
        // Delete cargo hero vector
        mTempHeroCargoVec.erase(mTempHeroCargoVec.begin(), mTempHeroCargoVec.end());
        */

    }
    catch (CXmlNode::Exception ex)
    {
        AfxMessageBox(ex.Message().c_str());
    }

}

/**
* Handle an item node.
* \param node Pointer to XML node we are handling
* \param speed Speed of vehicles on road or river, default value of 0.0
* \param width Width of river or road, default value of 0
* \param yPos y position of the item, default value of 0
*/
void CLevel::XmlItem(const std::shared_ptr<xmlnode::CXmlNode>& node, const double speed, const int width, const int yPos)
{
    // A pointer for the item we are loading
    shared_ptr<CItem> item;
    // Determines which vector to add item to
    bool heroCargo = false;

    wstring id = node->GetAttributeValue(L"id", L"");

    // We have an item.  What type?
    wstring type = node->GetName();
    if (type == L"decor")
    {
        item = make_shared<CDecor>(mGame, mImageMap[id][0]);
    }
    else if (type == L"rect")
    {
        item = make_shared<CRectangle>(mGame);
    }
    /* Format of car vector in map:
    * [0]- default image
    * [1]- second image
    */
    else if (type == L"car")
    {
        int xPos = node->GetAttributeIntValue(L"x", 0);
        item = make_shared<CCar>(mGame, mImageMap[id][0], mImageMap[id][1], speed * TileToPixels, 
            (int)(32 + yPos * TileToPixels), (int)(xPos * TileToPixels), width);
    }
    else if (type == L"boat")
    {
        int xPos = node->GetAttributeIntValue(L"x", 0);
        item = make_shared<CBoat>(mGame, mImageMap[id][0], speed * TileToPixels, 
            (int)(32 + yPos * TileToPixels), (int)(xPos * TileToPixels), width);
    }
    else if (type == L"sketchy")
    {
        int xPos = node->GetAttributeIntValue(L"x", 0);
        item = make_shared<CSketchyBoat>(mGame, mImageMap[id][0], mImageMap[id][1], speed * TileToPixels,
            (int)(32 + yPos * TileToPixels), (int)(xPos * TileToPixels), width);
    }
    /* Format of hero vector in map:
    * [0]- default image
    * [1]- hit image
    * [2]- mask
    */
    else if (type == L"hero")
    {
        // FIX: masked image is currently not loaded to mImageMap
        shared_ptr<CHero> hero = make_shared<CHero>(mGame, mImageMap[id][0], mImageMap[id][1], mImageMap[id][2]);
        mHero = hero; 
        hero->XmlLoad(node);
        // Hero isn't added to any vector so just return
        return;
    }
    /* Format of cargo vector in map:
    * [0]- default image
    * [1]- carried image
    */
    else if (type == L"cargo")
    {
        heroCargo = true;
        item = make_shared<CCargo>(mGame, mImageMap[id][0], mImageMap[id][1]);
    }

    // Item exists, add it to one of the vectors
    if (item != nullptr)
    {
        item->XmlLoad(node);

        if (!heroCargo)
        {
            Add(item);
        }
        else
        {
            AddCargo(item);
        }
    }
}

/**
 * Adds an item to this level
 * 
 * \param item item to add to level vector
 */
void CLevel::Add(std::shared_ptr<CItem> item)
{
    mBelowHero.push_back(item);
}

/**
 * Adds an item to cargo vector
 *
 * \param item item to add to cargo vector
 */
void CLevel::AddCargo(std::shared_ptr<CItem> item)
{
    mAboveHero.push_back(item);
}