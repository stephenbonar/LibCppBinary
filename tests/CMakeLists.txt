# CMakeLists.txt - Builds the LibCppBinary library tests.
#
# Copyright (C) 2025 Stephen Bonar
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

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(libcppbinarytests
               DataFieldTests.cpp 
               StringFieldTests.cpp 
               RawFieldTests.cpp 
               RawFileStreamTests.cpp 
               IntFieldTests.cpp
               ChunkHeaderTests.cpp)

target_link_libraries(libcppbinarytests
                      LibCppBinary
                      gtest
                      gtest_main
                      gmock)

target_include_directories(libcppbinarytests 
                           PRIVATE
                           ${PROJECT_SOURCE_DIR}/include)