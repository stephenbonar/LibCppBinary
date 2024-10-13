// MockFileSystem.h - Declares the MockFileSystem class.
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

#ifndef MOCK_FILE_SYSTEM_H
#define MOCK_FILE_SYSTEM_H

#include <gmock/gmock.h>
#include "FileSystem.h"

class MockFileSystem : public Binary::FileSystem
{
public:
    MOCK_METHOD(std::string, FileName, (), (const, override));
    MOCK_METHOD(size_t, Size, (), (const, override));
    MOCK_METHOD(bool, Exists, (), (const, override));
};

#endif