// FileTests.cpp - Defines the FileTests class and tests.
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

#include "FileTests.h"

using ::testing::InSequence;

FileTests::FileTests()
{
    mockFileStream = std::make_shared<MockFileStream>();
    mockFileSystem = std::make_shared<MockFileSystem>();
    testFile = std::make_shared<Binary::File>(mockFileStream, mockFileSystem);
}

TEST_F(FileTests, InitializesAFileWithAFilenameProperly)
{
    Binary::File fileWithFileName{ "Test.txt" };

    auto p = std::dynamic_pointer_cast<Binary::StandardFileStream>(
        fileWithFileName.Stream());
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->FileName(), "Test.txt");
}

TEST_F(FileTests, InitializesAFileWithDependeciesProperly)
{   
    EXPECT_EQ(testFile->Stream(), mockFileStream);
    EXPECT_EQ(testFile->System(), mockFileSystem);
}

TEST_F(FileTests, LoadsFileProperly)
{
    std::shared_ptr<Binary::DataStructure> data = testFile->Structure();
    ASSERT_NE(data, nullptr);

    auto object1 = std::make_shared<MockObject>();
    auto object2 = std::make_shared<MockObject>();
    auto object3 = std::make_shared<MockObject>();
    data->Add(object1);
    data->Add(object2);
    data->Add(object3);

    {
        InSequence seq;

        EXPECT_CALL(*object1, Read(mockFileStream.get()));
        EXPECT_CALL(*object2, Read(mockFileStream.get()));
        EXPECT_CALL(*object3, Read(mockFileStream.get()));
    }

    testFile->Load();
}

TEST_F(FileTests, SavesFileProperly)
{
    std::shared_ptr<Binary::DataStructure> data = testFile->Structure();
    ASSERT_NE(data, nullptr);

    auto object1 = std::make_shared<MockObject>();
    auto object2 = std::make_shared<MockObject>();
    auto object3 = std::make_shared<MockObject>();
    data->Add(object1);
    data->Add(object2);
    data->Add(object3);

    {
        InSequence seq;

        EXPECT_CALL(*object1, Write(mockFileStream.get()));
        EXPECT_CALL(*object2, Write(mockFileStream.get()));
        EXPECT_CALL(*object3, Write(mockFileStream.get()));
    }

    testFile->Load();
}