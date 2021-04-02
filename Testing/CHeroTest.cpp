/**
 * \file CHeroTest.cpp
 *
 * \author(s) Michael Dittman,
 */

#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <fstream>

#include"Hero.h"
#include "Game.h"
#include <regex>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Gdiplus;

const std::wstring HeroImageName = L"images/sparty.png";
const std::wstring HeroSwappedImageName = L"images/sparty-hit.png";
const std::wstring HeroMaskName = L"images/sparty-mask.png";

shared_ptr<Bitmap> heroBitmap = shared_ptr<Bitmap>(Bitmap::FromFile(HeroImageName.c_str()));
shared_ptr<Bitmap> heroSwappedBitmap = shared_ptr<Bitmap>(Bitmap::FromFile(HeroSwappedImageName.c_str()));
shared_ptr<Bitmap> heroMaskBitmap = shared_ptr<Bitmap>(Bitmap::FromFile(HeroMaskName.c_str()));

namespace Testing
{
	TEST_CLASS(CHeroTest)
	{
	public:

		TEST_METHOD_INITIALIZE(methodName)
		{
			extern wchar_t g_dir[];
			::SetCurrentDirectory(g_dir);
		}
		
		TEST_METHOD(TestNothing)
		{
			// This is an empty test just to ensure the system is working
		}

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
		*  Test a game with just the hero
		* /param filename The filename which contains XML to test
		*/
		void TestHeroType(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			// Ensure the Hero is there
			Assert::IsTrue(regex_search(xml, wregex(L"<level><hero.*</level>")));

		}

		void PopulateHero(CGame* game)
		{
			// Create a new hero
			shared_ptr<CHero> hero = make_shared<CHero>(game, heroBitmap, heroSwappedBitmap, heroMaskBitmap);
			// Add the hero to the game
			game->Add(hero);
		}

		/**
		* Test to ensure an that a file is empty
		* /param filename The filename which contains XML to test
		*/
		void TestEmpty(wstring filename)
		{
			Logger::WriteMessage(filename.c_str());

			wstring xml = ReadFile(filename);
			Logger::WriteMessage(xml.c_str());

			Assert::IsTrue(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
			Assert::IsTrue(regex_search(xml, wregex(L"<level/>")));

		}

		TEST_METHOD(TestCHeroSave)
		{
			// The save method is not important it is only here to save stuff to
			// the temporary directory to test the loading functions.

			// Create a path to temporary files
			wstring path = TempPath();

			// Create a new game
			CGame game;

			// Make sure an empty game saves ok

			// Create a path
			wstring file1 = path + L"CHeroTestEmpty";

			// Save to that path
			game.Save(file1);

			// Make sure its empty
			TestEmpty(file1);

			// Populate with a hero
			PopulateHero(&game);

			// Create another path
			wstring file2 = path + L"CHeroTestOneHero";
			// Save the game with the hero to that path
			game.Save(file2);

			// Make sure that path has the correct tags
			TestHeroType(file2);

		}

		TEST_METHOD(TestCHeroLoad)
		{

			// Create a path to temporary files
			wstring path = TempPath();

			// Create a new game
			CGame game;

			// Create a new path
			wstring file1 = path + L"EmptyTest";

			// Save the game to that path
			game.Save(file1);

			// Make sure its empty
			TestEmpty(file1);

			// Load it again, save it again, make sure its empty
			game.Load(file1);
			game.Save(file1);
			TestEmpty(file1);

			// Populate the game with a hero
			PopulateHero(&game);

			// Create another path
			wstring file2 = path + L"LoadTestOneHero";

			// Save the game to the path
			game.Save(file2);

			// Make sure there is one hero
			TestHeroType(file2);

			// Unsure of how tags will be handled

			// Load the game
			//game.Load(file2);
			//game.Save(file2);

			//TestHeroType(file2);


		}

		TEST_METHOD(TestCHeroMoveForward)
		{

			// Create a new game
			CGame game;
			// Set timer time to nonzero so hero can move
			game.SetTime(5.0);

			// Create a new hero
			shared_ptr<CHero> hero = make_shared<CHero>(&game, heroBitmap, heroSwappedBitmap, heroMaskBitmap);

			// Set its location (irrelevant, but processes for hero creation recorded regardless)
			hero->SetLocation(192, 192);

			// Add the hero item to the game list
			game.Add(hero);
			
			// Set the games hero to this hero
			game.SetHero(hero);

			// Test to ensure the hero's position
			Assert::IsTrue(hero->GetX() == 192);
			Assert::IsTrue(hero->GetY() == 192);

			// Assign the pressed key to be e (move forward)
			UINT nChar = 69;

			// Moves the hero 96 units (before virtual pixels, this will need changing)
			game.moveHero(nChar);

			Assert::IsTrue(hero->GetX() == 192);
			Assert::IsTrue(hero->GetY() == 128);

			// Move forward again
			game.moveHero(nChar);

			// ensure hero doesn't move at top boundary (y didn't change)
			Assert::IsTrue(hero->GetY() == 128);

		}

		TEST_METHOD(TestCHeroMoveBackward)
		{

			// Create a new game
			CGame game;
			// Set timer time to nonzero so hero can move
			game.SetTime(5.0);

			// Create a new hero
			shared_ptr<CHero> hero = make_shared<CHero>(&game, heroBitmap, heroSwappedBitmap, heroMaskBitmap);

			// Set its location (irrelevant, but processes for hero creation recorded regardless)
			hero->SetLocation(0, 0);

			// Add the hero item to the game list
			game.Add(hero);

			// Set the games hero to this hero
			game.SetHero(hero);

			// Test to ensure the hero's position
			Assert::IsTrue(hero->GetX() == 0);
			Assert::IsTrue(hero->GetY() == 0);

			// Assign the pressed key to be e (move backward)
			UINT nChar = 68;

			// Moves the hero 96 units (before virtual pixels, this will need changing)
			game.moveHero(nChar);

			// This will be changed later due to out of bounds testing
			Assert::IsTrue(hero->GetX() == 0);
			Assert::IsTrue(hero->GetY() == 64);

			// Set location at lower boundary
			hero->SetLocation(192, 896);

			// move the hero backward again
			game.moveHero(nChar);

			// Ensure hero doesn't move at lower boundary
			Assert::IsTrue(hero->GetY() == 896);
		}

		TEST_METHOD(TestCHeroMoveRight)
		{

			// Create a new game
			CGame game;
			// Set timer time to nonzero so hero can move
			game.SetTime(5.0);

			// Create a new hero
			shared_ptr<CHero> hero = make_shared<CHero>(&game, heroBitmap, heroSwappedBitmap, heroMaskBitmap);

			// Set its location (irrelevant, but processes for hero creation recorded regardless)
			hero->SetLocation(0, 0);

			// Add the hero item to the game list
			game.Add(hero);

			// Set the games hero to this hero
			game.SetHero(hero);

			// Test to ensure the hero's position
			Assert::IsTrue(hero->GetX() == 0);
			Assert::IsTrue(hero->GetY() == 0);

			// Assign the pressed key to be e (move right)
			UINT nChar = 70;

			// Moves the hero 96 units (before virtual pixels, this will need changing)
			game.moveHero(nChar);

			// This will be changed later due to out of bounds testing
			Assert::IsTrue(hero->GetX() == 64);
			Assert::IsTrue(hero->GetY() == 0);

		}

		TEST_METHOD(TestCHeroMoveLeft)
		{

			// Create a new game
			CGame game;
			// Set timer time to nonzero so hero can move
			game.SetTime(5.0);

			// Create a new hero
			shared_ptr<CHero> hero = make_shared<CHero>(&game, heroBitmap, heroSwappedBitmap, heroMaskBitmap);

			// Set its location (irrelevant, but processes for hero creation recorded regardless)
			hero->SetLocation(0, 0);

			// Add the hero item to the game list
			game.Add(hero);

			// Set the games hero to this hero
			game.SetHero(hero);

			// Test to ensure the hero's position
			Assert::IsTrue(hero->GetX() == 0);
			Assert::IsTrue(hero->GetY() == 0);

			// Assign the pressed key to be e (move left)
			UINT nChar = 83;

			// Moves the hero 96 units (before virtual pixels, this will need changing)
			game.moveHero(nChar);

			// This will be changed later due to out of bounds testing
			Assert::IsTrue(hero->GetX() == -64);
			Assert::IsTrue(hero->GetY() == 0);

		}

		TEST_METHOD(TestCHeroGettersSetters)
		{

			// Create a new game
			CGame game;

			// Create a new hero
			shared_ptr<CHero> hero = make_shared<CHero>(&game, heroBitmap, heroSwappedBitmap, heroMaskBitmap);

			// Set its location (irrelevant, but processes for hero creation recorded regardless)
			hero->SetLocation(0, 0);

			// Add the hero item to the game list
			game.Add(hero);

			// Set the games hero to this hero
			game.SetHero(hero);

			hero->SetOnBoat(false);

			Assert::IsFalse(hero->GetOnBoat());
		}

		TEST_METHOD(TestCHeroClone)
		{
			// Create a new game
			CGame game;

			// Create a new hero
			shared_ptr<CHero> hero = make_shared<CHero>(&game, heroBitmap, heroSwappedBitmap, heroMaskBitmap);

			auto heroClone = hero->CloneHero();
			Assert::IsNotNull(heroClone.get());
		}

	};
}