

![yesdb](/logo/yesdb2.png)

- A storage engine for study

## Features
- Write
- Read
- Compression
- Serialize

## Dependency
* [Catch2](https://github.com/catchorg/Catch2)
* [CRC32](https://github.com/google/crc32c)
* [Zstd](https://github.com/facebook/zstd)

## How to Run
```
cd yesdb
cmake -B build
cmake --build build
./test/server_test
```
## Physical Data Layout
```c
/*
* +-------+--------+--------+----------+-----+-------+
* | crc32 | tstamp | key_sz | value_sz | key | value | 
* +-------+--------+--------+----------+-----+-------+
*/
```
## TODO 2023.8
- Serialize()
- Deserialize()
- Wal
- Compression
- Cache
- Index
- Recovery