
#include "llvmFibonacci/llvmFibonacci.h"
#include <stdio.h>

int main (int argc, const char** argv) {

    if (argc != 2) {

        printf ("%s using N - the ordinal number of the Fibonacci number\n", argv [0]);

    } else {

        const char* funcName = "Fibonacci";
        char* error = NULL;
        LLVMModuleRef module = CreateFibonacciFunc ("fib_module", funcName, &error);

        if(LLVMWriteBitcodeToFile (module, "factorial.bc") != 0)
            printf ("Can't write bitcode. Error was catched on line %d\n", __LINE__);
        else
            system ("llvm-dis factorial.bc");
        
        error = NULL;
        RunFibonacciFunction (&module, funcName, atoi (argv [1]), &error);

    }

    return 0;

}
