# CMakeLists.txt - Builds the LibCppBinary library.
#
# Copyright (C) 2026 Stephen Bonar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Define the library build target to compile the source files into a static
# library.
add_library(LibCppBinary 
            StringField.cpp 
            RawField.cpp
            DataField.cpp
            StandardFileStream.cpp 
            IntField.cpp
            ChunkHeader.cpp
            BufferStream.cpp)

# Configure the include directories for the library target so the compiler
# knows where to find the header files.
target_include_directories(LibCppBinary
                           PUBLIC
                           ${PROJECT_SOURCE_DIR}/include)