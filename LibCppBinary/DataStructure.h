// DataStructure.h - Declares the DataStructure class.
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

#ifndef BINARY_DATA_STRUCTURE_H
#define BINARY_DATA_STRUCTURE_H

#include <vector>
#include <memory>
#include <sstream>
#include "Object.h"

namespace Binary
{
    class DataStructure : public Object
    {
    public:
        /// @brief Adds the specified object onto the end of the structure.
        /// @param object A pointer to the object to add.
        /// @pre object is not null.
        virtual void Add(std::shared_ptr<Object> object);

        /// @brief Removes the specified object from the structure.
        /// @param object A pointer to the object to remove.
        /// @pre object is not null.
        virtual void Remove(std::shared_ptr<Object> object);

        /// @brief Gets the objects that make up the structure.
        /// @return A vector of pointers to the structure's objects.
        virtual std::vector<std::shared_ptr<Object>> Objects() const 
        {
            return objects; 
        }

        /// @brief Gets the number of objects contained within the structure.
        /// @return The number of objects within the structure.
        virtual size_t Count() const { return objects.size(); }

        /// @brief Gets the size of the object in bytes.
        /// @return The size of the object.
        virtual size_t Size() const override;

        /// @brief Reads the object's value(s) in from the specified stream.
        /// @param s The stream to read from.
        /// @pre s is not null.
        virtual void Read(Stream* s) const override;

        /// @brief Writes the object's value(s) to the specified stream.
        /// @param s The stream to write to.
        /// @pre s is not null.
        virtual void Write(Stream* s) const override;

        /// @brief Gets a string representation in the default format.
        /// @return A string representation of the data.
        virtual std::string ToString() const override;

        /// @brief Gets a string representation in the specified format.
        /// @param f The format to get a string representation in.
        /// @return A string representation of the data. 
        virtual std::string ToString(Format f) const override;
    private:
        std::vector<std::shared_ptr<Object>> objects;
    };
}

#endif