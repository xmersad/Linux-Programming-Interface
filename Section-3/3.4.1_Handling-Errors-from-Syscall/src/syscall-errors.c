/* error handling for syscalls practice
 *
 * Sections (functions) are called in order:
 * 1) getpid() (no check usually needed)
 * 2) open() success and failure (print numeric errno in failure)
 * 3) check errno values with switch (simple examples)
 * 4) show that successful syscall does NOT clear errno
 * 5) getpriority() example where negative return may be valid
 * 6) perror / strerror demo (simple) and brief strerror_r usage
 *
 */

#define _POSIX_C_SOURCE 200809L


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>

/* Section 1:
 * Demonstrate getpid() which normally succeeds and doesn't need error-checking.
 */
static void section_1_getpid(void)
{
    printf("\n=== 1) getpid() ===\n");
    pid_t pid = getpid();
    printf("getpid() -> %d\n", (int)pid);
}

/* Section 2:
 * Demonstrate open() success (create + write) and open() failure.
 * On failure we only print the numeric errno here.
 */
static void section_2_open(void)
{
    printf("\n=== 2) open() success then failure ===\n");

    const char *okfile = "build/demo_open_ok.txt";
    int fd = open(okfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd >= 0) {
        const char *text = "demo: write OK\n";
        ssize_t w = write(fd, text, strlen(text));
        if (w < 0) {
            printf("write() returned -1, errno=%d\n", errno);
        } else {
            printf("created and wrote to '%s' (fd=%d, bytes=%zd)\n", okfile, fd, w);
        }
        close(fd);
    } else {
        printf("open('%s') failed: errno=%d\n", okfile, errno);
    }

    const char *nofile = "definitely_not_existing_file_12345.txt";
    int fd2 = open(nofile, O_RDONLY);
    if (fd2 < 0) {
        printf("open('%s') failed: returned -1, errno=%d\n", nofile, errno);
    } else {
        printf("unexpectedly opened '%s' (fd=%d)\n", nofile, fd2);
        close(fd2);
    }
}

/* Section 3:
 * Produce simple errors and inspect errno numerically with switch.
 * Example A: read(-1, ...) -> EBADF
 * Example B: open(nonexistent) -> ENOENT (or EACCES)
 */
static void section_3_errno_switch(void)
{
    printf("\n=== 3) error-number handling with switch ===\n");

    char buf[8];
    ssize_t r = read(-1, buf, sizeof(buf)); /* invalid fd */
    if (r < 0) {
        int e = errno;
        printf("read(-1,...) returned -1, errno=%d\n", e);
        switch (e) {
            case EBADF:
                printf("  EBADF: bad file descriptor\n");
                break;
            case EINTR:
                printf("  EINTR: interrupted system call\n");
                break;
            default:
                printf("  Other errno: %d\n", e);
                break;
        }
    } else {
        printf("read(-1,...) unexpectedly succeeded\n");
    }

    int fd = open("nonexistent_file_for_demo_9999.txt", O_RDONLY);
    if (fd < 0) {
        int e = errno;
        printf("open(nonexistent) returned -1, errno=%d\n", e);
        switch (e) {
            case ENOENT:
                printf("  ENOENT: no such file or directory\n");
                break;
            case EACCES:
                printf("  EACCES: permission denied\n");
                break;
            default:
                printf("  Other errno: %d\n", e);
                break;
        }
    } else {
        close(fd);
        printf("open(nonexistent) unexpectedly succeeded\n");
    }
}

/* Section 4:
 * Show that a successful syscall does NOT clear errno.
 * We set errno to a non-zero value, call a successful syscall and show errno persists.
 */
static void section_4_errno_not_cleared(void)
{
    printf("\n=== 4) successful syscall does NOT clear errno ===\n");
    errno = EINVAL;
    printf("errno set to %d BEFORE calling getppid()\n", errno);
    (void)getppid(); /* successful syscall */
    printf("after getppid(), errno still = %d (not cleared by success)\n", errno);
    printf("=> always check the syscall return value, not errno alone\n");
}

/* Section 5:
 * getpriority() may return negative values as valid results.
 * Reset errno to 0 before the call and if return == -1 then check errno.
 */
static void section_5_getpriority(void)
{
    printf("\n=== 5) getpriority() (negative valid values possible) ===\n");
    errno = 0;
    int pr = getpriority(PRIO_PROCESS, 0);
    if (pr == -1 && errno != 0) {
        printf("getpriority() returned -1 and errno=%d -> real error\n", errno);
    } else {
        printf("getpriority() -> %d (valid result)\n", pr);
    }
}

/* Section 6:
 * Simple perror / strerror demo and show Unknown error for invalid errnum.
 * Also show a simple strerror_r usage that fills a provided buffer.
 */
static void section_6_perror_strerror(void)
{
    printf("\n=== 6) perror / strerror demo and Unknown error case ===\n");

    int fd = open("/proc/this_path_does_not_exist_for_demo", O_RDONLY);
    if (fd < 0) {
        perror("perror: open failed");
        printf("strerror(errno) -> %s\n", strerror(errno));
    } else {
        close(fd);
    }

    printf("\nstrerror(ENOENT) -> %s\n", strerror(ENOENT));

    int bogus = 99999;
    printf("strerror(%d) -> %s\n", bogus, strerror(bogus)); /* typically: "Unknown error 99999" */

    char buf[128];
    buf[0] = '\0';
    (void)strerror_r(ENOENT, buf, sizeof(buf)); /* call and ignore return to avoid portability warnings */
    if (buf[0] != '\0') {
        printf("strerror_r(ENOENT) -> %s\n", buf);
    } else {
        /* fallback: if buf not filled, print strerror result */
        printf("strerror_r left buf empty, fallback -> %s\n", strerror(ENOENT));
    }
}

/* main: call sections in order */
int main(void)
{
    printf("Simple syscall error-handling demo (final)\n");

    section_1_getpid();
    section_2_open();
    section_3_errno_switch();
    section_4_errno_not_cleared();
    section_5_getpriority();
    section_6_perror_strerror();

    printf("\nEnd\n");
    return 0;
}

