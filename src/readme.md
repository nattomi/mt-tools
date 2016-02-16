## What is in this directory?
* filter.c      - source code of the convolution filter example
* genfreqs.c    - source code for generating a sequence of frequencies
* Makefile      - a global makefile
* mt            - subfolder containing the source code of the static library
* mtforward1d.c - source code of 1 dimensional forward modelling example
* print.c       - source code of the I/O example

## Compilation of examples

* To compile all examples at once, issue `make all`.
* To compile only example `xy`, issue `make xy`.

## List of examples
### print.c
Demonstrates how to read an input file containing MT recordings in netcdf format.

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

Usage examples:
```
./filter ../mtin.nc # filter id defaults to 1
./filter ../mtin.nc 0 # filter id too small
./filter ../mtin.nc 33
./filter ../mtin.nc 41 # filter id too large
```
### genfreqs.c
Generates a sequence of frequencies at prints them to stdout as a JSON array.

Usage examples:
```
./genfreqs # prints usage instructions
./genfreqs 5 30 40
```

### mtforward1d.c
1-dimensional forward modelling.

Usage examples:
```
./mtforward1d $(< ../tests/05_nodlast.json) # List of frequencies is missing
./mtforward1d $(< ../tests/01_notarray.json) '[10]' # first argument is not a json array
./mtforward1d $(< ../tests/02_entrynotobject.json) '[10]' # first argument is a json array, but contains an entry which is not a json object
./mtforward1d $(< ../tests/03_nosigma.json) '[10]' # first argument is a json array which contains a json object entry which doesn't contain a 'sigma' property
./mtforward1d $(< ../tests/04_nod.json) '[10]' # first argument is a json array which contains a json object entry which doesn't contain a 'd' property
./mtforward1d $(< ../tests/05_nodlast.json) '[10,15,20]' # first argument is a json array whose last entry doesn't contain a 'd' property, but it's not a problem since it's not used in the calculations
./mtforward1d $(< ../tests/05_nodlast.json) '[]' # No calculation is made because frequency array is empty
./mtforward1d $(< ../tests/05_nodlast.json) "$(./genfreqs 10 20 3)" # redirecting the output of genfreqs
```

## Remarks
Compiling `print.c` or `filter.c` will compile the static library as well (if needed). `cd` to the `mt` directory and run `make` there if you want to compile only the static library. 