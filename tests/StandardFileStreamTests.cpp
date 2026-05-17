// StandardFileStreamTests.cpp - Defines the StandardFileStreamTests class and tests.
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

#include "StandardFileStreamTests.h"

const char* testFileName{ "test.bin" };
const char* testWriteFileName{ "testwrite.bin" };
const char* testFullPath{ "/test/test.bin" };
const std::vector<char> stringFieldData{ 'T', 'e', 's', 't', 'i', 'n', 'g', '!' };
const std::vector<char> rawFieldData{ 0xA, 0xB, 0xC, 0xD };
const std::vector<char> chunk1IDData{ 'T', 'S', 'T', '1' };
const std::vector<char> chunk1SizeData{ 0x4, 0x0, 0x0, 0x0 };
const std::vector<char> chunk1Data{ 'A', 'B', 'C', 'D' };
const std::vector<char> chunk2IDData{ 'T', 'S', 'T', '2' };
const std::vector<char> chunk2SizeData{ 0x4, 0x0, 0x0, 0x0 };
const std::vector<char> chunk2Data{ 'E', 'F', 'G', 'H' };


StandardFileStreamTests::StandardFileStreamTests() 
{
    GenerateTestFile();
}

void StandardFileStreamTests::GenerateTestFile()
{
    
    std::fstream stream;
    stream.open(testFileName, std::ios::out | std::ios::binary);

    stream.write(stringFieldData.data(), stringFieldData.size());
    stream.write(rawFieldData.data(), rawFieldData.size());
    stream.write(chunk1IDData.data(), chunk1IDData.size());
    stream.write(chunk1SizeData.data(), chunk1SizeData.size());
    stream.write(chunk1Data.data(), chunk1Data.size());
    stream.write(chunk2IDData.data(), chunk2IDData.size());
    stream.write(chunk2SizeData.data(), chunk2SizeData.size());
    stream.write(chunk2Data.data(), chunk2Data.size());
}

TEST_F(StandardFileStreamTests, InitializesStreamProperly)
{
    Binary::StandardFileStream stream{ testFileName };

    EXPECT_EQ(stream.FileName(), testFileName);
    EXPECT_EQ(stream.FilePath(), testFileName);
    EXPECT_EQ(stream.IsOpen(), false);
    EXPECT_EQ(stream.Position(), 0);
}

TEST_F(StandardFileStreamTests, GetsBeginningProperly)
{
    Binary::StandardFileStream stream{ testFileName };

    EXPECT_EQ(stream.Beginning(), 0);
}

TEST_F(StandardFileStreamTests, GetsEndProperly)
{
    Binary::StandardFileStream stream{ testFileName };

    EXPECT_EQ(stream.End(), std::filesystem::file_size(testFileName));
}

TEST_F(StandardFileStreamTests, GetsFileSizeProperly)
{
    Binary::StandardFileStream stream{ testFileName };

    EXPECT_EQ(stream.FileSize(), std::filesystem::file_size(testFileName));
}

TEST_F(StandardFileStreamTests, DetectsFileExistsProperly)
{
    Binary::StandardFileStream stream{ testFileName };

    EXPECT_EQ(stream.FileExists(), true);
}

TEST_F(StandardFileStreamTests, DetectsFileDoesNotExistProperly)
{
    Binary::StandardFileStream stream{ "fake.bin" };

    EXPECT_EQ(stream.FileExists(), false);
}

TEST_F(StandardFileStreamTests, ParsesFileNameFromPathProperly)
{
    Binary::StandardFileStream stream{ testFullPath };

    EXPECT_EQ(stream.FileName(), testFileName);
}

TEST_F(StandardFileStreamTests, OpensStreamForReadingProperly)
{
    Binary::StandardFileStream stream{ testFileName };

    stream.Open(Binary::FileMode::Read);

    EXPECT_EQ(stream.Position(), 0);
    EXPECT_EQ(stream.IsOpen(), true);
    EXPECT_EQ(stream.Mode(), Binary::FileMode::Read);
}

TEST_F(StandardFileStreamTests, OpensStreamForWritingProperly)
{
    Binary::StandardFileStream stream{ testFileName };

    stream.Open(Binary::FileMode::Write);

    EXPECT_EQ(stream.Position(), 0);
    EXPECT_EQ(stream.IsOpen(), true);
    EXPECT_EQ(stream.Mode(), Binary::FileMode::Write);
}

TEST_F(StandardFileStreamTests, OpensStreamForReadingAndWritingProperly)
{
    Binary::StandardFileStream stream{ testFileName };

    stream.Open(Binary::FileMode::ReadWrite);

    EXPECT_EQ(stream.Position(), 0);
    EXPECT_EQ(stream.IsOpen(), true);
    EXPECT_EQ(stream.Mode(), Binary::FileMode::ReadWrite);
}

