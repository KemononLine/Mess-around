# NumPy数组基本用法

1. `Numpy`是`Python`科学计算库，用于快速处理任意维度的数组。
2. `NumPy`提供一个**N维数组类型ndarray**，它描述了**相同类型**的“items”的集合。
3. `numpy.ndarray`支持向量化运算。
4. `NumPy`使用c语言写的，底部解除了`GIL`，其对数组的操作速度不在受`python`解释器限制。

## numpy中的数组：

`Numpy`中的数组的使用跟`Python`中的列表非常类似。他们之间的区别如下：  
1. 一个列表中可以存储多种数据类型。比如`a = [1,'a']`是允许的，而数组只能存储同种数据类型。  
2. 数组可以是多维的，当多维数组中所有的数据都是数值类型的时候，相当于线性代数中的矩阵，是可以进行相互间的运算的。

## 创建数组（np.ndarray对象）：

`Numpy`经常和数组打交道，因此首先第一步是要学会创建数组。在`Numpy`中的数组的数据类型叫做`ndarray`。以下是两种创建的方式：

1. 根据`Python`中的列表生成：

   ```python
   import numpy as np
   a1 = np.array([1,2,3,4])
   print(a1)
   print(type(a1))
   ```

2. 使用`np.arange`生成，`np.arange`的用法类似于`Python`中的`range`：

   ```python
   import numpy as np
   a2 = np.arange(2,21,2)
   print(a2)
   ```

3. 使用`np.random`生成随机数的数组：

   ```python
   a1 = np.random.random(2,2) # 生成2行2列的随机数的数组
   a2 = np.random.randint(0,10,size=(3,3)) # 元素是从0-10之间随机的3行3列的数组
   ```

4. 使用函数生成特殊的数组：

   ```python
   import numpy as np
   a1 = np.zeros((2,2)) #生成一个所有元素都是0的2行2列的数组
   a2 = np.ones((3,2)) #生成一个所有元素都是1的3行2列的数组
   a3 = np.full((2,2),8) #生成一个所有元素都是8的2行2列的数组
   a4 = np.eye(3) #生成一个在斜方形上元素为1，其他元素都为0的3x3的矩阵
   ```

## ndarray常用属性：

### `ndarray.dtype`：

因为数组中只能存储同一种数据类型，因此可以通过`dtype`获取数组中的元素的数据类型。以下是`ndarray.dtype`的常用的数据类型：

| 数据类型 | 描述 | 唯一标识符 |
| --- | --- | --- |
| bool | 用一个字节存储的布尔类型（True或False） | 'b' |
| int8 | 一个字节大小，-128 至 127 | 'i1' |
| int16 | 整数，16 位整数\(-32768 ~ 32767\) | 'i2' |
| int32 | 整数，32 位整数\(-2147483648 ~ 2147483647\) | 'i4' |
| int64 | 整数，64 位整数\(-9223372036854775808 ~ 9223372036854775807\) | 'i8' |
| uint8 | 无符号整数，0 至 255 | 'u1' |
| uint16 | 无符号整数，0 至 65535 | 'u2' |
| uint32 | 无符号整数，0 至 2 \*\* 32 - 1 | 'u4' |
| uint64 | 无符号整数，0 至 2 \*\* 64 - 1 | 'u8' |
| float16 | 半精度浮点数：16位，正负号1位，指数5位，精度10位 | 'f2' |
| float32 | 单精度浮点数：32位，正负号1位，指数8位，精度23位 | 'f4' |
| float64 | 双精度浮点数：64位，正负号1位，指数11位，精度52位 | 'f8' |
| complex64 | 复数，分别用两个32位浮点数表示实部和虚部 | 'c8' |
| complex128 | 复数，分别用两个64位浮点数表示实部和虚部 | 'c16' |
| object\_ | python对象 | 'O' |
| string\_ | 字符串 | 'S' |
| unicode\_ | unicode类型 | 'U' |

