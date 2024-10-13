// StreamError.h - Declares the StreamError exception class.
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

#ifndef BINARY_STREAM_ERROR_H
#define BINARY_STREAM_ERROR_H

#include <stdexcept>

namespace Binary
{
    class StreamError : public std::runtime_error
    {
    public:
        /// @brief Constructs a StreamError exception.
        /// @param message The error message to include with the exception.
        StreamError(const char* message) : std::runtime_error(message) { }
    };
}

#endif