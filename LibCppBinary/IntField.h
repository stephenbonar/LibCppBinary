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

#include <cstdint>
#include <limits>
#include "RawField.h"
#include "FieldEndianness.h"

namespace Binary
{
    /// @brief Used for selecting the least significant byte on little endian.
    constexpr int lsbMask{ 0xFF };

    /// @brief Controls what endianness IntFields are created with by default.
    extern FieldEndianness defaultEndianness;

    /// @brief Determines the endianness of the system.
    /// @return The endianness of the current system.
    FieldEndianness GetSystemEndianness();

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
        IntField(int value, FieldEndianness endianness): RawField(IntSize)
        {
            InitializeData();
            this->endianness = endianness;
            SetValue(value);
        }

        /// @brief Gets the value of the field.
        /// @return The value of the field.
        IntType Value() const
        {
            return ConvertFromBytes();
        }

        /// @brief Gets the minimum value this field can hold.
        /// @return The minimum value the field can hold.
        IntType MinValue() const
        {
            if (!std::numeric_limits<IntType>::is_signed)
                return 0;

            switch (IntSize)
            {
                case 1:
                    return -128;
                case 2:
                    return -32768;
                case 3:
                    return -8388608;
                case 4:
                    return -2147483648;
                case 5:
                    return -549755813888;
                case 6:
                    return -140737488355328;
                case 7:
                    return -36028797018963968;
                case 8:
                    return 0x8000000000000000;
            }

            return 0;
        }

