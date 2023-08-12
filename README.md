

![yesdb](/logo/yesdb2.png)

- A storage engine for study

## Features

* Embeddedable library `yesdb`
* Predictable read/write performance
* Low latency
* High throughput

## Dependency:
* [Catch2](https://github.com/catchorg/Catch2)
* [CRC32](https://github.com/google/crc32c)
* [Zstd](https://github.com/facebook/zstd)

## How to Run
```
cmake -B build
cmake --build build
./test/server_test
```
## TODO-2023.8
- Serialize()
- Deserialize()
- Wal
- Compression
- Cache
- Index
- Recovery
