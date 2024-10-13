// MockFileStream.h - Declares the MockFileStream class.
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

#ifndef MOCK_FILE_STREAM_H
#define MOCK_FILE_STREAM_H

#include <gmock/gmock.h>
#include "FileStream.h"
#include "Field.h"

class MockFileStream : public Binary::FileStream
{
public:
    /*
    virtual std::string FileName() const = 0;

    virtual bool IsOpen() const = 0;

    virtual FileMode Mode() const = 0;

    virtual void Open(FileMode mode = FileMode::Read) = 0;

    virtual void Close() = 0;

    //virtual size_t Size() const = 0;

    virtual bool Exists() const = 0;

    MOCK_METHOD(std::size_t, End, (), (const, override));
    MOCK_METHOD(std::size_t, Position, (), (const, override));
    MOCK_METHOD(void, Read, (char* bytes, size_t length), (override));
    MOCK_METHOD(void, Write, (char* bytes, size_t length), (override));
    MOCK_METHOD(void, SetPosition, (std::size_t position), (override));
    */

    MOCK_METHOD(std::string, FileName, (), (const, override));
    MOCK_METHOD(bool, IsOpen, (), (const, override));
    MOCK_METHOD(bool, Exists, (), (const, override));
    MOCK_METHOD(std::size_t, Position, (), (const, override));
    MOCK_METHOD(Binary::FileMode, Mode, (), (const, override));
    MOCK_METHOD(std::size_t, Size, (), (const, override));
    MOCK_METHOD(void, Open, (Binary::FileMode mode), (override));
    MOCK_METHOD(void, Close, (), (override));
    MOCK_METHOD(void, Read, (char* bytes, size_t length), (override));
    MOCK_METHOD(void, Write, (char* bytes, size_t length), (override));
    MOCK_METHOD(void, SetPosition, (std::size_t position), (override));
    MOCK_METHOD(std::size_t, End, (), (const, override));
};

#endif