// BufferStream.h - Declares the BufferStream class.
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

#ifndef BINARY_BUFFER_STREAM_H
#define BINARY_BUFFER_STREAM_H

#include "RawField.h"
#include "Stream.h"

namespace Binary
{
    /// @brief Represents a memory buffer that can be used as a stream.
    ///
    /// Rather than reading or writing individual fields or structures to a 
    /// file, you can use this class to read or write a large block of data to 
    /// or from memory, which can improve performance. Individual fields and 
    /// structures can then be read from or written to the buffer as needed.
    ///
    /// @invariant Size must be greater than 0.
    /// @invariant Position must be between 0 and Size, inclusive.
    /// @invariant Buffer memory must always be valid and allocated to size.
    /// @invariant Reading advances the position by field or structure size.
    /// @invariant Reading does not modify the buffer's contents.
    /// @invariant Writing both advances the position and modifies buffer.
    class BufferStream : public RawField, public Stream
    {
    public:
        /// @brief Creates a new instance of BufferStream.
        /// @param size The size of the buffer, in bytes.
        /// @pre Size must be greater than 0.
        /// @post Buffer memory is allocated to the specified size.
        /// @post Position is set to beginning (0).
        BufferStream(size_t size) : RawField(size), position(0)
        { }

        /// @brief Reads data from the stream into the specified field.
        /// @param field A pointer to the field to read data into.
        /// @pre Field must not be null.
        /// @pre Field size must be <= remaining buffer size.
        /// @post Position is advanced by field size.
        /// @post Specified field is updated with the data read from the buffer.
        /// @throws std::out_of_range if field size > remaining buffer size.
        /// @throws std::invalid_argument if field is null.
        void Read(DataField* field) const override;

        /// @brief Reads data from stream into the specified data structure.
        /// @param structure A pointer to the data structure to read data into.
        /// @pre Structure must not be null.
        /// @pre Structure size must be <= remaining buffer size.
        /// @post Position is advanced by structure size.
        /// @post Specified structure is updated with the data read from buffer.
        /// @throws std::out_of_range if structure size > remaining buffer size.
        /// @throws std::invalid_argument if structure is null.
        void Read(DataStructure* structure) const override;
        
        /// @brief Finds the next chunk header with the specified ID.
        /// @param ID The ID of the chunk to find.
        /// @return A pointer to the chunk header if found, otherwise nullptr.
        /// @pre ID must be exactly 4 characters long.
        /// @post Position is advanced to the beginning of found chunk header.
        /// @throws std::invalid_argument if ID is not 4 characters long.
        std::shared_ptr<ChunkHeader> FindNextChunk(std::string id) const 
            override;

        /// @brief Writes data to the stream from the specified field.
        /// @param field A pointer to the field to write to the stream.
        /// @pre Field must not be null.
        /// @pre Field size must be <= remaining buffer size.
        /// @post Position is advanced by field size.
        /// @post Buffer is updated with the data from the specified field.
        /// @throws std::out_of_range if field size > remaining buffer size.
        /// @throws std::invalid_argument if field is null.
        void Write(DataField* field) override;

        /// @brief Writes the specified structure to the stream.
        /// @param structure A pointer to the structure to write to the stream.
        /// @pre Structure must not be null.
        /// @pre Structure size must be <= remaining buffer size.
        /// @post Position is advanced by structure size.
        /// @post Buffer is updated with the data from the specified structure.
        /// @throws std::out_of_range if structure size > remaining buffer size.
        /// @throws std::invalid_argument if structure is null.
        void Write(DataStructure* structure) override;

        /// @brief Gets the current position in the stream.
        /// @return A size_t representing the position.
        size_t Position() const override { return position; }

        /// @brief Sets the current position in the stream.
        /// @param position The position value to set.
        void SetPosition(size_t position) const override 
        { 
            this->position = position; 
        }

        /// @brief Gets the beginning position of the file.
        /// @return A size_t value representing the beginning position.
        size_t Beginning() const override { return 0; }

        /// @brief Gets the end position of the file.
        /// @return A size_t value representing the end position.
        size_t End() const override { return size; }
    private:
        // We make position mutable because we enforce logical constness, where
        // reading from the stream does not modify its contents even if the
        // position changes. Logical constness only enforces observable state
        // changes of the underlying data.
        mutable size_t position;
    };
}

#endif