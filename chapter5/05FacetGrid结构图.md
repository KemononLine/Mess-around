# FacetGrid结构图

之前我们在绘图的时候，学了`relplot`、`catplot`、`lmplot`等，这些函数可以通过`col`、`row`等在一个`Figure`中绘制多个图。这些函数之所以有这些功能，是因为他们的底层使用了`FacetGrid`来组装这些图形。今天我们就来学习`FacetGrid`的使用。

## 普通的Axes绘图：

在学习`FacetGrid`绘图之前，先来了解一下，实际上`seaborn`的绘图函数中也有大量的直接使用`Axes`进行绘图的，凡是函数名中已经明确显示了这个图的类型，这种图都是使用`Axes`绘图的。比如`sns.scatterplot`、`sns.lineplot`、`sns.barplot`等。`Axes`绘图可以直接使用之前`matplotlib`的一些方式设置图的元素。示例代码如下：

```python
fig,[ax1,ax2] = plt.subplots(2,1,figsize=(10,10))
sns.scatterplot(x="total_bill",y="tip",data=tips,ax=ax1)
sns.barplot(x="day",y="total_bill",data=tips,ax=ax2)
```

![](/assets/chapter05/facetgrid9.png)

## FacetGrid基本使用：

先创建一个`FacetGrid`对象，然后再调用这个对象的`map`方法。其中`map`方法的第一个参数是一个函数，后续`map`将调用这个函数来绘制图形。后面的参数就是传给这个函数的参数。示例代码如下：

```python
tips = sns.load_dataset("tips")
g = sns.FacetGrid(tips)
g.map(plt.scatter,"total_bill","tip")
```

效果图如下：  
![](/assets/chapter05/facetgrid1.png)

其中第一个参数是可以绘制`Axes`图，并且可以接收`color`参数的函数。可以取的值如下：

| 参数 | 描述 | 对应使用了`FacetGrid`函数 |
| --- | --- | --- |
| `plt.plot`/`sns.lineplot` | 绘制折线图 | `sns.relplot(kind="line")` |
| `plt.hexbin` | 绘制六边形图形 | `sns.jointplot(kind="hex")` |
| `plt.hist` | 绘制直方图 | `sns.distplot` |
| `plt.scatter`/`sns.scatterplot` | 绘制散点图 | `sns.relplot(kind="scatter")` |
| `sns.stripplot` | 绘制分类散点图 | `sns.catplot(kind="strip")` |
| `sns.swarmplot` | 绘制散开来的分类散点图 | `sns.catplot(kind="swarm")` |
| `sns.boxplot` | 绘制箱线图 | `sns.catplot(kind="box")` |
| `sns.violinplot` | 绘制小提琴图 | `sns.catplot(kind="violin")` |
| `sns.pointplot` | 绘制点线图 | `sns.catplot(kind="point")` |
| `sns.barplot` | 绘制条形图 | `sns.catplot(kind="bar")` |
| `sns.countplot` | 绘制数量柱状图 | `sns.catplot(kind="count")` |
| `sns.regplot` | 绘制带有回归线的散点图 | `sns.lmplot` |

## 绘制多个图形：

`FacetGrid`可以通过`col`和`row`参数，来在一个`Figure`上绘制多个图形，其中`col`和`row`都是数据集中的某个列的名字。只要指定这个名字，那么就会自动的按照指定列的值的个数绘制指定个数的图形。示例代码如下：

```python
g = sns.FacetGrid(tips,col="day",col_wrap=2)
g.map(sns.regplot,"total_bill","tip")
```

效果图如下：  
![](/assets/chapter05/facetgrid2.png)

## 添加颜色观察字段：

可以通过添加`hue`参数来控制每个图中元素的颜色来观察其他的字段。示例代码如下：

```python
g = sns.FacetGrid(tips,col="day",hue="time")
g.map(sns.regplot,"total_bill","tip")
```

![](/assets/chapter05/facetgrid4.png)

也可以通过`hue_kws`参数来添加`hue`散点的属性，比如设置散点的样式等。

## 设置每个图形的尺寸：

使用`FacetGrid`绘制出图形后，有时候我们想设置每个图形的尺寸或者是宽高比，那么我们可以通过在`FacetGrid`中设置`height`和`aspect`来实现，其中`height`表示的是每个图形的尺寸（默认是宽高一致），`aspect`表示的是`宽度/高度`的比例。示例代码如下：

```python
g = sns.FacetGrid(tips,col="day",row="time",height=10,aspect=2)
g.map(sns.regplot,"total_bill","tip")
```

效果图如下：  
![](/assets/chapter05/facetgrid3.png)

## 设置图例：

默认情况下，不会添加图例，我们可以通过`g.add_legend()`来添加图例。示例代码如下：

```python
g = sns.FacetGrid(tips,col="day",hue="time")
g.map(sns.regplot,"total_bill","tip")
g.add_legend()
```

![](/assets/chapter05/facetgrid5.png)

另外还可以：

1. 通过`title`来控制图例的标题。
2. 通过`label_order`来控制图例元素的顺序。

示例代码如下：

```python
sns.set(rc={"font.sans-serif":"simhei"})
g3 = sns.FacetGrid(tips,col="day",hue="time")
g3.map(plt.scatter,"total_bill","tip")
new_labels = ['午餐','晚餐']
g3.add_legend(title="时间")
for t,l in zip(g3._legend.texts,new_labels):
    t.set_text(l)
```

![](/assets/chapter05/facetgrid6.png)

## 设置标题：

设置标题可以通过`g.set_titles(template=None,row_template=None,col_template=None)`来实现，这三个参数分别代表的意义如下：

1. `template`：给图设置标题，其中有`{row_var}：绘制每行图像的名称`，`{row_name}：绘制每行图像的值`，`{col_var}：绘制每列图像的名称`，`{col_name}：绘制每列图像的值`这几个参数可以使用。
2. `col_template`：给图像设置列的标题。其中有`{col_var}`以及`{col_name}`可以使用。
3. `row_template`：给图像设置行的标题。其中有`{row_var}`以及`{row_name}`可以使用。

示例代码如下：

```python
g = sns.FacetGrid(tips,col="day",row="time")
g.map(sns.regplot,"total_bill","tip")
g.set_titles(template="时间{row_name}/星期{col_name}")
```

![](/assets/chapter05/facetgrid7.png)

## 设置坐标轴：

1. `g.set_axis_labels(x_var,y_var)`：一次性设置`x`和`y`的坐标的标题。
2. `g.set_xlabels(label)`：设置`x`轴的标题。
3. `g.set_ylabels(label)`：设置`y`轴的标题。
4. `g.set(xticks,yticks)`：设置`x`和`y`轴的刻度。
5. `g.set_xticklabels(labels)`：设置`x`轴的刻度文字。
6. `g.set_yticklabels(labels)`：设置`y`轴的刻度文字。

示例代码如下：

```python
g.set(xticks=range(0,60,10),xticklabels=['$0','$10','$20','$30','$40','$50'])
```

效果图如下：  
![](/assets/chapter05/facetgrid8.png)

## `g.set`方法：

`g.set`方法可以对`FacetGrid`下的每个子图`Axes`设置属性。其中可以设置的参数完全是根据`Axes`的属性来的。比如可以设置每个`Axes`的`facecolor`等。关于`Axes`有哪些属性，请参考`matplotlib.Axes`的官方文档：`https://matplotlib.org/api/axes_api.html?highlight=axes#matplotlib.axes.Axes`。

## `g.fig`：

通过`g.fig`，可以获取到当前的`Figure`对象。然后通过`Figure`对象再可以设置其他的属性，比如`dip`等。

