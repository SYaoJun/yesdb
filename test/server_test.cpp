#include "catch2/catch_test_macros.hpp"
#include <iostream>
#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zstd.h"

#define PAGE_SIZE 4096
using namespace yesdb;

void compressWithDictionary(const char* data, char* compressedData, size_t *cmpr_size, ZSTD_CDict* cdict) {
    size_t dataSize = strlen(data) + 1;
    // 压缩后数据的上界
    size_t compressedSize = ZSTD_compressBound(dataSize);

    // 执行压缩
    size_t actualSize = ZSTD_compress_usingCDict(
        ZSTD_createCCtx(),
        compressedData,
        compressedSize,
        data,
        dataSize,
        cdict
    );
    // 判断压缩结果
    if (ZSTD_isError(actualSize)) {
        printf("Executing zstd algorithm is error when compress dict.\n");
        exit(0);
    }
    // 打印原数据大小和压缩后的数据大小
    printf("Original data size: %zu bytes\n", dataSize);
    printf("Compressed data size: %zu bytes\n", actualSize);

    *cmpr_size = actualSize;
}

TEST_CASE("test_yesdb_write_and_read", "yesdb.db"){
     Yesdb yesdb("yesdb.db");
     yesdb.Open();
     std::string key = "yaojun";
     std::string value = "A database developer";
     bool ret = yesdb.Put(key, value);
     REQUIRE(ret == true);
     yesdb.Sync();
     std::string ret_value;
     ret = yesdb.Get(key, ret_value);
     REQUIRE(ret == true);
//     REQUIRE(value == ret_value);
     yesdb.Close();
}

TEST_CASE("zstd", "f"){
// 训练字典的内容
    const char* dictContent = "This is the compression dictionary.";
    size_t dictSize = strlen(dictContent);
    // 创建字典
    ZSTD_CDict* cdict = ZSTD_createCDict(dictContent, dictSize, 1);
    // 判断字典是否创建成功
    if (!cdict) {
        fprintf(stderr, "Failed to create compression dictionary.\n");
        return;
    }

    const char* original_data = "Hello, world! This is some sample data.fasdfasdfasdfgasdgafffffffffffffffasdfasdfasdfasdfasdggggggggggggggggggggggggahff";

    char* cmpr_data = (char*)malloc(PAGE_SIZE);
    size_t cmpr_size = 0;
    // 使用字典压缩数据
    compressWithDictionary(original_data, cmpr_data, &cmpr_size, cdict);
    ZSTD_freeCDict(cdict);
}
