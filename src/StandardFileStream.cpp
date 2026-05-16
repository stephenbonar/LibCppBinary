// StandardFileStream.cpp - Defines the StandardFileStream class.
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

#include "StandardFileStream.h"

using namespace Binary;

std::string StandardFileStream::FileName() const
{ 
    std::filesystem::path path = filePath;
    return path.filename().string(); 
}

void StandardFileStream::Open(FileMode m)
{
    switch (m)
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

    mode = m;
}

void StandardFileStream::Read(DataField* field) const
{
    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before reading." };
    }

    fileStream.read(field->RawData(), field->Size());
    position += field->Size();
}

void StandardFileStream::Read(DataStructure* structure) const
{
    for (DataField* field : structure->Fields())
    {
        Read(field);
    }
}

std::shared_ptr<ChunkHeader> StandardFileStream::FindNextChunk(std::string id)
    const
{
    bool chunkFound{ false };
    int idIndex{ 0 };
    size_t searchPosition{ position };

    if (id.size() != chunkIDSize)
    {
        throw std::invalid_argument{ chunkIDSizeError };
    }

    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before reading." };
    }
      
    fileStream.seekg(position);

    while (!fileStream.eof() && !chunkFound)
    {
        char currentByte{ 0 };
        fileStream.get(currentByte);
        searchPosition++;

        // Check if the current byte matches the ID character at the current ID
        // index so we know if we have a potential match.
        if (currentByte == id[idIndex])
        {
            idIndex++;

            // If we've got this far and the ID index is equal to the chunk ID 
            // size, then we've found a matching chunk header.
            if (idIndex == chunkIDSize)
            {
                // Return to the original position in the file now that we've
                // found the chunk header so we can read the header.
                searchPosition -= chunkIDSize;
                fileStream.seekg(searchPosition);
                position = searchPosition;

                chunkFound = true;
            }
        }
        else
        {
            // There's a mismatch so we need to start looking at the ID for
            // matching characters at the beginning again.
            idIndex = 0;
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

void StandardFileStream::Write(const DataField* field)
{
    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before writing." };
    }
        
    fileStream.write(field->RawData(), field->Size());
    position += field->Size();
}

void StandardFileStream::Write(const DataStructure* structure)
{
    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before writing." };
    }

    std::vector<const DataField*> fields = structure->Fields();

    for (size_t i = 0; i < fields.size(); i++)
    {
        fileStream.write(fields[i]->RawData(), fields[i]->Size());
        position += fields[i]->Size();
    }
}

size_t StandardFileStream::FileSize() const
{
    uintmax_t fileSize{ std::filesystem::file_size(filePath) };
    unsigned long long fileSizeLimit
    { 
        std::numeric_limits<size_t>::max() 
    };

    if (fileSize > fileSizeLimit)
    {
        std::stringstream error;
        error << "File size exceeds limit of " << fileSizeLimit;
        error << " bytes.";
        throw std::overflow_error{ error.str() };
    }
        
    return static_cast<size_t>(fileSize); 
}