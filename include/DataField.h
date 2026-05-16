// DataField.h - Declares the DataField class.
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

#ifndef BINARY_DATA_FIELD_H
#define BINARY_DATA_FIELD_H

#include <string>
#include <stdexcept>
#include "StringFormat.h"

namespace Binary
{
    /// @brief Indicates the number of bits in a byte of data.
    inline constexpr int bitsPerByte{ 8 };

    /// @brief Abstract base class representing a data field in a binary file.
    ///
    /// Classes that represent a data field in a binary file should derive from
    /// this class. The Binary::Stream class accepts pointers to instances of
    /// DataField for reading and writing data fields to binary data sources.
    /// By properly inheriting from this class, the Binary::Stream class and
    /// its derivatives will automatically support reading and writing your 
    /// derived type. 
    class DataField
    {
    public:
        /// @brief Default destructor; properly destroys the instance. 
        virtual ~DataField() = default;

        /// @brief Gets the size of the data in the field.
        /// @return The size of the data in the field, in bytes.
        virtual size_t Size() const = 0;

        /// @brief Provides access to the field's raw data via pointer.
        ///
        /// Provides access to the raw data stored in the field. Note that this
        /// class should manage the lifecycle of the data, so do not attempt to
        /// deallocate the memory behind the pointer manually.
        ///
        /// @return A raw pointer to the data.
        virtual char* RawData() = 0;

        /// @brief Provides access to the field's raw data via const pointer.
        ///
        /// Provides read-only access to the raw data stored in the field. Note 
        /// that this class should manage the lifecycle of the data, so do not 
        /// attempt to deallocate the memory behind the pointer manually.
        ///
        /// @return A raw pointer to the data. 
        virtual const char* RawData() const = 0;

        /// @brief Copies the raw data to another DataField.
        ///
        /// This method copies the raw data to another DataField, truncating
        /// the data if the other field is smaller than this one.
        ///
        /// @param other A pointer to the other DataField to copy the data to.
        /// @post The raw data from this field is copied to the other field.
        virtual void CopyRawDataTo(DataField* other);

        /// @brief Converts the field's data to a string representation.
        /// @return A string representation of the field's data.
        virtual std::string ToString() const = 0;

        /// @brief Converts the field's data to a string representation.
        /// @param format The format to use for the string conversion.
        /// @return A string representation of the field's data.
        virtual std::string ToString(StringFormat format) const = 0;
    };
}

#endif