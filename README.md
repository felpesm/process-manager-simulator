# Process Manager Simulator

## Description

In plan to develop my knowledge in C language, i developed that software.

It deals with shell commands to create processes. On the moment of the execution, all processes are put on a queue and will be executed with FIFO or RR scheduling algoritms.

## Prerequisites

* A C compiler on the machine (like gcc);
* A UNIX-like OS running on the machine.

## Installation

Basically, you can download the files from repository and compile the .c ones.

1. Clone the repository;
2. Compile the .c files;
3. Enjoy it.

### A way to compile

If you has gcc and make packages installed on your machine, you can automatically compile the project using the makefile from repository. Just execute it:

```
make compile
```

## Usage

Just execute the executable file after the compilation.

### About loading processes from a text file

A format of accepted text file is like that:

```
user:command:priority
ruy:uname -a:0
john:ls:1
```

## Contributing

If you find a issue on the library, go to Issue Track and report it.

And if you want to contribute coding the library, just fork it and send a pull request when needed.

## License

>"THE BEER-WARE LICENSE" (Revision 42):
>
><fmalbernaz@protonmail.com> wrote this file. As long as you retain this notice you can do whatever you want with this stuff. If we meet some day, and you think this stuff is worth it, you can buy me a beer in return.
>
>This project is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
>
>Felipe Matheus M.

[LICENSE](./LICENSE)