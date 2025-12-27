// BufferStream.h - Declares the BufferStream class.
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
    class BufferStream : public RawField, public Stream
    {
    public:
        /// @brief Creates a new instance of BufferStream.
        /// @param size The size of the buffer, in bytes.
        BufferStream(size_t size) : RawField(size), position(0)
        { }

        /* Shouldn't need these as they're inherited from RawField unless we need to change
           behavior later.
        // RawField overrides

        size_t Size() const override;

        char* Data() override;

        std::string ToString() const override;

        std::string ToString(StringFormat format) const override;
        */

        // Stream overrides

        /// @brief Reads data from the stream into the specified field.
        /// @param field A pointer to the field to read data into.
        void Read(DataField* field) override;

        /// @brief Reads data from stream into the specified data structure.
        /// @param structure A pointer to the data structure to read data into.
        void Read(DataStructure* structure) override;

        /// @brief Finds the next chunk header with the specified ID.
        /// @param ID The ID of the chunk to find.
        /// @return A pointer to the chunk header if found, otherwise nullptr.
        std::shared_ptr<ChunkHeader> FindNextChunk(std::string id) override;

        /// @brief Writes data to the stream from the specified field.
        /// @param field A pointer to the field to write to the stream.
        void Write(DataField* field) override;

        /// @brief Writes the specified structure to the stream.
        /// @param structure A pointer to the structure to write to the stream.
        void Write(DataStructure* structure) override;

        /// @brief Gets the current position in the stream.
        /// @return A size_t representing the position.
        uintmax_t Position() const override;

        /// @brief Sets the current position in the stream.
        /// @param position The position value to set.
        void SetPosition(uintmax_t position) override;

        /// @brief Gets the beginning position of the file.
        /// @return A size_t value representing the beginning position.
        uintmax_t Beginning() const override;

        /// @brief Gets the end position of the file.
        /// @return A size_t value representing the end position.
        uintmax_t End() const override;

    /*
    protected:
        // RawField protected methods
        std::string FormatData(StringFormat format) const;
    */

    private:
        uintmax_t position;
    /* Shouldn't need these as they're implementation details for RawField
        // RawField private methods
        std::string ConvertTerminated() const;

        std::string ConvertRaw() const;

        std::string ConvertPrintable() const;

        std::string ConvertBin() const;

        std::string ConvertHex() const;

    */

    };
}

#endif