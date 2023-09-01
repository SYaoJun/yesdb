#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zstd.h>
#include <iostream>

int main() {
    const char *dictContent = "This is the compression dictionary.";
    size_t dictSize = strlen(dictContent);
    ZSTD_CDict *cdict = ZSTD_createCDict(dictContent, dictSize, 1);
    if (!cdict) {
        fprintf(stderr, "Failed to create compression dictionary.\n");
        return 0;
    }
    std::cout << "create success!" << std::endl;
    return 0;
}