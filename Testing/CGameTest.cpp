/**
 * \file CGameTest.cpp
 *
 * \author(s) Michael Dittman,
 *
 * Test the functionality of CGame
 */



#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <regex>
#include <streambuf>
#include <fstream>
#include "Game.h"
#include "Cargo.h"
#include "Vehicle.h"
#include "Hero.h"
#include "Decor.h"
#include "IsCargoVisitor.h"


using namespace std;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace Gdiplus;

wstring gameTestFilename = L"images/road1.png";
namespace Testing
{
	class CTestVisitor : public CItemVisitor
	{
	public:
		virtual void VisitCargo(CCargo* cargo) { mNumCargo++; }
		virtual void VisitVehicle(CVehicle* vehicle) { mNumVehicles++; }
		virtual void VisitHero(CHero* hero) { mNumHeroes++; }
		virtual void VisitDecor(CDecor* decor) { mNumDecors++; }

		int mNumCargo = 0;
		int mNumVehicles = 0;
		int mNumHeroes = 0;
		int mNumDecors = 0;
	};

	TEST_CLASS(CGameTest)
	{
	public:

		/**
		 * Create a path to a place to put temporary files
		 */
		wstring TempPath()
		{
			// Create a path to temporary files
			wchar_t path_nts[MAX_PATH];
			GetTempPath(MAX_PATH, path_nts);

			// Convert null terminated string to wstring
			return wstring(path_nts);
		}

		/**
		 * Read a file into a wstring and return it.
		 * \param filename Name of the file to read
		 * \return File contents
		 */
		wstring ReadFile(const wstring& filename)
		{
			ifstream t(filename);
			wstring str((istreambuf_iterator<char>(t)),
				istreambuf_iterator<char>());

			return str;
		}

		/**
		* Test to ensure a file is compatible with game
		*/
		void TestIsXml(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<level/>")));
		}

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}

		TEST_METHOD(TestCGameConstruct)
		{
			CGame game;
		}

		TEST_METHOD(TestCGameLoad)
		{

			// Create a path to temporary files
			wstring tempPath = TempPath();

			CGame game;

			wstring file1 = tempPath + L"level0";

			wstring path = L".\\levels\\";
			wstring file2 = path + L"level1.xml";

			// Load level 1 and save it to temp folder
			game.Load(file2);
			wstring file3 = tempPath + L"level1.xml";
			game.Save(file3);

			TestIsXml(file3);
		}

		TEST_METHOD(TestCGameVisitor)
		{
			shared_ptr<Bitmap> bitmap = shared_ptr<Bitmap>(Bitmap::FromFile(gameTestFilename.c_str()));
			// Construct a game
			CGame game;

			// Ensure no visit functions called on empty game
			CTestVisitor visitor;
			game.Accept(&visitor);
			Assert::AreEqual(0, visitor.mNumCargo,
				L"Visitor number of cargo objects");
			Assert::AreEqual(0, visitor.mNumVehicles,
				L"Visitor number of vehicle objects");
			Assert::AreEqual(0, visitor.mNumHeroes,
				L"Visitor number of hero objects");
			Assert::AreEqual(0, visitor.mNumDecors,
				L"Visitor number of decor objects");

			// Add one of each object
			auto cargo = make_shared<CCargo>(&game, bitmap, bitmap);
			auto vehicle = make_shared<CVehicle>(&game, bitmap);
			auto hero = make_shared<CHero>(&game, bitmap, bitmap, bitmap);
			auto decor = make_shared<CDecor>(&game, bitmap);

			game.Add(cargo);
			game.Add(vehicle);
			game.Add(hero);
			game.Add(decor);

			// Ensure every visit function works
			CTestVisitor visitor2;
			game.Accept(&visitor2);
			Assert::AreEqual(1, visitor2.mNumCargo,
				L"Visitor number of cargo objects");
			Assert::AreEqual(1, visitor2.mNumVehicles,
				L"Visitor number of vehicle objects");
			Assert::AreEqual(1, visitor2.mNumHeroes,
				L"Visitor number of hero objects");
			Assert::AreEqual(1, visitor2.mNumDecors,
				L"Visitor number of decor objects");
		}

		TEST_METHOD(TestGameHitTest)
		{
			shared_ptr<Bitmap> bitmap = shared_ptr<Bitmap>(Bitmap::FromFile(gameTestFilename.c_str()));
			// Construct a game
			CGame game;

			// Add one of each object
			auto cargo = make_shared<CCargo>(&game, bitmap, bitmap);
			auto vehicle = make_shared<CVehicle>(&game, bitmap);
			auto hero = make_shared<CHero>(&game, bitmap, bitmap, bitmap);
			auto decor = make_shared<CDecor>(&game, bitmap);

			game.Add(cargo);
			game.Add(vehicle);
			game.Add(hero);
			game.Add(decor);

			// Set their positions
			cargo->SetLocation(100, 200);
			vehicle->SetLocation(400, 200);
			hero->SetLocation(100, 500);
			decor->SetLocation(400, 500);

			Assert::IsTrue(game.HitTest(100, 200) != nullptr);
			Assert::IsTrue(game.HitTest(400, 200) == nullptr);
			Assert::IsTrue(game.HitTest(100, 500) == nullptr);
			Assert::IsTrue(game.HitTest(400, 500) == nullptr);

		}

	};
}