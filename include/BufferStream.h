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
        BufferStream(size_t size) : RawField(size), position(0)
        { }

        /// @copydoc Stream::Read
        void Read(DataField* field) const override;

        /// @copydoc Stream::Read
        void Read(DataStructure* structure) const override;
        
        /// @copydoc Stream::FindNextChunk
        std::shared_ptr<ChunkHeader> FindNextChunk(std::string id) const 
            override;

        /// @copydoc Stream::Write
        void Write(const DataField* field) override;

        /// @copydoc Stream::Write
        void Write(const DataStructure* structure) override;

        /// @copydoc Stream::Position 
        size_t Position() const override { return position; }

        /// @copydoc Stream::SetPosition
        void SetPosition(size_t position) const override;

        /// @copydoc Stream::Beginning
        size_t Beginning() const override { return 0; }

        /// @copydoc Stream::End
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