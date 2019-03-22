#include "gtest/gtest.h"
#include "lib.h"

TEST(version_tests, test1)
{
	ASSERT_TRUE(version()>0);
}

