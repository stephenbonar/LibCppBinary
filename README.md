# LibCppBinary

LibCppBinary is a modern, cross-platform C++ library for reading and writing 
binary data to / from files using the provided field, data structure, and stream
classes.

## Features

- Binary data field classes allow for easy manipulation of binary data
  - `Binary::RawField` allows manipulation of fields without interpretation
  - `Binary::StringField` allows manipulation of string fields
  - `Binary::IntField` template allows manipulation of integer fields
    - The following template specializations are available:
	  - `UInt8Field`
	  - `Int8Field`
      - `UInt16Field`
	  - `Int16Field`
      - `UInt24Field`
	  - `Int24Field`
      - `UInt32Field`
	  - `Int32Field`
      - `UInt64Field`
	  - `Int64Field`
  - `Binary::DataField` base class allows for future extensibility
  - IntFields can manipulate both little and big endian formats and convert
    between the two. By default, IntFields follow the endianness of the platform
	but can be changed to the opposite endianness as fields in binary files
	can often differ from the platform the program is running on.
  - IntFields provide methods that handle the conversion of the raw bytes to
    native integer types using the correct endianness so you don't have to do
	the conversions yourself.
  - All data field classes provide ToString() methods that return a text 
    representation of the binary data in an appropriate default format but
	a specific format can be specified. Possible formats include:
	  - `Terminated` : Formats as null-terminated string
      - `Raw`        : Formats the string data "as-is" using the bytes.
      - `Printable`  : Replaces any non-printable chars with a space.
      - `Bin`        : Binary representation in 1s and 0s.
	  - `Hex`        : Hexadecimal representation.
	  - `Dec`        : Decimal representation. Only use for int fields.
  - Binary data structure classes allow you to group binary fields for reading
    and writing data fields in order as one chunk from / to a file.
    - The `Binary::DataStructure` base struct allows you to build your own
	  groupings of `Binary::DataField` objects.
	- The `Binary::ChunkHeader` data structure allows you to read and write
	  tagged chunks such as IFF / RIFF tags from media files.
  - Binary stream classes allow reading and writing from / to files and memory
    - `Binary::FileStream` allows for reading and writing from / to files. It
	  is a base class derived from `Binary::Stream` both for extensibility
	  purposes and so mock file streams can be used with tests.
    - `Binary::StandardFileStream` is the standard implementation of FileStream.
	- `Binary::BufferStream` allows for reading / writing data in memory.
    - `Binary::Stream` base class allows for future extensibility.
	- All binary stream classes support reading and writing all types that
	  derive from `Binary::DataField` and `Binary::DataStructure`
    - All streams support finding chunks and sub-chunks using chunk IDs.

## Requirements

- C++17 or greater compatible compiler
- CMake 3.11 or greater

Test dependencies are fetched automatically by CMake:

- GoogleTest / GoogleMock via `FetchContent`

## Including the Library in Your Project

This library is designed to be included directly into your project rather than
being built / installed as a dynamic library, although you could do either.
The easiest way is to add the following to your CMakeLists.txt file in your
own CMake project:

include(FetchContent)
FetchContent_Declare(
    LibCppBinary
    URL https://github.com/stephenbonar/LibCppBinary/archive/HASH.zip
)

Where HASH is the SHA hash for the specific commit of the library you want to 
include, which most likely should be the commit of the most recent stable
release version of the library. Replace HASH with the specific commit hash you want to use.

You then need to link the library to your project's CMake target by adding this
line to your CMakeLists.txt:

target_link_libraries(YOUR_TARGET LibCppBinary)

Where YOUR_TARGET is the name of your project's CMake build target.

Finally, to include the library header into your source files:

```cpp
#include "LibCppBinary.h"
```

## Build

If you do want to build the library separately, perhaps to modify it and run the
tests:

From the repository root:

```bash
cmake -S . -B build
cmake --build build
```

The static library target is `LibCppBinary`.

## Run Tests

```bash
ctest --test-dir build --output-on-failure
```

Or run the test binary directly:

```bash
./build/bin/libcppbinarytests
```

## Generate API Documentation

Doxygen configuration is included.

```bash
doxygen Doxyfile
```

Generated docs are written under `docs/`.

### Example: Define a Binary Record Structure

```cpp
#include "LibCppBinary.h"

struct ExampleRecord : public Binary::DataStructure
{
	Binary::StringField magic{4};
	Binary::UInt32Field version;

	std::vector<Binary::DataField*> Fields() override
	{
		return { &magic, &version };
	}

	std::vector<const Binary::DataField*> Fields() const override
	{
		return { &magic, &version };
	}

	size_t Size() const override
	{
		return magic.Size() + version.Size();
	}
};
```

### Example: Write and Read a Record from a File

```cpp
#include "LibCppBinary.h"

int main()
{
	ExampleRecord out;
	out.magic.SetValue("LBIN");
	out.version.SetValue(1);

	Binary::StandardFileStream stream{"example.bin"};
	stream.Open(Binary::FileMode::Write);
	stream.Write(&out);
	stream.Close();

	ExampleRecord in;
	stream.Open(Binary::FileMode::Read);
	stream.Read(&in);
	stream.Close();

	return 0;
}
```

### Example: Work with In-Memory Binary Data

```cpp
#include "LibCppBinary.h"

int main()
{
	Binary::BufferStream buffer{16};

	Binary::UInt16Field a;
	Binary::UInt16Field b;

	a.SetValue(0x1234);
	b.SetValue(0xABCD);

	buffer.Write(&a);
	buffer.Write(&b);

	buffer.SetPosition(0);

	Binary::UInt16Field r1;
	Binary::UInt16Field r2;
	buffer.Read(&r1);
	buffer.Read(&r2);

	return 0;
}
```

## Repository Layout

- `include/` public headers
- `src/` library implementation and library target definition
- `tests/` GoogleTest suite
- `docs/` requirements and generated Doxygen output

## License

Licensed under the Apache License, Version 2.0. See `LICENSE` for details.
