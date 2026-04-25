// ChunkHeaderTests.cpp - Defines the ChunkHeaderTests class and tests.
//
// Copyright (C) 2026 Stephen Bonar
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
// See the License for the specific language governing permissions and
// limitations under the License.

#include "ChunkHeaderTests.h"

ChunkHeaderTests::ChunkHeaderTests()
{

}

TEST_F(ChunkHeaderTests, ProperlyObtainsFieldPointers)
{
    Binary::ChunkHeader header;
    std::vector<Binary::DataField*> fields = header.Fields();

    ASSERT_EQ(fields.size(), 2);
    EXPECT_EQ(fields[0], &header.id);
    EXPECT_EQ(fields[1], &header.dataSize);
}

TEST_F(ChunkHeaderTests, ProperlyObtainsSize)
{
    Binary::ChunkHeader header;

    EXPECT_EQ(header.Size(), header.id.Size() + header.dataSize.Size());
}

TEST_F(ChunkHeaderTests, CopyAssignmentOperatorPerformsDeepCopy)
{
    Binary::ChunkHeader header1;
    header1.id.SetValue("TEST");
    header1.dataSize.SetValue(255);

    Binary::ChunkHeader header2;
    header2 = header1;

    EXPECT_EQ(header2.id.Value(), header1.id.Value());
    EXPECT_EQ(header2.dataSize.Value(), header1.dataSize.Value());
}