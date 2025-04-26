# Requirements

## Story: Data Fields

### Description

As a **user**, **I** *want* **support** for data **fields** so **I** can *manipulate* individual data **elements** in a binary **file**.

### Requirements

A data **field** should *have* a **size** and an **array** of **data** of the reported **size**. All other **types** of data **fields** should *derive* from this **class**.

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

## Actors

- User

## Use Case

- Manipulate data elements in a binary file.

## Features

- Support for data fields

## Entities

| class DataField |
| - |
| + size_t Size() |
| + char* Data() |

| class File |
| - |

## Relationships

- All types of data fields should derive from the DataField class. 

