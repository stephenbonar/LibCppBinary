// BufferStream.cpp - Defines the BufferStream class.
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

#include "BufferStream.h"
#include <cstring>

using namespace Binary;

void BufferStream::Read(DataField* field) const
{
    if (field == nullptr)
    {
        throw std::invalid_argument("The specified field cannot be null.");
    }

    if (position + field->Size() > size)
    {
        throw std::out_of_range("Cannot read past the end of buffer.");
    }

    std::memcpy(field->RawData(), rawData.get() + position, field->Size());
    position += field->Size();
}

void BufferStream::Read(DataStructure* structure) const
{
    if (structure == nullptr)
    {
        throw std::invalid_argument("The specified structure cannot be null.");
    }

    for (DataField* field : structure->Fields())
    {
        Read(field);
    }
}

std::shared_ptr<ChunkHeader> BufferStream::FindNextChunk(std::string id) const
{
    if (id.size() != chunkIDSize)
    {
        throw std::invalid_argument(chunkIDSizeError);
    }

    // Slide over every possible 4-byte start and compare exact chunk IDs.
    for (size_t searchPosition = position;
         searchPosition + chunkIDSize <= size;
         searchPosition++)
    {
        if (std::memcmp(rawData.get() + searchPosition, id.data(), chunkIDSize)
            == 0)
        {
            auto header = std::make_shared<ChunkHeader>();
            position = searchPosition;
            Read(header.get());
            return header;
        }
    }

    // If we reach this point, then we reached the end of the buffer without 
    // finding a match, so we return nullptr to indicate that the chunk header 
    // was not found.
    return nullptr;
}

void BufferStream::Write(const DataField* field)
{
    if (field == nullptr)
    {
        throw std::invalid_argument("The specified field cannot be null.");
    }

    if (position + field->Size() > size)
    {
        throw std::out_of_range("Attempt to write past end of buffer.");
    }

    std::memcpy(rawData.get() + position, field->RawData(), field->Size());
    position += field->Size();
}

void BufferStream::Write(const DataStructure* structure)
{
    if (structure == nullptr)
    {
        throw std::invalid_argument("The specified structure cannot be null.");
    }

    for (const DataField* field : structure->Fields())
    {
        Write(field);
    }
}

void BufferStream::SetPosition(size_t position) const
{ 
    if (position > size)
    {
        throw std::out_of_range("Position cannot be set past end of buffer.");
    }

    this->position = position; 
}
