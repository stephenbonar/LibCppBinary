# Requirements

## Story: Data Fields

### Description

As a **user**, **I** *want* **support** for data **fields** so **I** can *manipulate* individual data **elements** in a binary **file**.

### Requirements

A data **field** should *have* a **size** and an **array** of **data** of the reported **size**. All other **types** of data **fields** should *derive* from this **class**.

## Story: Stream

### Description

As a **user**, **I** *want* the **ability** to *interact* with binary **streams** so **I** can *read* and write binary **data** to and from different data **sources**.

### Requirements

A **stream** should *allow* the **user** to *read* and *write* data **fields** to **it**. A **stream** should also *have* a **position** that *determines* where in the **stream** the next data **field** should be *read* from or *written* to. A **stream** should also *have* a **beginning** and **end** **position**. All **types** of binary **streams** should *derive* from this **class**.


## Story: File Stream

### Description

As a **user**, **I** *want* the **ability** to *interact* with file **streams** so **I** can *read* and *write* to binary **files**.

### Requirements

A file **stream** should *have* a file **name** and a **path**. A file **stream** should *have* a **mode** that *allows* the **user** to *open* the **stream** for **reading**, **writing**, or **both**.  A file **stream** should also *indicate* whether it is **open** or not. Additionally, a file **stream** should also *indicate* whether or not it **exists**. Finally, a file **stream** should *have* the **ability** to be *closed*.

## Story: Raw Fields

### Description

As a **user**, **I** *want* **support** for raw **fields** so **I** can *manipulate* raw **data** in binary **files** without any specific interpretation of the data.

## Story: String Fields

### Description

As a **user**, **I** *want* **support** for string **fields** so **I** can *manipulate* text **data** in binary **files**.

### Requirements

A string **field** should *have* a **value**. When the **user** *sets* the **value**, if the specified **value** is longer than the field **size**, it should *truncate* the specified **value** to *fit*.

## Story: Data Formatting

### Description

As a **user**, **I** *want* the **ability** to *format* the string representations of data **fields** so **I** can *choose* how a **field** should be *displayed*.

### Requirements

All data **fields** should *have* the **ability** to *convert* their **data** to a string **representation**. By default, the **data** should be *converted* to **string** in its raw **format**, but the **user** should *be* **able** to *specify* **ASCII**, **binary**, **decimal**, and **hexadecimal** **formats** as well.

### Description

As a **user**, **I** *want* **support** for integer **fields** so **I** can *manipulate* numeric **data** in binary **files**.

### Requirements

The integer **field** should *inherit* from data **field**. The integer **field** should *be* a **template** that *specifies* the integer **type** and **size**. This will *ensure* that the **user** can *get* the **value** as a standard **integer** **type** from the C++ type **system**, but the underlying raw **data** will *be* the exact **size** and **endianness** of the **field** as *stored* in the **file**. When the **user** *gets* the **value**, the **field** will *convert* the **value** from the raw bytes to the integer type. This will also allow the user to set the value using a standard integer type. The field will also convert the value being set to raw **bytes**. The **library** should *provide* some **typedefs** that *provide* the following **specializations** of the **template**: **UInt8**, **Int8**, **UInt16**, **Int16**, **UInt24**, **Int24**, **UInt32**, **Int32**, **UInt64**, and **Int64**. These **specializations** should *use* the minimum **size** integer **type** necessary to *hold* the **size** of the **field** on all **platforms** and **architectures**. All integer **fields** should *default* to the **endianness** of the **system**, but individual **instances** should also *allow* the **user** to *set* the **endianness** of a **field** explicitly. The **endianness** will *determine* the byte **order** that is *read* from and *written* to the **file**. The **field** should *indicate* the min and max **values** the **field** can *store*. If the **user** attempts to *set* a **value** larger or smaller than the min or max **values**, the **field** should *throw* an std::overflow_error **exception**.

## Noun-Verb Parse

