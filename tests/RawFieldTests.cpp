// RawFieldTests.cpp - Defines the RawFieldTests class and tests.
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

#include "RawFieldTests.h"

RawFieldTests::RawFieldTests()
{
    
}

TEST_F(RawFieldTests, InitializesRawFieldProperlyViaSize)
{
    Binary::RawField field{ 4 };

    ASSERT_NE(field.Data(), nullptr);
    EXPECT_EQ(field.Size(), 4);
}

TEST_F(RawFieldTests, SizeCanOnlyBeGreaterThanZero)
{
    ASSERT_THROW(Binary::RawField{ 0 }, std::invalid_argument);
}

TEST_F(RawFieldTests, DeepCopiesDataProperly)
{
    Binary::RawField original{ 4 };
    ASSERT_NE(original.Data(), nullptr);
    ASSERT_EQ(original.Size(), 4);
    original.Data()[0] = 'T';
    original.Data()[1] = 'E';
    original.Data()[2] = 'S';
    original.Data()[3] = 'T';

    Binary::RawField copy{ original };
    ASSERT_NE(copy.Data(), nullptr);

    // The pointers should not be the same in a deep copy.
    ASSERT_NE(original.Data(), copy.Data());

    // Ensure the data was copied byte for byte.
    EXPECT_EQ(original.Size(), copy.Size());
    EXPECT_EQ(copy.Data()[0], 'T');
    EXPECT_EQ(copy.Data()[1], 'E');
    EXPECT_EQ(copy.Data()[2], 'S');
    EXPECT_EQ(copy.Data()[3], 'T');
}

TEST_F(RawFieldTests, FormatsStringRawProperly)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.Data(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.Data()[0] = 'T';
    field.Data()[1] = 'E';
    field.Data()[2] = 'S';
    field.Data()[3] = 'T';

    EXPECT_EQ(field.ToString(Binary::StringFormat::Raw), "TEST");
}

TEST_F(RawFieldTests, FormatsStringPrintableProperly)
{
    Binary::RawField field{ 5 };
    ASSERT_NE(field.Data(), nullptr);
    ASSERT_EQ(field.Size(), 5);
    field.Data()[0] = 'T';
    field.Data()[1] = 'S';
    field.Data()[2] = 'T';

    // Non-printable control code to replace with '.'.
    field.Data()[3] = 1;

    // Extended ASCII character to replace wilth '.'.
    field.Data()[4] = -1;

    EXPECT_EQ(field.ToString(Binary::StringFormat::Printable), "TST..");
}

TEST_F(RawFieldTests, FormatsStringBinProperly)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.Data(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.Data()[0] = 0;
    field.Data()[1] = 1;
    field.Data()[2] = 2;
    field.Data()[3] = -1;

    EXPECT_EQ(field.ToString(Binary::StringFormat::Bin),
              "00000000 00000001 00000010 11111111");
}

TEST_F(RawFieldTests, FormatsStringHexProperly)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.Data(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.Data()[0] = 0;
    field.Data()[1] = 1;
    field.Data()[2] = 2;
    field.Data()[3] = -1;

    EXPECT_EQ(field.ToString(Binary::StringFormat::Hex), "00 01 02 FF");
}

TEST_F(RawFieldTests, DoesNotFormatStringDec)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.Data(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.Data()[0] = 0;
    field.Data()[1] = 1;
    field.Data()[2] = 2;
    field.Data()[3] = -1;

    ASSERT_THROW(field.ToString(Binary::StringFormat::Dec), 
                 std::invalid_argument);
}

TEST_F(RawFieldTests, FormatsHexByDefault)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.Data(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.Data()[0] = 0xA;
    field.Data()[1] = 0xB;
    field.Data()[2] = 0xC;
    field.Data()[3] = 0xD;

    EXPECT_EQ(field.ToString(), "0A 0B 0C 0D");
}