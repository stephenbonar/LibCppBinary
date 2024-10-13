// RawField.cpp - Defines the RawField class.
//
// Copyright (C) 2024 Stephen Bonar
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
// See the License for the specific language governing permissionsand
// limitations under the License.

#include "RawField.h"

using namespace Binary;

const char* Binary::rawFieldFormatError
{ 
    "RawField can only be formatted as Bin, Hex, or Ascii" 
};

RawField::RawField(std::size_t size) : size{ size }
{
    if (size < minFieldSize)
        throw InvalidField{ fieldSizeError };
    data = std::make_unique<char[]>(size);
}

RawField::RawField(const RawField& f)
{
    data = std::make_unique<char[]>(f.Size());
    std::memcpy(data.get(), f.data.get(), f.Size());
    size = f.size;
}

RawField::RawField(RawField&& f)
{
    data = std::move(f.data);
    size = f.size;
    f.size = 0;
}

RawField& RawField::operator=(const RawField& f)
{
    data = std::make_unique<char[]>(f.Size());
    std::memcpy(data.get(), f.data.get(), f.Size());
    size = f.size;
    return *this;
}

RawField& RawField::operator=(RawField&& f)
{
    data = std::move(f.data);
    size = f.size;
    f.size = 0;
    return *this;
}

std::string RawField::ToString() const
{
    if (data == nullptr)
        throw InvalidField{ nullFieldError };
    return FormatHex(data.get(), size);
}

std::string RawField::ToString(Format f) const
{
    if (data == nullptr)
        throw InvalidField{ nullFieldError };
    switch (f)
    {
        case Format::Ascii:
            return FormatAscii(data.get(), size);
        case Format::Bin:
            return FormatBin(data.get(), size);
        case Format::Hex:
            return FormatHex(data.get(), size);
        case Format::Dec:
            throw InvalidFormat{ rawFieldFormatError };
        default:
            return ToString();
    }
}

std::ostream& Binary::operator<<(std::ostream& os, const RawField& f)
{
    os << f.ToString();
    return os;
}
