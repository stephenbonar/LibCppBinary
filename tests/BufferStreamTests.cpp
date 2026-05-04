// BufferStreamTests.cpp - Defines the BufferStreamTests class and tests.
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

#include "BufferStreamTests.h"

void BufferStreamTests::SetUp()
{
    buffer = std::make_unique<Binary::BufferStream>(bufferSize);
}

TEST_F(BufferStreamTests, ConstructorSetsSizeProperly)
{
    EXPECT_EQ(buffer->Size(), bufferSize);
}

TEST_F(BufferStreamTests, PositionInitiallyZero)
{
    EXPECT_EQ(buffer->Position(), 0);
}

TEST_F(BufferStreamTests, SetPositionUpdatesPosition)
{
    constexpr uintmax_t newPosition{ 5 };
    buffer->SetPosition(newPosition);
    EXPECT_EQ(buffer->Position(), newPosition);
}

TEST_F(BufferStreamTests, ReadsAndWritesFieldsProperly)
{
    constexpr size_t fieldSize{ 6 };
    Binary::RawField fieldToWrite(fieldSize);
    const char testData[fieldSize] = { 'H', 'e', 'l', 'l', 'o', '\0' };
    std::memcpy(fieldToWrite.RawData(), testData, fieldSize);

    buffer->Write(&fieldToWrite);
    buffer->SetPosition(0);
    Binary::RawField fieldToRead(fieldSize);
    buffer->Read(&fieldToRead);

    EXPECT_EQ(std::memcmp(fieldToRead.RawData(), testData, fieldSize), 0);
}

TEST_F(BufferStreamTests, ReadsAndWritesDataStructuresProperly)
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

TEST_F(BufferStreamTests, DoesNotReadFieldPastEndOfBuffer)
{
    constexpr size_t fieldSize{ bufferSize + 1 };
    Binary::RawField fieldToRead(fieldSize);

    buffer->SetPosition(0);
    EXPECT_THROW(buffer->Read(&fieldToRead), std::out_of_range);
}

TEST_F(BufferStreamTests, DoesNotWriteFieldPastEndOfBuffer)
{
    constexpr size_t fieldSize{ bufferSize + 1 };
    Binary::RawField fieldToWrite(fieldSize);

    buffer->SetPosition(0);
    EXPECT_THROW(buffer->Write(&fieldToWrite), std::out_of_range);
}

TEST_F(BufferStreamTests, DoesNotReadStructurePastEndOfBuffer)
{
    Binary::ChunkHeader structureToRead;

    buffer->SetPosition(bufferSize - 1);
    EXPECT_THROW(buffer->Read(&structureToRead), std::out_of_range);
}

TEST_F(BufferStreamTests, DoesNotWriteStructurePastEndOfBuffer)
{
    Binary::ChunkHeader structureToWrite;

    buffer->SetPosition(bufferSize - 1);
    EXPECT_THROW(buffer->Write(&structureToWrite), std::out_of_range);
}

TEST_F(BufferStreamTests, BeginningAndEndPositionsAreCorrect)
{
    EXPECT_EQ(buffer->Beginning(), 0);
    EXPECT_EQ(buffer->End(), bufferSize);
}

TEST_F(BufferStreamTests, FindNextChunkReturnsChunkProperly)
{
    Binary::BufferStream largeBuffer{ 16 };

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

TEST_F(BufferStreamTests, FindNextChunkThrowsForInvalidID)
{
    EXPECT_THROW(buffer->FindNextChunk("TOO_LONG"), std::invalid_argument);
    EXPECT_THROW(buffer->FindNextChunk("SH"), std::invalid_argument);
}

TEST_F(BufferStreamTests, ThrowsInvalidArgumentForNullFieldRead)
{
    Binary::DataField* nullField{ nullptr };

    // Uses EXPECT_EXIT with ExitedWithCode(0) so the test only passes if
    // std::invalid_argument is properly thrown. A segfault (abnormal
    // termination) or missing null check (no exception) will fail the test.
    EXPECT_EXIT(
        {
            try 
            {
                buffer->Read(nullField);
                exit(1); // No exception thrown: fail
            } 
            catch (const std::invalid_argument&) 
            {
                exit(0); // Correct exception thrown: pass
            }
            catch (...)
            {
                exit(2); // Wrong exception type: fail
            }
        },
        testing::ExitedWithCode(0),
        ""
    );
}

TEST_F(BufferStreamTests, ThrowsInvalidArgumentForNullStructureRead)
{
    Binary::DataStructure* nullStructure{ nullptr };

    // Uses EXPECT_EXIT with ExitedWithCode(0) so the test only passes if
    // std::invalid_argument is properly thrown. A segfault (abnormal
    // termination) or missing null check (no exception) will fail the test.
    EXPECT_EXIT(
        {
            try
            {
                buffer->Read(nullStructure);
                exit(1); // No exception thrown: fail
            }
            catch (const std::invalid_argument&)
            {
                exit(0); // Correct exception thrown: pass
            }
            catch (...)
            {
                exit(2); // Wrong exception type: fail
            }
        },
        testing::ExitedWithCode(0),
        ""
    );
}

TEST_F(BufferStreamTests, ThrowsInvalidArgumentForNullFieldWrite)
{
    Binary::DataField* nullField{ nullptr };

    // Uses EXPECT_EXIT with ExitedWithCode(0) so the test only passes if
    // std::invalid_argument is properly thrown. A segfault (abnormal
    // termination) or missing null check (no exception) will fail the test.
    EXPECT_EXIT(
        {
            try
            {
                buffer->Write(nullField);
                exit(1); // No exception thrown: fail
            }
            catch (const std::invalid_argument&)
            {
                exit(0); // Correct exception thrown: pass
            }
            catch (...)
            {
                exit(2); // Wrong exception type: fail
            }
        },
        testing::ExitedWithCode(0),
        ""
    );
}

TEST_F(BufferStreamTests, ThrowsInvalidArgumentForNullStructureWrite)
{
    Binary::DataStructure* nullStructure{ nullptr };

    // Uses EXPECT_EXIT with ExitedWithCode(0) so the test only passes if
    // std::invalid_argument is properly thrown. A segfault (abnormal
    // termination) or missing null check (no exception) will fail the test.
    EXPECT_EXIT(
        {
            try
            {
                buffer->Write(nullStructure);
                exit(1); // No exception thrown: fail
            }
            catch (const std::invalid_argument&)
            {
                exit(0); // Correct exception thrown: pass
            }
            catch (...)
            {
                exit(2); // Wrong exception type: fail
            }
        },
        testing::ExitedWithCode(0),
        ""
    );
}

TEST_F(BufferStreamTests, SetPositionThrowsIfGreaterThanSize)
{
    // Try to set position past the end of the buffer
    EXPECT_THROW(buffer->SetPosition(bufferSize + 1), std::out_of_range);
}
