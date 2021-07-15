#include "llvmFibonacci.h"

LLVMModuleRef CreateFibonacciFunc (const char* moduleName, const char* funcName, char** error) {

    LLVMModuleRef mainModule = LLVMModuleCreateWithName (moduleName);

    LLVMValueRef fibFunc = CreateHeaderForFibonacciFunc (&mainModule, funcName);
    CreateBodyForFibonacciFunc (&fibFunc);
    
    //verifications
    LLVMVerifyModule    (mainModule, LLVMAbortProcessAction, error);
    LLVMDisposeMessage  (*error);

    LLVMVerifyFunction  (fibFunc, LLVMAbortProcessAction);

    return mainModule;

}

LLVMValueRef CreateHeaderForFibonacciFunc (LLVMModuleRef* module, const char* funcName) {

    LLVMTypeRef     funcParams []   = {LLVMInt32Type ()};
    LLVMTypeRef     funcType        = LLVMFunctionType (LLVMInt32Type (), funcParams, 1, 0);
    LLVMValueRef    funcFib         = LLVMAddFunction (*module, funcName, funcType);

    return funcFib;

}

void CreateBodyForFibonacciFunc (LLVMValueRef* fibFunc) {

    LLVMBuilderRef builder = LLVMCreateBuilder ();
    CreateAlgorithmFibonacciFunc       (&builder, fibFunc);

}

void CreateAlgorithmFibonacciFunc (LLVMBuilderRef* builder, LLVMValueRef* fibFunc) {

    LLVMBasicBlockRef ifBB      = LLVMAppendBasicBlock (*fibFunc, "if");
    LLVMBasicBlockRef ifRetBB   = LLVMAppendBasicBlock (*fibFunc, "ifRet");
    LLVMBasicBlockRef elseBB    = LLVMAppendBasicBlock (*fibFunc, "else");
    
    CreateIfRetFibonacciFunc (builder, fibFunc, &ifBB, &ifRetBB, &elseBB);
    CreateRecursiveRetFibonacciFunc (builder, fibFunc, &elseBB);

}

void CreateIfRetFibonacciFunc (LLVMBuilderRef* builder, LLVMValueRef* fibFunc, LLVMBasicBlockRef* ifBB, LLVMBasicBlockRef* ifRetBB, LLVMBasicBlockRef* elseBB) {

    //HERE WE COMPARATE OUR ORDINARY NUMBER AND 2 (N < 2)
    LLVMPositionBuilderAtEnd (*builder, *ifBB);

    LLVMValueRef ordNum         = LLVMGetParam (*fibFunc, 0);
    LLVMValueRef numToCmpWith   = LLVMConstInt (LLVMInt32Type (), 2, 0); 
    LLVMValueRef cmpVal         = LLVMBuildICmp (*builder, LLVMIntULT, ordNum, numToCmpWith, "cmpVal");

    LLVMBuildCondBr (*builder, cmpVal, *ifRetBB, *elseBB);

    //RETURN return N;
    LLVMPositionBuilderAtEnd (*builder, *ifRetBB);

    LLVMBuildRet (*builder, ordNum);

}

void CreateRecursiveRetFibonacciFunc (LLVMBuilderRef* builder, LLVMValueRef* fibFunc, LLVMBasicBlockRef* returnBB) {

    LLVMPositionBuilderAtEnd (*builder, *returnBB);

    LLVMValueRef _NSubTwo = LLVMBuildSub (*builder, LLVMGetParam (*fibFunc, 0), LLVMConstInt (LLVMInt32Type (), 2, 0), "_NSubTwo");
    LLVMValueRef _NSubOne = LLVMBuildSub (*builder, LLVMGetParam (*fibFunc, 0), LLVMConstInt (LLVMInt32Type (), 1, 0), "_NSubOne");

    LLVMValueRef callFibWithNSubTwo = LLVMBuildCall (*builder, *fibFunc, &_NSubTwo, 1, "callFibWithNSubTwo");
    LLVMValueRef callFibWithNSubOne = LLVMBuildCall (*builder, *fibFunc, &_NSubOne, 1, "callFibWithNSubOne");

    LLVMValueRef newFibNum          = LLVMBuildAdd  (*builder, callFibWithNSubOne, callFibWithNSubTwo, "result");

    LLVMBuildRet (*builder, newFibNum);

}

void RunFibonacciFunction (LLVMModuleRef* module, const char* funcName, int arg, char** error) {

    LLVMExecutionEngineRef engine;
    LLVMLinkInMCJIT ();
    LLVMInitializeNativeTarget ();
    LLVMInitializeNativeAsmPrinter ();

    if (LLVMCreateExecutionEngineForModule (&engine, *module, error) != 0) {

        printf ("error with execution engine: %s was catched in function %s.\n", *error, __FUNCTION__);
        LLVMDisposeMessage (*error);
        
        return;

    }

    int (*func)(int) = (int (*)(int))LLVMGetFunctionAddress (engine, funcName);
    printf ("%d\n", func (arg));

}