| Subject Noun | Type | Verb | Type | Object Noun | Type | X |
| - | - | - | - | - | - | - |
| user | actor | want | desire | support | feature | X |
| I | actor | want | desire | (data) field | entity | X |
| I | actor | (can) manipulate | use case | (data) element | entity | X |
| file | entity | N/A | N/A | N/A | N/A | X |
| (data) field | entity | have | composition | size | attribute | X |
| (data) field | entity | have | composition | array | entity | X |
| (data) field | entity | have | composition | data | attribute | X |
| type | data type | N/A | N/A | N/A | N/A | X |
| (data) field | entity | derive | relationship | class | data type | X |
| user | actor | want | desire | ability | feature | X |
| I | actor | interact | feature | (binary) stream | entity | X |
| I | actor | read | use case | (binary) data | entity | X |
| I | actor | write | use case | (binary) data | entity | X |
| (data) source | entity | N/A | N/A | N/A | N/A | C |
| stream | entity | have | composition | (stream) mode | entity | X |
| mode | attribute | allows | feature | user | actor | X |
| user | actor | open | action | (file) stream | entity | X |
| (file) mode | has | composition | read | attribute | X |
| (file) mode | has | composition | write | attribute | X |
| (file) mode | has | composition | readwrite | attribute | X |
| stream | entity | allow | feature | user | actor | X |
| user | actor | read | action | (data) field | parameter | X |
| user | actor | write | action | (data) field | parameter | X |
| stream | entity | have | composition | position | attribute | X |
| postion | attribute | determines | feature | N/A | N/A | X |
| (file) stream | entity | have | feature | ability | feature | X |
| user | actor | close | action | (file) stream | entity | X |
| stream | entity | derive | relationship | class | data type | X |
| user | actor | want | desire | ability | feature | X |
| I | actor | interact | feature | (file) stream | entity | X |
| I | actor | read | use case | (binary) file | entity | X |
| I | actor | write | use case | (binary) file | entity | X |
| (file) stream | entity | have | composition | (file) name | attribute | X |
| (file) stream | entity | have | composition | (file) path | attribute | X |
| (file) stream | entity | indicate | composition | (is) open | attribute | X |
| (file) stream | entity | indicate | composition | exists | attribute | X |
| user | actor | want | desire | support | feature | X |
| (raw) field | entity | N/A | N/A | N/A | N/A | X |
| I | actor | manipulate | use case | (raw) data | entity | X |
| user | actor | want | desire | support | feature | X |
| (string) field | entity | N/A | N/A | N/A | N/A | X |
| I | actor | manipulate | use case | (text) data | entity | X |
| (string) field | entity | have | composition | value | attribute | X |
| user | actor | set | action | value | attribute | X |
| user | actor | set | action | value | parameter | X |
| (string) field | entity | truncate | action | value | parameter | C |
| user | actor | want | desire | ability | feature | X |
| I | actor | format | action | (string representation of data) field | return value | X |
| I | actor | choose | use case | field | entity | X |
| (data) field | entity | have | composition | ability | feature | X |
| (data) field | entity | convert | action | string | return value | X |
| (string) format | entity | N/A | N/A | N/A | N/A |
| (string) format | entity | has | composition | (raw) format | attribute | X |
| (string) format | entity | has | composition | (ascii) format | attribute | X |
| (string) format | entity | has | composition | (bin) format | attribute | X |
| (string) format | entity | has | composition | (hex) format | attribute | X |
| (string) format | entity | has | composition | (dec) format | attribute | X |
| user | actor | (be able to) specify | feature | format | parameter | X |
| (raw) field | entity | convert | action | (raw) format | return value | X |
| (raw) field | entity | convert | action | (ascii) format | return value | X |
| (raw) field | entity | convert | action | (bin) format | return value | X |
| (raw) field | entity | convert | action | (hex) format | return value | X |
| (raw) field | entity | convert | action | (dec) format | return value | X |
| user | actor | want | desire | support | feature | X |
| (integer) field | entity | N/A | N/A | N/A | N/A |
| I | actor | manipulate | use case | (numeric) data | X |
| (integer) field | entity | be | type | template | generic | X |
| template | generic | specifies | specialization | (integer) test | data type | X |
| template | generic | specifies | specialization | data size | template parameter | X |
| template | generic | ensures | feature | user | actor | X |
| user | actor | get | action | value | attribute | X |
| (C++ type) system | feature | N/A | N/A | N/A | N/A |
| (raw) data | attribute | be | constraint | (exact) size | template parameter | X |
| (raw) data | attribute | be | constraint | endianness | entity | X |
| field | entity | stored | action | file | entity | C |
| field | entity | convert | action | bytes | attribute | X |
| library | library | provide | feature | typedefs | data types | X |
| typedefs | data type | provide | relationship | specializations | data types | X |
| specialization | data type | use | composition | (minimum integer size) | template parameter | X |
| (integer) type | data type | hold | composition | size | constraint | X |
| platform | feature | N/A | N/A | N/A | N/A | X |
| architecture | feature | N/A | N/A | N/A | N/A | X |
| (integer) field | entity | (set) default | action  | endianness | attribute | X |
| (integer) field | entity | (get) system | action | endianness | attribute | X |
| (field) instance | entity | allow | feature | user | X |
| user | actor | set | action | endianness | attribute | X |
| endianness | attribute | determine | constraint | byte order | X |
| field | entity | indicate | composition | (min) value | attribute | X |
| field | entity | indicate | composition | (max) value | attribute | X |
| field | entity | throw | constraint | exception | entity | X |

