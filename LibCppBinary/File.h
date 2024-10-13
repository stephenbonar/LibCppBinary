// File.h - Declares the File class.
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

#ifndef BINARY_FILE_H
#define BINARY_FILE_H

#include <string>
#include <memory>
#include "FileStream.h"
#include "FileSystem.h"
#include "DataStructure.h"

namespace Binary
{
    /// @brief Represents a binary file.
    class File
    {
    public:
        /// @brief Constructor; creates a File using a filename.
        /// 
        /// Creates a new File instance using the default FileStream and
        /// FileSystem dependencies.
        ///
        /// @param name The name / path of the file.
        File(std::string name)
        {
            
        }

        /// @brief Constructor; creates a File using specified dependencies.
        ///
        /// Use this constructor to create a File instance using dependency
        /// injection. This is ideal for testing or using implementations of
        /// FileStream and FileSystem that are not based on the standard
        /// library.
        ///
        /// @param fileStream The FileStream to use.
        /// @param fileSystem The FileSystem to use.
        File(std::shared_ptr<FileStream> fileStream, 
             std::shared_ptr<FileSystem> fileSystem)
        {

        }

        /// @brief Gets the filename.
        /// @return A string representing the filename / path to the file.
        std::string Name() const { return ""; }

        /// @brief Gets a pointer to the file's underlying DataStructure.
        /// @return A pointer to the file's DataStructure.
        std::shared_ptr<DataStructure> Structure() const { return nullptr; }

        /// @brief Gets a pointer to the associated FileStream.
        /// @return A pointer to the FileStream this file uses.
        std::shared_ptr<FileStream> Stream() const { return nullptr; }

        /// @brief Gets a pointer to the associated FileSystem.
        /// @return A pointer to the FileSystem this file uses.
        std::shared_ptr<FileSystem> System() const { return nullptr; }

        /// @brief Gets the total size of the file.
        /// @return The total size of the file. 
        size_t Size() const { return 0; }

        /// @brief Determines whether or not the file exists.
        /// @return true if the file exists, otherwise false.
        bool Exists() const { return false; }

        /// @brief Loads the entire file into its DataStructure.
        void Load();

        /// @brief Save the current information in the file's DataStructure.
        void Save();
    private:
        std::shared_ptr<DataStructure> structure;
        std::shared_ptr<FileStream> stream;
        std::shared_ptr<FileSystem> system;
    };
}

#endif