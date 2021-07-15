; ModuleID = 'factorial.bc'
source_filename = "fib_module"

define i32 @Fibonacci(i32 %0) {
if:
  %cmpVal = icmp ult i32 %0, 2
  br i1 %cmpVal, label %ifRet, label %else

ifRet:                                            ; preds = %if
  ret i32 %0

else:                                             ; preds = %if
  %_NSubTwo = sub i32 %0, 2
  %_NSubOne = sub i32 %0, 1
  %callFibWithNSubTwo = call i32 @Fibonacci(i32 %_NSubTwo)
  %callFibWithNSubOne = call i32 @Fibonacci(i32 %_NSubOne)
  %result = add i32 %callFibWithNSubOne, %callFibWithNSubTwo
  ret i32 %result
}
