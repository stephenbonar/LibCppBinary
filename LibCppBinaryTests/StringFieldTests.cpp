// StringFieldTests.cpp - Defines the StringFieldTests class and tests.
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

#include "StringFieldTests.h"

StringFieldTests::StringFieldTests()
{
    std::vector<char> nonPrt{ '\x01', '\x7F', '\x80', '\xFF' };
    std::vector<char> prt{ 
        'T', 'h', 'i', 's', ' ', 'i', 's', ' ', 
        'a', ' ', 't', 'e', 's', 't', '!' 
    };
    std::vector<char> mixed{ 'T', '\x01', 'E', '\x7F', 'S', '\x80', 'T' };

    nonPrintableField = std::make_unique<Binary::StringField>(nonPrt.size());
    printableField = std::make_unique<Binary::StringField>(prt.size());
    mixedField = std::make_unique<Binary::StringField>(mixed.size());

    std::memcpy(nonPrintableField->Data(), nonPrt.data(), nonPrt.size());
    std::memcpy(printableField->Data(), prt.data(), prt.size());
    std::memcpy(mixedField->Data(), mixed.data(), mixed.size());
}

void StringFieldTests::ExpectCreatedProperly(std::size_t size)
{
    ASSERT_NO_THROW(Binary::StringField{ size });
    Binary::StringField f{ size };
    EXPECT_EQ(f.Size(), size);
    std::stringstream expectedStringStream;

    for (std::size_t i = 0; i < size; i++)
    {
        expectedStringStream << ".";
    }

    EXPECT_EQ(f.ToString(), expectedStringStream.str());
}

TEST_F(StringFieldTests, CreatesStringFieldProperly)
{
    ExpectCreatedProperly(1);
    ExpectCreatedProperly(10);
    ExpectCreatedProperly(255);
}

TEST_F(StringFieldTests, CreatesIntFieldsWithAlternateConstructorsProperly)
{
    Binary::StringField f{ printableString, 15 };
    EXPECT_EQ(f.ToString(), printableString);
}

TEST_F(StringFieldTests, DoesNotCreateInvalidStringField)
{
    ASSERT_THROW(Binary::StringField{ 0 }, Binary::InvalidField);
}

TEST_F(StringFieldTests, ConvertsToStringProperly)
{
    EXPECT_EQ(nonPrintableField->ToString(), nonPrintableString);
    EXPECT_EQ(printableField->ToString(), printableString);
    EXPECT_EQ(mixedField->ToString(), mixedString);
}

TEST_F(StringFieldTests, ConvertsToStringWithSpecifiedFormatProperly)
{
    EXPECT_EQ(mixedField->ToString(Binary::Format::Ascii), mixedString);
    EXPECT_EQ(mixedField->ToString(Binary::Format::Hex), mixedStringHex);
    EXPECT_EQ(mixedField->ToString(Binary::Format::Bin), mixedStringBin);
}

TEST_F(StringFieldTests, DoesNotAcceptDecFormat)
{
    ASSERT_THROW(mixedField->ToString(Binary::Format::Dec), 
        Binary::InvalidFormat);
}

TEST_F(StringFieldTests, SetsValuesProperly)
{
    Binary::StringField smallerField{ 5 };
    Binary::StringField sameSizeField{ 15 };
    Binary::StringField largerField{ 20 };

    smallerField.SetData(printableString);
    sameSizeField.SetData(printableString);
    largerField.SetData(printableString);

    EXPECT_EQ(smallerField.ToString(), printableStringSmaller);
    EXPECT_EQ(sameSizeField.ToString(), printableString);
    EXPECT_EQ(largerField.ToString(), printableStringLarger);
}

TEST_F(StringFieldTests, CreatesDeepCopies)
{
    Binary::StringField f2 = Binary::StringField{ *printableField };
    EXPECT_NE(f2.Data(), printableField->Data());
    EXPECT_EQ(f2.Size(), printableField->Size());
    EXPECT_EQ(f2.ToString(), printableField->ToString());

    Binary::StringField f3{ 1 };
    f3 = f2;
    EXPECT_NE(f2.Data(), f3.Data());
    EXPECT_EQ(f2.Size(), f3.Size());
    EXPECT_EQ(f2.ToString(), f3.ToString());
}

TEST_F(StringFieldTests, MovesFieldsProperly)
{
    auto size = printableField->Size();
    Binary::StringField f2 = Binary::StringField(std::move(*printableField));
    ASSERT_THROW(printableField->ToString(), Binary::InvalidField);
    EXPECT_EQ(printableField->Data(), nullptr);
    EXPECT_EQ(printableField->Size(), 0);
    ASSERT_NE(f2.Data(), nullptr);
    EXPECT_EQ(f2.Size(), size);
    EXPECT_EQ(f2.ToString(), printableString);

    Binary::StringField f3{ 1 };
    f3 = std::move(f2);
    ASSERT_THROW(printableField->ToString(), Binary::InvalidField);
    ASSERT_THROW(f2.ToString(), Binary::InvalidField);
    EXPECT_EQ(printableField->Data(), nullptr);
    EXPECT_EQ(f2.Data(), nullptr);
    EXPECT_EQ(printableField->Size(), 0);
    EXPECT_EQ(f2.Size(), 0);
    ASSERT_NE(f3.Data(), nullptr);
    EXPECT_EQ(f3.Size(), size);
    EXPECT_EQ(f3.ToString(), printableString);
}

TEST_F(StringFieldTests, OutputsToStandardStreamProperly)
{
    std::stringstream s;
    s << *printableField;
    EXPECT_EQ(s.str(), printableField->ToString());
}

TEST_F(StringFieldTests, ReadsFromStreamProperly)
{
    MockStream s;

    EXPECT_CALL(s, Read(printableField->Data(), printableField->Size()));

    printableField->Read(&s);
}

TEST_F(StringFieldTests, WritesToStreamProperly)
{
    MockStream s;

    EXPECT_CALL(s, Write(printableField->Data(), printableField->Size()));

    printableField->Write(&s);
}