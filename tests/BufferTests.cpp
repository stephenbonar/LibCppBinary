// BufferTests.cpp - Defines the BufferTests class and tests.
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

#include "BufferTests.h"

void BufferTests::SetUp()
{
    buffer = std::make_unique<Binary::Buffer>(bufferSize);
}

TEST_F(BufferTests, ConstructorSetsSizeProperly)
{
    EXPECT_EQ(buffer->Size(), bufferSize);
}

TEST_F(BufferTests, PositionInitiallyZero)
{
    EXPECT_EQ(buffer->Position(), 0);
}

TEST_F(BufferTests, SetPositionUpdatesPosition)
{
    constexpr uintmax_t newPosition{ 5 };
    buffer->SetPosition(newPosition);
    EXPECT_EQ(buffer->Position(), newPosition);
}

TEST_F(BufferTests, ReadsAndWritesFieldsProperly)
{
    constexpr size_t fieldSize{ 6 };
    Binary::RawField fieldToWrite(fieldSize);
    const char testData[fieldSize] = { 'H', 'e', 'l', 'l', 'o', '\0' };
    std::memcpy(fieldToWrite.Data(), testData, fieldSize);

    buffer->Write(&fieldToWrite);
    buffer->SetPosition(0);
    Binary::RawField fieldToRead(fieldSize);
    buffer->Read(&fieldToRead);

    EXPECT_EQ(std::memcmp(fieldToRead.Data(), testData, fieldSize), 0);
}

TEST_F(BufferTests, ReadsAndWritesDataStructuresProperly)
{
    Binary::ChunkHeader headerToWrite;
    headerToWrite.id.SetValue("TEST");
    headerToWrite.dataSize.SetValue(4);

    buffer->Write(&headerToWrite);
    buffer->SetPosition(0);
    Binary::ChunkHeader headerToRead;
    buffer->Read(&headerToRead);

    EXPECT_EQ(headerToRead.id.Value(), "TEST");
    EXPECT_EQ(headerToRead.dataSize.Value(), 4);
}

TEST_F(BufferTests, DoesNotReadPastEndOfBuffer)
{
    constexpr size_t fieldSize{ bufferSize + 1 };
    Binary::RawField fieldToRead(fieldSize);

    buffer->SetPosition(0);
    EXPECT_THROW(buffer->Read(&fieldToRead), std::out_of_range);
}

TEST_F(BufferTests, DoesNotWritePastEndOfBuffer)
{
    constexpr size_t fieldSize{ bufferSize + 1 };
    Binary::RawField fieldToWrite(fieldSize);

    buffer->SetPosition(0);
    EXPECT_THROW(buffer->Write(&fieldToWrite), std::out_of_range);
}

TEST_F(BufferTests, BeginningAndEndPositionsAreCorrect)
{
    EXPECT_EQ(buffer->Beginning(), 0);
    EXPECT_EQ(buffer->End(), bufferSize);
}

TEST_F(BufferTests, FindNextChunkReturnsChunkProperly)
{
    Binary::Buffer largeBuffer{ 16 };

    Binary::ChunkHeader header1;
    header1.id.SetValue("CHN1");
    header1.dataSize.SetValue(4);
    Binary::ChunkHeader header2;
    header2.id.SetValue("CHN2");
    header2.dataSize.SetValue(4);

    largeBuffer.Write(&header1);
    largeBuffer.Write(&header2);
    largeBuffer.SetPosition(0);

    std::shared_ptr<Binary::ChunkHeader> foundHeader = largeBuffer.FindNextChunk("CHN2");
    ASSERT_NE(foundHeader, nullptr);
    EXPECT_EQ(foundHeader->id.Value(), "CHN2");
    EXPECT_EQ(foundHeader->dataSize.Value(), 4);
    EXPECT_EQ(largeBuffer.Position(), header1.Size() + header2.Size());
}