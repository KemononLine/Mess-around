# Jupyter notebook使用

## 常用快捷键：

### 命令模式（按Esc键）：
1. Enter：转入编辑模式
2. Shift-Enter：运行本单元，选中下个单元
3. Ctrl-Enter：运行本单元
4. Alt-Enter：运行本单元，在其下插入新单元
5. Y：单元转入代码状态
6. M：单元转入markdown状态
7. R：单元转入raw状态
8. 1：设定 1 级标题
9. 2：设定 2 级标题
10. 3：设定 3 级标题
11. 4：设定 4 级标题
12. 5：设定 5 级标题
13. 6：设定 6 级标题
14. Up：选中上方单元
15. K：选中上方单元
16. Down：选中下方单元
17. J：选中下方单元
18. Shift-K：扩大选中上方单元
19. Shift-J：扩大选中下方单元
20. A：在上方插入新单元
21. B：在下方插入新单元
22. X：剪切选中的单元
23. C：复制选中的单元
24. Shift-V：粘贴到上方单元
25. V：粘贴到下方单元
26. Z：恢复删除的最后一个单元
27. D,D：删除选中的单元
28. Shift-M：合并选中的单元
29. Ctrl-S：文件存盘
30. S：文件存盘
31. L：转换行号
32. O：转换输出
33. Shift-O：转换输出滚动
34. Esc：关闭页面
35. Q：关闭页面
36. H：显示快捷键帮助
37. I,I：中断Notebook内核
38. 0,0：重启Notebook内核
39. Shift：忽略
40. Shift-Space：向上滚动
41. Space：向下滚动

### 编辑模式：
1. Tab : 代码补全或缩进
2. Shift-Tab : 提示
3. Ctrl-] : 缩进
4. Ctrl-[ : 解除缩进
5. Ctrl-A : 全选
6. Ctrl-Z : 复原
7. Ctrl-Shift-Z : 再做
8. Ctrl-Y : 再做
9. Ctrl-Home : 跳到单元开头
10. Ctrl-Up : 跳到单元开头
11. Ctrl-End : 跳到单元末尾
12. Ctrl-Down : 跳到单元末尾
13. Ctrl-Left : 跳到左边一个字首
14. Ctrl-Right : 跳到右边一个字首
15. Ctrl-Backspace : 删除前面一个字
16. Ctrl-Delete : 删除后面一个字
17. Esc : 进入命令模式
18. Ctrl-M : 进入命令模式
19. Shift-Enter : 运行本单元，选中下一单元
20. Ctrl-Enter : 运行本单元
21. Alt-Enter : 运行本单元，在下面插入一单元
22. Ctrl-Shift-- : 分割单元
23. Ctrl-Shift-Subtract : 分割单元
24. Ctrl-S : 文件存盘
25. Shift : 忽略
26. Up : 光标上移或转入上一单元
27. Down :光标下移或转入下一单元

## 注意事项：
`jupyter notebook`每一个`cell`运行完后都会把这个`cell`中的变量保存到内存中，如果在一个`cell`中修改了之前的变量，再此运行这个`cell`的时候可能会导致一些问题产生。比如以下代码：
```python
# 第一个cell中的代码
a = 10
b = 20

# 第二个cell中的代码
c = a/b
b = 0
```
因为第二个`cell`修改了`b`变量，此时在整个环境中`b`都是等于0的，所以以后再运行这个`cell`的时候，`a/b`这个就会出问题了。这时候可以使用`Kernel->Rstart&Run All`来重新运行整个项目。


