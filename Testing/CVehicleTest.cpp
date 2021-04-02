/**
 * \file CVehicleTest.cpp
 *
 * \author Michael Dittman
 */
#include "pch.h"
#include "CppUnitTest.h"
#include "Vehicle.h"
#include <memory>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Gdiplus;

namespace Testing
{

	/** Mock class for CVehicle */
	class CVehicleMock : public CItem
	{
	public:
		CVehicleMock(CGame* game, shared_ptr<Bitmap> bitmap) : CItem(game, bitmap) {}

	};

	TEST_CLASS(CVehicleTest)
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

		

	};
}