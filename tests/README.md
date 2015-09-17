## Running a test
forwardmt1d "$(< tests/01_notarray.json)"

## List of tests
mt1df - no input 
mt1df $(< 05_nodlast.json) - List of frequencies is missing
mt1df $(< 01_notarray.json) '[10]' - first argument is not a json array
mt1df $(< 02_entrynotobject.json) '[10]' - first argument is a json array, but contains an entry which is not a json object
mt1df $(< 03_nosigma.json) '[10]' - first argument is a json array which contains a json object entry which doesn't contain a 'sigma' property
mt1df $(< 04_nod.json) '[10]' - first argument is a json array which contains a json object entry which doesn't contain a 'd' property
mt1df $(< 05_nodlast.json) '[10,15,20]' - first argument is a json array whose last entry doesn't contain a 'd' property, but it's not a problem since it's not used in the calculations
mt1df $(< 05_nodlast.json) '[]' - No calculation is made because frequency array is empty 
