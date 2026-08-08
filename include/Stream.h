// Stream.h - Declares the Stream class.
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

#ifndef BINARY_STREAM_H
#define BINARY_STREAM_H

#include <memory>
#include <string>
#include "DataField.h"
#include "DataStructure.h"
#include "ChunkHeader.h"

namespace Binary
{
    /// @brief Abstract base class representing a binary stream.
    ///
    /// Classes that represent a binary stream should derive from this 
    /// class. This class accepts pointers to instances of DataField and other
    /// types composed of data fields for reading and writing to and from the 
    /// binary data source.
    class Stream
    {
    public:
        /// @brief Default destructor; properly destroys the instance.
        virtual ~Stream() = default;

        /// @brief Reads data from the stream into the specified field.
        /// @param field The field to read data into.
        /// @pre Field size must be <= remaining buffer size.
        /// @post Position is advanced by field size.
        /// @post Specified field is updated with the data read from the buffer.
        /// @throws std::out_of_range if field size > remaining buffer size.
        virtual void Read(DataField& field) const = 0;

        /// @brief Reads data from stream into the specified data structure.
        /// @param structure The data structure to read data into.
        /// @pre Structure size must be <= remaining buffer size.
        /// @post Position is advanced by structure size.
        /// @post Specified structure is updated with the data read from buffer.
        /// @throws std::out_of_range if structure size > remaining buffer size.
        virtual void Read(DataStructure& structure) const = 0;

        /// @brief Finds the next chunk header with the specified ID.
        /// @param id The ID of the chunk to find.
        /// @return A pointer to the chunk header if found, otherwise nullptr.
        /// @pre id must be exactly 4 characters long.
        /// @post Position is advanced to the beginning of found chunk header.
        /// @throws std::invalid_argument if id is not 4 characters long.
        virtual std::shared_ptr<ChunkHeader> FindNextChunk(
            const std::string& id) const = 0;

        /// @brief Writes data to the stream from the specified field.
        /// @param field The field to write to the stream.
        /// @pre Field size must be <= remaining buffer size.
        /// @post Position is advanced by field size.
        /// @post Buffer is updated with the data from the specified field.
        /// @throws std::out_of_range if field size > remaining buffer size.
        virtual void Write(const DataField& field) = 0;

        /// @brief Writes the specified structure to the stream.
        /// @param structure The structure to write to the stream.
        /// @pre Structure size must be <= remaining buffer size.
        /// @post Position is advanced by structure size.
        /// @post Buffer is updated with the data from the specified structure.
        /// @throws std::out_of_range if structure size > remaining buffer size.
        virtual void Write(const DataStructure& structure) = 0;

        /// @brief Gets the current position in the stream.
        /// @return A size_t representing the position.
        virtual size_t Position() const = 0;

        /// @brief Sets the current position in the stream.
        /// @param p The position value to set.
        /// @pre Position must be between 0 and size, inclusive.
        /// @post Position is updated to the specified value.
        /// @throws std::out_of_range if position > size.
        virtual void SetPosition(size_t p) const = 0;
        
        /// @brief Gets the beginning position of the file.
        /// @return A size_t value representing the beginning position.
        virtual size_t Beginning() const = 0;

        /// @brief Gets the end position of the file.
        /// @return A size_t value representing the end position.
        virtual size_t End() const = 0;
    };
}

#endif