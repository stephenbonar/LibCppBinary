// DataStructure.h - Declares the DataStructure struct.
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

#ifndef BINARY_DATA_STRUCTURE_H
#define BINARY_DATA_STRUCTURE_H

#include <vector>
#include "DataField.h"

namespace Binary
{
    /// @brief Abstract base struct representing data structure in binary file.
    ///
    /// Structs that represent a data structure in a binary file should derive
    /// from this struct. The Binary::Stream class accepts pointers to instances
    /// of DataStructure for reading and writing data structures to binary data
    /// sources. By properly inheriting from this struct, the Binary::Stream
    /// class and its derivatives will automatically support reading and 
    /// writing your derived type.
    ///
    /// This provides an interface for a binary data structures. It is 
    /// recommended that the derived implementations follow these guidelines:
    ///
    /// 1) Make fields available as public struct members for general access.
    /// 2) Fields() should return a vector of pointers to the struct members
    ///    in the order that they should be read from and written to files.
    /// 3) Size() should sum all of the field sizes.
    struct DataStructure
    {
        /// @brief Provides a vector of raw pointers to the structure's fields.
        ///
        /// This method is primarily intended for use by Binary::Stream and its
        /// derivatives for reading the fields from and to those streams.
        /// Access the fields directly rather than via this method.
        ///
        /// @return The vector containing the raw pointers for the field.
        virtual std::vector<DataField*> Fields() = 0;

        /// @brief Gets the total size of all fields in the structure.
        /// @return The total size of the structure.
        virtual size_t Size() const = 0;
    };
}

#endif