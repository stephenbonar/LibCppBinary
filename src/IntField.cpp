// IntField.cpp - Defines the IntField class.
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

#include "IntField.h"

Binary::FieldEndianness Binary::defaultEndianness = 
    Binary::GetSystemEndianness();

Binary::FieldEndianness Binary::GetSystemEndianness()
{
    // Setting the value to 1 will make the least significant byte 1.
    int testValue{ 1 };

    // Get pointer to the raw bytes of testValue so we can check byte order.
    char* testValuePtr = reinterpret_cast<char*>(&testValue);

    // If the first byte is the least significant byte, it will contain the 1
    // and we know we're running on a little endian system, otherwise it's big.
    if (testValuePtr[0] == 1)
    {
        return Binary::FieldEndianness::Little;
    }
    else
    {
        return Binary::FieldEndianness::Big;
    }
}
