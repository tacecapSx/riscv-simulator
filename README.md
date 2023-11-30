# riscv-simulator
A solution to the final assignment of Computer Architecture and Engineering (02155) made by Betina Mee Hansen [s195389] ([@Mee-creator](https://github.com/Mee-creator)), Martin Handest [s224755] ([@tacecapSx](https://github.com/tacecapSx)) and Viktor Saxil Egesby [s214951] ([@viktoregesby](https://github.com/viktoregesby)) in C.

## Build Setup

```bash
# Run make
$ make riscv

# run tests
$ ./riscv-simulator test/task_n/example.bin
```

## Comparing results
The simulator will output a result file in the same directory as the provided `.bin` file with the file extension `.bin.res`. The simulator includes a version of the "check_output.sh" script as part of the program. It will automatically run after every program execution and compare the given `.res` file (if found) to our generated `.bin.res` file and check for differences. If one or more differences are found, the simulator will print where they were found. Otherwise, if no differences were found, the simulator will end with *"No differences found!"*.
