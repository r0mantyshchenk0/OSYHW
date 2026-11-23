/* Prevod desitkovych cisel na hexadecimalni zapis bez libc. */

static long sys_read(int fd, void *buf, unsigned long count)
{
    long result;
    __asm__ volatile (
        "syscall"
        : "=a" (result)
        : "a" (0L), "D" ((long)fd), "S" (buf), "d" (count)
        : "rcx", "r11", "memory"
    );
    return result;
}

static long sys_write(int fd, const void *buf, unsigned long count)
{
    long result;
    __asm__ volatile (
        "syscall"
        : "=a" (result)
        : "a" (1L), "D" ((long)fd), "S" (buf), "d" (count)
        : "rcx", "r11", "memory"
    );
    return result;
}

__attribute__((noreturn))
static void sys_exit(int code)
{
    __asm__ volatile (
        "syscall"
        :
        : "a" (60L), "D" ((long)code)
        : "rcx", "r11", "memory"
    );
    __builtin_unreachable();
}

static void print_hex(unsigned int num)
{
    static const char digits[] = "0123456789abcdef";
    char buf[11];
    unsigned int pos = sizeof(buf) - 1;
    buf[pos] = '\n';

    do {
        buf[--pos] = digits[num & 15U];
        num >>= 4;
    } while (num != 0);

    buf[--pos] = 'x';
    buf[--pos] = '0';

    /* Zapis muze byt kratsi nez pozadovana delka. */
    unsigned long remaining = sizeof(buf) - pos;
    const char *p = buf + pos;
    while (remaining != 0) {
        long written = sys_write(1, p, remaining);
        if (written <= 0)
            sys_exit(1);
        p += written;
        remaining -= (unsigned long)written;
    }
}

__attribute__((noreturn))
void _start(void)
{
    char buf[4096];
    unsigned int num = 0;
    int has_digits = 0;

    for (;;) {
        long count = sys_read(0, buf, sizeof(buf));
        if (count < 0)
            sys_exit(1);

        if (count == 0) {
            if (has_digits)
                print_hex(num);
            sys_exit(0);
        }

        for (long i = 0; i < count; ++i) {
            char ch = buf[i];
            if (ch >= '0' && ch <= '9') {
                num = num * 10U + (unsigned int)(ch - '0');
                has_digits = 1;
                continue;
            }

            if (has_digits) {
                print_hex(num);
                num = 0;
                has_digits = 0;
            }

            if (ch != ' ' && ch != '\n')
                sys_exit(0);
        }
    }
}
