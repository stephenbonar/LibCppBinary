// StandardFileStream.h - Declares the StandardFileStream class.
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

#ifndef BINARY_STANDARD_FILE_STREAM_H
#define BINARY_STANDARD_FILE_STREAM_H

#include <string>
#include <filesystem>
#include <fstream>
#include "FileStream.h"
#include "FileMode.h"

namespace Binary
{
    /// @brief Provides a standard file stream for manipulating binary files.
    ///
    /// This class provides the standard implementation for reading from
    /// and writing to binary data files. It accepts pointers to instances of 
    /// DataField and other types composed of data fields for reading from and
    /// writing to the file. This class can be used directly for manipulating
    /// binary data in any binary file type, but more specialized file stream
    /// classes can inherit from this class to add onto the base functionality.
    
    class StandardFileStream : public FileStream
    {
    public:
        StandardFileStream(std::string filePath) 
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
        virtual size_t FileSize() const override
        {
            uintmax_t fileSize{ std::filesystem::file_size(filePath) };
            unsigned long long fileSizeLimit
            { 
                std::numeric_limits<size_t>::max() 
            };

            if (fileSize > fileSizeLimit)
            {
                std::stringstream error;
                error << "File size exceeds limit of " << fileSizeLimit;
                error << " bytes.";
                throw std::overflow_error{ error.str() };
            }
                
            return static_cast<size_t>(fileSize); 
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
        virtual void Read(DataField* field) const override;

        /// @brief Reads data from stream into the specified data structure.
        /// @param field A pointer to the data structure to read data into.
        virtual void Read(DataStructure* structure) const override;

        /// @brief Finds the next chunk header with the specified ID.
        /// @param chunkID The ID of the chunk to find.
        /// @return A pointer to the chunk header if found, otherwise nullptr.
        virtual std::shared_ptr<ChunkHeader> FindNextChunk(std::string id) const
            override;

        /// @brief Writes data to the stream from the specified field.
        /// @param field A pointer to the field to write to the stream.
        virtual void Write(DataField* field) override;

        /// @brief Writes the specified structure to the stream.
        /// @param structure A pointer to the structure to write to the stream.
        virtual void Write(DataStructure* structure) override;

        /// @brief Gets the current position in the stream.
        /// @return A size_t representing the position.
        virtual size_t Position() const override { return position; }

        /// @brief Sets the current position in the stream.
        /// @param position The position value to set.
        virtual void SetPosition(size_t p) const override
        {
            position = p;
            fileStream.seekg(p);
        }

        /// @brief Gets the beginning position of the file.
        /// @return A size_t value representing the beginning position.
        virtual size_t Beginning() const override { return 0; }

        /// @brief Gets the end position of the file.
        /// @return A size_t value representing the end position.
        virtual size_t End() const override { return FileSize(); }
    private:
        std::string filePath;

        // We make both position and fileStream mutable because we enforce
        // logical constness, where reading from the stream does not modify its
        // contents even if the position changes. Logical constness only 
        // enforces observable state changes of the underlying data.
        mutable size_t position;
        mutable std::fstream fileStream;

        FileMode mode;
    };
}

#endif