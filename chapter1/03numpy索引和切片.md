# Numpy数组操作

## 索引和切片：

1. 获取某行的数据：

   ```python
    # 1. 如果是一维数组
    a1 = np.arange(0,29)
    print(a1[1]) #获取下标为1的元素

    a1 = np.arange(0,24).reshape((4,6))
    print(a1[1]) #获取下标为1的行的数据
   ```

2. 连续获取某几行的数据：

   ```python
    # 1. 获取连续的几行的数据
    a1 = np.arange(0,24).reshape((4,6))
    print(a1[0:2]) #获取0行到1行的数据

    # 2. 获取不连续的几行的数据
    print(a1[[0,2,3]])

    # 3. 也可以使用负数进行索引
    print(a1[[-1,-2]])
   ```

3. 获取某行某列的数据：

   ```python
    a1 = np.arange(0,24).reshape((4,6))
    print(a1[1,1]) #获取1行1列的数据

    print(a1[0:2,0:2]) #获取0-1行的0-1列的数据
    print(a1[[1,2],[2,3]]) #获取(1,2)和(2,3)的两个数据，这也叫花式索引
   ```

4. 获取某列的数据：

   ```python
    a1 = np.arange(0,24).reshape((4,6))
    print(a1[:,1]) #获取第1列的数据
   ```

## 布尔索引：

布尔运算也是矢量的，比如以下代码：

```python
a1 = np.arange(0,24).reshape((4,6))
print(a1<10) #会返回一个新的数组，这个数组中的值全部都是bool类型
> [[ True  True  True  True  True  True]
 [ True  True  True  True False False]
 [False False False False False False]
 [False False False False False False]]
```

这样看上去没有什么用，假如我现在要实现一个需求，要将`a1`数组中所有小于10的数据全部都提取出来。那么可以使用以下方式实现：

```python
a1 = np.arange(0,24).reshape((4,6))
a2 = a1 < 10
print(a1[a2]) #这样就会在a1中把a2中为True的元素对应的位置的值提取出来
```

其中布尔运算可以有`!=`、`==`、`>`、`<`、`>=`、`<=`以及`&(与)`和`|(或)`。示例代码如下：

```python
a1 = np.arange(0,24).reshape((4,6))
a2 = a1[(a1 < 5) | (a1 > 10)]
print(a2)
```

## 值的替换：

利用索引，也可以做一些值的替换。把满足条件的位置的值替换成其他的值。比如以下代码：

```python
a1 = np.arange(0,24).reshape((4,6))
a1[3] = 0 #将第三行的所有值都替换成0
print(a1)
```

也可以使用条件索引来实现：

```python
a1 = np.arange(0,24).reshape((4,6))
a1[a1 < 5] = 0 #将小于5的所有值全部都替换成0
print(a1)
```

还可以使用函数来实现：

```python
# where函数：
a1 = np.arange(0,24).reshape((4,6))
a2 = np.where(a1 < 10,1,0) #把a1中所有小于10的数全部变成1，其余的变成0
print(a2)
```



