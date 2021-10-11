# Numpy练习题

## 一、查看Numpy的版本号：

```python
import numpy as np
print(np.__version__)
```

## 二、如何创建一个所有值都是False的布尔类型的数组：

```python
np.full((3,3),False,dtype=np.bool)
```

## 三、将一个有10个数的数组的形状进行转换：

```python
arr = np.arange(10)
arr.reshape(2,5) #转换成(2,5)的数组
arr[:,np.newaxis] #转换成(10,1)的数组
```

`np.newaxis`所处的位置，会变成1。比如：

```python
arr = np.random.randint(0,10,size=(10,2))
arr1 = arr[:,np.newaxis,:]
print(arr1.shape)
# 结果是(10,1,2)，因为np.newaxis所在的位置是1
```

## 四、将数组中所有偶数都替换成0（改变原来数组和不改变原来数组两种方式实现）：

```python
arr = np.random.randint(0,10,size=(3,3))
# 1. 不改变原来数组
arr1 = np.where(arr%2==0,0,arr)
print(arr1)
# 2. 改变原来数组
arr[arr%2==0] = 0
```

## 五、创建一个一维且有10个数的数组，元素是从`0-1`之间，但是不包含0和1：

```python
arr = np.linspace(0,1,12)[1:-1]
```

其中的`linspace`是在起始值和结束值之间平均的获取指定个数的数。比如以上就是从`0-1`之间获取12个数组。

## 六、求以下数组大于等于5并且小于等于10的数组：

```python
a = np.arange(15)
# 方法1
index = np.where((a >= 5) & (a <= 10))
a[index]

# 方法2:
index = np.where(np.logical_and(a>=5, a<=10))
a[index]
#> (array([6, 9, 10]),)

# 方法3：
a[(a >= 5) & (a <= 10)]
```

## 七、将一个二维数组的行和列分别进行逆向：

```python
a = np.arange(15).reshape(3,5)
# 反转行
a1 = a[::-1] #里面传一个数进去（没有出现逗号），代表的是只对行进行操作
# 反转列
a2 = a[:,::-1] #里面传两个数进去，第一个是所有的行，第二个就是针对所有的列，但是取值的方向是从后面到前面。
```

## 八、如何将科学计数法转换为浮点类型打印：

```python
# set_printoptions用来设置打印的时候的一些配置和选项
# 将suppress设置为True，就不会显示成科学计数法了，并且通过precision来控制小数点后要保留几位
np.set_printoptions(suppress=True,precision=6)
rand_arr = np.random.random([3,3])/1e3
print(rand_arr)
```

## 九、获取一个数组中唯一的元素：

```python
arr = np.random.randint(0,20,(10,10))
np.unique(arr)
```

## 十、获取一个数组中唯一的元素个数的排行：

```python
arr = np.random.randint(0,20,(10,10))
np.unique(arr,return_counts=True)
```

## 十一、如何找到数组中每行的最大值：

```python
# 解决方案1：
np.random.seed(100)
a = np.random.randint(1,10, [5,3])
print(a)
print("="*30)
print(np.amax(a,axis=1))

# 解决方案2：
print(np.apply_along_axis(np.max,arr=a,axis=1))
```

## 十二、如何按照行求最小值与最大值相除的结果：

```python
np.random.seed(100)
a = np.random.randint(1,10, [5,3])
np.apply_along_axis(lambda x: np.min(x)/np.max(x),arr=a,axis=1)
```

## 十三、判断两个数组是否完全相等：

```python
a = np.array([0,1,2])
b = np.arange(3)
(a == b).all()
```

## 十四、设置一个数组不能修改值：

```python
a = np.zeros((2,2))
a.flags.writable = False
a[0] = 1
```

## 十五、找到数组中离某个元素的最近的值：

```python
np.random.seed(100)
Z = np.random.uniform(0,1,10)
z = 0.5
m = Z[np.abs(Z - z).argmin()]
print(m)
```



