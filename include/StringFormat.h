// StringFormat.h - Declares the StringFormat enum.
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

#ifndef BINARY_STRING_FORMAT_H
#define BINARY_STRING_FORMAT_H

namespace Binary
{
    /// @brief Determines the format to output a string representation in.
    ///
    /// Data fields can be converted to a string representation. This enum
    /// allows you to choose the format of the string representation.
    enum class StringFormat
    {
        /// @brief Formats the string as a null-terminated string.
        Terminated,

        /// @brief Formats the string's characters "as-is" from the bytes.
        Raw,

        /// @brief Replaces any non-printable characters with a space.
        Printable,

        /// @brief Provides a binary representation of the data bytes.
        Bin,

        /// @brief Provides a hexadecimal representation of the bytes.
        Hex,

        /// @brief Formats bytes as decimal. Only works on int field types.
        Dec
    };
}

#endif