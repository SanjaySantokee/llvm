#include "hardware_specs.h"
#include <llvm-c/Core.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>

#include <sys/sysinfo.h>

int main() {
    LLVMTargetRef target;
    char *error = NULL;
    LLVMTargetMachineRef target_machine;
    struct sysinfo info;

    // Initialize LLVM
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();

    // Get the host target
    if (LLVMGetHostTarget(&target, &error)) {
        printf("Error getting host target: %s\n", error);
        LLVMDisposeMessage(error);
        return 1;
    }

    // Create a target machine
    target_machine = LLVMCreateTargetMachine(target, LLVMGetHostTriple(), "", "", LLVMCodeGenLevelDefault, LLVMRelocDefault, LLVMCodeModelDefault);

    // Print hardware information
    printf("CPU model: %s\n", LLVMGetTargetMachineCpu(target_machine));
    printf("CPU architecture: %s\n", LLVMGetTargetMachineFeatureString(target_machine));
    sysinfo(&info);
    printf("Total memory: %ldMB\n", info.totalram/1024/1024);

    // Clean up
    LLVMDisposeTargetMachine(target_machine);
    return 0;
}
