import re

def generate_stubs(input_file):
    symbols = set()
    pattern = re.compile(r'\s+U\s+([a-zA-Z0-9_@]+)')
    
    # 標準ライブラリ関数を完璧に網羅するための除外リスト
    # 今回エラーが出た全ての関数をここに追加した
    ignore_list = {
        "dlopen", "dlsym", "dlclose", "dlerror",
        # stdio系
        "fopen", "fclose", "fread", "fwrite", "fprintf", "fscanf", "fseek", "clearerr", "fseeko", "ftell", "ftello",
        "fgets", "fputs", "fputc", "fflush", "feof", "ferror", "fileno", "freopen",
        "perror", "puts", "sprintf", "sscanf", "vasprintf", "vprintf", "vsscanf", "remove", "rename", "fdopen",
        # 数学系
        "acos", "acosf", "asin", "asinf", "atan", "atanf", "atan2", "atan2f",
        "cos", "cosf", "exp", "expf", "exp2", "exp2f", "fmod", "fmodf", "hypot",
        "log", "log10", "log10f", "log2f", "logb", "logf", "pow", "powf", "sqrt", "sqrtf",
        "sin", "sincosf", "sinf", "tan", "tanf", "ldexp", "ldexpf", "modf", "modff",
        "nearbyintf", "remainderf", "scalbn",
        # 文字列・メモリ系
        "calloc", "malloc", "free", "realloc", "memcpy", "memmove", "memset", "memalign", "memchr", "memcmp",
        "strlen", "strcmp", "strcpy", "strncpy", "strcat", "strchr", "strcspn", "strdup", "strerror",
        "strlcpy", "strncat", "strncmp", "strrchr", "strspn", "strstr", "strcasecmp",
        "strtod", "strtof", "strtol", "strtold", "strtoll", "strtoul", "strtoull", "strxfrm",
        "isalnum", "isalpha", "islower", "isspace", "isupper", "isxdigit", "tolower", "toupper",
        # その他
        "abort", "_exit", "exit", "printf", "snprintf", "vfprintf", "vsnprintf", "wcslen",
        "wmemchr", "wmemcmp", "wmemcpy", "wmemmove",
        "pthread_create", "pthread_join", "pthread_mutex_lock", "pthread_mutex_unlock"
    }

    with open(input_file, 'r') as f:
        for line in f:
            match = pattern.search(line)
            if match:
                symbol = match.group(1).split('@')[0]
                if symbol not in ignore_list:
                    symbols.add(symbol)
    
    with open('stubs.c', 'w') as f:
        f.write('#include <stdio.h>\n\n')
        for s in sorted(symbols):
            # Android/Unity固有の未定義シンボルのみをスタブ化
            f.write(f'void {s}() {{ printf("STUB: {s} called\\n"); }}\n')
    
    print(f"Generated {len(symbols)} stubs in stubs.c. Standard functions ignored.")

# nm.txt から読み込む
generate_stubs('nm.txt')
