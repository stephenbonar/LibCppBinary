// Field.h - Declares the Field class.
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

#ifndef BINARY_FIELD_H
#define BINARY_FIELD_H

#include "Object.h"

#include <cstddef>
#include <string>
#include <stdexcept>
#include "Object.h"

namespace Binary
{
    constexpr int minFieldSize{ 1 };
    extern const char* fieldSizeError;
    extern const char* nullFieldError;

    class InvalidField : public std::invalid_argument
    {
    public:
        /// @brief Constructs an InvalidInstruction exception.
        /// @param message The error message to include with the exception.
        InvalidField(const char* message) : std::invalid_argument(message) { }
    };

    class Field : public Object
    {
    public:
        //virtual ~Field() = default;

        /// @brief Gets a raw pointer to the underlying data.
        ///
        /// This interface is intended for use with legacy APIs that need to
        /// work with the raw data. The delete[] instruction should not be 
        /// called on this pointer, nor should it be dereferenced once the
        /// Field has been destroyed or goes out of scope.
        ///
        /// @return The raw pointer to the underlying data.
        virtual char* Data() = 0;

        /// @brief Gets the size of the field, in bytes.
        /// @return The size of the raw field, in bytes.
        ///virtual std::size_t Size() const = 0; 
    };
}

#endif