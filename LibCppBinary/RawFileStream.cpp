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
    return path.filename(); 
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
    fileStream.read(field->Data(), field->Size());
    position += field->Size();
}