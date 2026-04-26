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
        throw std::invalid_argument("Chunk ID must be exactly " +
                                    std::to_string(chunkIDSize) + 
                                    " characters.");
    }

    bool idFound{ false };
    size_t searchPosition{ position };
    int idIndex{ 0 };

    while (searchPosition < size)
    {
        // Check if the byte at the search position matches the ID character at
        // the current ID index so we know if we have a potential match.
        if (rawData[searchPosition] == id[idIndex])
        {
            idIndex++;

            // If we've got this far and the ID index is equal to the chunk ID 
            // size, then we've found a matching chunk header.
            if (idIndex == chunkIDSize)
            {
                idFound = true;
                auto header = std::make_shared<ChunkHeader>();

                // Set the search position back to the beginning of the chunk 
                // header since we know we found the header at that position.
                searchPosition -= (chunkIDSize - 1);

                // Set the postion to the search position as we want to advance
                // the position to the beginning of the found chunk header.
                position = searchPosition;

                Read(header.get());
                return header;
            }
        }
        else
        {
            // There's a mismatch so we need to start looking at the ID for
            // matching characters at the beginning again.
            idIndex = 0;
        }

        // Keep advancing the search position until we find a match or reach the
        // end of the buffer.
        searchPosition++;
    }

    // If we reach this point, then we reached the end of the buffer without 
    // finding a match, so we return nullptr to indicate that the chunk header 
    // was not found.
    return nullptr;
}

void BufferStream::Write(DataField* field)
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

void BufferStream::Write(DataStructure* structure)
{
    if (structure == nullptr)
    {
        throw std::invalid_argument("The specified structure cannot be null.");
    }

    for (DataField* field : structure->Fields())
    {
        Write(field);
    }
}
