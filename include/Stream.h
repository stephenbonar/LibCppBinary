// Stream.h - Declares the Stream class.
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
        /// @param field A pointer to the field to read data into.
        virtual void Read(DataField* field) = 0;

        /// @brief Reads data from stream into the specified data structure.
        /// @param field A pointer to the data structure to read data into.
        virtual void Read(DataStructure* structure) = 0;

        /// @brief Finds the next chunk header with the specified ID.
        /// @param chunkID The ID of the chunk to find.
        /// @return A pointer to the chunk header if found, otherwise nullptr.
        virtual std::shared_ptr<ChunkHeader> FindNextChunk(std::string ID) = 0;

        /// @brief Writes data to the stream from the specified field.
        /// @param field A pointer to the field to write to the stream.
        virtual void Write(DataField* field) = 0;

        /// @brief Writes the specified structure to the stream.
        /// @param structure A pointer to the structure to write to the stream.
        virtual void Write(DataStructure* structure) = 0;

        /// @brief Gets the current position in the stream.
        /// @return A size_t representing the position.
        virtual uintmax_t Position() const = 0;

        /// @brief Sets the current position in the stream.
        /// @param position The position value to set.
        virtual void SetPosition(uintmax_t position) = 0;

        /// @brief Gets the beginning position of the file.
        /// @return A size_t value representing the beginning position.
        virtual uintmax_t Beginning() const = 0;

        /// @brief Gets the end position of the file.
        /// @return A size_t value representing the end position.
        virtual uintmax_t End() const = 0;
    };
}

#endif