TEST_F(StandardFileStreamTests, ReadsDataFieldsProperly)
{
    Binary::StandardFileStream stream{ testFileName };
    Binary::StringField stringField{ stringFieldData.size() };
    Binary::RawField rawField{ rawFieldData.size() };

    stream.Open(Binary::FileMode::Read);
    stream.Read(&stringField);
    stream.Read(&rawField);

    uintmax_t readPosition = stringFieldData.size() + rawFieldData.size();

    EXPECT_EQ(stream.Position(), readPosition);
    
    for (size_t i = 0; i < stringField.Size(); i++)
        EXPECT_EQ(stringField.RawData()[i], stringFieldData[i]);

    for (size_t i = 0; i < rawField.Size(); i++)
        EXPECT_EQ(rawField.RawData()[i], rawFieldData[i]);
}

TEST_F(StandardFileStreamTests, WritesDataFieldsProperly)
{
    Binary::StandardFileStream stream{ testWriteFileName };
    Binary::StringField readStringField{ stringFieldData.size() };
    Binary::RawField readRawField{ rawFieldData.size() };
    Binary::StringField writeStringField{ stringFieldData.size() };
    Binary::RawField writeRawField{ rawFieldData.size() };

    writeStringField.SetValue(stringFieldData.data());

    for (size_t i = 0; i < rawFieldData.size(); i++)
        writeRawField.RawData()[i] = rawFieldData[i];

    stream.Open(Binary::FileMode::Write);
    stream.Write(&writeStringField);
    stream.Write(&writeRawField);

    EXPECT_EQ(stream.Position(), 
              writeStringField.Size() + writeRawField.Size());

    stream.Close();

    stream.Open(Binary::FileMode::Read);
    stream.Read(&readStringField);
    stream.Read(&readRawField);
    stream.Close();

    EXPECT_EQ(stream.FileSize(), stringFieldData.size() + rawFieldData.size());
    
    for (size_t i = 0; i < stringFieldData.size(); i++)
        EXPECT_EQ(stringFieldData.data()[i], readStringField.RawData()[i]);
    
    for (size_t i = 0; i < rawFieldData.size(); ++i)
        EXPECT_EQ(rawFieldData[i], readRawField.RawData()[i]);
}

TEST_F(StandardFileStreamTests, WritesDataStructuresProperly)
{
    Binary::ChunkHeader writeHeader;
    writeHeader.id.SetValue("TEST");
    writeHeader.dataSize.SetValue(4);
    Binary::ChunkHeader readHeader;

    Binary::StandardFileStream writeStream{ testWriteFileName };
    writeStream.Open(Binary::FileMode::Write);
    writeStream.Write(&writeHeader);
    writeStream.Close();

    ASSERT_EQ(std::filesystem::file_size(testWriteFileName), 8);

    Binary::StandardFileStream readStream{ testWriteFileName };
    readStream.Open(Binary::FileMode::Read);
    readStream.Read(&readHeader);
    readStream.Close();

    EXPECT_EQ(readHeader.id.Value(), "TEST");
    EXPECT_EQ(readHeader.dataSize.Value(), 4);
}

TEST_F(StandardFileStreamTests, SetsPositionProperly)
{
    Binary::StandardFileStream stream{ testFileName };
    Binary::RawField rawField{ rawFieldData.size() };

    stream.Open(Binary::FileMode::Read);
    stream.SetPosition(8);
    stream.Read(&rawField);

    EXPECT_EQ(stream.Position(), 12);

    for (size_t i = 0; i < rawField.Size(); i++)
        EXPECT_EQ(rawField.RawData()[i], rawFieldData[i]);
}

TEST_F(StandardFileStreamTests, ClosesFileProperly)
{
    Binary::StandardFileStream stream{ testFileName };
    Binary::StringField stringField{ stringFieldData.size() };

    stream.Open(Binary::FileMode::Read);
    stream.Read(&stringField);
    stream.Close();

    EXPECT_EQ(stream.IsOpen(), false);
    EXPECT_EQ(stream.Position(), 0);
}

TEST_F(StandardFileStreamTests, OnlyAllowsReadWhenOpen)
{
    Binary::StringField stringField{ stringFieldData.size() };
    Binary::StandardFileStream stream{ testFileName };

    EXPECT_THROW(stream.Read(&stringField), std::runtime_error);
}

TEST_F(StandardFileStreamTests, OnlyAllowsWriteWhenOpen)
{
    Binary::StringField stringField{ stringFieldData.size() };
    Binary::StandardFileStream stream{ testWriteFileName };

    EXPECT_THROW(stream.Write(&stringField), std::runtime_error);
}

