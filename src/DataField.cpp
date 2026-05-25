// DataField.cpp - Defines the DataField class.
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

#include "DataField.h"
#include <algorithm>
#include <cstring>

using namespace Binary;

void DataField::CopyRawDataTo(DataField* other)
{
    if (other == nullptr)
    {
        throw std::invalid_argument("Other field cannot be null.");
    }

    if (other == this)
    {
        return;
    }

    size_t copySize = std::min(Size(), other->Size());
    std::memcpy(other->RawData(), RawData(), copySize);
}