## Actors

- User

## Use Case

- Manipulate data elements in a binary file
- Read and write data to and from a binary data source
- Read and write to / from binary files
- Manipulate raw data without any specific interpretation of the data in binary files
- Manipulate text data in binary files
- Choose how data fields in binary files are displayed
- Manipulate numeric data in binary files

## Features

- Support for data fields
- Ability to interact with binary streams
- Ability to open binary streams
- Ability to determine where to read and write to in a stream
- Ability to close a file stream
- Ability to interact with file streams
- Support for raw data fields
- Support for string fields
- Ability to convert data fields to a string representation
- Ability to format string representations of data fields
- Ability to specify string formats
- Support for integer fields
- Convert standard integer values from C++ type system to raw bytes
- Support for multiple sizes of signed and unsigned integer fields
- Cross platform
- Set endianness of integer fields

## Entities

| class DataField |
| - |
| + size_t Size() |
| + char* Data() |
| + void ToString(StringFormat format) |

| class RawField : DataField |
| - |

| enum class StringFormat |
| - |
| + Raw |
| + Ascii |
| + Hex |
| + Dec |
| + Bin |

| class StringField : RawField |
| - |
| + std::string Value() |
| + void SetValue(std::string value) |
| - std::string ConvertRaw() |
| - std::string ConvertAscii() |
| - std::string ConvertBin() |
| - std::string ConvertHex() |

| class File |
| - |

| class Stream |
| - |
| + void Read(DataField* field) |
| + void Write(DataField* field) |
| + size_t Position() |
| + void SetPosition() |
| + size_t Beginning() |
| + size_t End() |

| class FileStream : Stream |
| - |
| + std::string FileName() |
| + std::string FilePath() |
| + FileMode Mode() |
| + bool IsOpen() |
| + bool Exists() |
| + void Open(FileMode mode) |
| + void Close() |

| enum class FileMode |
| - |
| + Read |
| + Write |
| + ReadWrite |

| class IntField<typename IntType, size_t IntSize> : DataField |
| - |
| + static Endianness GetSystemEndianness() |
| + IntType Value() |
| + void SetValue(IntType value) |
| + FieldEndianness Endianness() |
| + IntType MinValue() |
| + IntType MaxValue() |
| + void SetEndianness(FieldEndianness endianness) |
| + void SetDefaultEndianness() |
| - void ConvertToBytes(IntType value) |
| - IntType ConvertFromBytes() |
| - FieldEndianness endianness |

| typedef UInt8 : IntField<unsigned int, 1> |
| - |

| typedef Int8Field : IntField<int, 1> |
| - |

| typedef UInt16Field : IntField<unsigned int, 2> |
| - |

| typedef Int16Field : IntField<int, 2> |
| - | 

| typedef UInt24Field : IntField<unsigned long, 3> |
| - |

| typedef Int24Field : IntField<long, 3> |
| - |

| typedef UInt32Field : IntField<unsigned long, 4> |
| - |

| typedef Int32Field : IntField<long, 4> |
| - |

| typedef UInt64Field : IntField<unsigned long long, 8> |
| - | 

| typedef Int64Field : IntField<long long, 8> |
| - | 

| enum class FieldEndianness |
| - |
| + LittleEndian |
| + BigEndian |

## Relationships

- All types of data fields should derive from the DataField class. 
- All types of streams should derive from the Stream class.
- Typedef specializations of IntField.
