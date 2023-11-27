# riscv-simulator
A solution to the final assignment of Computer Architecture and Engineering (02155) made by Betina Mee Hansen [s195389] ([@Mee-creator](https://github.com/Mee-creator)), Martin Handest [s224755] ([@tacecapSx](https://github.com/tacecapSx)) and Viktor Saxil Egesby [s214951] ([@viktoregesby](https://github.com/viktoregesby)) in C.

## Build Setup

```bash
# Run make
$ make riscv

# run tests
$ ./riscv-simulator test/task_n/example.bin
```

## Compare results
We made our own version of the "check_output.sh" script as part of the program, this will automatically run after every test and compare the correct.res to our output.res and check for differences. If a difference is found we print where we found it, otherwise if no differences is found we print that.
