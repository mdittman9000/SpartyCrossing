#include "pch.h"
#include "CppUnitTest.h"

#include "Item.h"
#include "Game.h"
#include "Level.h"
#include "Vehicle.h"
#include "Decor.h"
#include <string>
#include <memory>

using namespace Gdiplus;
using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

wstring filename = L"images/road1.png";

namespace Testing
{

	/** Mock class for testing CIitem */
	class CItemMock : public CItem
	{
	public:
		CItemMock(CGame* game, shared_ptr<Bitmap> bitmap) : CItem(game, bitmap) {}

		/** Accept a visitor
		* \param visitor The visitor we accept */
		virtual void Accept(CItemVisitor* visitor) override { }

		virtual std::shared_ptr<CItem> Clone() const { return std::make_shared<CItemMock>(*this); }
	};
	TEST_CLASS(CItemTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestCItemGettersSetters)
		{
			shared_ptr<Bitmap> itemBitmap = shared_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
			// Construct an item to test
			CGame game;
			CItemMock item(&game, itemBitmap);

			// Test SetLocation, GetX, and GetY
			item.SetLocation(9.3, 15.6);
			Assert::AreEqual(9.3, item.GetX(), 0.0001);
			Assert::AreEqual(15.6, item.GetY(), 0.0001);
			
			// Test GetGame
			Assert::IsTrue(&game == item.GetGame());

			unique_ptr<Bitmap> image = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
			item.GetHeight();
			// Test GetWidth and GetHeight
			Assert::AreEqual(image->GetWidth(), item.GetWidth(), 0.0001);
			Assert::AreEqual(image->GetHeight(), item.GetHeight(), 0.0001);
		}

		TEST_METHOD(TestCItemClone)
		{
			shared_ptr<Bitmap> bitmap = shared_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
			// Construct a game
			CGame game;

			// Add one of each object
			auto cargo = make_shared<CCargo>(&game, bitmap, bitmap);
			auto vehicle = make_shared<CVehicle>(&game, bitmap);
			auto decor = make_shared<CDecor>(&game, bitmap);

			// Clone each object
			auto cargoClone = cargo->Clone();
			auto vehicleClone = vehicle->Clone();
			auto decorClone = decor->Clone();

			// Check that the clones are not just nullptrs
			Assert::IsNotNull(cargoClone.get());
			Assert::IsNotNull(vehicleClone.get());
			Assert::IsNotNull(decorClone.get());
		}

	};
}