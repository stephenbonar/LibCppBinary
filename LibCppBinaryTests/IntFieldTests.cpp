// IntFieldTests.cpp - Defines the IntFieldTests class and tests.
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

#include "IntFieldTests.h"

IntFieldTests::IntFieldTests()
{

}

TEST_F(IntFieldTests, ProperlyDetectsSystemEndianness)
{
    // Set the value to 1, which also sets the least significant byte to 1.
    int testValue = 1;

    // Get a pointer to the raw bytes of the value.
    char* testValuePtr = reinterpret_cast<char*>(&testValue);

    // If the first byte is the list significant byte, then we know we're
    // running on a little endian system. Check for little endian, otherwise
    // if we're running big endian, check for big.
    if (testValuePtr[0] == 1)
    {
        EXPECT_EQ(Binary::GetSystemEndianness(), 
                  Binary::FieldEndianness::Little);
    }
    else
    {
        EXPECT_EQ(Binary::GetSystemEndianness(), 
                  Binary::FieldEndianness::Big);
    }
}

TEST_F(IntFieldTests, InitializesFieldProperly)
{
    Binary::UInt16Field field;

    EXPECT_EQ(field.Value(), 0);
    EXPECT_EQ(field.Endianness(), Binary::GetSystemEndianness());
}

TEST_F(IntFieldTests, InitializesFieldWithValueProperly)
{
    Binary::UInt16Field field{ 100 };

    EXPECT_EQ(field.Value(), 100);
    EXPECT_EQ(field.Endianness(), Binary::GetSystemEndianness());
}

TEST_F(IntFieldTests, InitializesFieldWithEndiannessProperly)
{
    Binary::UInt16Field field{ Binary::FieldEndianness::Big };

    EXPECT_EQ(field.Value(), 0);
    EXPECT_EQ(field.Endianness(), Binary::FieldEndianness::Big);
}

TEST_F(IntFieldTests, InitializesFieldWithValueAndEndiannessProperly)
{
    Binary::UInt16Field field{ 100, Binary::FieldEndianness::Big };

    EXPECT_EQ(field.Value(), 100);
    EXPECT_EQ(field.Endianness(), Binary::FieldEndianness::Big);
}

TEST_F(IntFieldTests, SetsUnsignedValueProperly)
{
    Binary::UInt16Field field;

    field.SetValue(1000);

    EXPECT_EQ(field.Value(), 1000);
}

TEST_F(IntFieldTests, SetsSignedValueProperly)
{
    Binary::Int16Field field;

    field.SetValue(-1000);

    EXPECT_EQ(field.Value(), -1000);
}

TEST_F(IntFieldTests, SetsUnsignedBigEndianProperly)
{
    Binary::UInt16Field field;

    field.SetEndianness(Binary::FieldEndianness::Big);
    field.SetValue(1000);

    ASSERT_EQ(field.Size(), 2);
    EXPECT_EQ(field.Data()[0], 0x3);
    EXPECT_EQ(field.Data()[1], 0xE8);
}

TEST_F(IntFieldTests, SetsUnsignedLittleEndianProperly)
{
    Binary::UInt16Field field;

    field.SetEndianness(Binary::FieldEndianness::Little);
    field.SetValue(1000);

    ASSERT_EQ(field.Size(), 2);
    EXPECT_EQ(field.Data()[0], 0xE8);
    EXPECT_EQ(field.Data()[1], 0x3);
}

TEST_F(IntFieldTests, SetsSignedBigEndianProperly)
{
    Binary::Int16Field field;

    field.SetEndianness(Binary::FieldEndianness::Big);
    field.SetValue(-1000);

    ASSERT_EQ(field.Size(), 2);
    EXPECT_EQ(field.Data()[0], 0xFC);
    EXPECT_EQ(field.Data()[1], 0x18);
}

TEST_F(IntFieldTests, SetsSignedLittleEndianProperly)
{
    Binary::Int16Field field;

    field.SetEndianness(Binary::FieldEndianness::Little);
    field.SetValue(-1000);

    ASSERT_EQ(field.Size(), 2);
    EXPECT_EQ(field.Data()[0], 0x18);
    EXPECT_EQ(field.Data()[1], 0xFC);
}

TEST_F(IntFieldTests, SetstoDefaultEndiannessProperly)
{
    Binary::UInt16Field field;

    field.SetToDefaultEndianness();

    EXPECT_EQ(field.Endianness(), Binary::defaultEndianness);
}