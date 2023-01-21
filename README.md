# llvm
The LLVM (Low Level Virtual Machine) IR framework is mainly used to create compilers, code generators and other code manipulating tools.

## LLVM IR with C and Linux using Docker

This guide will show you how to install and use LLVM IR with C and Linux using Docker.

## Installation

1. Pull the official LLVM image from Docker Hub:
    ```
    docker pull llvm
    ```

2. Run the LLVM image in a container, mounting the current directory to the container's `/src` directory:
    ```
    docker run -it -v $(pwd):/src llvm
    ```

3. In the container, navigate to the `/src` directory:
    ```
    cd /src
    ```
4. Compile and run your C code with LLVM IR:
    ```
    clang -S -emit-llvm -o file.ll file.c
    ```
5. You can use lli to run the IR file, which is the just-in-time (JIT) compiler:
    ```
    lli file.ll
    ```
6. You can also use opt for optimization, and llc to generate machine code:
    ```
    opt -O3 -S file.ll -o file_opt.ll
    llc file_opt.ll -o file.s
    ```
7. You can use gcc to link and generate the binary:
    ```
    gcc file.s -o file
    ```
8. You can now run the binary:
    ```
    ./file
    ```