TEST_F(StandardFileStreamTests, ReadsDataStructuresProperly)
{
    Binary::StandardFileStream stream{ testFileName };
    Binary::ChunkHeader header;

    stream.Open(Binary::FileMode::Read);

    size_t chunkPosition = stringFieldData.size() + rawFieldData.size();
    stream.SetPosition(chunkPosition);

    stream.Read(&header);

    EXPECT_EQ(stream.Position(), chunkPosition + header.Size());
    EXPECT_EQ(header.id.Value(), "TST1");
    EXPECT_EQ(header.dataSize.Value(), 4);
}

TEST_F(StandardFileStreamTests, FindsChunkHeadersProperly)
{
    Binary::StandardFileStream stream{ testFileName };
    
    stream.Open(Binary::FileMode::Read);
    std::shared_ptr<Binary::ChunkHeader> header = stream.FindNextChunk("TST2");

    uintmax_t expectedPosition = stringFieldData.size() + rawFieldData.size() +
        chunk1IDData.size() + chunk1SizeData.size() + chunk1Data.size() + 
        chunk2IDData.size() + chunk2SizeData.size();

    ASSERT_NE(header, nullptr);
    EXPECT_EQ(header->id.Value(), "TST2");
    EXPECT_EQ(header->dataSize.Value(), 4);
    EXPECT_EQ(stream.Position(), expectedPosition);
}

TEST_F(StandardFileStreamTests, FindNextChunkThrowsErrorWhenIDWrongSize)
{
    Binary::StandardFileStream stream{ testFileName };

    stream.Open(Binary::FileMode::Read);

    // Should be exactly 4 bytes long.
    EXPECT_THROW(stream.FindNextChunk(""), std::invalid_argument);
    EXPECT_THROW(stream.FindNextChunk("TEST5"), std::invalid_argument);
}

TEST_F(StandardFileStreamTests, ReturnsNullptrWhenChunkHeaderNotFound)
{
    Binary::StandardFileStream stream{ testFileName };
    
    stream.Open(Binary::FileMode::Read);
    std::shared_ptr<Binary::ChunkHeader> header = stream.FindNextChunk("TST3");

    EXPECT_EQ(header, nullptr);
}

TEST_F(StandardFileStreamTests, ThrowsInvalidArgumentForNullFieldRead)
{
    Binary::DataField* nullField{ nullptr };
    Binary::StandardFileStream stream{ testFileName };
    stream.Open(Binary::FileMode::Read);

    // Uses EXPECT_EXIT with ExitedWithCode(0) so the test only passes if
    // std::invalid_argument is properly thrown. A segfault (abnormal
    // termination) or missing null check (no exception) will fail the test.
    EXPECT_EXIT(
        {
            try
            {
                stream.Read(nullField);
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

TEST_F(StandardFileStreamTests, ThrowsInvalidArgumentForNullStructureRead)
{
    Binary::DataStructure* nullStructure{ nullptr };
    Binary::StandardFileStream stream{ testFileName };
    stream.Open(Binary::FileMode::Read);

    // Uses EXPECT_EXIT with ExitedWithCode(0) so the test only passes if
    // std::invalid_argument is properly thrown. A segfault (abnormal
    // termination) or missing null check (no exception) will fail the test.
    EXPECT_EXIT(
        {
            try
            {
                stream.Read(nullStructure);
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

TEST_F(StandardFileStreamTests, ThrowsInvalidArgumentForNullFieldWrite)
{
    Binary::DataField* nullField{ nullptr };
    Binary::StandardFileStream stream{ testWriteFileName };
    stream.Open(Binary::FileMode::Write);

    // Uses EXPECT_EXIT with ExitedWithCode(0) so the test only passes if
    // std::invalid_argument is properly thrown. A segfault (abnormal
    // termination) or missing null check (no exception) will fail the test.
    EXPECT_EXIT(
        {
            try
            {
                stream.Write(nullField);
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

TEST_F(StandardFileStreamTests, ThrowsInvalidArgumentForNullStructureWrite)
{
    Binary::DataStructure* nullStructure{ nullptr };
    Binary::StandardFileStream stream{ testWriteFileName };
    stream.Open(Binary::FileMode::Write);

    // Uses EXPECT_EXIT with ExitedWithCode(0) so the test only passes if
    // std::invalid_argument is properly thrown. A segfault (abnormal
    // termination) or missing null check (no exception) will fail the test.
    EXPECT_EXIT(
        {
            try
            {
                stream.Write(nullStructure);
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

TEST_F(StandardFileStreamTests, SetPositionThrowsIfGreaterThanFileSize)
{
    Binary::StandardFileStream stream{ testFileName };

    size_t positionPastEnd = std::filesystem::file_size(testFileName) + 1;
    EXPECT_THROW(stream.SetPosition(positionPastEnd), std::out_of_range);
}