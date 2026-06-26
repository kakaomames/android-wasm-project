import re

def generate_stubs(input_file):
    symbols = set()
    pattern = re.compile(r'\s+U\s+([a-zA-Z0-9_@]+)')

    SIGNATURE_MAP = {
        "pthread_kill": "int pthread_kill(int thread, int sig) { return 0; }",
        "pthread_mutex_destroy": "int pthread_mutex_destroy(void *mutex) { return 0; }",
        "pthread_exit": "int pthread_exit(void *retval) { return 0; }",
        "pthread_cond_broadcast": "int pthread_cond_broadcast(void *cond) { return 0; }",
        "pthread_getspecific": "int pthread_getspecific(int key) { return 0; }",
        "sem_post": "int sem_post(void *sem) { return 0; }",
        "pthread_cond_wait": "int pthread_cond_wait(void *cond, void *mutex) { return 0; }",
        "pthread_rwlock_rdlock": "int pthread_rwlock_rdlock(void *rwlock) { return 0; }",
        "pthread_equal": "int pthread_equal(int t1, int t2) { return 0; }",
        "pthread_atfork": "int pthread_atfork(void *prepare, void *parent, void *child) { return 0; }",
        "pthread_rwlock_wrlock": "int pthread_rwlock_wrlock(void *rwlock) { return 0; }",
        "pthread_self": "int pthread_self(void) { return 0; }",
        "sem_wait": "int sem_wait(void *sem) { return 0; }",
        "pthread_cond_signal": "int pthread_cond_signal(void *cond) { return 0; }",
        "pthread_detach": "int pthread_detach(int thread) { return 0; }",
        "pthread_key_delete": "int pthread_key_delete(int key) { return 0; }",
        "pthread_once": "int pthread_once(void *once_control, void (*init_routine)(void)) { return 0; }",
        "pthread_cond_init": "int pthread_cond_init(void *cond, void *attr) { return 0; }",
        "pthread_key_create": "int pthread_key_create(void *key, void (*destructor)(void*)) { return 0; }",
        "pthread_mutex_init": "int pthread_mutex_init(void *mutex, void *attr) { return 0; }",
        "pthread_mutex_trylock": "int pthread_mutex_trylock(void *mutex) { return 0; }",
        "pthread_cond_timedwait": "int pthread_cond_timedwait(void *cond, void *mutex, void *abstime) { return 0; }",
        "pthread_rwlock_unlock": "int pthread_rwlock_unlock(void *rwlock) { return 0; }",
        "pthread_cond_destroy": "int pthread_cond_destroy(void *cond) { return 0; }",
        "pthread_setspecific": "int pthread_setspecific(int key, const void *value) { return 0; }"
    }
    # 標準ライブラリ関数を完璧に網羅するための除外リスト
    # 今回エラーが出た全ての関数をここに追加した
    # ignore_list = {"dlopen", "dlsym", "dlclose", "dlerror","fopen", "fclose", "fread", "fwrite", "fprintf", "fscanf", "fseek", "clearerr", "fseeko", "ftell", "ftello", "fgets", "fputs", "fputc", "fflush", "feof", "ferror", "fileno", "freopen", "perror", "puts", "sprintf", "sscanf", "vasprintf", "vprintf", "vsscanf", "remove", "rename", "fdopen", "acos", "acosf", "asin", "asinf", "atan", "atanf", "atan2", "atan2f", "cos", "cosf", "exp", "expf", "exp2", "exp2f", "fmod", "fmodf", "hypot", "log", "log10", "log10f", "log2f", "logb", "logf", "pow", "powf", "sqrt", "sqrtf", "sin", "sincosf", "sinf", "tan", "tanf", "ldexp", "ldexpf", "modf", "modff", "nearbyintf", "remainderf", "scalbn", "calloc", "malloc", "free", "realloc", "memcpy", "memmove", "memset", "memalign", "memchr", "memcmp", "strlen", "strcmp", "strcpy", "strncpy", "strcat", "strchr", "strcspn", "strdup", "strerror", "strlcpy", "strncat", "strncmp", "strrchr", "strspn", "strstr", "strcasecmp", "strtod", "strtof", "strtol", "strtold", "strtoll", "strtoul", "strtoull", "strxfrm", "isalnum", "isalpha", "islower", "isspace", "isupper", "isxdigit", "tolower", "toupper", "abort", "_exit", "exit", "printf", "snprintf", "vfprintf", "vsnprintf", "wcslen", "wmemchr", "wmemcmp", "wmemcpy", "wmemmove", "pthread_create", "pthread_join", "pthread_mutex_lock", "pthread_mutex_unlock"}
    ignore_list = {
        # Math系 (エラーが出たもの)
        "acos", "acosf", "asin", "asinf", "atan", "atan2", "atan2f", "atanf",
        "cos", "cosf", "exp", "expf", "fmod", "hypot", "log", "log10", "pow",
        "sqrt", "sin", "sinf", "tan", "tanf", "modf", "modff", "nearbyintf",
        # Stdlib / Malloc系
        "calloc", "malloc", "free", "realloc", "posix_memalign", "abort", "exit", "_exit",
        # Stdio系
        "clearerr", "fclose", "feof", "ferror", "fflush", "fgetc", "fgets",
        "fopen", "fprintf", "fputc", "fputs", "fread", "fseek", "fwrite",
        "printf", "snprintf", "sprintf", "sscanf", "vfprintf", "vsnprintf",
        # String系
        "memchr", "memcmp", "memcpy", "memmove", "memset",
        "strcat", "strchr", "strcmp", "strcpy", "strlen", "strncmp", "strncpy",
        # その他
        "raise", "lseek", "strnlen", "wcrtomb"
    }


    
    with open(input_file, 'r') as f:
        for line in f:
            match = pattern.search(line)
            if match:
                symbol = match.group(1).split('@')[0]
                if symbol not in ignore_list:
                    symbols.add(symbol)
    
    with open('stubs.c', 'w') as f:
        f.write('#include <stdio.h>\n#include <stddef.h>\n\n')
        for s in sorted(symbols):
            if s in SIGNATURE_MAP:
                f.write(f'{SIGNATURE_MAP[s]}\n')
            else:
                # 不明なシンボルはデフォルトの void 型でスタブ化
                f.write(f'void {s}() {{ printf("STUB: {s} called\\n"); }}\n')
    
    print(f"Generated stubs in stubs.c with {len(symbols)} symbols.")

generate_stubs('nm.txt')

    
    
    # (f"Generated {len(symbols)} stubs in stubs.c. Standard functions ignored.")

# nm.txt から読み込む
generate_stubs('nm.txt')
