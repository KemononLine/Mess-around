# matplotlib配置

## 修改默认的配置：
修改默认的配置可以通过`matplotlib.rcParams`来设置，比如修改字体，修改线条大小和宽度等。示例代码如下：
```python
import matplotlib.pyplot as plt
# 设置字体为仿宋
plt.rcParams['font.sans-serif'] = ['FangSong']
# 设置字体大小为20
plt.rcParams['font.size'] = 20
# 设置线条宽度
plt.rcParams['lines.linewidth'] = 2
# 设置线条颜色
plt.rcParams['axes.prop_cycle'] = plt.cycler('color', ['r', 'y'])
```

其中`rcParams`中可以设置的属性为如下：

在`Windows`上如果想要显示中文，那么可以通过设置`font.sans-serif`来设置，示例代码如下：
```python
plt.rcParams['font.sans-serif'] = ['FangSong']
```
这个属性可以设置以下字体都可以显示中文：

|字体名|英文名称|
|---|---|
|黑体|SimHei|
|仿宋|FangSong|
|楷体|KaiTi|
|宋体|SimSun|
|隶书|LiSu|
|幼圆|YouYuan|
|华文细黑|STXihei|
|华文楷体|STKaiti|
|华文宋体|STSong|
|华文中宋|STZhongsong|
|华文仿宋|STFangsong|
|方正舒体|FZShuTi|
|方正姚体|FZYaoti|
|华文彩云|STCaiyun|
|华文琥珀|STHupo|
|华文隶书|STLiti|
|华文行楷|STXingkai|
|华文新魏|STXinwei|

`Mac`和`Linux`支持的字体可能会不同，如果不行，可以使用`matplotlib.font_manager`来指定具体的字体。

## 自定义配置文件：
有时候我们可能需要设置一大堆参数，并且这个配置在后面很多项目中可能都会用到，那么这时候我们就可以把这些配置信息放到文件中（可配置项见下），文件的命名规则为`[名称].mplstyle`，然后把这个文件放到`matplotlib.get_configdir()/stylelib`的目录中，在写代码的时候根据名称加载这个配置文件，示例代码如下：
```python
plt.style.use("名称")
```


## 可配置项：
更多可配置项请参考：https://raw.githubusercontent.com/matplotlib/matplotlib/master/matplotlibrc.template