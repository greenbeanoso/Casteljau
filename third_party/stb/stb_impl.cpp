// =============================================================================
// stb_impl.cpp
// =============================================================================
// stb 系列函式庫（stb_image.h / stb_image_write.h ...）都是「header-only」的
// 單一標頭檔函式庫。它們的用法有一個固定慣例：
//
//   在「整個專案中，只能有一個 .cpp 檔案」在 #include 之前定義：
//       #define STB_IMAGE_WRITE_IMPLEMENTATION
//   這樣編譯器才會在這個檔案裡「真正產生」函式的實作（.o 目的檔內容）。
//
//   如果專案中的其他檔案也想使用 stb_image_write 的函式（例如 main.cpp），
//   只要「不要」再定義 STB_IMAGE_WRITE_IMPLEMENTATION、直接
//   #include "stb_image_write.h" 即可，就只是宣告而不會重複產生實作。
//
// 這種寫法可以讓函式庫維持「只有一個標頭檔」就能使用，
// 不需要額外編譯 .lib / .so，對初學者非常友善。
// =============================================================================

#define STB_IMAGE_WRITE_IMPLEMENTATION //定義一個巨集（macro）
#include "stb_image_write.h"
// 3-1
