// StringFieldTests.cpp - Defines the StringFieldTests class and tests.
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

#include "StringFieldTests.h"

StringFieldTests::StringFieldTests()
{
    
}

TEST_F(StringFieldTests, InitalizesStringFieldProperlyViaString)
{
    Binary::StringField field{ "Testing" };

    ASSERT_NE(field.Data(), nullptr);
    EXPECT_EQ(field.Size(), 7);
    EXPECT_EQ(field.Value(), "Testing");
}

TEST_F(StringFieldTests, GetsValueProperly)
{
    Binary::StringField field{ "Testing" };

    EXPECT_EQ(field.Value(), "Testing");
}

TEST_F(StringFieldTests, SetsValueProperly)
{
    Binary::StringField field{ 4 };
    field.SetValue("Testing");

    EXPECT_EQ(field.Value(), "Test");
}