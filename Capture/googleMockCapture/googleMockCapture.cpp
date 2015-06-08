// googleMockCapture.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <gtest\gtest.h>
#include <gmock\gmock.h>
#include "BackgndSubtractorGMM.h"

int add(int a,int b){ return a+b;};

int _tmain(int argc, char** argv)
{
	testing::InitGoogleTest(&argc,argv);
	RUN_ALL_TESTS();
	return 0;
}

TEST(Easy, Pos)
{
	EXPECT_EQ(4,add(2,2));
}