        /// @brief Gets the maximum value this field can hold.
        /// @return The maximum value the field can hold.
        IntType MaxValue() const
        {
            if (!std::numeric_limits<IntType>::is_signed)
            {
                switch (IntSize)
                {
                    case 1:
                        return 255;
                    case 2:
                        return 65535;
                    case 3:
                        return 16777215;
                    case 4:
                        return 4294967295;
                    case 5:
                        return 1099511627775;
                    case 6:
                        return 281474976710655;
                    case 7:
                        return 72057594037927935;
                    case 8:
                        return 18446744073709551615ULL;
                }
            }
            else
            {
                switch (IntSize)
                {
                    case 1:
                        return 127;
                    case 2:
                        return 32767;
                    case 3:
                        return 8388607;
                    case 4:
                        return 2147483647;
                    case 5:
                        return 549755813887;
                    case 6:
                        return 140737488355327;
                    case 7:
                        return 36028797018963967;
                    case 8:
                        return 9223372036854775807;
                }
            }

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
                data[i] = 0;
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
            FieldEndianness systemEndianness = Binary::GetSystemEndianness();

            if (systemEndianness == FieldEndianness::Little && 
                endianness == FieldEndianness::Little)
            {
                StoreLittleEndianAsLittleEndian(value);
            }
            else if (systemEndianness == FieldEndianness::Little &&
                     endianness == FieldEndianness::Big)
            {
                StoreLittleEndianAsBigEndian(value);
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
            FieldEndianness systemEndianness = Binary::GetSystemEndianness();

            if (systemEndianness == FieldEndianness::Little &&
                endianness == FieldEndianness::Little)
            {
                return RetrieveLittleEndianAsLittleEndian();
            }
            else if (systemEndianness == FieldEndianness::Little &&
                     endianness == FieldEndianness::Big)
            {
                return RetrieveBigEndianAsLittleEndian();
            }

            return 0;
        }

        /// @brief Stores the specified value in the field as little endian.
        /// @pre The specified value is in little endian format.
        /// @param value The value to store.
        void StoreLittleEndianAsLittleEndian(IntType value)
        {
            // Start the shift amount at 0 to obtain the least significant
            // byte of value first, which is what we want for little endian.
            int shiftAmount = 0;

            for (int i = 0; i < IntSize; ++i)
            {
                // Get the next byte from value by shifting it to the least
                // significant byte. By doing bitwise with the lsb mask, all
                // other bytes are zeroed out.
                data[i] = static_cast<char>((value >> shiftAmount) & lsbMask);

                // Increase the shift amount to select the next byte.
                shiftAmount += bitsPerByte;
            }  
        }

        /// @brief Stores the specified value in the field as big endian.
        /// @pre The specified value is in little endian format.
        /// @param value The value to store.
        void StoreLittleEndianAsBigEndian(IntType value)
        {
            // Because the byte order is reversed for big endian values, we
            // start the shift amount towards the size and decrease to 0.
            int shiftAmount = (IntSize - 1) * bitsPerByte;

            for (int i = 0; i < IntSize; ++i)
            {
                // Get the next byte from value by shifting it to the least
                // significant byte. By doing bitwise with the lsb mask, all
                // other bytes are zeroed out.
                data[i] = static_cast<char>((value >> shiftAmount) & lsbMask);

                // Decrease the shift amount to select the next byte.
                shiftAmount -= bitsPerByte;
            }  
        }

        /// @brief Retrieves the stored little endian value as little endian.
        /// @return The little endian value.
        IntType RetrieveLittleEndianAsLittleEndian() const
        {
            // Assemble the retrieved value in a 64-bit variable so it can hold
            // all possible sized values.
            uint64_t retrievedValue{ 0 };

            // Start the shift amount at 0 to obtain the least significant
            // byte of value first, which is what we want for little endian.
            int shiftAmount = 0;

            for (int i = 0; i < IntSize; ++i)
            {
                // First convert the raw byte char to an uint8_t so it can be
                // bitwised OR'd to the rest of the retrieved value. We keep
                // everything unsigned to avoid sign conversion errors.
                uint8_t byte = static_cast<uint8_t>(data[i]);

                // Then, Bitwise OR the next byte to the retrieved value by 
                // shifting it into the correct position to continue assembling
                // the value.
                retrievedValue |= static_cast<uint64_t>(byte << shiftAmount);

                // Increase the shift amount to select the next byte.
                shiftAmount += bitsPerByte;
            }

            return static_cast<IntType>(retrievedValue);
        }

        /// @brief Retrieves the stored big endian value as little endian.
        /// @return The little endian value. 
        IntType RetrieveBigEndianAsLittleEndian() const
        {
            // Assemble the retrieved value in a 64-bit variable so it can hold
            // all possible sized values.
            uint64_t retrievedValue{ 0 };

            // Because the byte order is reversed for big endian values, we
            // start the shift amount towards the size and decrease to 0.
            int shiftAmount = (IntSize - 1) * bitsPerByte;

            for (int i = 0; i < IntSize; ++i)
            {
                // First convert the raw byte char to an uint8_t so it can be
                // bitwised OR'd to the rest of the retrieved value. We keep
                // everything unsigned to avoid sign conversion errors.
                uint8_t byte = static_cast<uint8_t>(data[i]);

                // Then, Bitwise OR the next byte to the retrieved value by 
                // shifting it into the correct position to continue assembling
                // the value.
                retrievedValue |= byte << shiftAmount;

                // Decrease the shift amount to select the next byte.
                shiftAmount -= bitsPerByte;
            }

            return static_cast<IntType>(retrievedValue);
        } 
    };

    /// @brief Represents an unsigned 8-bit integer field in a binary file.
    using UInt8Field = IntField<uint8_t, 1>;

    /// @brief Represents an unsigned 16-bit integer field in a binary file.
    using UInt16Field = IntField<uint16_t, 2>;

    /// @brief Represents an unsigned 24-bit integer field in a binary file.
    using UInt24Field = IntField<uint32_t, 3>;

    /// @brief Represents an unsigned 32-bit integer field in a binary file.
    using UInt32Field = IntField<uint32_t, 4>;

    /// @brief Represents an unsigned 64-bit integer field in a binary file.
    using UInt64Field = IntField<uint64_t, 8>;

    /// @brief Represents a signed 8-bit integer field in a binary file.
    using Int8Field = IntField<int8_t, 1>;

    /// @brief Represents a signed 16-bit integer field in a binary file.
    using Int16Field = IntField<int16_t, 2>;

    /// @brief Represents a signed 24-bit integer field in a binary file.
    using Int24Field = IntField<int32_t, 3>;

    /// @brief Represents a signed 32-bit integer field in a binary file.
    using Int32Field = IntField<int32_t, 4>;

    /// @brief Represents a signed 64-bit integer field in a binary file.
    using Int64Field = IntField<int64_t, 8>;
}

#endif