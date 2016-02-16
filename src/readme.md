## What is in this directory?
filter.c - source code of the convolution filter example
Makefile - a global makefile
mt       - subfolder containing the source code of the static library
print.c  - source code of the I/O example

## List of examples
### print.c
Demonstrates how to read an input file containing MT recordings in netcdf format.

Compilation: `make print`
Usage examples:
```
./print ../mtin.nc 
./print ../mtin.nc | head
./print ../mtin.nc | tail
```
### filter.c:
Demonstrates how to
* read an input file containing MT recordings in netcdf format,
* run a convolution-type complex filter and
* dump the result into a netcdf file (or print it to stdout).

Compilation: `make filter`
Usage examples:
```
./filter ../mtin.nc # filter id defaults to 1
./filter ../mtin.nc 0 # filter id too small
./filter ../mtin.nc 33
./filter ../mtin.nc 41 # filter id too large
```

## Remarks
Compiling either of the examples will compile the static library as well (if needed). `cd` to the `mt` directory and run `make` there if you want to compile only the static library. 