// RawFileStreamTests.cpp - Defines the RawFileStreamTests class and tests.
//
// Copyright (C) 2025 Stephen Bonar
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

#include "RawFileStreamTests.h"

const char* testFileName{ "test.bin" };
const char* testFullPath{ "/test/test.bin" };
const std::vector<char> stringFieldData{ 'T', 'e', 's', 't', 'i', 'n', 'g', '!' };
const std::vector<char> rawFieldData{ 0xA, 0xB, 0xC, 0xD };

RawFileStreamTests::RawFileStreamTests() 
{
    GenerateTestFile();
}

void RawFileStreamTests::GenerateTestFile()
{
    
    std::fstream stream;
    stream.open(testFileName, std::ios::out | std::ios::binary);

    stream.write(stringFieldData.data(), stringFieldData.size());
    stream.write(rawFieldData.data(), rawFieldData.size());
}

TEST_F(RawFileStreamTests, InitializesStreamProperly)
{
    Binary::RawFileStream stream{ testFileName };

    EXPECT_EQ(stream.FileName(), testFileName);
    EXPECT_EQ(stream.FilePath(), testFileName);
    EXPECT_EQ(stream.IsOpen(), false);
    EXPECT_EQ(stream.Position(), 0);
}

TEST_F(RawFileStreamTests, GetsBeginningProperly)
{
    Binary::RawFileStream stream{ testFileName };

    EXPECT_EQ(stream.Beginning(), 0);
}

TEST_F(RawFileStreamTests, GetsEndProperly)
{
    Binary::RawFileStream stream{ testFileName };

    EXPECT_EQ(stream.End(), std::filesystem::file_size(testFileName));
}

TEST_F(RawFileStreamTests, GetsFileSizeProperly)
{
    Binary::RawFileStream stream{ testFileName };

    EXPECT_EQ(stream.FileSize(), std::filesystem::file_size(testFileName));
}

TEST_F(RawFileStreamTests, DetectsFileExistsProperly)
{
    Binary::RawFileStream stream{ testFileName };

    EXPECT_EQ(stream.FileExists(), true);
}

TEST_F(RawFileStreamTests, DetectsFileDoesNotExistProperly)
{
    Binary::RawFileStream stream{ "fake.bin" };

    EXPECT_EQ(stream.FileExists(), false);
}

TEST_F(RawFileStreamTests, ParsesFileNameFromPathProperly)
{
    Binary::RawFileStream stream{ testFullPath };

    EXPECT_EQ(stream.FileName(), testFileName);
}

TEST_F(RawFileStreamTests, OpensStreamForReadingProperly)
{
    Binary::RawFileStream stream{ testFileName };

    stream.Open(Binary::FileMode::Read);

    EXPECT_EQ(stream.Position(), 0);
    EXPECT_EQ(stream.IsOpen(), true);
    EXPECT_EQ(stream.Mode(), Binary::FileMode::Read);
}

TEST_F(RawFileStreamTests, OpensStreamForWritingProperly)
{
    Binary::RawFileStream stream{ testFileName };

    stream.Open(Binary::FileMode::Write);

    EXPECT_EQ(stream.Position(), 0);
    EXPECT_EQ(stream.IsOpen(), true);
    EXPECT_EQ(stream.Mode(), Binary::FileMode::Write);
}

TEST_F(RawFileStreamTests, OpensStreamForReadingAndWritingProperly)
{
    Binary::RawFileStream stream{ testFileName };

    stream.Open(Binary::FileMode::ReadWrite);

    EXPECT_EQ(stream.Position(), 0);
    EXPECT_EQ(stream.IsOpen(), true);
    EXPECT_EQ(stream.Mode(), Binary::FileMode::ReadWrite);
}

TEST_F(RawFileStreamTests, ReadsDataFieldsProperly)
{
    Binary::RawFileStream stream{ testFileName };
    Binary::StringField stringField{ stringFieldData.size() };
    Binary::RawField rawField{ rawFieldData.size() };

    stream.Open(Binary::FileMode::Read);
    stream.Read(&stringField);
    stream.Read(&rawField);

    EXPECT_EQ(stream.Position(), stream.End());
    
    for (size_t i = 0; i < stringField.Size(); i++)
        EXPECT_EQ(stringField.Data()[i], stringFieldData[i]);

    for (size_t i = 0; i < rawField.Size(); i++)
        EXPECT_EQ(rawField.Data()[i], rawFieldData[i]);
}

TEST_F(RawFileStreamTests, SetsPositionProperly)
{
    Binary::RawFileStream stream{ testFileName };
    Binary::RawField rawField{ rawFieldData.size() };

    stream.Open(Binary::FileMode::Read);
    stream.SetPosition(8);
    stream.Read(&rawField);

    EXPECT_EQ(stream.Position(), 12);

    for (size_t i = 0; i < rawField.Size(); i++)
        EXPECT_EQ(rawField.Data()[i], rawFieldData[i]);
}

TEST_F(RawFileStreamTests, ClosesFileProperly)
{
    Binary::RawFileStream stream{ testFileName };
    Binary::StringField stringField{ stringFieldData.size() };

    stream.Open(Binary::FileMode::Read);
    stream.Read(&stringField);
    stream.Close();

    EXPECT_EQ(stream.IsOpen(), false);
    EXPECT_EQ(stream.Position(), 0);
}