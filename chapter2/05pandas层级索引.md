# 层级索引（hierarchical indexing） 

> 下面创建一个Series， 在输入索引Index时，输入了由两个子list组成的list，第一个子list是外层索引，第二个list是内层索引。

示例代码：

```python
import pandas as pd
import numpy as np

ser_obj = pd.Series(np.random.randn(12),index=[
                ['a', 'a', 'a', 'b', 'b', 'b', 'c', 'c', 'c', 'd', 'd', 'd'],
                [0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2]
            ])
print(ser_obj)
```

运行结果：

```
a  0    0.099174
   1   -0.310414
   2   -0.558047
b  0    1.742445
   1    1.152924
   2   -0.725332
c  0   -0.150638
   1    0.251660
   2    0.063387
d  0    1.080605
   1    0.567547
   2   -0.154148
dtype: float64
```

## MultiIndex索引对象

* 打印这个Series的索引类型，显示是MultiIndex

* 直接将索引打印出来，可以看到有lavels,和labels两个信息。levels表示两个层级中分别有那些标签，labels是每个位置分别是什么标签。

示例代码：

```python
print(type(ser_obj.index))
print(ser_obj.index)
```

运行结果：

```python
<class 'pandas.indexes.multi.MultiIndex'>
MultiIndex(levels=[['a', 'b', 'c', 'd'], [0, 1, 2]],
           labels=[[0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3], [0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2]])
```

## 选取子集 {#选取子集}

* 根据索引获取数据。因为现在有两层索引，当通过外层索引获取数据的时候，可以直接利用外层索引的标签来获取。

* 当要通过内层索引获取数据的时候，在list中传入两个元素，前者是表示要选取的外层索引，后者表示要选取的内层索引。

### 1. 外层选取： {#1-外层选取：}

> ser\_obj\['outer\_label'\]

示例代码：

```python
# 外层选取
print(ser_obj['c'])
```

运行结果：

```
0   -1.362096
1    1.558091
2   -0.452313
dtype: float64
```

### 2. 内层选取： {#2-内层选取：}

> ser\_obj\[:, 'inner\_label'\]

示例代码：

```python
# 内层选取
print(ser_obj[:, 2])
```

运行结果：

```
a    0.826662
b    0.015426
c   -0.452313
d   -0.051063
dtype: float64
```

**常用于分组操作、透视表的生成等**

---

## 交换分层顺序

### swaplevel\(\) {#1-swaplevel}

> .swaplevel\( \)交换内层与外层索引。

示例代码：

```python
print(ser_obj.swaplevel())
```

运行结果：

```
0  a    0.099174
1  a   -0.310414
2  a   -0.558047
0  b    1.742445
1  b    1.152924
2  b   -0.725332
0  c   -0.150638
1  c    0.251660
2  c    0.063387
0  d    1.080605
1  d    0.567547
2  d   -0.154148
dtype: float64
```

## 交换并排序分层 {#交换并排序分层}

### sortlevel\(\) {#sortlevel}

> .sortlevel\( \)先对外层索引进行排序，再对内层索引进行排序，默认是升序。

示例代码：

```python
# 交换并排序分层
print(ser_obj.swaplevel().sortlevel())
```

运行结果：

```
0  a    0.099174
   b    1.742445
   c   -0.150638
   d    1.080605
1  a   -0.310414
   b    1.152924
   c    0.251660
   d    0.567547
2  a   -0.558047
   b   -0.725332
   c    0.063387
   d   -0.154148
dtype: float64
```



