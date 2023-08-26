![yesdb](/logo/yesdb2.png)

- A storage engine for study

# Features

- Builtin server (`yesdb-server`)
- Predictable read/write performance
- Low latency
- High throughput

# Benchmark

```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
               put_test * |     100 |     0.787 |    7873 |      - |   127010.9
               put_test * |    1000 |     2.984 |    2984 |      - |   335083.2
               put_test * |   10000 |    26.584 |    2658 |      - |   376173.2
===============================================================================
```

# Dependency

- [Catch2](https://github.com/catchorg/Catch2)
- [CRC32](https://github.com/google/crc32c)
- [Zstd](https://github.com/facebook/zstd)
- [Picobench](https://github.com/iboB/picobench)
- [Adaptive Radix Tree](https://github.com/rafaelkallis/adaptive-radix-tree)
- [Plog](https://github.com/SergiusTheBest/plog)

# Install Dependency

The dependency install in `/usr/local/` for default, otherwise you need change include path. ART no need to install

```
# Catch2
git clone https://github.com/catchorg/Catch2.git
cd Catch2 && cmake -B build && cmake --build build && cd build && sudo make install
# Other dependency similar
```

# How to Run

```
cd yesdb
cmake -B build
cmake --build build
```

# Physical Data Layout

```c
/*
* +-------+--------+--------+----------+-----+-------+
* | crc32 | tstamp | key_sz | value_sz | key | value | 
* +-------+--------+--------+----------+-----+-------+
*/
```

# TODO 2023.8

- Wal
- Index
- Recovery

# Done

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
