// DataStructureTests.cpp - Defines the DataStructureTests class.
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

#include "DataStructureTests.h"

using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;

DataStructureTests::DataStructureTests()
{
    mockObject1 = std::make_shared<MockObject>();
    mockObject2 = std::make_shared<MockObject>();
    mockObject3 = std::make_shared<MockObject>();
    mockStream = std::make_shared<MockStream>();
}

void DataStructureTests::AddMockObjectsToStructure()
{
    testStructure.Add(mockObject1);
    testStructure.Add(mockObject2);
    testStructure.Add(mockObject3);
}

TEST_F(DataStructureTests, StructureInitializedEmpty)
{
    EXPECT_EQ(testStructure.Count(), 0);
}

TEST_F(DataStructureTests, AddsObjectsSuccessfully)
{
    AddMockObjectsToStructure();
    std::vector<std::shared_ptr<Binary::Object>> objects 
        = testStructure.Objects();

    ASSERT_EQ(objects.size(), 3);
    EXPECT_EQ(testStructure.Count(), 3);
    EXPECT_EQ(objects.at(0), mockObject1);
    EXPECT_EQ(objects.at(1), mockObject2);
    EXPECT_EQ(objects.at(2), mockObject3);
}

TEST_F(DataStructureTests, RemovesObjectsSuccessfully)
{
    AddMockObjectsToStructure();
    
    testStructure.Remove(mockObject2);
    std::vector<std::shared_ptr<Binary::Object>> objects 
        = testStructure.Objects();
    
    ASSERT_EQ(objects.size(), 2);
    EXPECT_EQ(testStructure.Count(), 2);
    EXPECT_EQ(objects.at(0), mockObject1);
    EXPECT_EQ(objects.at(1), mockObject3);
}

TEST_F(DataStructureTests, DoesNotAddNullPointers)
{
    EXPECT_THROW(testStructure.Add(nullptr), std::invalid_argument);
}

TEST_F(DataStructureTests, DoesNotRemoveNullPointers)
{
    EXPECT_THROW(testStructure.Remove(nullptr), std::invalid_argument);
}

TEST_F(DataStructureTests, CalculatesSizeCorrectlyWhenAllObjectsHaveValidSize)
{
    AddMockObjectsToStructure();
    std::vector<std::shared_ptr<Binary::Object>> objects 
        = testStructure.Objects();

    EXPECT_CALL(*mockObject1, Size())
        .WillRepeatedly(Return(1));
    EXPECT_CALL(*mockObject2, Size())
        .WillRepeatedly(Return(2));
    EXPECT_CALL(*mockObject3, Size())
        .WillRepeatedly(Return(3));

    EXPECT_EQ(testStructure.Size(), 6);
}

TEST_F(DataStructureTests, ReadsFromStreamProperly)
{
    AddMockObjectsToStructure();

    {
        InSequence seq;

        EXPECT_CALL(*mockObject1, Read(mockStream.get()));
        EXPECT_CALL(*mockObject2, Read(mockStream.get()));
        EXPECT_CALL(*mockObject3, Read(mockStream.get()));
    }

    testStructure.Read(mockStream.get());
}

TEST_F(DataStructureTests, WritesToStreamProperly)
{
    AddMockObjectsToStructure();

    {
        InSequence seq;

        EXPECT_CALL(*mockObject1, Write(mockStream.get()));
        EXPECT_CALL(*mockObject2, Write(mockStream.get()));
        EXPECT_CALL(*mockObject3, Write(mockStream.get()));
    }

    testStructure.Write(mockStream.get());
}

TEST_F(DataStructureTests, OutputsAllObjectsToString)
{
    AddMockObjectsToStructure();
    std::stringstream expectedOutput;
    expectedOutput << "1" << std::endl << "2" << std::endl << "3" << std::endl;

    {
        InSequence seq;

        EXPECT_CALL(*mockObject1, ToString())
            .WillRepeatedly(Return("1"));
        EXPECT_CALL(*mockObject2, ToString())
            .WillRepeatedly(Return("2"));
        EXPECT_CALL(*mockObject3, ToString())
            .WillRepeatedly(Return("3"));
    }

    EXPECT_EQ(testStructure.ToString(), expectedOutput.str());
}

TEST_F(DataStructureTests, OutputsAllObjectsToStringWithSpecifiedFormat)
{
    AddMockObjectsToStructure();
    std::stringstream expectedOutput;
    expectedOutput << "00000001" << std::endl 
                   << "00000010" << std::endl 
                   << "00000011" << std::endl;

    {
        InSequence seq;

        EXPECT_CALL(*mockObject1, ToString(Binary::Format::Bin))
            .WillRepeatedly(Return("00000001"));
        EXPECT_CALL(*mockObject2, ToString(Binary::Format::Bin))
            .WillRepeatedly(Return("00000010"));
        EXPECT_CALL(*mockObject3, ToString(Binary::Format::Bin))
            .WillRepeatedly(Return("00000011"));
    }

    EXPECT_EQ(testStructure.ToString(Binary::Format::Bin), 
              expectedOutput.str());
}