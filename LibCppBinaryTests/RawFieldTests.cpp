// RawFieldTests.cpp - Defines the RawFieldTests class and tests.
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

#include "RawFieldTests.h"

RawFieldTests::RawFieldTests()
{
    std::vector<char> testData{ 'T', 'e', 's', 't', '!' };
    testField = std::make_unique<Binary::RawField>(testData.size());
    std::memcpy(testField->Data(), testData.data(), testData.size());
}

void RawFieldTests::ExpectCreatedProperly(std::size_t size)
{
    ASSERT_NO_THROW(Binary::RawField{ size });
    Binary::RawField f{ size };
    EXPECT_EQ(f.Size(), size);
    std::stringstream expectedStringStream;
    for (std::size_t i = 0; i < size; i++)
    {
        expectedStringStream << "00";
        if (i < size - 1)
        {
            expectedStringStream << " ";
        }
    }
    EXPECT_EQ(f.ToString(), expectedStringStream.str());
}

TEST_F(RawFieldTests, CreatesRawFieldProperly)
{
    ExpectCreatedProperly(1);
    ExpectCreatedProperly(10);
    ExpectCreatedProperly(255);
}

TEST_F(RawFieldTests, DoesNotCreateInvalidRawField)
{
    ASSERT_THROW(Binary::RawField{ 0 }, Binary::InvalidField);
}

TEST_F(RawFieldTests, ConvertsToStringProperly)
{
    EXPECT_EQ(testField->ToString(), testHexString);
}

TEST_F(RawFieldTests, ConvertsToStringWithSpecifiedFormatProperly)
{
    EXPECT_EQ(testField->ToString(Binary::Format::Hex), testHexString);
    EXPECT_EQ(testField->ToString(Binary::Format::Bin), testBinString);
    EXPECT_EQ(testField->ToString(Binary::Format::Ascii), testAsciiString);
}

TEST_F(RawFieldTests, DoesNotAcceptDecFormat)
{
    ASSERT_THROW(testField->ToString(Binary::Format::Dec), 
        Binary::InvalidFormat);
}

TEST_F(RawFieldTests, CreatesDeepCopies)
{
    Binary::RawField f2 = Binary::RawField{ *testField };
    EXPECT_NE(f2.Data(), testField->Data());
    EXPECT_EQ(f2.Size(), testField->Size());
    EXPECT_EQ(f2.ToString(), testField->ToString());

    Binary::RawField f3{ 1 };
    f3 = f2;
    EXPECT_NE(f2.Data(), f3.Data());
    EXPECT_EQ(f2.Size(), f3.Size());
    EXPECT_EQ(f2.ToString(), f3.ToString());
}

TEST_F(RawFieldTests, MovesFieldsProperly)
{
    auto size = testField->Size();
    Binary::RawField f2 = Binary::RawField(std::move(*testField));
    ASSERT_THROW(testField->ToString(), Binary::InvalidField);
    EXPECT_EQ(testField->Data(), nullptr);
    EXPECT_EQ(testField->Size(), 0);
    ASSERT_NE(f2.Data(), nullptr);
    EXPECT_EQ(f2.Size(), size);
    EXPECT_EQ(f2.ToString(), testHexString);

    Binary::RawField f3{ 1 };
    f3 = std::move(f2);
    ASSERT_THROW(testField->ToString(), Binary::InvalidField);
    ASSERT_THROW(f2.ToString(), Binary::InvalidField);
    EXPECT_EQ(testField->Data(), nullptr);
    EXPECT_EQ(f2.Data(), nullptr);
    EXPECT_EQ(testField->Size(), 0);
    EXPECT_EQ(f2.Size(), 0);
    ASSERT_NE(f3.Data(), nullptr);
    EXPECT_EQ(f3.Size(), size);
    EXPECT_EQ(f3.ToString(), testHexString);
}

TEST_F(RawFieldTests, OutputsToStandardStreamProperly)
{
    std::stringstream s;
    s << *testField;
    EXPECT_EQ(s.str(), testField->ToString());
}

TEST_F(RawFieldTests, ReadsFromStreamProperly)
{
    MockStream s;

    EXPECT_CALL(s, Read(testField->Data(), testField->Size()));

    testField->Read(&s);
}

TEST_F(RawFieldTests, WritesToStreamProperly)
{
    MockStream s;

    EXPECT_CALL(s, Write(testField->Data(), testField->Size()));

    testField->Write(&s);
}