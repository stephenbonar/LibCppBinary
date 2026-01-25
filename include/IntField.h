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

// Define the min and max values that are not in the standard library.
#define INT24_MIN -8388608
#define INT40_MIN -549755813888
#define INT48_MIN -140737488355328
#define INT56_MIN -36028797018963968
#define UINT24_MAX 16777215
#define UINT40_MAX 109951162777
#define UINT48_MAX 281474976710655
#define UINT56_MAX 72057594037927935
#define INT24_MAX 8388607
#define INT40_MAX 549755813887
#define INT48_MAX 140737488355327
#define INT56_MAX 36028797018963967

namespace Binary
{
    /// @brief Used for selecting the least significant byte on little endian.
    constexpr int byteMask{ 0xFF };

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
        IntField(IntType value) : RawField(IntSize)
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
        IntField(IntType value, FieldEndianness endianness): RawField(IntSize)
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
                    return INT8_MIN;
                case 2:
                    return static_cast<IntType>(INT16_MIN);
                case 3:
                    return static_cast<IntType>(INT24_MIN);
                case 4:
                    return static_cast<IntType>(INT32_MIN);
                case 5:
                    return static_cast<IntType>(INT40_MIN);
                case 6:
                    return static_cast<IntType>(INT48_MIN);
                case 7:
                    return static_cast<IntType>(INT56_MIN);
                case 8:
                    return static_cast<IntType>(INT64_MIN);
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
                        return UINT8_MAX;
                    case 2:
                        return static_cast<IntType>(UINT16_MAX);
                    case 3:
                        return static_cast<IntType>(UINT24_MAX);
                    case 4:
                        return static_cast<IntType>(UINT32_MAX);
                    case 5:
                        return static_cast<IntType>(UINT40_MAX);
                    case 6:
                        return static_cast<IntType>(UINT48_MAX);
                    case 7:
                        return static_cast<IntType>(UINT56_MAX);
                    case 8:
                        return static_cast<IntType>(UINT64_MAX);
                }
            }
            else
            {
                switch (IntSize)
                {
                    case 1:
                        return INT8_MAX;
                    case 2:
                        return static_cast<IntType>(INT16_MAX);
                    case 3:
                        return static_cast<IntType>(INT24_MAX);
                    case 4:
                        return static_cast<IntType>(INT32_MAX);
                    case 5:
                        return static_cast<IntType>(INT40_MAX);
                    case 6:
                        return static_cast<IntType>(INT48_MAX);
                    case 7:
                        return static_cast<IntType>(INT56_MAX);
                    case 8:
                        return static_cast<IntType>(INT64_MAX);
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

        /// @brief Converts the field's data to a string representation.
        /// @return A string representation of the field's data.
        std::string ToString() const override
        {
            return std::to_string(Value());
        }

        /// @brief Converts the field's data to a string representation.
        /// @param format The format to use for the string conversion.
        /// @return A string representation of the field's data.
        std::string ToString(StringFormat format) const override
        {
            if (format == StringFormat::Dec)
                return std::to_string(Value());
            else
                return FormatData(format);
        }
    private:
        FieldEndianness endianness;

        /// @brief Initializes the data.
        void InitializeData()
        {
            for (size_t i = 0; i < Size(); i++)
                rawData[i] = 0;
        }

        /// @brief Converts the specified value to the data bytes.
        ///
        /// Converts the specified value to the underlying bytes in the proper
        /// byte order depending on the endianness of the field. This should
        /// work the same on both little endian and big endian systems as
        /// the library has been re-written to use the C++ type system as much
        /// as possible.
        ///
        /// @param value The value to convert.
        void ConvertToBytes(IntType value)
        {
            if (endianness == FieldEndianness::Little)
            {
                StoreLittleEndian(value);
            }
            else if (endianness == FieldEndianness::Big)
            {
                StoreBigEndian(value);
            }
        }

        /// @brief Gets the integer value from the raw data bytes.
        ///
        /// Converts the raw data bytes to the appropriate integer value using
        /// the correct endianness to match the system endianness. This should
        /// work the same on both little endian and big endian systems as
        /// the library has been re-written to use the C++ type system as much
        /// as possible.
        ///
        /// @return The integer value of the field.
        IntType ConvertFromBytes() const
        {
            if (endianness == FieldEndianness::Little)
            {
                return RetrieveLittleEndian();
            }
            else if (endianness == FieldEndianness::Big)
            {
                return RetrieveBigEndian();
            }

            return 0;
        }

        /// @brief Stores the specified value in the field as little endian.
        /// @param value The value to store.
        void StoreLittleEndian(IntType value)
        {
            // Start the shift amount at 0 to obtain the least significant
            // byte of value first, which is what we want for little endian.
            int shiftAmount = 0;

            for (int i = 0; i < IntSize; ++i)
            {
                // Get the next byte from value by shifting it to the least
                // significant byte. By doing bitwise with the lsb mask, all
                // other bytes are zeroed out.
                rawData[i] = 
                    static_cast<char>((value >> shiftAmount) & byteMask);

                // Increase the shift amount to select the next byte.
                shiftAmount += bitsPerByte;
            }  
        }

        /// @brief Stores the specified value in the field as big endian.
        /// @pre The specified value is in little endian format.
        /// @param value The value to store.
        void StoreBigEndian(IntType value)
        {
            // Because the byte order is reversed for big endian values, we
            // start the shift amount towards the size and decrease to 0.
            int shiftAmount = (IntSize - 1) * bitsPerByte;

            for (int i = 0; i < IntSize; ++i)
            {
                // Get the next byte from value by shifting it to the least
                // significant byte. By doing bitwise with the lsb mask, all
                // other bytes are zeroed out.
                rawData[i] = 
                    static_cast<char>((value >> shiftAmount) & byteMask);

                // Decrease the shift amount to select the next byte.
                shiftAmount -= bitsPerByte;
            }  
        }

        /// @brief Retrieves the stored little endian value.
        /// @return The little endian value.
        IntType RetrieveLittleEndian() const
        {
            bool isNegative = false;

            // Assemble the retrieved value in a 64-bit variable so it can hold
            // all possible sized values. We make it unsigned so we don't have
            // acccidental sign changes during the process.
            uint64_t retrievedValue{ 0 };

            // Start the shift amount at 0 to obtain the least significant
            // byte of value first, which is what we want for little endian.
            int shiftAmount = 0;

            for (int i = 0; i < IntSize; ++i)
            {
                // First convert the raw byte char to an uint8_t so it can be
                // bitwised OR'd to the rest of the retrieved value. We keep
                // everything unsigned to avoid sign conversion errors.
                uint8_t byte = static_cast<uint8_t>(rawData[i]);

                // Determine if the most significant byte has the sign bit
                // enabled to determine if the entire number is negative.
                if (i == (IntSize - 1) && byte > 127)
                    isNegative = true;

                // Then, Bitwise OR the next byte to the retrieved value by 
                // shifting it into the correct position to continue assembling
                // the value. Cast the byte to uint64_t because the compiler
                // might implicity cast to 32-bit int instead. 
                uint64_t shifted = static_cast<uint64_t>(byte) << shiftAmount;
                retrievedValue |= shifted;

                // Increase the shift amount to select the next byte.
                shiftAmount += bitsPerByte;
            }
           
            return ConvertRetrievedValue(retrievedValue, isNegative);
        }

        /// @brief Retrieves the stored big endian value.
        /// @return The little endian value. 
        IntType RetrieveBigEndian() const
        {
            bool isNegative = false;

            // Assemble the retrieved value in a 64-bit variable so it can hold
            // all possible sized values. We make it unsigned so we don't have
            // acccidental sign changes during the process.
            uint64_t retrievedValue{ 0 };

            // Because the byte order is reversed for big endian values, we
            // start the shift amount towards the size and decrease to 0.
            int shiftAmount = (IntSize - 1) * bitsPerByte;

            for (int i = 0; i < IntSize; ++i)
            {
                // First convert the raw byte char to an uint8_t so it can be
                // bitwised OR'd to the rest of the retrieved value. We keep
                // everything unsigned to avoid sign conversion errors.
                uint8_t byte = static_cast<uint8_t>(rawData[i]);

                // Determine if the most significant byte has the sign bit
                // enabled to determine if the entire number is negative.
                if (i == 0 && byte > 127)
                    isNegative = true;

                // Then, Bitwise OR the next byte to the retrieved value by 
                // shifting it into the correct position to continue assembling
                // the value. Cast the byte to uint64_t because the compiler
                // might implicity cast to 32-bit int instead. 
                retrievedValue |= static_cast<uint64_t>(byte) << shiftAmount;

                // Decrease the shift amount to select the next byte.
                shiftAmount -= bitsPerByte;
            }

            return ConvertRetrievedValue(retrievedValue, isNegative);
        }
        
        /// @brief Sign extends the specified value by padding it leading 1's.
        /// @param value The value to sign extend.
        /// @return The sign extended value.
        IntType SignExtend(IntType value) const
        {
            int valueTotalBytes = sizeof(value);
            IntType signExtendedValue = value;
            
            // Start the loop 1 byte past IntSize as we only need to pad the
            // extra leading bytes.
            for (int bytes = IntSize + 1; bytes <= valueTotalBytes; bytes++)
            {
                int amountToShift = (bytes - 1) * bitsPerByte;
                signExtendedValue |= byteMask << amountToShift;
            }

            return signExtendedValue;
        }

        /// @brief Converts the retrieved value back into IntType.
        /// @param retrievedValue The uint64_t to be converted.
        /// @param isNegative Determines if the value represents a negative.
        /// @return The converted value.
        IntType ConvertRetrievedValue(uint64_t retrievedValue, bool isNegative)
            const
        {
            IntType convertedValue{ static_cast<IntType>(retrievedValue) };

            // If we're dealing with a signed, negative number, we may need to
            // sign extend it by padding it with leading 1's (bytes of 0xFF) to
            // fill the extra bytes if the size of IntType is > IntSize.
            if (std::numeric_limits<IntType>::is_signed && isNegative)
            {
                // We only need to pad the most significant bytes above and beyond
                // IntSize. When IntType matches the size of IntSize, this code 
                // will never run. But in cases where IntType's size is greater 
                // than the size of the raw data, such as Int24Field, we need to
                // pad the extra bytes. 
                if (sizeof(convertedValue) > IntSize)
                    return SignExtend(convertedValue);
            }
            
            return convertedValue;
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