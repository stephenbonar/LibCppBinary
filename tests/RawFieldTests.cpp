// RawFieldTests.cpp - Defines the RawFieldTests class and tests.
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

#include "RawFieldTests.h"

RawFieldTests::RawFieldTests()
{
    
}

TEST_F(RawFieldTests, InitializesRawFieldProperlyViaSize)
{
    Binary::RawField field{ 4 };

    ASSERT_NE(field.RawData(), nullptr);
    EXPECT_EQ(field.Size(), 4);
}

TEST_F(RawFieldTests, SizeCanOnlyBeGreaterThanZero)
{
    ASSERT_THROW(Binary::RawField{ 0 }, std::invalid_argument);
}

TEST_F(RawFieldTests, DeepCopiesDataProperly)
{
    Binary::RawField original{ 4 };
    ASSERT_NE(original.RawData(), nullptr);
    ASSERT_EQ(original.Size(), 4);
    original.RawData()[0] = 'T';
    original.RawData()[1] = 'E';
    original.RawData()[2] = 'S';
    original.RawData()[3] = 'T';

    Binary::RawField copy{ original };
    ASSERT_NE(copy.RawData(), nullptr);

    // The pointers should not be the same in a deep copy.
    ASSERT_NE(original.RawData(), copy.RawData());

    // Ensure the data was copied byte for byte.
    EXPECT_EQ(original.Size(), copy.Size());
    EXPECT_EQ(copy.RawData()[0], 'T');
    EXPECT_EQ(copy.RawData()[1], 'E');
    EXPECT_EQ(copy.RawData()[2], 'S');
    EXPECT_EQ(copy.RawData()[3], 'T');
}

TEST_F(RawFieldTests, FormatsStringRawProperly)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.RawData(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.RawData()[0] = 'T';
    field.RawData()[1] = 'E';
    field.RawData()[2] = 'S';
    field.RawData()[3] = 'T';

    EXPECT_EQ(field.ToString(Binary::StringFormat::Raw), "TEST");
}

TEST_F(RawFieldTests, FormatsStringPrintableProperly)
{
    Binary::RawField field{ 5 };
    ASSERT_NE(field.RawData(), nullptr);
    ASSERT_EQ(field.Size(), 5);
    field.RawData()[0] = 'T';
    field.RawData()[1] = 'S';
    field.RawData()[2] = 'T';

    // Non-printable control code to replace with '.'.
    field.RawData()[3] = 1;

    // Extended ASCII character to replace with '.'.
    field.RawData()[4] = -1;

    EXPECT_EQ(field.ToString(Binary::StringFormat::Printable), "TST..");
}

TEST_F(RawFieldTests, FormatsStringPrintableReplacesBoundaryControlChar)
{
    Binary::RawField field{ 3 };
    ASSERT_NE(field.RawData(), nullptr);
    ASSERT_EQ(field.Size(), 3);

    // Printable space character (32) should be kept.
    field.RawData()[0] = 32;

    // Unit Separator (31) is a non-printable control character and must be
    // replaced with '.'.
    field.RawData()[1] = 31;

    // DEL (127) is non-printable and must be replaced with '.'.
    field.RawData()[2] = 127;

    EXPECT_EQ(field.ToString(Binary::StringFormat::Printable), " ..");
}

TEST_F(RawFieldTests, FormatsStringBinProperly)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.RawData(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.RawData()[0] = 0;
    field.RawData()[1] = 1;
    field.RawData()[2] = 2;
    field.RawData()[3] = -1;

    EXPECT_EQ(field.ToString(Binary::StringFormat::Bin),
              "00000000 00000001 00000010 11111111");
}

TEST_F(RawFieldTests, FormatsStringHexProperly)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.RawData(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.RawData()[0] = 0;
    field.RawData()[1] = 1;
    field.RawData()[2] = 2;
    field.RawData()[3] = -1;

    EXPECT_EQ(field.ToString(Binary::StringFormat::Hex), "00 01 02 FF");
}

TEST_F(RawFieldTests, DoesNotFormatStringDec)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.RawData(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.RawData()[0] = 0;
    field.RawData()[1] = 1;
    field.RawData()[2] = 2;
    field.RawData()[3] = -1;

    ASSERT_THROW(field.ToString(Binary::StringFormat::Dec), 
                 std::invalid_argument);
}

TEST_F(RawFieldTests, FormatsHexByDefault)
{
    Binary::RawField field{ 4 };
    ASSERT_NE(field.RawData(), nullptr);
    ASSERT_EQ(field.Size(), 4);
    field.RawData()[0] = 0xA;
    field.RawData()[1] = 0xB;
    field.RawData()[2] = 0xC;
    field.RawData()[3] = 0xD;

    EXPECT_EQ(field.ToString(), "0A 0B 0C 0D");
}

TEST_F(RawFieldTests, CopyAssignmentOperatorWorksProperly)
{
    Binary::RawField original{ 4 };
    original.RawData()[0] = 'A';
    original.RawData()[1] = 'B';
    original.RawData()[2] = 'C';
    original.RawData()[3] = 'D';

    Binary::RawField copy{ 4 };
    copy.RawData()[0] = 'X';
    copy.RawData()[1] = 'Y';
    copy.RawData()[2] = 'Z';
    copy.RawData()[3] = 'W';

    copy = original;

    ASSERT_EQ(copy.Size(), original.Size());
    ASSERT_NE(copy.RawData(), original.RawData());
    EXPECT_EQ(copy.RawData()[0], 'A');
    EXPECT_EQ(copy.RawData()[1], 'B');
    EXPECT_EQ(copy.RawData()[2], 'C');
    EXPECT_EQ(copy.RawData()[3], 'D');
}

