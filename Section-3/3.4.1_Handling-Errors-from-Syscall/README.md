# 3.4.1 Handling Errors from Syscalls

A focused exercise that demonstrates common patterns for checking and reporting errors from system calls. The program walks through several examples (getpid, open, read, getpriority, perror/strerror) to show correct error-checking idioms and pitfalls such as relying on `errno` without checking return values.

## Goal

Illustrate practical syscall error-handling techniques and behaviors:

* How to check syscall return values rather than relying on `errno` alone.
* Printing numeric `errno` and mapping it to human-readable messages (using `perror`, `strerror`, and `strerror_r`).
* Examples of errors produced by invalid calls (EBADF, ENOENT, EACCES).
* Demonstrate that successful syscalls do not clear `errno` and that some syscalls (e.g., `getpriority`) may return valid negative values.

## Prerequisites

* Linux development host with standard C library and headers.
* `gcc` and `make` installed.

> Note: The repository follows a common Makefile convention; see the section README or the root README for repository-wide build policy. Use the exercise `Makefile` (`make`) to build this exercise.

## Build

From the exercise directory run:

```bash
make
```

The `Makefile` builds the example binary under `build/` (e.g., `build/syscall-errors`) and may create example output files under `build/` (e.g., `build/demo_open_ok.txt`).

## Run / Test

Run the example binary:

```bash
./build/syscall-errors
```

### Example output (sample run)

```
Simple syscall error-handling demo (final)

=== 1) getpid() ===
getpid() -> 19249

=== 2) open() success then failure ===
created and wrote to 'demo_open_ok.txt' (fd=3, bytes=15)
open('definitely_not_existing_file_12345.txt') failed: returned -1, errno=2

=== 3) error-number handling with switch ===
read(-1,...) returned -1, errno=9
  EBADF: bad file descriptor
open(nonexistent) returned -1, errno=2
  ENOENT: no such file or directory

=== 4) successful syscall does NOT clear errno ===
errno set to 22 BEFORE calling getppid()
after getppid(), errno still = 22 (not cleared by success)
=> always check the syscall return value, not errno alone

=== 5) getpriority() (negative valid values possible) ===
getpriority() -> 0 (valid result)

=== 6) perror / strerror demo and Unknown error case ===
perror: open failed: No such file or directory
strerror(errno) -> No such file or directory

strerror(ENOENT) -> No such file or directory
strerror(99999) -> Unknown error 99999
strerror_r(ENOENT) -> No such file or directory

End
```

Files produced in `build/` for the sample run:

```
build/demo_open_ok.txt
build/syscall-errors
```

## What to expect and what you learn

* **Section 1 (getpid):** `getpid()` normally succeeds; it illustrates a syscall with no expected failure in typical conditions.
* **Section 2 (open):** shows a successful `open()` (creating and writing a small file) and a failed `open()` to a non-existent path. On failure the program prints the numeric `errno` so you can observe concrete error codes (e.g., `errno=2` for `ENOENT`).
* **Section 3 (errno switch):** demonstrates mapping numeric `errno` values to meaningful explanations using `switch` and known errno constants (EBADF, ENOENT, EACCES).
* **Section 4 (errno persistence):** shows that a successful syscall does NOT clear `errno`; therefore checking `errno` alone is insufficient — always check the syscall return value.
* **Section 5 (getpriority):** `getpriority()` can return negative values that are valid; reset `errno` before calling and treat `return == -1 && errno != 0` as an error condition.
* **Section 6 (perror/strerror):** demonstrates `perror()` and `strerror()` output, the typical `Unknown error N` behavior for out-of-range error numbers, and a simple `strerror_r()` usage that fills a caller-provided buffer.

## Implementation notes

* The program is organized into small `section_*` functions called sequentially from `main()`; each section focuses on a single lesson.
* Error reporting uses both numeric `errno` prints and string helpers (`perror`, `strerror`, `strerror_r`) to show differences in presentation and portability caveats.
* The demo creates `build/demo_open_ok.txt` when `open(..., O_CREAT|O_WRONLY|O_TRUNC)` succeeds; ensure `build/` exists or let the `Makefile` create it.
* The code intentionally sets and inspects `errno` values to teach correct checking practices; avoid writing real production code that relies on global `errno` without proper return-value checks.
* Portability: `strerror_r()` has two API variants (XSI vs GNU); this demo uses the simple pattern of calling it and printing the buffer when filled to avoid complex compatibility handling.

## Status & Tags

* **Status:** ready
* **Tags:** error-handling, errno, syscall, perror, strerror, strerror_r, getpriority, system-programming

## Author

Mersad Karimi — [xmersdkarimi@gmail.com](mailto:xmersdkarimi@gmail.com)

Source file: `src/syscall-errors.c`

