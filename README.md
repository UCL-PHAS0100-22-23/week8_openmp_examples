# Building the examples

We'll manually be compiling all examples with GCC in the terminal. To compile you should run the command:
```
g++ [-fopenmp] [-O2] <sources.cpp>
```

with optional `-fopenmp` or `-O2` flags to enable openmp and compiler optimisations respectively. You should replace `<sources.cpp>` with `main.cpp timer.cpp` in examples that use the provided timer code, or usually `main.cpp` otherwise.

# Running the examples

Each example can be run with:
```
./a.out
```

To change the number of threads OpenMP uses, we set the environment variable before running the executable:
```bash
OMP_NUM_THREADS=<N> ./a.out
```

Change `<N>` to the number of threads you desire, for example:
```bash
OMP_NUM_THREADS=8 ./a.out
```

In later examples you will want to set the schedule used in OpenMP loops that use the `runtime` schedule. You can set this at the same time as setting the number of threads with:
```bash
OMP_NUM_THREADS=N OMP_SCHEDULE=<value> ./a.out
```

Replace `<schedule>` to the desired value.
