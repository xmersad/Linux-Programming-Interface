# 3.3 Detect Glibc Version

This exercise demonstrates how to identify the glibc version through three mechanisms: compile‑time macros, a runtime glibc‑provided function, and `confstr()` configuration queries. It helps illustrate the differences between build‑time and runtime environments and how each method behaves on systems using glibc or alternative C libraries.


## Goal

Demonstrate three methods to determine the GNU C Library (glibc) version and show what information each method provides:

1. **Compile-time macros** (`__GLIBC__` and `__GLIBC_MINOR__`) — report the version the code was compiled against.
2. **Runtime function** (`gnu_get_libc_version()`) — returns the linked glibc version string at runtime.
3. **Runtime confstr** (`confstr(_CS_GNU_LIBC_VERSION, ...)`) — returns the implementation string (commonly `"glibc X.Y"`) when glibc is present.

This exercise highlights differences between compile-time and runtime information and how alternative C libraries or mismatched toolchains affect results.

## Prerequisites

* Linux development environment with glibc headers and libraries (development package) when testing against glibc.
* `gcc` and `make` available on the host.

> Note: The repository follows a common Makefile convention; see the section README or the root README for the repository-wide build policy. Use the exercise `Makefile` (`make`) to build this exercise.

## Build

Use the provided `Makefile`. From the exercise directory run:

```bash
make
```

The `Makefile` builds the example binary under `build/`.

## Run / Test

Run the example binary and observe three detection outputs (compile-time macro, `gnu_get_libc_version()`, and `confstr()`):

```bash
./build/detecting-libc-version
```

### Expected outputs and what they mean

**Typical glibc system (example: glibc 2.31):**

```
Libc version (compile-time) detected by __GLIBC__ is : 2.31
Libc version (runtime) detected by gnu_get_libc_version is : 2.31 
Libc version (runtime) detected by confstr() is : glibc 2.31 
```

* **What you learn:** compile-time macros show the headers/toolchain version used when compiling. `gnu_get_libc_version()` and `confstr()` report the runtime library version.

**If compiled without glibc headers (macros not defined):**

```
This program has not been compiled with glibc
Libc version (runtime) detected by gnu_get_libc_version is : 2.31 
Libc version (runtime) detected by confstr() is : glibc 2.31 
```

* **What you learn:** the program may still run and detect runtime glibc even if compile-time macros were absent (depends on how it was compiled/linked).

**If the runtime C library is not glibc (e.g., musl):**

```
Libc version (compile-time) detected by __GLIBC__ is : 2.31   # only if compiled against glibc headers
Libc version (runtime) detected by gnu_get_libc_version is : 2.31  # only if linked against glibc
This system is not using glibc
```

* **What you learn:** `confstr(_CS_GNU_LIBC_VERSION,...)` returns size 0 on non-glibc implementations; the program interprets that as “not using glibc”. Runtime detection methods depend on the linked C library.

## Implementation notes

* `__GLIBC__` and `__GLIBC_MINOR__` are compile-time macros provided by glibc headers. They indicate what the compiler headers exposed at build time.
* `gnu_get_libc_version()` is a glibc-specific exported function that returns a version string (e.g., `"2.31"`). If the binary is linked against glibc, this call returns the runtime glibc version; otherwise the symbol may be missing.
* `confstr(_CS_GNU_LIBC_VERSION, ...)` returns a string like `"glibc 2.31"` when glibc supports that configuration name; a return value of `0` means the name is not supported by the C library.
* The code uses a Variable Length Array (`char buffer[size];`) after querying `confstr()` for required size. For maximum portability you may prefer `malloc()` and `free()` to avoid VLA reliance on some toolchains.
* Cross-compilation: compile-time macros reflect the cross-toolchain headers. Runtime detection depends on the target runtime environment; running the binary on the target yields the runtime values.

## Status & Tags

* **Status:** ready
* **Tags:** glibc, libc-detection, runtime, compile-time, confstr, gnu_get_libc_version, system-programming

## Author

Mersad Karimi — [xmersdkarimi@gmail.com](mailto:xmersdkarimi@gmail.com)

*Source file:* `src/detecting-libc-version.c`
