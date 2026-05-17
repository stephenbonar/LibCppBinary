# LibCppBinary

LibCppBinary is a modern, cross-platform library for reading and writing binary
data through strongly typed fields, structures, and streams.

It provides a small set of composable primitives that make binary file work
predictable and explicit:

- Field types for raw bytes, strings, and integers of multiple sizes
- Stream abstractions for files and in-memory buffers
- Data structure support for ordered field serialization
- Chunk-header support for tagged binary formats
- String formatting helpers for text output (raw, printable, bin, hex, dec)

## Features

- `DataField` base abstraction for binary field types
- `RawField` for fixed-size byte data
- `StringField` for fixed-size text fields
- `IntField` template with specializations:
  - `UInt8Field`, `Int8Field`
  - `UInt16Field`, `Int16Field`
  - `UInt24Field`, `Int24Field`
  - `UInt32Field`, `Int32Field`
  - `UInt64Field`, `Int64Field`
- Configurable integer endianness (`FieldEndianness`)
- `Stream` interface for position-based I/O
- `StandardFileStream` for binary file I/O
- `BufferStream` for in-memory binary I/O
- `DataStructure` interface for grouping ordered fields
- `ChunkHeader` structure (`id` + `dataSize`) and chunk scanning helpers

## Requirements

- C++17 or greater compatible compiler
- CMake 3.11 or greater

Test dependencies are fetched automatically by CMake:

- GoogleTest / GoogleMock via `FetchContent`

## Build

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

## Quick Start

### Include the Library

```cpp
#include "LibCppBinary.h"
```

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

## CMake Integration

If LibCppBinary is included as a subdirectory in another CMake project:

```cmake
add_subdirectory(path/to/LibCppBinary)
target_link_libraries(your_target PRIVATE LibCppBinary)
```

## Repository Layout

- `include/` public headers
- `src/` library implementation and library target definition
- `tests/` GoogleTest suite
- `docs/` requirements and generated Doxygen output

## License

Licensed under the Apache License, Version 2.0. See `LICENSE` for details.
