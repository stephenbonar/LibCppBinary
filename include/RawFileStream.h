// RawFileStream.h - Declares the RawFileStream class.
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

#ifndef BINARY_RAW_FILE_STREAM_H
#define BINARY_RAW_FILE_STREAM_H

#include <string>
#include <filesystem>
#include <fstream>
#include "FileStream.h"
#include "FileMode.h"

namespace Binary
{
    /// @brief Provides a generic file stream for manipulating binary files.
    ///
    /// This class provides a basic, generic implementation for reading from
    /// and writing to binary data files. It accepts pointers to instances of 
    /// DataField and other types composed of data fields for reading from and
    /// writing to the file. This class can be used directly for manipulating
    /// binary data in any binary file type, but more specialized file stream
    /// classes can inherit from this class to add onto the base functionality.
    ///
    /// NOTE: This class uses virtual inheritance from FileStream to allow for
    /// multiple inheritance in derived classes. For instance, a derived class
    /// may want to inherit the standard implementation this class provides but
    /// still add its own specialized functionality as another abstract base
    /// class. By using virtual inheritance here, we avoid the diamond problem.
    class RawFileStream : public virtual FileStream
    {
    public:
        RawFileStream(std::string filePath) 
            : filePath(filePath), position(0), mode(Binary::FileMode::Read)
        { }

        /// @brief Gets the name of the file.
        /// @return A string representing the name of the file.
        virtual std::string FileName() const override;

        /// @brief Gets the full path to the file on disk.
        /// @return A string representing the full path to the file.
        virtual std::string FilePath() const override { return filePath; }

        /// @brief Determines whether or not the file is open.
        /// @return True if it is open, otherwise false.
        virtual bool IsOpen() const override { return fileStream.is_open(); }

        /// @brief Determines whether or not the file exists on disk.
        /// @return True if it exists, otherwise false.
        virtual bool FileExists() const override
        {
            return std::filesystem::exists(filePath); 
        }

        /// @brief Gets the size of the file associated with the stream.
        /// @return The size of the file, in bytes.
        virtual uintmax_t FileSize() const override
        {
            return std::filesystem::file_size(filePath); 
        }
        
        /// @brief Determines the mode the file is set to open in.
        /// @return The file mode.
        virtual FileMode Mode() const override { return mode; }

        /// @brief Opens the file in the specified mode.
        /// @param mode The mode to open the file in.
        virtual void Open(FileMode mode) override;

        /// @brief Closes the file. 
        virtual void Close() override
        {
            fileStream.close();
            position = 0;
        }

        /// @brief Reads data from the stream into the specified field.
        /// @param field A pointer to the field to read data into.
        virtual void Read(DataField* field) override;

        /// @brief Reads data from stream into the specified data structure.
        /// @param field A pointer to the data structure to read data into.
        virtual void Read(DataStructure* structure) override;

        /// @brief Finds the next chunk header with the specified ID.
        /// @param chunkID The ID of the chunk to find.
        /// @return A pointer to the chunk header if found, otherwise nullptr.
        virtual std::shared_ptr<ChunkHeader> FindNextChunk(std::string ID) 
            override;

        /// @brief Writes data to the stream from the specified field.
        /// @param field A pointer to the field to write to the stream.
        virtual void Write(DataField* field) override;

        /// @brief Writes the specified structure to the stream.
        /// @param structure A pointer to the structure to write to the stream.
        virtual void Write(DataStructure* structure) override;

        /// @brief Gets the current position in the stream.
        /// @return A size_t representing the position.
        virtual uintmax_t Position() const override { return position; }

        /// @brief Sets the current position in the stream.
        /// @param position The position value to set.
        virtual void SetPosition(uintmax_t position) override
        {
            this->position = position;
            fileStream.seekg(position);
        }

        /// @brief Gets the beginning position of the file.
        /// @return A size_t value representing the beginning position.
        virtual uintmax_t Beginning() const override { return 0; }

        /// @brief Gets the end position of the file.
        /// @return A size_t value representing the end position.
        virtual uintmax_t End() const override { return FileSize(); }
    private:
        uintmax_t position;
        std::string filePath;
        std::fstream fileStream;
        FileMode mode;
    };
}

#endif