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
    EXPECT_EQ(static_cast<uint8_t>(field.RawData()[0]), 0x3);
    EXPECT_EQ(static_cast<uint8_t>(field.RawData()[1]), 0xE8);
}

TEST_F(IntFieldTests, SetsUnsignedLittleEndianProperly)
{
    Binary::UInt16Field field;

    field.SetEndianness(Binary::FieldEndianness::Little);
    field.SetValue(1000);

    ASSERT_EQ(field.Size(), 2);
    EXPECT_EQ(static_cast<uint8_t>(field.RawData()[0]), 0xE8);
    EXPECT_EQ(static_cast<uint8_t>(field.RawData()[1]), 0x3);
}

TEST_F(IntFieldTests, SetsSignedBigEndianProperly)
{
    Binary::Int16Field field;

    field.SetEndianness(Binary::FieldEndianness::Big);
    field.SetValue(-1000);

    ASSERT_EQ(field.Size(), 2);
    EXPECT_EQ(static_cast<uint8_t>(field.RawData()[0]), 0xFC);
    EXPECT_EQ(static_cast<uint8_t>(field.RawData()[1]), 0x18);
}

TEST_F(IntFieldTests, SetsSignedLittleEndianProperly)
{
    Binary::Int16Field field;

    field.SetEndianness(Binary::FieldEndianness::Little);
    field.SetValue(-1000);

    ASSERT_EQ(field.Size(), 2);
    EXPECT_EQ(static_cast<uint8_t>(field.RawData()[0]), 0x18);
    EXPECT_EQ(static_cast<uint8_t>(field.RawData()[1]), 0xFC);
}

TEST_F(IntFieldTests, SetstoDefaultEndiannessProperly)
{
    Binary::UInt16Field field;

    field.SetToDefaultEndianness();

    EXPECT_EQ(field.Endianness(), Binary::defaultEndianness);
}

TEST_F(IntFieldTests, GetsMinAndMaxValuesProperly)
{
    Binary::UInt8Field uint8;
    Binary::UInt16Field uint16;
    Binary::UInt24Field uint24;
    Binary::UInt32Field uint32;
    Binary::UInt64Field uint64;

    Binary::Int8Field int8;
    Binary::Int16Field int16;
    Binary::Int24Field int24;
    Binary::Int32Field int32;
    Binary::Int64Field int64;

    EXPECT_EQ(uint8.MinValue(), 0);
    EXPECT_EQ(uint8.MaxValue(), UINT8_MAX);
    EXPECT_EQ(uint16.MinValue(), 0);
    EXPECT_EQ(uint16.MaxValue(), UINT16_MAX);
    EXPECT_EQ(uint24.MinValue(), 0);
    EXPECT_EQ(uint24.MaxValue(), 16777215);
    EXPECT_EQ(uint32.MinValue(), 0);
    EXPECT_EQ(uint32.MaxValue(), UINT32_MAX);
    EXPECT_EQ(uint64.MinValue(), 0);
    EXPECT_EQ(uint64.MaxValue(), UINT64_MAX);

    EXPECT_EQ(int8.MinValue(), INT8_MIN);
    EXPECT_EQ(int8.MaxValue(), INT8_MAX);
    EXPECT_EQ(int16.MinValue(), INT16_MIN);
    EXPECT_EQ(int16.MaxValue(), INT16_MAX);
    EXPECT_EQ(int24.MinValue(), -8388608);
    EXPECT_EQ(int24.MaxValue(), 8388607);
    EXPECT_EQ(int32.MinValue(), INT32_MIN);
    EXPECT_EQ(int32.MaxValue(), INT32_MAX);
    EXPECT_EQ(int64.MinValue(), INT64_MIN);
    EXPECT_EQ(int64.MaxValue(), INT64_MAX);
}

TEST_F(IntFieldTests, SetsMinValuesProperly)
{
    Binary::UInt8Field uint8;
    Binary::UInt16Field uint16;
    Binary::UInt24Field uint24;
    Binary::UInt32Field uint32;
    Binary::UInt64Field uint64;

    Binary::Int8Field int8;
    Binary::Int16Field int16;
    Binary::Int24Field int24;
    Binary::Int32Field int32;
    Binary::Int64Field int64;

    uint8.SetValue(0);
    uint16.SetValue(0);
    uint24.SetValue(0);
    uint32.SetValue(0);
    uint64.SetValue(0);

    int8.SetValue(INT8_MIN);
    int16.SetValue(INT16_MIN);
    int24.SetValue(-8388608);
    int32.SetValue(INT32_MIN);
    int64.SetValue(INT64_MIN);
    
    EXPECT_EQ(uint8.Value(), uint8.MinValue());
    EXPECT_EQ(uint16.Value(), uint16.MinValue());
    EXPECT_EQ(uint24.Value(), uint24.MinValue());
    EXPECT_EQ(uint32.Value(), uint32.MinValue());
    EXPECT_EQ(uint64.Value(), uint64.MinValue());

    EXPECT_EQ(int8.Value(), int8.MinValue());
    EXPECT_EQ(int16.Value(), int16.MinValue());
    EXPECT_EQ(int24.Value(), int24.MinValue());
    EXPECT_EQ(int32.Value(), int32.MinValue());
    EXPECT_EQ(int64.Value(), int64.MinValue());
}

