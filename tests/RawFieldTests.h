// RawFieldTests.h - Declares the RawFieldTests class and tests.
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

#ifndef RAW_FIELD_TESTS_H
#define RAW_FIELD_TESTS_H

#include <stdexcept>
#include <gtest/gtest.h>
#include "RawField.h"

class RawFieldTests : public ::testing::Test
{
protected:
    RawFieldTests();
};

#endif