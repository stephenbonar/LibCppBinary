// RawFileStream.cpp - Defines the RawFileStream class.
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

#include "RawFileStream.h"

using namespace Binary;

std::string RawFileStream::FileName() const
{ 
    std::filesystem::path path = filePath;
    return path.filename().string(); 
}

void RawFileStream::Open(FileMode mode)
{
    switch (mode)
    {
        case FileMode::Read:
            fileStream.open(filePath, std::ios::in | std::ios::binary);
            break;
        case FileMode::Write:
            fileStream.open(filePath, std::ios::out | std::ios::binary);
            break;
        case FileMode::ReadWrite:
            fileStream.open(filePath, 
                std::ios::in | std::ios::out | std::ios::binary);
            break;
    }

    this->mode = mode;
}

void RawFileStream::Read(DataField* field)
{
    if (!IsOpen())
        throw std::runtime_error{ "You must open the file before reading." };

    fileStream.read(field->Data(), field->Size());
    position += field->Size();
}

void RawFileStream::Read(DataStructure* structure)
{
    for (DataField* field : structure->Fields())
        Read(field);
}

std::shared_ptr<ChunkHeader> RawFileStream::FindNextChunk(std::string ID) 
{
    bool chunkFound{ false };
    int byteMatchIndex{ 0 };
    uintmax_t tempPosition{ position };

    if (ID.size() != 4)
        throw std::invalid_argument{ "ID should be 4 characters long." };

    if (!IsOpen())
        throw std::runtime_error{ "You must open the file before reading." };
      
    fileStream.seekg(position);

    while (!fileStream.eof() && !chunkFound)
    {
        char nextByte{ 0 };
        fileStream.get(nextByte);
        tempPosition++;

        if (nextByte == ID[byteMatchIndex])
        {
            byteMatchIndex++;

            if (byteMatchIndex == 4)
            {
                tempPosition -= 4;
                fileStream.seekg(tempPosition);
                position = tempPosition;
                chunkFound = true;
            }
        }
        else
        {
            byteMatchIndex = 0;
        }
    }

    if (chunkFound)
    {
        auto header = std::make_shared<Binary::ChunkHeader>();
        Read(header.get());
        return header;
    }
    else
    {
        fileStream.seekg(position);
        return nullptr;
    }
}

void RawFileStream::Write(DataField* field)
{
    if (!IsOpen())
        throw std::runtime_error{ "You must open the file before writing." };
        
    fileStream.write(field->Data(), field->Size());
    position += field->Size();
}