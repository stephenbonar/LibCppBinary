// StandardFileStream.cpp - Defines the StandardFileStream class.
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

#include "StandardFileStream.h"

using namespace Binary;

std::string StandardFileStream::FileName() const
{ 
    std::filesystem::path path = filePath;
    return path.filename().string(); 
}

void StandardFileStream::Open(FileMode mode)
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

void StandardFileStream::Read(DataField* field) const
{
    if (!IsOpen())
        throw std::runtime_error{ "You must open the file before reading." };

    fileStream.read(field->RawData(), field->Size());
    position += field->Size();
}

void StandardFileStream::Read(DataStructure* structure) const
{
    for (DataField* field : structure->Fields())
        Read(field);
}

std::shared_ptr<ChunkHeader> StandardFileStream::FindNextChunk(std::string id)
    const
{
    bool chunkFound{ false };
    int byteMatchIndex{ 0 };
    uintmax_t tempPosition{ position };

    if (id.size() != 4)
        throw std::invalid_argument{ "ID should be 4 characters long." };

    if (!IsOpen())
        throw std::runtime_error{ "You must open the file before reading." };
      
    fileStream.seekg(position);

    while (!fileStream.eof() && !chunkFound)
    {
        char nextByte{ 0 };
        fileStream.get(nextByte);
        tempPosition++;

        if (nextByte == id[byteMatchIndex])
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

void StandardFileStream::Write(DataField* field)
{
    if (!IsOpen())
        throw std::runtime_error{ "You must open the file before writing." };
        
    fileStream.write(field->RawData(), field->Size());
    position += field->Size();
}

void StandardFileStream::Write(DataStructure* structure)
{
    if (!IsOpen())
        throw std::runtime_error{ "You must open the file before writing." };

    std::vector<DataField*> fields = structure->Fields();

    for (size_t i = 0; i < fields.size(); i++)
    {
        fileStream.write(fields[i]->RawData(), fields[i]->Size());
        position += fields[i]->Size();
    }
}