/**
 * \file Rectangle.cpp
 *
 * \author Andrew Haakenson
 */

#include "pch.h"
#include "Rectangle.h"
#include <sstream>

using namespace Gdiplus;
using namespace std;

/// Number of pixels wide and tall a tile is.
const int TileToPixels = 64;

/**
 * Constructor for CRectangle.
 *
 * \param game Pointer to the game this rectangle is a part of
 */
CRectangle::CRectangle(CGame* game) :
	CDecor(game)
{
}

/**
 * Copy constructor
 * \param rectangle Rectangle being copied
 */
CRectangle::CRectangle(const CRectangle& rectangle) : CDecor(rectangle)
{
	mColor = rectangle.mColor;
	mHeight = rectangle.mHeight;
	mWidth = rectangle.mWidth;
}

/**
 * Draws a rectangle object onto the screen
 *
 * \param graphics Graphics device to draw on
 */
void CRectangle::Draw(Gdiplus::Graphics* graphics)
{
	double xCoordinate = GetX();
	double yCoordinate = GetY();
	SolidBrush brush(Color(mColor[0], mColor[1], mColor[2]));
	// Repeats drawing rectangles in both directions
	for (int x = 0; x < GetRepeatX(); x++)
	{
		for (int y = 0; y < GetRepeatY(); y++)
		{
			// Draws a filled rectangle
			graphics->FillRectangle(&brush, 
				(int)xCoordinate + x * TileToPixels, (int)yCoordinate + y * TileToPixels, 
				(int)(mWidth * (double)TileToPixels) + 1, (int)(mHeight * (double)TileToPixels) + 1);
		}
	}
}

/**
 * Load the attributes for a rectangle node.
 *
 * \param node The Xml node we are loading the decor from
 */
void CRectangle::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
	CDecor::XmlLoad(node);

	// Save height and width
	double height = node->GetAttributeDoubleValue(L"height", 0);
	double width = node->GetAttributeDoubleValue(L"width", 0);
	mHeight = height;
	mWidth = width;

	wstring colors = node->GetAttributeValue(L"color", L"");
	wstringstream stream(colors);
	wstring colorString;
	int i = 0;
	// Split the color string into ints and put in respective spot on color vector
	while (getline(stream, colorString, L','))
	{
		int colorInt = stoi(colorString);
		mColor[i] = colorInt;
		i++;
	}
	
}