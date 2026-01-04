// RawField.cpp - Defines the RawField class.
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

#include "RawField.h"

using namespace Binary;

constexpr int bitsPerByte{ 8 };
constexpr int hexOctetWidth{ 2 };
constexpr char hexPadCharacter{ '0' };
constexpr char byteSeparator{ ' ' };
constexpr int printableAsciiBegin{ 31 };
constexpr int printableAsciiEnd{ 126};
constexpr char nonPrintableReplacement{ '.' };

RawField::RawField(size_t size)
{
    if (size < 1)
        throw std::invalid_argument("Size cannot be less than 1");

    this->size = size;
    rawData = std::make_unique<char[]>(size);
}

RawField::RawField(const RawField& other)
{
    size = other.size;
    rawData = std::make_unique<char[]>(size);
    std::memcpy(rawData.get(), other.rawData.get(), other.size);
}

std::string RawField::ToString() const
{
    return FormatData(StringFormat::Hex);
}

std::string RawField::ToString(StringFormat format) const
{
    if (format == StringFormat::Dec)
        throw std::invalid_argument("Dec format only available for ints");

    return FormatData(format);
}

std::string RawField::FormatData(StringFormat format) const
{
    switch (format)
    {
        case StringFormat::Terminated:
            return ConvertTerminated();
        case StringFormat::Printable:
            return ConvertPrintable();
        case StringFormat::Bin:
            return ConvertBin();
        case StringFormat::Hex:
            return ConvertHex();
        default:
            return ConvertRaw();
    }
}

std::string RawField::ConvertTerminated() const
{
    bool nullFound = false;

    for (size_t i = 0; i < size; i++)
    {
        if (rawData[i] == '\0')
        {
            nullFound = true;
            break;
        }
    }

    if (nullFound)
    {
        // Convert the data to a c-style string by using implicit conversion
        // to const char* as the array needs to be const to convert to string.
        const char* cstr = rawData.get();

        return std::string(cstr);
    }
    else
    {
        // If there is no null terminator, we'll need to use the convert raw
        // method anyway.
        return ConvertRaw();
    }
}

std::string RawField::ConvertRaw() const
{
    std::stringstream stream;

    for (size_t i = 0; i < size; i++)
        stream << rawData[i];

    return stream.str();
}

std::string RawField::ConvertPrintable() const
{
    std::stringstream stream;

    for (std::size_t i = 0; i < size; i++)
    {
        if (rawData[i] < printableAsciiBegin || rawData[i] > printableAsciiEnd)
            stream << nonPrintableReplacement;
        else
            stream << rawData[i];
    }
    
    return stream.str();
}

std::string RawField::ConvertBin() const
{
    const auto lastByteIndex = size - 1;
    std::stringstream stream;

    for (std::size_t i = 0; i < size; i++)
    {
        // We cannot put a signed char into a bitset without first casting
        // to unsigned long long.
        auto byte = static_cast<unsigned long long>(rawData[i]);

        // The bitset streams the byte as a string representation of binary.
        stream << std::bitset<bitsPerByte>{ byte };

        // Don't insert an extra separator if we're at the end.
        if (i != lastByteIndex)
            stream << byteSeparator;
    }

    return stream.str();
}

std::string RawField::ConvertHex() const
{
    const auto lastByteIndex = size - 1;
    std::stringstream stream;

    for (std::size_t i = 0; i < size; i++)
    {
        // First cast to unsigned so we don't carry a negative value
        unsigned char u = static_cast<unsigned char>(rawData[i]);

        // Then store the unsigned char value in an integer so the 
        // stringstream captures the numeric value instead of ASCII
        unsigned int byte = u;

        stream << std::hex << std::setw(hexOctetWidth)
            << std::setfill(hexPadCharacter) << byte;

        // Don't insert an extra separator if we're at the end
        if (i != lastByteIndex)
            stream << byteSeparator;
    }
    
    auto hex = stream.str();
    std::transform(hex.begin(), hex.end(), hex.begin(), ::toupper);
    return hex;
}