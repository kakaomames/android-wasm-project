import re

def generate_stubs(input_file):
    symbols = set()
    pattern = re.compile(r'\s+U\s+([a-zA-Z0-9_@]+)')
    
    # 完全に無視する標準関数リスト（libc, math, pthread系）
    # これらはシステムが提供するので、スタブを作ると衝突する
    ignore_list = {
        "fopen", "fclose", "fread", "fwrite", "fprintf", "fscanf", "fseek", "fseeko", "ftell", "ftello",
        "fgets", "fputs", "fputc", "fflush", "feof", "ferror", "fileno", "freopen",
        "acos", "acosf", "asin", "asinf", "atan", "atanf", "atan2", "atan2f",
        "cos", "cosf", "exp", "expf", "exp2", "exp2f", "fmod", "fmodf",
        "clearerr", "calloc", "malloc", "free", "realloc", "memcpy", "memmove", "memset",
        "abort", "_exit", "exit", "strlen", "strcmp", "strcpy", "strncpy",
        "pthread_create", "pthread_join", "pthread_mutex_lock", "pthread_mutex_unlock",
        "printf", "snprintf", "vfprintf", "vsnprintf"
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
        # Android特有の関数やUnity特有の関数だけをスタブにする
        for s in sorted(symbols):
            f.write(f'void {s}() {{ printf("STUB: {s} called\\n"); }}\n')
    
    print(f"Generated {len(symbols)} stubs in stubs.c (Ignored {len(ignore_list)} standard functions)")

generate_stubs('nm.txt')
