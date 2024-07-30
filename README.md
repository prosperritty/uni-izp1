# IZP 1. project
The goal of the project is to create a program that would emulate the algorithm for calculating the enabling and disabling of keys on the virtual navigation keyboard. The input of the program is the data of known addresses and the string entered by the user. The output of the program will contain the characters that should be allowed on the keyboard.
### Evaluation 10/10
# Build and try
First make the project:
```console
$ make
gcc keyfilter.c -o keyfilter -Wall -Wextra -Wall -std=c11
```
Now you can start by using:
```console
$ ./keyfilter `letters` < `file.txt`
```
- **letters** is a string to be searched from *file.txt*
- **file.txt** is a collection of cities

# Example

```console
$ cat file.txt
Oslo
Prague
Paris
Vienna
```

```console
$ ./keyfilter < file.txt
Enable: OPV
```

```console
$ ./keyfilter p < file.txt
Enable: AR
```

```console
$ ./keyfilter pa < file.txt
Found: PARIS
```

```console
$ ./keyfilter o < file.txt
Found: OSLO
```

```console
$ ./keyfilter V < file.txt
Found: VIENNA
```

```console
$ ./keyfilter g < file.txt
Not found
```
