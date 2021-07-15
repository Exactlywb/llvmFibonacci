cmake_minimum_required (VERSION 3.13.4)
project (Fibonacci)

find_path (LLVM_DIR LLVM-Config.cmake /usr/lib/llvm-10/cmake)

find_package (LLVM REQUIRED CONFIG)

message (STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message (STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories (${LLVM_INCLUDE_DIRS})
separate_arguments  (LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions     (${LLVM_DEFINITIONS_LIST})

set (SOURCES main.c llvmFibonacci/llvmFibonacci.h llvmFibonacci/llvmFibonacci.c)
add_executable (main ${SOURCES})

llvm_map_components_to_libnames (llvm_libs core executionengine mcjit interpreter analysis native bitwriter)
target_link_libraries           (main ${llvm_libs})
