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
    /// @brief The size of the chunk ID field, in bytes.
    inline constexpr int chunkIDSize{ 4 };

    /// @brief Error message for invalid chunk ID size.
    extern const char* chunkIDSizeError;
    
    /// @brief Represents the header of a binary data chunk.
    struct ChunkHeader : public DataStructure
    {
        /// @brief The ID of the chunk.
        StringField id{ chunkIDSize };

        /// @brief The size of the chunk's data.
        UInt32Field dataSize;

        /// @copydoc DataStructure::Fields
        std::vector<DataField*> Fields() override;

        /// @copydoc DataStructure::Fields
        std::vector<const DataField*> Fields() const override;

        /// @copydoc DataStructure::Size
        size_t Size() const override;
        
        /// @brief Assignment operator for ChunkHeader.
        ///
        /// Copies the values of all fields from another ChunkHeader instance.
        ///
        /// @param other The ChunkHeader to copy from.
        /// @return Reference to this ChunkHeader after assignment.
        ChunkHeader& operator=(const ChunkHeader& other);
    };
}

#endif