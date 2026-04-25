// FieldEndianness.h - Declares the FieldEndianness enum.
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

#ifndef BINARY_FIELD_ENDIANNESS_H
#define BINARY_FIELD_ENDIANNESS_H

namespace Binary
{
    /// @brief Determines the byte order of an integer.
    enum class FieldEndianness
    {
        /// @brief Least significant byte comes first.
        Little,

        /// @brief Most significant byte comes first.
        Big
    };
}

#endif