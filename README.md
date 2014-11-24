# Paginator #
A virtual memory mapping simulator for the concept of paging used in operating systems.
It uses a binary file as a backing store / swap file and a list of memory accesses.
"Physical" memory is an array of chars.

#### Features ####
- Configurable number of pages in the backing store file
- Configurable number of frames of "physical" memory
- Decimal or Hex address output
- Debug mode

#### Usage ####
    paginator [options] backing_store address_list

#### Options ####
    -f num        Use `num` frames of "physical" memory (default 256).
    -p num        Backing store has `num` pages of memory (default 256).
    -h            Print addresses in hexadecimal.
    -d            Print extra debugging information about tlb hits,
                  victimization, and statistics.

#### Dependencies ####
Uses `make` and `gcc` to build.

#### Building ####
Run `make` in the root directory of the project. Object files are placed into the obj directory. Final binary is placed in the bin directory. Run `make clean` to wipe the obj and bin directories.
