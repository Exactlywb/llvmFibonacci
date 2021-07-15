#include <stdlib.h>
#include <stdio.h>

#include <llvm-c/Core.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/ExecutionEngine.h>

// |!| HERE WE BUILD SIMPLE FUNCTION TO COUNT FIBONACCI NUMBER
// |!| I SHOULD NOT PUT DIFFERENT ASSERTS IN THE FIBONACCI FUNC. DO NOT BLAME IT ON ME

// |!| EXAMPLE:
// int Fib (int N) {

//     if (N < 2)
//         return N;

//     return Fib (N - 1) + Fib (N - 2);

// }

LLVMModuleRef   CreateFibonacciFunc                 (const char* moduleName, const char* funcName, char** error);
LLVMValueRef    CreateHeaderForFibonacciFunc        (LLVMModuleRef* module, const char* funcName);
void            CreateBodyForFibonacciFunc          (LLVMValueRef* fibFunc);

void            CreateAlgorithmFibonacciFunc        (LLVMBuilderRef* builder, LLVMValueRef* fibFunc);

void            CreateIfRetFibonacciFunc            (LLVMBuilderRef* builder, LLVMValueRef* fibFunc, LLVMBasicBlockRef* ifBB, 
                                                    LLVMBasicBlockRef* ifRetBB, LLVMBasicBlockRef* elseBB);

void            CreateRecursiveRetFibonacciFunc     (LLVMBuilderRef* builder, LLVMValueRef* fibFunc, LLVMBasicBlockRef* returnBB);

void            RunFibonacciFunction                (LLVMModuleRef* module, const char* funcName, int arg, char** error);
