#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Target.h>
#include <llvm-c/Analysis.h>
#include <llvm-c/Transforms/Scalar.h>

int main() {
    // Create a new module
    LLVMModuleRef module = LLVMModuleCreateWithName("math_module");

    // Create a function for the math operation
    LLVMTypeRef func_type = LLVMFunctionType(LLVMInt32Type(), NULL, 0, 0);
    LLVMValueRef math_func = LLVMAddFunction(module, "math_operation", func_type);

    // Create a basic block
    LLVMBasicBlockRef entry = LLVMAppendBasicBlock(math_func, "entry");

    // Create a builder
    LLVMBuilderRef builder = LLVMCreateBuilder();
    LLVMPositionBuilderAtEnd(builder, entry);

    // Create variables
    LLVMValueRef a = LLVMBuildAlloca(builder, LLVMInt32Type(), "a");
    LLVMBuildStore(builder, LLVMConstInt(LLVMInt32Type(), 2, 0), a);
    LLVMValueRef b = LLVMBuildAlloca(builder, LLVMInt32Type(), "b");
    LLVMBuildStore(builder, LLVMConstInt(LLVMInt32Type(), 3, 0), b);

    // Perform the math operation
    LLVMValueRef a_val = LLVMBuildLoad(builder, a, "a_val");
    LLVMValueRef b_val = LLVMBuildLoad(builder, b, "b_val");
    LLVMValueRef c = LLVMBuildAdd(builder, a_val, b_val, "c");

    // Return the result
    LLVMBuildRet(builder, c);

    // Verify the module
    char *error = NULL;
    if (LLVMVerifyModule(module, LLVMAbortProcessAction, &error)) {
        printf("Error verifying module: %s\n", error);
        LLVMDisposeMessage(error);
        return 1;
    }

    // Create an execution engine
    LLVMExecutionEngineRef engine;
    if (LLVMCreateExecutionEngineForModule(&engine, module, &error)) {
        printf("Error creating execution engine: %s\n", error);
        LLVMDisposeMessage(error);
        return 1;
    }

    // Run the function
    int (*math_operation)() = (int (*)())LLVMGetFunctionAddress(engine, "math_operation");
    int result = math_operation();
    printf("Result: %d\n", result);

    // Clean up
