# Linux Programming Interface 

This repository contains practical exercise implementations and examples for *The Linux Programming Interface* by Michael Kerrisk. It is explicitly designed as a hands-on resource for **system-level programming**: low-level user-space APIs, process and thread control, IPC (pipes, sockets, message queues), file and device I/O, signals, memory management, and other kernel-facing programming topics.

## Repository Goals

- Provide runnable, well-documented implementations of selected exercises from *The Linux Programming Interface*.
- Offer concise, practical notes and implementation tips focused on system-level programming techniques and common pitfalls.
- Create reproducible examples that can be built and tested on typical Linux development hosts and embedded targets.
- Organize exercises so they are easy to navigate, extend, and reuse as teaching or practice material.
- Encourage contributions that improve correctness, portability, and clarity for learners of system programming.

## Intended audience

- System programmers learning Linux user-space APIs and tools.
- Embedded and kernel-adjacent developers who want practical examples of system calls and low-level patterns.
- Students and instructors using *The Linux Programming Interface* as a course or self-study reference.

## Repository layout

```
.
├── README.md                    # this file: repo overview, goals, and section index
├── LICENSE                      # repository license
└── Section-<number>/
    ├── README.md                # section overview and exercise table (index for that section)
    └── <exercise-dir>/
        ├── src/                 # source code (implementation)
        ├── build/               # example build artifacts (platform-specific binaries)
        ├── Makefile             # build rules: targets: all, clean, (test)
        └── README.md            # exercise-specific instructions and explanation
```

## Indexing strategy

The repository-level `README.md` does not list every exercise. Instead it documents each **Section** and the topics covered by that Section (for example: Section 3 — Error handling, libc detection, syscall error conventions). Each `Section-<n>/README.md` contains the detailed Exercise index table for that section with links to individual exercise folders, short goals, and statuses.

This approach keeps the root README compact and gives each section a single place to manage and document its exercises.

## Exercise placement policy

- Exercises are organized into multiple Sections. Each Section may contain many exercises; exercises are **not** enumerated exhaustively in the root README.
- For each exercise there is a dedicated directory that includes a local `README.md`, the implementation under `src/`, optional build outputs under `build/`, and a `Makefile` for building the exercise.
- Section-level `README.md` files list the exercises for that Section in a table (Exercise, Path, Short Goal, Status). The Section README is the canonical index for that Section’s exercises.

> Note: Because this document is the repository root README, it shows a **summary table of Sections** (links and short descriptions). Individual exercises are documented inside their Section README files.

## Sections summary (root-level table)

| Section | Link                                                                                    | Short description                                                                       |
| ------- | --------------------------------------------------------------------------------------- | --------------------------------------------------------------------------------------- |
| 3       | [Section-3](https://github.com/xmersad/Linux-Programming-Interface/tree/main/Section-3) | Error handling, libc version detection, syscall error conventions, and related examples |

*(Add more sections to this table as the repository grows — each entry should link to ****Section-\<n>**** and include a one-line summary of the section topics.)*

## Exercise structure and build policy

- Each exercise contains two primary directories: `src/` (source files) and `build/` (build output examples). A `Makefile` at the exercise root must provide at least the `all` and `clean` targets; add a `test` target where applicable.
- Exercise `README.md` must be actionable and include: Title, Goal, Prerequisites, Build, Run/Test, Implementation notes, and Status & Tags.
- Keep compiled artifacts out of version control; prefer `.gitignore` entries and store small example binaries in `build/` only when necessary for demonstration.

## Naming conventions

- Exercise directories: `Section-<n>/<m>_<Short_Title>` (e.g., `Section-3/3.3_Detect_Glibc_Version`). Use underscores for exercise titles and hyphens where helpful.
- Keep source code in `src/` and binary/output under `build/` to avoid accidental commits of compiled artifacts.

## Contributing

- Open an issue to propose new exercises or significant changes before creating large PRs.
- Follow the Exercise README template when adding new exercises.
- Keep PRs focused and include short test steps and expected results.

## License

This repository is licensed under the [MIT License](https://github.com/xmersad/Linux-Programming-Interface/blob/main/LICENSE).
