// DataStructureTests.h - Declares the DataStructureTests class.
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

#ifndef DATA_STRUCTURE_TESTS_H
#define DATA_STRUCTURE_TESTS_H

#include <memory>
#include <sstream>
#include <gtest/gtest.h>
#include "DataStructure.h"
#include "MockObject.h"
#include "MockStream.h"

class DataStructureTests : public ::testing::Test
{
protected:
    DataStructureTests();

    void AddMockObjectsToStructure();

    Binary::DataStructure testStructure;
    std::shared_ptr<MockObject> mockObject1;
    std::shared_ptr<MockObject> mockObject2;
    std::shared_ptr<MockObject> mockObject3;
    std::shared_ptr<MockStream> mockStream;
};

#endif