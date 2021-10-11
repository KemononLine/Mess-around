# Pandas统计计算和描述

示例代码：

```python
arr1 = np.random.rand(4,3)
pd1 = pd.DataFrame(arr1,columns=list('ABC'),index=list('abcd'))
f = lambda x: '%.2f'% x
pd2 = pd1.applymap(f).astype(float)
pd2
```

运行结果：

```
      A            B           C
a    0.87        0.26        0.67
b    0.69        0.89        0.17
c    0.94        0.33        0.04
d    0.35        0.46        0.29
```

## 常用的统计计算 {#常用的统计计算}

### sum, mean, max, min… 

> axis=0 按列统计，axis=1按行统计
>
> skipna 排除缺失值， 默认为True

示例代码：

```python
pd2.sum() #默认把这一列的Series计算,所有行求和
pd2.sum(axis='columns') #指定求每一行的所有列的和
pd2.idxmax()#查看每一列所有行的最大值所在的标签索引，同样我们也可以通过axis='columns'求每一行所有列的最大值的标签索引
```

运行结果：

```
A    2.85
B    1.94
C    1.17
dtype: float64


a    1.80
b    1.75
c    1.31
d    1.10
dtype: float64


A    c
B    b
C    a
dtype: object
```

![](/assets/999.png)

## 常用的统计描述

### describe 产生多个统计数据

示例代码：

```python
pd2.describe()#查看汇总
```

运行结果：

```python
                A        B        C
count      4.000000    4.00000        4.000000
mean       0.712500    0.48500        0.292500
std        0.263613    0.28243        0.271585
min        0.350000    0.26000        0.040000
25%        0.605000    0.31250        0.137500
50%        0.780000    0.39500        0.230000
75%        0.887500    0.56750        0.385000
max        0.940000    0.89000        0.670000
```

```python
#百分比:除以原来的量
pd2.pct_change() #查看行的百分比变化，同样指定axis='columns'列与列的百分比变化
     A                 B                C
a    NaN              NaN             NaN
b    -0.206897        2.423077        -0.746269
c    0.362319        -0.629213        -0.764706
d    -0.627660        0.393939        6.250000
```

## 常用的统计描述方法：

![](/assets/4.png)

