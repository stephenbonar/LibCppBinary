// BufferStream.cpp - Defines the BufferStream class.
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

#include "BufferStream.h"

using namespace Binary;

void BufferStream::Read(DataField* field) const
{
    if (position + field->Size() > size)
        throw std::out_of_range("Attempt to read past end of buffer.");

    std::memcpy(field->RawData(), rawData.get() + position, field->Size());
    position += field->Size();
}

void BufferStream::Read(DataStructure* structure) const
{
    for (DataField* field : structure->Fields())
        Read(field);
}

std::shared_ptr<ChunkHeader> BufferStream::FindNextChunk(std::string id) const
{
    if (id.size() != 4)
        throw std::invalid_argument("Chunk ID must be exactly 4 characters.");

    bool idFound{ false };
    size_t searchPosition{ position };
    int idIndex{ 0 };

    while (searchPosition < size)
    {
        if (rawData[searchPosition] == id[idIndex])
        {
            idIndex++;

            if (idIndex == 4)
            {
                idFound = true;
                auto header = std::make_shared<ChunkHeader>();
                searchPosition -= 3;
                position = searchPosition;
                Read(header.get());
                return header;
            }
        }
        else
        {
            idIndex = 0;
        }

        searchPosition++;
    }

    return nullptr;
}

void BufferStream::Write(DataField* field)
{
    if (position + field->Size() > size)
        throw std::out_of_range("Attempt to write past end of buffer.");

    std::memcpy(rawData.get() + position, field->RawData(), field->Size());
    position += field->Size();
}

void BufferStream::Write(DataStructure* structure)
{
    for (DataField* field : structure->Fields())
        Write(field);
}

size_t BufferStream::Position() const
{
    return position;
}

void BufferStream::SetPosition(size_t pos) const
{
    position = pos;
}

size_t BufferStream::Beginning() const
{
    return 0;
}

size_t BufferStream::End() const
{
    return size;
}
