# Numpy库介绍

`NumPy`是一个功能强大的`Python`库，主要用于对多维数组执行计算。`NumPy`这个词来源于两个单词-- `Numerical`和`Python`。`NumPy`提供了大量的库函数和操作，可以帮助程序员轻松地进行数值计算。在数据分析和机器学习领域被广泛使用。他有以下几个特点：  
1. numpy内置了并行运算功能，当系统有多个核心时，做某种计算时，numpy会自动做并行计算。  
2. Numpy底层使用C语言编写，内部解除了GIL（全局解释器锁），其对数组的操作速度不受Python解释器的限制，效率远高于纯Python代码。  
3. 有一个强大的N维数组对象Array（一种类似于列表的东西）。  
4. 实用的线性代数、傅里叶变换和随机数生成函数。

总而言之，他是一个非常高效的用于处理数值型运算的包。

## 安装：

通过`pip install numpy`即可安装。

## 教程地址：
1. 官网：`https://docs.scipy.org/doc/numpy/user/quickstart.html`。
2. 中文文档：`https://www.numpy.org.cn/user_guide/quickstart_tutorial/index.html`。


## Numpy数组和Python列表性能对比：

比如我们想要对一个Numpy数组和Python列表中的每个素进行求平方。那么代码如下：

```python
# Python列表的方式
t1 = time.time()
a = []
for x in range(100000):
    a.append(x**2)
t2 = time.time()
t = t2 - t1
print(t)
```

花费的时间大约是`0.07180`左右。而如果使用`numpy`的数组来做，那速度就要快很多了：

```python
t3 = time.time()
b = np.arange(100000)**2
t4 = time.time()
print(t4-t3)
```



