// Object.h - Declares the Object class.
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

#ifndef BINARY_OBJECT_H
#define BINARY_OBJECT_H

#include <string>
#include "Stream.h"
#include "Format.h"

namespace Binary
{
    /// @brief Represents a binary data object.
    ///
    /// This is the base class that most other binary data classes should
    /// derive from.
    class Object
    {
    public:
        /// @brief Virtual destructor; ensures proper polymorphic deallocation.
        virtual ~Object() = default;

        /// @brief Gets the size of the object in bytes.
        /// @return The size of the object.
        virtual size_t Size() const = 0;

        /// @brief Reads the object's value(s) in from the specified stream.
        /// @param s The stream to read from.
        /// @pre s is not null.
        virtual void Read(Stream* s) const = 0;

        /// @brief Writes the object's value(s) to the specified stream.
        /// @param s The stream to write to.
        /// @pre s is not null.
        virtual void Write(Stream* s) const = 0;

        /// @brief Gets a string representation in the default format.
        /// @return A string representation of the data.
        virtual std::string ToString() const = 0;

        /// @brief Gets a string representation in the specified format.
        /// @param f The format to get a string representation in.
        /// @return A string representation of the data. 
        virtual std::string ToString(Format f) const = 0;
    };
}

#endif