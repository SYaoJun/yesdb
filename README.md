[中文版](README_cn.md)

[![Build](https://github.com/syaojun/yesdb/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/syaojun/yesdb/actions/workflows/ubuntu.yml)

![yesdb](/logo/yesdb2.png)

# yesdb

- 一个基于Bitcask的KV存储引擎

## 编译说明

- 要求C++17
- 所有第三方都是采用源码编译

## 关键特性

- 高性能

  - 追加写数据
  - 数据分层冷温热
  - 布隆过滤器和BITMAP索引
  - RDMA

- 低成本

  - 采用ZSTD压缩
  - 适配S3对象存储

## 性能测试

```
===============================================================================
   Name (baseline is *)   |   Dim   |  Total ms |  ns/op  |Baseline| Ops/second
===============================================================================
               put_test * |     100 |     0.787 |    7873 |      - |   127010.9
               put_test * |    1000 |     2.984 |    2984 |      - |   335083.2
               put_test * |   10000 |    26.584 |    2658 |      - |   376173.2
===============================================================================
```

## 依赖包

- [Catch2](https://github.com/catchorg/Catch2)
- [CRC32](https://github.com/google/crc32c)
- [Zstd](https://github.com/facebook/zstd)
- [Picobench](https://github.com/iboB/picobench)
- [Adaptive Radix Tree](https://github.com/rafaelkallis/adaptive-radix-tree)
- [Plog](https://github.com/SergiusTheBest/plog)

## 编译

```console
git submodule update --init --recursive
cmake -B build
cmake --build build
```

## 运行

```console
./test/db_bench
```

## 数据模型

```c
/*
* +-------+--------+--------+----------+-----+-------+
* | crc32 | tstamp | key_sz | value_sz | key | value | 
* +-------+--------+--------+----------+-----+-------+
*/
```

## 待完成

- Wal
- Index
- Recovery
