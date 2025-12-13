// Buffer.h - Declares the Buffer class.
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

#ifndef BINARY_BUFFER_H
#define BINARY_BUFFER_H

#include "RawField.h"
#include "Stream.h"

namespace Binary
{
    class Buffer : public RawField, public Stream
    {
    public:
        Buffer(size_t size) : RawField(size), position(0)
        { }

        /* Shouldn't need these as they're inherited from RawField unless we need to change
           behavior later.
        // RawField overrides

        size_t Size() const override;

        char* Data() override;

        std::string ToString() const override;

        std::string ToString(StringFormat format) const override;
        */

        // Stream overrides

        void Read(DataField* field) override;

        void Read(DataStructure* structure) override;

        std::shared_ptr<ChunkHeader> FindNextChunk(std::string ID) override;

        void Write(DataField* field) override;

        void Write(DataStructure* structure) override;

        uintmax_t Position() const override;

        void SetPosition(uintmax_t position) override;

        uintmax_t Beginning() const override;

        uintmax_t End() const override;
    protected:
        // RawField protected methods
        std::string FormatData(StringFormat format) const;

    private:
        uintmax_t position;
    /* Shouldn't need these as they're implementation details for RawField
        // RawField private methods
        std::string ConvertTerminated() const;

        std::string ConvertRaw() const;

        std::string ConvertPrintable() const;

        std::string ConvertBin() const;

        std::string ConvertHex() const;

    */

    };
}

#endif