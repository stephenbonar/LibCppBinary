// MockObject.h - Declares the MockObject class.
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

#ifndef MOCK_OBJECT_H
#define MOCK_OBJECT_H

#include <gmock/gmock.h>
#include "Object.h"

class MockObject : public Binary::Object
{
public:
    MOCK_METHOD(size_t, Size, (), (const, override));
    MOCK_METHOD(void, Read, (Binary::Stream* s), (const, override));
    MOCK_METHOD(void, Write, (Binary::Stream* s), (const, override));
    MOCK_METHOD(std::string, ToString, (), (const, override));
    MOCK_METHOD(std::string, ToString, (Binary::Format f), (const, override));
};


#endif