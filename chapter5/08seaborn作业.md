# Seaborn作业

## 一、 有一组温度数据，按照时间和温度绘制折线图。
```python
bj_temps = [29,27,23,22]
bj_hours = ["20时","23时","2时","5时"]
plt.figure(figsize=(5,2))
axes = sns.lineplot(range(0,4),bj_temps,marker="o")
axes.set_xticks(range(0,4))
axes.set_xticklabels(bj_hours)
```
效果图如下：
![](/assets/chapter05/作业1.png)


## 二、有以下国家数据，根据时间绘制条形图。
```python
legals = pd.read_csv("../法人人数年度数据.csv",encoding='GB18030')
temp_legals = legals[1:11]

# 清理数据
new_legals = pd.DataFrame()
for index in temp_legals.index:
    row_values =temp_legals.loc[index]
    for x in range(2009,2018):
        year = "%d年"%x
        series = pd.Series({"指标":row_values['指标'],'年份':year,"数量":row_values[year]})
        new_legals = pd.concat([new_legals,series.to_frame().T])
new_legals.reset_index(drop=True,inplace=True)

# 开始绘图
plt.figure(figsize=(20,5))
sns.barplot(x="年份",y="数量",hue="指标",data=new_legals)
plt.legend(ncol=4)
```
![](/assets/chapter05/作业2.png)


## 三、有链家网的数据，请按照以下要求实现绘图：
1. `x`轴是`Region（行政区）`，`y`轴是每个区的平均每平米的单价，绘制条形图。`x`轴是`Region（行政区）`，`y`轴是每平米的单价，绘制箱线图。`x`轴是`Region`，`y`轴是每平米的单价，绘制`swarm`图。以上三个图需要绘制在一个`figure`上。
    ```python
    lianjia = pd.read_csv("../lianjia.csv",encoding='utf-8')
    lianjia['UnitPrice'] = lianjia['Price']/lianjia['Size']
    house_mean = lianjia.groupby('Region')['UnitPrice'].mean().sort_values(ascending=False).to_frame().reset_index()
    fig,axes_arr = plt.subplots(3,1,figsize=(20,15))
    sns.barplot(x="Region",y="UnitPrice",data=house_mean,ax=axes_arr[0])
    sns.boxplot(x="Region",y="UnitPrice",data=lianjia,ax=axes_arr[1])
    sns.swarmplot(x="Region",y="UnitPrice",data=lianjia,ax=axes_arr[2])
    ```
    ![](/assets/chapter05/作业3.png)
    
2. 使用`FacetGrid`绘制尺寸与单价的关系，并且区分有无电梯。
    ```python
    fg = sns.FacetGrid(lianjia,col="Elevator",height=6,aspect=2)
    fg.map(sns.regplot,"Size","UnitPrice")
    fg.add_legend()
    ```
    ![](/assets/chapter05/作业4.png)

