# np.random模块

`np.random`为我们提供了许多获取随机数的函数。这里统一来学习一下。

## np.random.seed：

用于指定随机数生成时所用算法开始的整数值，如果使用相同的`seed()`值，则每次生成的随即数都相同，如果不设置这个值，则系统根据时间来自己选择这个值，此时每次生成的随机数因时间差异而不同。一般没有特殊要求不用设置。以下代码：

```python
np.random.seed(1)
print(np.random.rand()) # 打印0.417022004702574
print(np.random.rand()) # 打印其他的值，因为随机数种子只对下一次随机数的产生会有影响。
```

## np.random.rand：

生成一个值为`[0,1)`之间的数组，形状由参数指定，如果没有参数，那么将返回一个随机值。示例代码如下：

```python
data1 = np.random.rand(2,3,4) # 生成2块3行4列的数组，值从0-1之间
data2 = np.random.rand() #生成一个0-1之间的随机数
```

## np.random.randn：

生成均值\(μ\)为0，标准差（σ）为1的标准正态分布的值。示例代码如下：

```python
data = np.random.randn(2,3) #生成一个2行3列的数组，数组中的值都满足标准正太分布
```

## np.random.randint：

生成指定范围内的随机数，并且可以通过`size`参数指定维度。示例代码如下：

```python
data1 = np.random.randint(10,size=(3,5)) #生成值在0-10之间，3行5列的数组
data2 = np.random.randint(1,20,size=(3,6)) #生成值在1-20之间，3行6列的数组
```

## np.random.choice：

从一个列表或者数组中，随机进行采样。或者是从指定的区间中进行采样，采样个数可以通过参数指定：

```python
data = [4,65,6,3,5,73,23,5,6]
result1 = np.random.choice(data,size=(2,3)) #从data中随机采样，生成2行3列的数组
result2 = np.random.choice(data,3) #从data中随机采样3个数据形成一个一维数组
result3 = np.random.choice(10,3) #从0-10之间随机取3个值
```

## np.random.shuffle：

把原来数组的元素的位置打乱。示例代码如下：

```python
a = np.arange(10)
np.random.shuffle(a) #将a的元素的位置都会进行随机更换
```

## 更多：

更多的random模块的文档，请参考`Numpy`的官方文档：[https://docs.scipy.org/doc/numpy/reference/routines.random.html](https://docs.scipy.org/doc/numpy/reference/routines.random.html)