TEST_F(IntFieldTests, SetsMaxValuesProperly)
{
    Binary::UInt8Field uint8;
    Binary::UInt16Field uint16;
    Binary::UInt24Field uint24;
    Binary::UInt32Field uint32;
    Binary::UInt64Field uint64;

    Binary::Int8Field int8;
    Binary::Int16Field int16;
    Binary::Int24Field int24;
    Binary::Int32Field int32;
    Binary::Int64Field int64;

    uint8.SetValue(UINT8_MAX);
    uint16.SetValue(UINT16_MAX);
    uint24.SetValue(16777215);
    uint32.SetValue(UINT32_MAX);
    uint64.SetValue(UINT64_MAX);

    int8.SetValue(INT8_MAX);
    int16.SetValue(INT16_MAX);
    int24.SetValue(8388607);
    int32.SetValue(INT32_MAX);
    int64.SetValue(INT64_MAX);

    EXPECT_EQ(uint8.Value(), uint8.MaxValue());
    EXPECT_EQ(uint16.Value(), uint16.MaxValue());
    EXPECT_EQ(uint24.Value(), uint24.MaxValue());
    EXPECT_EQ(uint32.Value(), uint32.MaxValue());
    EXPECT_EQ(uint64.Value(), uint64.MaxValue());

    EXPECT_EQ(int8.Value(), int8.MaxValue());
    EXPECT_EQ(int16.Value(), int16.MaxValue());
    EXPECT_EQ(int24.Value(), int24.MaxValue());
    EXPECT_EQ(int32.Value(), int32.MaxValue());
    EXPECT_EQ(int64.Value(), int64.MaxValue());
}

TEST_F(IntFieldTests, SetsBigEndianMinValuesProperly)
{
    Binary::UInt8Field uint8{ Binary::FieldEndianness::Big };
    Binary::UInt16Field uint16{ Binary::FieldEndianness::Big };
    Binary::UInt24Field uint24{ Binary::FieldEndianness::Big };
    Binary::UInt32Field uint32{ Binary::FieldEndianness::Big };
    Binary::UInt64Field uint64{ Binary::FieldEndianness::Big };

    Binary::Int8Field int8{ Binary::FieldEndianness::Big };
    Binary::Int16Field int16{ Binary::FieldEndianness::Big };
    Binary::Int24Field int24{ Binary::FieldEndianness::Big };
    Binary::Int32Field int32{ Binary::FieldEndianness::Big };
    Binary::Int64Field int64{ Binary::FieldEndianness::Big };

    uint8.SetValue(0);
    uint16.SetValue(0);
    uint24.SetValue(0);
    uint32.SetValue(0);
    uint64.SetValue(0);

    int8.SetValue(INT8_MIN);
    int16.SetValue(INT16_MIN);
    int24.SetValue(-8388608);
    int32.SetValue(INT32_MIN);
    int64.SetValue(INT64_MIN);
    
    EXPECT_EQ(uint8.Value(), uint8.MinValue());
    EXPECT_EQ(uint16.Value(), uint16.MinValue());
    EXPECT_EQ(uint24.Value(), uint24.MinValue());
    EXPECT_EQ(uint32.Value(), uint32.MinValue());
    EXPECT_EQ(uint64.Value(), uint64.MinValue());

    EXPECT_EQ(int8.Value(), int8.MinValue());
    EXPECT_EQ(int16.Value(), int16.MinValue());
    EXPECT_EQ(int24.Value(), int24.MinValue());
    EXPECT_EQ(int32.Value(), int32.MinValue());
    EXPECT_EQ(int64.Value(), int64.MinValue());
}

TEST_F(IntFieldTests, SetsBigEndianMaxValuesProperly)
{
    Binary::UInt8Field uint8{ Binary::FieldEndianness::Big };
    Binary::UInt16Field uint16{ Binary::FieldEndianness::Big };
    Binary::UInt24Field uint24{ Binary::FieldEndianness::Big };
    Binary::UInt32Field uint32{ Binary::FieldEndianness::Big };
    Binary::UInt64Field uint64{ Binary::FieldEndianness::Big };

    Binary::Int8Field int8{ Binary::FieldEndianness::Big };
    Binary::Int16Field int16{ Binary::FieldEndianness::Big };
    Binary::Int24Field int24{ Binary::FieldEndianness::Big };
    Binary::Int32Field int32{ Binary::FieldEndianness::Big };
    Binary::Int64Field int64{ Binary::FieldEndianness::Big };

    uint8.SetValue(UINT8_MAX);
    uint16.SetValue(UINT16_MAX);
    uint24.SetValue(16777215);
    uint32.SetValue(UINT32_MAX);
    uint64.SetValue(UINT64_MAX);

    int8.SetValue(INT8_MAX);
    int16.SetValue(INT16_MAX);
    int24.SetValue(8388607);
    int32.SetValue(INT32_MAX);
    int64.SetValue(INT64_MAX);

    EXPECT_EQ(uint8.Value(), uint8.MaxValue());
    EXPECT_EQ(uint16.Value(), uint16.MaxValue());
    EXPECT_EQ(uint24.Value(), uint24.MaxValue());
    EXPECT_EQ(uint32.Value(), uint32.MaxValue());
    EXPECT_EQ(uint64.Value(), uint64.MaxValue());

    EXPECT_EQ(int8.Value(), int8.MaxValue());
    EXPECT_EQ(int16.Value(), int16.MaxValue());
    EXPECT_EQ(int24.Value(), int24.MaxValue());
    EXPECT_EQ(int32.Value(), int32.MaxValue());
    EXPECT_EQ(int64.Value(), int64.MaxValue());
}

TEST_F(IntFieldTests, ToStringReturnsValueByDefault)
{
    Binary::UInt8Field field{ 100 };

    EXPECT_EQ(field.ToString(), "100");
}
