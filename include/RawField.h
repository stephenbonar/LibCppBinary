// RawField.h - Declares the RawField class.
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

#ifndef BINARY_RAW_FIELD_H
#define BINARY_RAW_FIELD_H

#include <string>
#include <cstring>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <bitset>
#include <iomanip>
#include <algorithm>
#include "DataField.h"
#include "StringFormat.h"

namespace Binary
{
    /// @brief Represents a raw data field in a binary file.
    ///
    /// Binary files can sometimes contain data fields that need to be read or
    /// written without respect to its interpretation. Use the RawField to read
    /// or write data without a specific interpretation from or to a
    /// Binary::Stream, such as a Binary::FileStream. More specialized field
    /// types should inherit from this class as it provides a lot of the basic
    /// functionality for managing the raw data.
    ///
    /// @invariant The size of the field is greater than 0.
    /// @invariant Data is stored in char buffer equal to the size of the field.
    /// @invariant Copying and assignment are deep copies of the field's data.
    class RawField : public DataField
    {
    public:
        /// @brief Constructor; creates a new instance of Field.
        /// @param size The size of the field, in bytes.
        /// @pre Size is > 0.
        RawField(size_t size);

        /// @brief Copy constructor; creates a deep copy of the field.
        /// @param other The field to copy.
        RawField(const RawField& other);

        /// @copydoc DataField::Size
        size_t Size() const override { return size; }

        /// @copydoc DataField::RawData
        char* RawData() override { return rawData.get(); }

        /// @copydoc DataField::RawData
        const char* RawData() const override { return rawData.get(); }

        /// @copydoc DataField::ToString
        std::string ToString() const override;

        /// @copydoc DataField::ToString
        std::string ToString(StringFormat format) const override;

        /// @brief Assignment operator for RawField.
        ///
        /// Copies the size and data from another RawField instance.
        ///
        /// @param other The RawField to copy from.
        /// @return Reference to this RawField after assignment.
        RawField& operator=(const RawField& other);
    protected:
        size_t size;
        std::unique_ptr<char[]> rawData;

        /// @brief Format's the field's data as a string in a specific format.
        /// @param format The format to use.
        /// @return A formated string representation of the data.
        std::string FormatData(StringFormat format) const;
    private:
        /// @brief Converts the data to a standard null-terminated string.
        /// @return The formatted string representation of the data.
        std::string ConvertTerminated() const;

        /// @brief Converts the data to a string even with non-printable chars.
        /// @return The formatted string representation of the data.
        std::string ConvertRaw() const;

        /// @brief Converts the data to a string with only printable chars.
        /// @return The formatted string representation of the data.
        std::string ConvertPrintable() const;

        /// @brief Converts the data to a string formatted as binary digits.
        /// @return The formatted string representation of the data.
        std::string ConvertBin() const;

        /// @brief Converts the data to a string formatted as hex digits.
        /// @return The formatted string representation of the data.
        std::string ConvertHex() const;
    };
};

#endif