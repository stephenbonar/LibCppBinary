// ChunkHeader.h - Declares the ChunkHeader struct.
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

#ifndef BINARY_CHUNK_HEADER_H
#define BINARY_CHUNK_HEADER_H

#include <vector>
#include "DataStructure.h"
#include "DataField.h"
#include "StringField.h"
#include "IntField.h"

namespace Binary
{
    /// @brief Represents the header of a binary data chunk.
    struct ChunkHeader : public DataStructure
    {
        /// @brief The ID of the chunk.
        StringField id{ 4 };

        /// @brief The size of the chunk's data.
        UInt32Field dataSize;

        /// @brief Provides a vector of raw pointers to the structure's fields.
        ///
        /// This method is primarily intended for use by Binary::Stream and its
        /// derivatives for reading the fields from and to those streams.
        /// Access the fields directly rather than via this method.
        ///
        /// @return The vector containing the raw pointers for the field.
        std::vector<DataField*> Fields() override;

        /// @brief Gets the total size of all fields in the structure.
        /// @return The total size of the structure.
        size_t Size() const override;
        
        ChunkHeader& operator=(const ChunkHeader& other);
    };
}

#endif