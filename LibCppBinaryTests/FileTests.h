// FileTests.h - Declares the FileTests class.
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

#ifndef FILE_TESTS_H
#define FILE_TESTS_H

#include <memory>
#include <gtest/gtest.h>
#include "MockObject.h"
#include "MockFileSystem.h"
#include "MockFileStream.h"
#include "StandardFileStream.h"
#include "File.h"

class FileTests : public ::testing::Test
{
protected:
    FileTests();

    std::shared_ptr<Binary::File> testFile;
    std::shared_ptr<MockFileStream> mockFileStream;
    std::shared_ptr<MockFileSystem> mockFileSystem;
};

#endif