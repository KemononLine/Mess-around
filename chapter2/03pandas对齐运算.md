# Pandas的对齐运算 {#pandas的对齐运算}

是数据清洗的重要过程，可以按索引对齐进行运算，如果没对齐的位置则补NaN，最后也可以填充NaN

> ## Series的对齐运算 {#series的对齐运算}

#### 1. Series 按行、索引对齐 {#1-series-按行、索引对齐}

示例代码：

```python
s1 = pd.Series(range(10, 20), index = range(10))
s2 = pd.Series(range(20, 25), index = range(5))

print('s1: ' )
print(s1)

print('') 

print('s2: ')
print(s2)
```

运行结果：

```
s1: 
0    10
1    11
2    12
3    13
4    14
5    15
6    16
7    17
8    18
9    19
dtype: int64

s2: 
0    20
1    21
2    22
3    23
4    24
dtype: int64
```

#### 2. Series的对齐运算 {#2-series的对齐运算}

示例代码：

```python
# Series 对齐运算
s1 + s2
```

运行结果：

```
0    30.0
1    32.0
2    34.0
3    36.0
4    38.0
5     NaN
6     NaN
7     NaN
8     NaN
9     NaN
dtype: float64
```

> ## DataFrame的对齐运算 {#dataframe的对齐运算}

#### 1. DataFrame按行、列索引对齐 {#1-dataframe按行、列索引对齐}

示例代码：

```python
df1 = pd.DataFrame(np.ones((2,2)), columns = ['a', 'b'])
df2 = pd.DataFrame(np.ones((3,3)), columns = ['a', 'b', 'c'])

print('df1: ')
print(df1)

print('') 
print('df2: ')
print(df2)
```

运行结果：

```
df1: 
     a    b
0  1.0  1.0
1  1.0  1.0

df2: 
     a    b    c
0  1.0  1.0  1.0
1  1.0  1.0  1.0
2  1.0  1.0  1.0
```

#### 2. DataFrame的对齐运算 {#2-dataframe的对齐运算}

示例代码：

```python
# DataFrame对齐操作
df1 + df2
```

运行结果：

```python
     a    b   c
0  2.0  2.0 NaN
1  2.0  2.0 NaN
2  NaN  NaN NaN
```

> ## 填充未对齐的数据进行运算 {#填充未对齐的数据进行运算}

#### 1. fill\_value {#1-fillvalue}

> 使用`add`,`sub`,`div`,`mul`的同时，
>
> 通过`fill_value`指定填充值，未对齐的数据将和填充值做运算

示例代码：

```python
print(s1)
print(s2)
s1.add(s2, fill_value = -1)

print(df1)
print(df2)
df1.sub(df2, fill_value = 2.)
```

运行结果：

```python
# print(s1)
0    10
1    11
2    12
3    13
4    14
5    15
6    16
7    17
8    18
9    19
dtype: int64

# print(s2)
0    20
1    21
2    22
3    23
4    24
dtype: int64

# s1.add(s2, fill_value = -1)
0    30.0
1    32.0
2    34.0
3    36.0
4    38.0
5    14.0
6    15.0
7    16.0
8    17.0
9    18.0
dtype: float64


# print(df1)
     a    b
0  1.0  1.0
1  1.0  1.0

# print(df2)
     a    b    c
0  1.0  1.0  1.0
1  1.0  1.0  1.0
2  1.0  1.0  1.0


# df1.sub(df2, fill_value = 2.)
     a    b    c
0  0.0  0.0  1.0
1  0.0  0.0  1.0
2  1.0  1.0  1.0
```

**算术方法表**:

| 方法 | 描述 |
| :--- | :--- |
| add，radd | 加法（+） |
| sub，rsub | 减法（-） |
| div，rdiv | 除法（/） |
| floordiv，rfllordiv | 整除（//） |
| mul，rmul | 乘法（\*） |
| pow，rpow | 幂次方（\*\*） |



