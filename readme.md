# Pilou

*This repository is a tribute to a friend and his cat.*

Pilou is a derivative of the [brainfuck](https://en.wikipedia.org/wiki/Brainfuck) programming language.

This repository contains the [pilou compiler source code](pilousource) and [some pilou code examples](pilouexamples).

## Table of contents

- [Table of contents](#table-of-contents)
- [Commands](#commands)
- [Usage](#usage)
    - [Print help](#print-help)
    - [Compile a pilou file to brainfuck](#compile-a-pilou-file-to-brainfuck)
    - [Compile a pilou file to c](#compile-a-pilou-file-to-c)
- [Install](#install)
- [Uninstall](#uninstall)

## Commands

Pilou | Brainfuck | C
---|---|---
`Pilou` | `>` | `ptr++;​`
`piloU` | `<` | `ptr--;​`
`pIlou` | `+` | `++(*ptr);​`
`pilOu` | `-` | `--(*ptr);​`
`PiLoU` | `.` | `putchar(*ptr);​`
`pIlOu` | `,` | `(*ptr) = getchar();​`
`PIlou` | `[` | `while(*ptr) {​`
`piLOU` | `]` | `}`

The compiler will ignore all character sequences other than the eight pilou commands.

## Usage

### Print help

```sh
pilou -h
```

### Compile a pilou file to brainfuck

```sh
pilou -b path/to/file
```

The output file will be `path/to/file.bf`.

### Compile a pilou file to c

```sh
pilou -c path/to/file
```

The output file will be `path/to/file.c`.

## Install

```sh
git clone https://github.com/gbeldilmi/pilou.git
cd pilou/pilousource
gcc pilou.c -o pilou
sudo cp pilou /usr/bin/pilou
```

## Uninstall

```sh
sudo rm /usr/bin/pilou
```
