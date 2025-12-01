## Linux Programming Interface — Exercises Repository

This repository contains practical exercise implementations and examples for *The Linux Programming Interface* by Michael Kerrisk. It is explicitly designed as a hands-on resource for **system-level programming**: low-level user-space APIs, process and thread control, IPC (pipes, sockets, message queues), file and device I/O, signals, memory management, and other kernel-facing programming topics.

## Repository Goals (explicit)

* Provide runnable, well-documented implementations of selected exercises from *The Linux Programming Interface*.
* Offer concise, practical notes and implementation tips focused on system-level programming techniques and common pitfalls.
* Create reproducible examples that can be built and tested on typical Linux development hosts and embedded targets.
* Organize exercises so they are easy to navigate, extend, and reuse as teaching or interview/practice material.
* Encourage contributions that improve correctness, portability, and clarity for learners of system programming.

## Intended audience

This repo is targeted at:

* System programmers learning Linux user-space APIs and tools.
* Embedded and kernel-adjacent developers who want practical examples of system calls and low-level patterns.
* Students and instructors using *The Linux Programming Interface* as a course or self-study reference.

## Repository layout

```
.
├── README.md                    # this file: repo overview, goals, and exercise index
├── LICENSE
└── Section-<number>/
    ├── README.md
    └── <exercise-dir>/
        ├── src/             # source code
        ├── build/           # build example (x86-64)
        ├── Makefile         # build rules
        └── README.md        # exercise-specific instructions and explanation
        
```

## Downloading the book

Link to the official book page or the publisher (O'Reilly): replace `<OFFICIAL_BOOK_URL>` with the authoritative source. If you have a legally owned local copy you may place relevant excerpts or notes under `docs/` and reference them; do not commit copyrighted PDFs unless you have distribution rights.

```
# English comment: replace <OFFICIAL_BOOK_URL> with the book's official page or your course-provided link
Official book page: <OFFICIAL_BOOK_URL>
```

## Exercise index (example table)

This table should be kept up-to-date. Each row links to the exercise folder and briefly states the goal and status.

| Section |          Exercise         |                     Path                    |                            Short Goal                            | Status |
| :-----: | :-----------------------: | :-----------------------------------------: | :--------------------------------------------------------------: | :----: |
|    3    | Determining Glibc Version | `./Section-3/3.3_Determining_Glibc_Version` | Detect runtime glibc version and demonstrate symbol/version APIs |  ready |
| :-----: | :-----------------------: | :-----------------------------------------: | :--------------------------------------------------------------: | :----: |


## Exercise README template (required)

Each exercise directory must include a `README.md` with these fields:

1. **Title** — short exercise title
2. **Goal** — explicit, single-paragraph statement of what the exercise demonstrates
3. **Prerequisites** — required tools/libraries (gcc, make, libc version, kernel features)
4. **Build & Test** — minimal commands to build and run (relative paths)
5. **Implementation notes** — brief design choices, portability concerns, and references to book sections
6. **Status & Tags** — ready/draft, difficulty, related topics (e.g., sockets, signals)

## Naming conventions

* Use `Section-<n>/<m>_<Short_Title>` for directories, where `<n>` is the book section and `<m>` is an exercise number. Use hyphens and underscores for readability.
* Keep source under `src/` and provide a `Makefile` with targets: `all`, `clean`, and `test` when appropriate.

## Contributing (brief)

* Open an issue describing the proposed exercise or improvement before large PRs.
* Follow the Exercise README template for any new exercise directories.
* Keep commits focused and include short descriptions of behavior and test steps.

## License

MIT

