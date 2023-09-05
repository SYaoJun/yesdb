[English](README_en.md)

[![Ubuntu](https://github.com/syaojun/yesdb/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/syaojun/yesdb/actions/workflows/ubuntu.yml) ![yesdb](/logo/yesdb2.png)

# yesdb

- 一个基于Bitcask的KV存储引擎

## 编译说明

- C++17
- 所有第三方包都是采用源码编译
- 已适配Ninja生成器

  ## 关键特性

- 读

- 写
- 合并

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

- 依赖包都在cmake目录下，有对应的源码链接。

## 编译

```console
cmake -B build
cmake --build build
```

## 运行

```console
./bin/gtest_test
```

## 数据模型

```c
/*
* +-------+--------+--------+----------+-----+-------+
* | crc32 | tstamp | key_sz | value_sz | key | value | 
* +-------+--------+--------+----------+-----+-------+
*/
```
