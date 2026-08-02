// DataFieldTests.cpp - Defines the DataFieldTests class and tests.
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

#include "DataFieldTests.h"
#include "MockDataField.h"
#include "RawField.h"
#include <cstring>

TEST_F(DataFieldTests, CopiesRawDataProperly)
{
    // Create a source mock data field with 10 bytes
    MockDataField source;
    char sourceData[10] = {0x01, 0x02, 0x03, 0x04, 0x05,
                           0x06, 0x07, 0x08, 0x09, 0x0A};
    
    // Set up expectations for the source field
    EXPECT_CALL(source, Size()).WillRepeatedly(::testing::Return(10));
    EXPECT_CALL(source, RawData()).WillRepeatedly(::testing::Return(sourceData));
    
    // Create a destination mock data field with 5 bytes
    MockDataField destination;
    char destData[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    
    // Set up expectations for the destination field
    EXPECT_CALL(destination, Size()).WillRepeatedly(::testing::Return(5));
    EXPECT_CALL(destination, RawData()).WillRepeatedly(::testing::Return(destData));
    
    // Call CopyRawDataTo - should copy 5 bytes (the minimum of the two sizes)
    source.CopyRawDataTo(destination);
    
    // Verify that the destination received the first 5 bytes of source data
    EXPECT_EQ(destData[0], 0x01);
    EXPECT_EQ(destData[1], 0x02);
    EXPECT_EQ(destData[2], 0x03);
    EXPECT_EQ(destData[3], 0x04);
    EXPECT_EQ(destData[4], 0x05);
}

TEST_F(DataFieldTests, CopyRawDataToSelfDoesNothing)
{
    Binary::RawField field{ 4 };
    field.RawData()[0] = 'T';
    field.RawData()[1] = 'E';
    field.RawData()[2] = 'S';
    field.RawData()[3] = 'T';

    EXPECT_NO_THROW(field.CopyRawDataTo(field));
    EXPECT_EQ(field.RawData()[0], 'T');
    EXPECT_EQ(field.RawData()[1], 'E');
    EXPECT_EQ(field.RawData()[2], 'S');
    EXPECT_EQ(field.RawData()[3], 'T');
}