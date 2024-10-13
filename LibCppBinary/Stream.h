// Stream.h - Declares the Stream class.
//
// Copyright (C) 2024 Stephen Bonar
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

#include <string>
#include "StreamError.h"

namespace Binary
{
    /// @brief Represents a binary data stream.
    ///
    /// This is the abstract base class for all binary data streams. Classes
    /// that implement a binary data stream should inherit from this class as
    /// it declares the methods that should be common to all binary data stream
    /// classes.
    ///
    /// @invariant Beginning position is always 0. 
    /// @invariant Ending position should be >= beginning position.
    /// @invariant Position should always be between beginning and end.
    /// @invariant Size is ending position.
    class Stream
    {
    public:
        /// @brief Destructor; allows derived types to be properly deallocated.
        virtual ~Stream() = default;

        /// @brief The position that represents the beginning of the stream.
        /// @return A number representing the beginning position. 
        virtual size_t Beginning() const { return 0; }

        /// @brief The position that represents the end of the stream.
        /// @return A number representing the ending position.
        virtual size_t End() const = 0;

        /// @brief Indicates if the stream position is at the beginning.
        /// @return true if at the beginning, otherwise false.
        virtual bool IsAtBeginning() const;

        /// @brief Indicates if the stream position is at the end.
        /// @return true if at the end, otherwise false.
        virtual bool IsAtEnd() const;

        /// @brief Gets the current position of the stream.
        /// @return A number between 0 and the end representing the position.
        virtual std::size_t Position() const = 0;

        /// @brief Determines the size of the stream.
        /// @return A number representing the size of the stream. 
        virtual std::size_t Size() const { return End(); }

        /// @brief Reads a block of data from the stream.
        /// @param bytes A pointer to a buffer to read the bytes of data into.
        /// @param length The size of the buffer, in bytes.
        /// @pre bytes is not a null pointer.
        /// @pre bytes has been properly allocated.
        /// @pre length accurately reflects the size of the bytes buffer.
        virtual void Read(char* bytes, size_t length) = 0;

        /// @brief Writes a block of data to the stream.
        /// @param bytes A pointer to the buffer of bytes to write.
        /// @param length The size of the buffer, in bytes.
        /// @pre bytes is not a null pointer.
        /// @pre bytes has been properly allocated.
        /// @pre length accurately reflects the size of the bytes buffer.
        virtual void Write(char* bytes, size_t length) = 0;

        /*
        /// @brief Reads a FieldStruct from the steam.
        /// @param s A pointer to the FieldStruct to read data into.
        /// @pre s is not a null pointer.
        /// @pre FieldStruct size is not > End() - Position().
        virtual void Read(FieldStruct* s);

        /// @brief Writes a FieldStruct to the stream.
        /// @param s A pointer to the FieldStruct to write date into.
        /// @pre s is not a null pointer.
        virtual void Write(FieldStruct* s);
        */

        /// @brief Sets the current position in the stream. 
        /// @param position A value between the beginning and the end.
        /// @pre Position is between the beginning and the end of the stream.
        /// @post Position() returns the same value as position.
        virtual void SetPosition(std::size_t position) = 0;
    };
}

#endif