// StreamTests.cpp - Defines the StreamTests class and tests.
//
// Copyright (C) 2024 Stephen Bonar
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http ://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissionsand
// limitations under the License.

#include "StreamTests.h"

using ::testing::Return;

StreamTests::StreamTests()
{
    testStream = std::make_shared<MockStream>();
}

TEST_F(StreamTests, BeginningPositionIsZero)
{
    EXPECT_EQ(testStream->Beginning(), 0);
}

TEST_F(StreamTests, SizeIsEnd)
{
    EXPECT_CALL(*testStream, End())
        .WillRepeatedly(Return(1));

    EXPECT_EQ(testStream->Size(), testStream->End());
}

TEST_F(StreamTests, CorrectlyIdentifiesBeginningPosition)
{
    EXPECT_CALL(*testStream, Position())
        .WillRepeatedly(Return(0));

    EXPECT_TRUE(testStream->IsAtBeginning());
}

TEST_F(StreamTests, CorrectlyIdentifiesEndPosition)
{
    EXPECT_CALL(*testStream, Position())
        .WillRepeatedly(Return(1));
    EXPECT_CALL(*testStream, End())
        .WillRepeatedly(Return(1));

    EXPECT_TRUE(testStream->IsAtEnd());
}
