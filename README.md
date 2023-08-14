

![yesdb](/logo/yesdb2.png)

- A storage engine for study

## Features
* Builtin server (`yesdb-server`)
* Predictable read/write performance
* Low latency
* High throughput

## Dependency
* [Catch2](https://github.com/catchorg/Catch2)
* [CRC32](https://github.com/google/crc32c)
* [Zstd](https://github.com/facebook/zstd)
* [Picobench](https://github.com/iboB/picobench)
* [Adaptive Radix Tree](https://github.com/rafaelkallis/adaptive-radix-tree)
* [Plog](https://github.com/SergiusTheBest/plog)
## Install Dependency
ART no need install
```
# Catch2
git clone https://github.com/catchorg/Catch2.git
cd Catch2 && cmake -B build && cmake --build build && cd build && sudo make install
# Other dependency similar
```
## How to Run
```
cd yesdb
cmake -B build
cmake --build build
./src/yesdb_server
curl http://0.0.0.0:18080/yesdb
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
- Wal
- Index
- Recovery
## Done 
- Read
- Write
- Serialize
- Deserialize
- Compress
- Decompress
- DBServer
- Log
- ART
- Benchmark
