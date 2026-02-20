# Kawika's Data Structure and Algorithm Tool
The purpose of this program is to practice building data structures and running various algorithms on them in the C language. It is an academic project.

## Usage

buildstruct [command] [flags]

## Commands

- build   creates a new data structure of the selected type
    - necessary flags: -t, -d
- add     adds to an existing data structure
    - necessary flags: -i, -d
- destroy deletes an existing data structure
    - necessary flags: -i
- algo    performs an algorithmic operation on a data structure
    - necessary flags: -i
- print   prints a visual representation of the data structure, as well as information about the structure
    - necessary flags: -i
- quit    ends the program

## Flags

+ -t [type]   selects the type of data structure to generate
    + linkedlist
+ -d [data]   selects data for program to insert into structure (currently only integer values)
+ -i [id]     selects a data structure by id

## Examples

buildstruct make -t LinkedList -d 1

buildstruct destroy -i 1