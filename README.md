# muSAVE

muSAVE (SAVE short for SPIR-V Assembly Viewer and Editor) is a public domain single-file C library for viewing SPIR-V binary code in a readable assembly format. To use it, simply download the `muSAVE.h` file, add it to your include path, and include it like so:

```
#define MUSAVE_IMPLEMENTATION
#include "muSAVE.h"
```

Note that not defining `MUSAVE_IMPLEMENTATION` will will define the functions, structs, and enums, but will not give an implementation for the functions, meaning that you can include it across multiple files without redefinition errors as long as you define `MUSAVE_IMPLEMENTATION` once in your main file.

# Licensing

muSAVE is licensed under public domain or MIT, whichever you prefer. More information is provided in the accompanying file `license.md` and at the bottom of `muSAVE.h`.

# Other library dependencies

muSAVE is dependent on muString v3.1.0, meaning that all functions, macros, and types defined in that library are also included in this. They are not explicity stated here, and you'll have to go to the README in muString to learn more about those.

# General information

## General function syntax

All muSAVE functions have `muResult* result` as their first parameter. It's used to check if the function succeeded or failed. The function will dereference the given pointer as `MU_TRUE` or `MU_FALSE` to indicate so. `MU_NULL_PTR` can always be passed in if you decide to not check the result of the function.

## Macros

### Version

Near the top of the file, the version of muSAVE is defined with `MUSAVE_VERSION_MAJOR`, `MUSAVE_VERSION_MINOR`, and `MUSAVE_VERSION_PATCH`. These versions match the releases on the GitHub page and can be used to check if the correct version of muSAVE is running.

### Static/Extern defines

Defining `MU_STATIC` before including `muSAVE.h` will set all the definitions of the functions to static. Otherwise, it defaults to extern. Additionally, you can define `MUDEF` directly to have full control over its definition.

### C standard library dependencies

muSAVE relies on several C standard library functions, types, and defines. The list of types can be found below:

`int8_m`: equivalent to `int8_t`, uses  `stdint.h` for definition.

`uint8_m`: equivalent to `uint8_t`, uses  `stdint.h` for definition.

`int16_m`: equivalent to `int16_t`, uses  `stdint.h` for definition.

`uint16_m`: equivalent to `uint16_t`, uses  `stdint.h` for definition.

`int32_m`: equivalent to `int32_t`, uses  `stdint.h` for definition.

`uint32_m`: equivalent to `uint32_t`, uses  `stdint.h` for definition.

`int64_m`: equivalent to `int64_t`, uses  `stdint.h` for definition.

`uint64_m`: equivalent to `uint64_t`, uses  `stdint.h` for definition.

The list of functions can be found below:

`mu_memcpy`: equivalent to `memcpy`, uses `string.h` for definition.

The list of defines can be found below:

`MU_SIZE_MAX`: equivalent to `SIZE_MAX`, uses `stdint.h` for definition.

Note that all of these macros can be overwritten by defining them before including `muSAVE.h`.

Note that overwriting all macros relating to a C standard library header file prevents it from being included. For example, if `mu_memcpy` is overwritten, which is the only macro that is used in relation to `string.h`, then `string.h` will not be included.

### Null macros

muSAVE uses the macro `MU_NULL_PTR` to refer to a null pointer, and is just the value 0.

### Boolean macros

There is one macro who is based on the `muBool` enum.

Defined below is `muResult`, used to determine the result of a task:

```
#define muResult muBool
#define MU_FAILURE MU_FALSE
#define MU_SUCCESS MU_TRUE
```

### Print macros

There are two macros used to print, `mu_print` for printing just a string, and `mu_printf` for printing a formatted string of bytes. Both use `printf`, and thus have a dependency on `stdio.h`. If `MUSAVE_NO_PRINT` is defined, these macros are set to do nothing, muSAVE is guaranteed to never print any information, and `stdio.h` is never included. Additionally, `mu_print` and `mu_printf` can be overwritten by the user. If both are overwritten, `stdio.h` is not included.

# Functions

## Converting SPIR-V binary to assembly

The function `mu_spirv_binary_to_assembly` is used to translate SPIR-V binary code to a readable assembly format, defined below:

```
MUDEF muString mu_spirv_binary_to_assembly(muResult* result, const char* binary, size_m len);
```

Note that if `result` is dereferenced to equal `MU_FAILURE` by this function, the `muString` struct returned has both the member `s` and `ws` as 0 or `MU_NULL_PTR`.

Note that the `muString` struct returned follows all the usual rules of a `muString` struct, meaning that it should be destroyed later with `mu_string_destroy` to avoid memory leaks.

# Assembly syntax

The following section describes how the assembly generated from a successful call to `mu_spirv_binary_to_assembly` is generally formatted.

## Beginning of text

The first part of the text gives information on what version of muSAVE generated it, formatted like so:

```
; Assembly generated by muSAVE vMA.MI.PA
```

`MA`, `MI`, and `PA` will be replaced with the `MUSAVE_VERSION_MAJOR`, `MUSAVE_VERSION_MINOR`, and `MUSAVE_VERSION_PATCH` macros respectively.

## First words of physical layout

The next part gives information about the physical layout of the SPIR-V binary, described in the first few bytes of the binary, formatted like so:

```
; == First words of physical layout ==
; Magic:     0x07230203 (SPIR-V)
; Version:   v1.0.0
; Bound:     40
```

All of the numbers given are variable and can vary from one SPIR-V binary to another, with the only exception being `Magic` which should always equal `0x07230203`.

## Instruction list

The next part is the instruction list, beginning like so:

```
; == Instruction list ==
```

Everything below are the instructions listed in the SPIR-V binary. The general format of it is:

```
(CASTING INFORMATION) InstructionName (Parameters) {ListParameters}
```

All of the information about the instructions and their parameters is based off of the SPIR-V spec offered on the Khronos registry.

All of the instructions have a name associated with them. If the name wasn't successfully found, it will be replaced with `UnknownInstruction`.

If the instruction begins with "`[%N]`", where `N` is some given decimal number, that means that the given instruction's result is being casted to the type corresponding to the given ID `N`.

If "`%N = `" appears before the given instruction name, where `N` is some given decimal number, that means that the given instruction is being applied to the given ID whose number corresponds to `N`.

If one of the given parameters after the instruction name is a number beginning with `%`, it's an ID.

If one of the given parameters after the instruction name is surrounded by quotation marks, it's a string.

If one of the given parameters after the instruction name is a number with no `%` before it or quotation marks surrounding it, it's a decimal number.

If one of the given parameters after the instruction name is a name with no quotation marks surrounding it, it's an enum value corresponding with a number specified in the SPIR-V spec.

If one of the given parameters after the instruction name is surrounded in curly brackets, it's a list value.
