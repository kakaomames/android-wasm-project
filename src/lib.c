#include <stdio.h>
#include <emscripten.h>

// メインモジュールから呼ばれる関数
int EMSCRIPTEN_KEEPALIVE add(int a, int b) {
    return a + b;
}
