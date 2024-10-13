// StandardFileStream.h - Declares the StandardFileStream class.
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
// See the License for the specific language governing permissionsand
// limitations under the License.

#ifndef BINARY_STANDARD_FILE_STREAM_H
#define BINARY_STANDARD_FILE_STREAM_H

#include <fstream>
#include <memory>
#include "FileStream.h"
#include "FileMode.h"

namespace Binary
{
    class StandardFileStream : public FileStream
    {
    public:
        StandardFileStream(std::string fileName, FileMode mode = FileMode::Read) 
            : fileName{ fileName }, stream{ }, 
            mode{ mode }, size{ 0 }, position{ 0 }
        {

        }

        std::string FileName() const override
        {
            return "";
        }

        bool IsOpen() const override
        {
            return false;
            //return stream.is_open();
        }

        bool Exists() const override
        {
            return false;
            //return std::filesystem::exists(mFileName);
        }

        std::size_t Position() const override
        {
            return -1;
            //return mOffset;
        }

        FileMode Mode() const override
        {
            return FileMode::Read;
            //return mMode;
        }

        std::size_t Size() const override;

        void Open(FileMode m = FileMode::Read) override;

        void Close() override
        {
            //mStream.close();
        }

        void Read(char* bytes, size_t length) override;

        void Write(char* bytes, size_t length) override;

        void SetPosition(std::size_t position) override;
    private:
        std::string fileName;
        std::fstream stream;
        FileMode mode;
        std::size_t size;
        std::size_t position;
    };
}

#endif