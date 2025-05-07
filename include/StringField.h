// StringField.h - Declares the StringField class.
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

#ifndef BINARY_STRING_FIELD_H
#define BINARY_STRING_FIELD_H

#include <string>
#include <sstream>
#include <memory>
#include "RawField.h"

namespace Binary
{
    /// @brief Represents a string field in a binary file.
    ///
    /// Binary files can sometimes still contain text fields or strings. Use
    /// the string field to read or write these types of fields from and to
    /// a Binary::Stream, such as a Binary::DataFileStream.
    class StringField : public RawField
    {
    public:
        /// @brief Constructor; creates a new instance of StringField.
        /// @param size The size of the field, in bytes.
        /// @pre Size is > 0.
        StringField(size_t size) : RawField(size) { }

        /// @brief Constructor; creates a new instance of StringField.
        ///
        /// This constructor creates a new StringField instance of the same
        /// size as the specified string and initializes it to the same
        /// value as the specified string.
        ///
        /// @param value The string to create the field from.
        /// @pre Specified string length is > 0. 
        StringField(std::string value) : RawField(value.length()) 
        {
            SetValue(value); 
        }

        /// @brief Copy constructor; creates a deep copy of the field.
        /// @param other The field to copy.
        StringField(const StringField& other) : RawField(other) { }

        /// @brief Gets the value of the field as a string.
        /// @return A string representing the value of the field.
        std::string Value() const;

        /// @brief Sets the value of the field.
        ///
        /// If the specified string's size is greater than the field's size,
        /// the specified value will be truncated to fit the field.
        ///
        /// @param value The string to set the field's value to.
        void SetValue(std::string value);

        /// @brief Converts the field's data to a string representation.
        /// @return A string representation of the field's data.
        std::string ToString() const override
        {
            return RawField::ToString(StringFormat::Raw);
        }

        /// @brief Converts the field's data to a string representation.
        /// @param format The format to use for the string conversion.
        /// @return A string representation of the field's data.
        std::string ToString(StringFormat format) const override
        {
            return RawField::ToString(format);
        }
    };
}

#endif