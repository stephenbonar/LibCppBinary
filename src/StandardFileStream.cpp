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
#include <array>

using namespace Binary;

std::string StandardFileStream::FileName() const
{ 
    std::filesystem::path path = filePath;
    return path.filename().string(); 
}

void StandardFileStream::Open(FileMode m)
{
    if (fileStream.is_open())
    {
        fileStream.close();
    }

    fileStream.clear();

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

    if (!fileStream.is_open())
    {
        throw std::runtime_error{ "Failed to open file." };
    }

    position = 0;

    if (m != FileMode::Write)
    {
        fileStream.seekg(0);
    }

    if (m != FileMode::Read)
    {
        fileStream.seekp(0);
    }

    mode = m;
}

void StandardFileStream::Read(DataField& field) const
{
    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before reading." };
    }

    fileStream.read(field.RawData(), field.Size());

    if (fileStream.fail())
    {
        throw std::runtime_error{ "Failed to read from file." };
    }

    position += field.Size();
}

void StandardFileStream::Read(DataStructure& structure) const
{
    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before reading." };
    }

    for (DataField* field : structure.Fields())
    {
        Read(*field);
    }
}

std::shared_ptr<ChunkHeader> StandardFileStream::FindNextChunk(const std::string& id) const
{
    const size_t originalPosition{ position };

    if (id.size() != chunkIDSize)
    {
        throw std::invalid_argument{ chunkIDSizeError };
    }

    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before reading." };
    }

    for (size_t searchPosition = position;
         searchPosition + chunkIDSize <= FileSize();
         searchPosition++)
    {
        fileStream.clear();
        fileStream.seekg(searchPosition);

        std::array<char, chunkIDSize> candidate{};
        fileStream.read(candidate.data(), chunkIDSize);

        if (fileStream.gcount() != chunkIDSize)
        {
            break;
        }

        if (std::equal(candidate.begin(), candidate.end(), id.begin()))
        {
            fileStream.clear();
            fileStream.seekg(searchPosition);
            position = searchPosition;

            auto header = std::make_shared<Binary::ChunkHeader>();
            Read(*header);
            return header;
        }
    }

    fileStream.clear();
    fileStream.seekg(originalPosition);
    position = originalPosition;
    return nullptr;
}

void StandardFileStream::Write(const DataField& field)
{
    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before writing." };
    }

    fileStream.write(field.RawData(), field.Size());

    if (fileStream.fail())
    {
        throw std::runtime_error{ "Failed to write to file." };
    }

    position += field.Size();
}

void StandardFileStream::Write(const DataStructure& structure)
{
    if (!IsOpen())
    {
        throw std::runtime_error{ "You must open the file before writing." };
    }

    for (const DataField* field : structure.Fields())
    {
        Write(*field);
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