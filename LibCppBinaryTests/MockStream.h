// MockStream.h - Declares the MockStream class.
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

#ifndef MOCK_STREAM_H
#define MOCK_STREAM_H

#include <gmock/gmock.h>
#include "Stream.h"

class MockStream : public Binary::Stream
{
public:
    //MOCK_METHOD(std::size_t, Beginning, (), (const, override));
    MOCK_METHOD(std::size_t, End, (), (const, override));
    //MOCK_METHOD(bool, IsAtBeginning, (), (const, override));
    //MOCK_METHOD(bool, IsAtEnd, (), (const, override));
    MOCK_METHOD(std::size_t, Position, (), (const, override));
    //MOCK_METHOD(std::size_t, Size, (), (const, override));
    MOCK_METHOD(void, Read, (char* bytes, size_t length), (override));
    MOCK_METHOD(void, Write, (char* bytes, size_t length), (override));
    MOCK_METHOD(void, SetPosition, (std::size_t position), (override));
};

#endif