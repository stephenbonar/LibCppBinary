// IntField.h - Declares the IntField class.
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

#ifndef BINARY_INT_FIELD_H
#define BINARY_INT_FIELD_H

#include "RawField.h"
#include "FieldEndianness.h"

namespace Binary
{
    /// @brief Controls what endianness IntFields are created with by default.
    extern FieldEndianness defaultEndianness;

    /// @brief Represents an integer field in a binary file.
    ///
    /// Binary files can sometimes contain integer fields of varying sizes,
    /// signed or unsigned, with little endian or big endian byte order. This
    /// class template allows for a number of different variations of the
    /// int fields. Use the specializations of this template 
    /// (UInt8Field, Int8Field, UInt16Field, Int16Field, UInt24Field, 
    /// Int24Field, UInt32Field, Int32Field, UInt64Field, Int64Field) to read
    /// or write these types of fields from and to a Binary::Stream, such as a
    /// Binary::DataFileStream.
    template<typename IntType, size_t IntSize>
    class IntField : public RawField
    {
    public:
        /// @brief Default constructor; creates a new instance of IntField.
        IntField() : RawField(IntSize)
        {
            InitializeData();
            SetToDefaultEndianness();
        }

        /// @brief Constructor; creates a new instance of IntField.
        /// @param value The value to initalize the field to.
        IntField(int value) : RawField(IntSize)
        {
            InitializeData();
            SetToDefaultEndianness();
            SetValue(value);
        }

        /// @brief Constructor; creates a new instance of IntField.
        /// @param endianness The endianness the field should use.
        IntField(FieldEndianness endianness) : RawField(IntSize)
        {
            InitializeData();
            this->endianness = endianness;
        }

        /// @brief Constructor; creates a new instance of IntField.
        /// @param value The value to initialize the field to.
        /// @param  The endianness the field should use.
        IntField(int value, FieldEndianness Endianness): RawField(IntSize)
        {
            InitializeData();
            this->endianness = endianness;
            SetValue(value);
        }

        /// @brief Gets the value of the field.
        /// @return The value of the field.
        IntType Value() const
        {
            return 0;
        }

        /// @brief Gets the minimum value this field can hold.
        /// @return The minimum value the field can hold.
        IntType MinValue() const
        {
            return 0;
        }

        /// @brief Gets the maximum value this field can hold.
        /// @return The maximum value the field can hold.
        IntType MaxValue() const
        {
            return 0;
        }

        /// @brief Gets the endianness of the field.
        /// @return The endianness of the field.
        FieldEndianness Endianness() const
        {
            return endianness;
        }

        /// @brief Sets the value of the field.
        /// @param value The value to set.
        void SetValue(IntType value)
        {
            ConvertToBytes(value);
        }

        /// @brief Sets the endianness of the field.
        /// @param endianness The endianness to set the field to.
        void SetEndianness(FieldEndianness endianness)
        {
            // TODO: Test for flip byte order and implement byte flipping code. 
            this->endianness = endianness;
        }

        /// @brief Sets the field to use the default endianness.
        void SetToDefaultEndianness()
        {
            SetEndianness(defaultEndianness);
        }
    private:
        FieldEndianness endianness;

        /// @brief Initializes the data.
        void InitializeData()
        {
            for (size_t i = 0; i < Size(); i++)
                Data[i] = 0;
        }

        /// @brief Converts the specified value to the data bytes.
        ///
        /// Converts the specified value to the underlying bytes in the proper
        /// byte order depending on the endianness of the field and the system
        /// endianness.
        ///
        /// @param value The value to convert.
        void ConvertToBytes(IntType value)
        {
            FieldEndianness systemEndianness = GetSystemEndianness();

            if (systemEndianness == FieldEndianness::Little && 
                endianness == FieldEndianness::Little)
            {
                
            }
        }

        /// @brief Gets the integer value from the raw data bytes.
        ///
        /// Converts the raw data bytes to the appropriate integer value using
        /// the correct endianness to match the system endianness.
        ///
        /// @return The integer value of the field.
        IntType ConvertFromBytes() const
        {

        }
    };

    /// @brief Represents an unsigned 8-bit integer field in a binary file.
    using UInt8Field = IntField<unsigned int, 1>;

    /// @brief Represents an unsigned 16-bit integer field in a binary file.
    using UInt16Field = IntField<unsigned int, 2>;

    /// @brief Represents an unsigned 24-bit integer field in a binary file.
    using UInt24Field = IntField<unsigned long, 3>;

    /// @brief Represents an unsigned 32-bit integer field in a binary file.
    using UInt32Field = IntField<unsigned long, 4>;

    /// @brief Represents an unsigned 64-bit integer field in a binary file.
    using UInt64Field = IntField<unsigned long long, 8>;

    /// @brief Represents a signed 8-bit integer field in a binary file.
    using Int8Field = IntField<int, 1>;

    /// @brief Represents a signed 16-bit integer field in a binary file.
    using Int16Field = IntField<int, 2>;

    /// @brief Represents a signed 24-bit integer field in a binary file.
    using Int24Field = IntField<long, 3>;

    /// @brief Represents a signed 32-bit integer field in a binary file.
    using Int32Field = IntField<long, 4>;

    /// @brief Represents a signed 64-bit integer field in a binary file.
    using Int64Field = IntField<long long, 8>;

    /// @brief Determines the endianness of the system.
    /// @return The endianness of the current system.
    FieldEndianness GetSystemEndianness();
}

#endif