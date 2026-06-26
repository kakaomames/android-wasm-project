import re

def generate_stubs(input_file):
    symbols = set()
    # nmの出力から ' U ' を含む行を抽出
    pattern = re.compile(r'\s+U\s+([a-zA-Z0-9_@]+)')
    
    with open(input_file, 'r') as f:
        for line in f:
            match = pattern.search(line)
            if match:
                symbol = match.group(1).split('@')[0] # @LIBCなどを除去
                symbols.add(symbol)
    
    with open('stubs.c', 'w') as f:
        f.write('#include <stdio.h>\n\n')
        for s in sorted(symbols):
            # C言語のスタブ関数を生成
            f.write(f'void {s}() {{ printf("STUB: {s} called\\n"); }}\n')
    
    print(f"Generated {len(symbols)} stubs in stubs.c")

# 使い方: nmの出力をファイル(nm_output.txt)に保存して実行
generate_stubs('nm.txt')
