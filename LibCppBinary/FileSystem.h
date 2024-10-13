// FileSystem.h - Declares the FileSystem class.
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

#ifndef BINARY_FILE_SYSTEM_H
#define BINARY_FILE_SYSTEM_H

#include <string>

namespace Binary
{
    /// @brief Abstract base class for accessing file system info.
    ///
    /// Provides access to information about a file in the file system.
    /// Objects that derive from this class should provide a wrapper around
    /// file system routines.
    class FileSystem
    {
    public:
        /// @brief Destructor; allows derived types to be properly deallocated.
        virtual ~FileSystem() = default;

        /// @brief Gets the path of the file associated with this object.
        /// @return The filename / path of the associated object.
        virtual std::string FileName() const =0;

        /// @brief Determines the size of the associated file. 
        /// @return The size of the file.
        virtual size_t Size() const =0;

        /// @brief Determines if the file exists.
        /// @return true if the file exists, otherwise false. 
        virtual bool Exists() const =0;
    };
}

#endif