我们可以看到，`Numpy`中关于数值的类型比`Python`内置的多得多，这是因为`Numpy`为了能高效处理处理海量数据而设计的。举个例子，比如现在想要存储上百亿的数字，并且这些数字都不超过254（一个字节内），我们就可以将`dtype`设置为`int8`，这样就比默认使用`int64`更能节省内存空间了。类型相关的操作如下：

1. 默认的数据类型：
   ```python
   import numpy as np
   a1 = np.array([1,2,3])
   print(a1.dtype) 
   # 如果是windows系统，默认是int32
   # 如果是mac或者linux系统，则根据系统来
   ```
2. 指定`dtype`：
   ```python
   import numpy as np
   a1 = np.array([1,2,3],dtype=np.int64)
   # 或者 a1 = np.array([1,2,3],dtype="i8")
   print(a1.dtype)
   ```
3. 修改`dtype`：
   ```python
   import numpy as np
   a1 = np.array([1,2,3])
   print(a1.dtype) # window系统下默认是int32
   # 以下修改dtype
   a2 = a1.astype(np.int64) # astype不会修改数组本身，而是会将修改后的结果返回
   print(a2.dtype)
   ```

### `ndarray.size`：

获取数组中总的元素的个数。比如有个二维数组：

```python
   import numpy as np
   a1 = np.array([[1,2,3],[4,5,6]])
   print(a1.size) #打印的是6，因为总共有6个元素
```

### `ndarray.ndim`：

数组的维数。比如：

```python
   a1 = np.array([1,2,3])
   print(a1.ndim) # 维度为1
   a2 = np.array([[1,2,3],[4,5,6]])
   print(a2.ndim) # 维度为2
   a3 = np.array([[[1,2,3],[4,5,6]],[[7,8,9],[10,11,12]]])
   print(a3.ndim) # 维度为3
```

### `ndarray.shape`：

数组的维度的元组。比如以下代码：

```python
   a1 = np.array([1,2,3])
   print(a1.shape) # 输出(3,)，意思是一维数组，有3个数据

   a2 = np.array([[1,2,3],[4,5,6]])
   print(a2.shape) # 输出(2,3)，意思是二位数组，2行3列

   a3 = np.array([
       [
           [1,2,3],
           [4,5,6]
       ],
       [
           [7,8,9],
           [10,11,12]
       ]
   ])
   print(a3.shape) # 输出(2,2,3)，意思是三维数组，总共有2个元素，每个元素是2行3列的

   a44 = np.array([1,2,3],[4,5])
   print(a4.shape) # 输出(2,)，意思是a4是一个一维数组，总共有2列
   print(a4) # 输出[list([1, 2, 3]) list([4, 5])]，其中最外面层是数组，里面是Python列表
```

另外，我们还可以通过`ndarray.reshape`来重新修改数组的维数。示例代码如下：

```python
   a1 = np.arange(12) #生成一个有12个数据的一维数组
   print(a1) 

   a2 = a1.reshape((3,4)) #变成一个2维数组，是3行4列的
   print(a2)

   a3 = a1.reshape((2,3,2)) #变成一个3维数组，总共有2块，每一块是2行2列的
   print(a3)

   a4 = a2.reshape((12,)) # 将a2的二维数组重新变成一个12列的1维数组
   print(a4)

   a5 = a2.flatten() # 不管a2是几维数组，都将他变成一个一维数组
   print(a5)
```

注意，`reshape`并不会修改原来数组本身，而是会将修改后的结果返回。如果想要直接修改数组本身，那么可以使用`resize`来替代`reshape`。

### `ndarray.itemsize`：

数组中每个元素占的大小，单位是字节。比如以下代码：

```python
   a1 = np.array([1,2,3],dtype=np.int32)
   print(a1.itemsize) # 打印4，因为每个字节是8位，32位/8=4个字节
```



