// StandardFileStream.h - Declares the StandardFileStream class.
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
    ///
    /// @invariant The file path is not empty.
    /// @invariant Position must be between 0 and Size, inclusive.
    /// @invariant Reading advances the position by field or structure size.
    /// @invariant Reading does not modify the file's contents.
    /// @invariant Writing advances the position and modifies file contents.
    class StandardFileStream : public FileStream
    {
    public:
        /// @brief Constructor; creates a new instance of StandardFileStream.
        /// @param filePath The path to the file on disk.
        /// @pre File path must not be empty.
        StandardFileStream(std::string filePath) 
            : filePath(filePath), position(0), mode(Binary::FileMode::Read)
        { }

        /// @copydoc FileStream::FileName
        virtual std::string FileName() const override;

        /// @copydoc FileStream::FilePath
        virtual std::string FilePath() const override { return filePath; }

        /// @copydoc FileStream::IsOpen
        virtual bool IsOpen() const override { return fileStream.is_open(); }

        /// @copydoc FileStream::FileExists
        virtual bool FileExists() const override
        {
            return std::filesystem::exists(filePath); 
        }

        /// @copydoc FileStream::FileSize
        virtual size_t FileSize() const override;
        
        /// @copydoc FileStream::Mode
        virtual FileMode Mode() const override { return mode; }

        /// @copydoc FileStream::Open
        virtual void Open(FileMode mode) override;

        /// @copydoc FileStream::Close
        virtual void Close() override
        {
            fileStream.close();
            position = 0;
        }

        /// @copydoc Stream::Read
        virtual void Read(DataField* field) const override;

        /// @copydoc Stream::Read
        virtual void Read(DataStructure* structure) const override;

        /// @copydoc Stream::FindNextChunk
        virtual std::shared_ptr<ChunkHeader> FindNextChunk(std::string id) const
            override;

        /// @copydoc Stream::Write
        virtual void Write(const DataField* field) override;

        /// @copydoc Stream::Write
        virtual void Write(const DataStructure* structure) override;

        /// @copydoc Stream::Position
        virtual size_t Position() const override { return position; }

        /// @copydoc Stream::SetPosition
        virtual void SetPosition(size_t p) const override
        {
            position = p;
            fileStream.seekg(p);
        }

        /// @copydoc Stream::Beginning
        virtual size_t Beginning() const override { return 0; }

        /// @copydoc Stream::End
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