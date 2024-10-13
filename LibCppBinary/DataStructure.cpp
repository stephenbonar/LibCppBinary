// DataStructure.cpp - Defines the DataStructure class.
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
// See the License for the specific language governing permissions and
// limitations under the License.

#include "DataStructure.h"

using namespace Binary;

const char* addNullObjectError{ "Cannot add null object to structure." };
const char* removeNullObjectError
{
    "Cannot remove null object from structure." 
};

void DataStructure::Add(std::shared_ptr<Object> object)
{
    if (object == nullptr)
        throw std::invalid_argument{ addNullObjectError };

    objects.push_back(object);
}

void DataStructure::Remove(std::shared_ptr<Object> object)
{
    if (object == nullptr)
        throw std::invalid_argument{ removeNullObjectError };

    for (auto i = objects.begin(); i != objects.end(); i++)
    {
        // Dereference the iterator to obtain the shared_ptr and compare it to
        // the specified object pointer to determine if it's the one we want
        // to remove. 
        if (*i == object)
            objects.erase(i);
    }
}

size_t DataStructure::Size() const
{
    size_t size{ 0 };

    for (auto o : objects)
        size += o->Size();

    return size;
}

void DataStructure::Read(Stream* s) const
{
    for (auto o : objects)
        o->Read(s);
}

void DataStructure::Write(Stream* s) const
{
    for (auto o: objects)
        o->Write(s);
}

std::string DataStructure::ToString() const
{
    std::stringstream s;

    for (auto o : objects)
        s << o->ToString() << std::endl;

    return s.str();
}

std::string DataStructure::ToString(Format f) const
{
    std::stringstream s;

    for (auto o : objects)
        s << o->ToString(f) << std::endl;

    return s.str();
}