// index.html または main.js
async function loadLibraryToOS(filename) {
    console.log(`[JS Loader] ${filename} を取得中...`);
    
    // 1. HTTPでダウンロード
    const response = await fetch(filename);
    const arrayBuffer = await response.arrayBuffer();
    const data = new Uint8Array(arrayBuffer);
    
    // 2. Wasm側のメモリに一時領域を確保 (Emscriptenのスタック/ヒープを借りる)
    const ptr = Module._malloc(data.length);
    Module.HEAPU8.set(data, ptr);
    
    // 3. C側の関数を叩いて、君の guest_mem に転送させる
    Module._copy_so_to_guest_memory(ptr, data.length, filename);
    
    // 4. 一時領域を開放
    Module._free(ptr);
    console.log(`[JS Loader] ${filename} をGem-OSにロード完了！`);
}
