# 编程项目 #06

这个任务占40分（课程成绩的4.0%）,必须在二月25号周一11:59之前做完并交上，因为期中考试，所以时间调整为两周。

### 任务预览

这个任务的目的是对文件读写，列表和函数的进一步练习。

### 背景

数据挖掘就是通过整理大量的数据，然后找到有用的信息。通常用在金融领域，从大量的数据集合中提取信息。大数据集合和对他们的分析被成为“大数据”http://en.wikipedia.org/wiki/Big_data

在这个任务中，我们需要对苹果股票做一些预先的数据挖掘，你的程序需要计算从1984-2013年的每月的苹果股票平均价钱。你需要报告每月的高低细节信息。

### 任务说明

1. 我们会给你一个苹果每天的股票价格信息文件，文件名是`table.csv`，这个文件可以通过记事本或者类似的文本编辑器打开，数据以逗号分隔。如果你用Excel打开，它将以表格的方式显示数据。

2. 你必须实现下面的函数：

- `get_input_descriptor()`

在这个函数中，你需要不断提示用户去输入文件名直到用户输入的文件能被正常打开，返回这个打开的文件的文件描述符。

- `get_data_list(file_object, column_number)`

在这个函数中，你需要去读取苹果的数据。这个函数足够灵活，能读取任何一列（0-6）的数据。如果你读取第6列，你会得到调整后的每日收盘信息。如果你读取第5列，你会得到那天的成交量信息。这个函数返回一个列表，包含一些元组。每个元组是这样的格式：`(日期,数据)`。例如，如果我们收集第6列的数据的话，应该是这样的：`('2013-02-08',474.98)`

- `average_data(list_of_tuples)` 

在这个函数中，参数是上面的`get_data_list`函数生成的列表，你需要求每个月的平均值，并且重新生成一个包含若干元组的列表。元组是这样的格式：(数据平均值,日期)，例如，(2972945.4545454546,'07:1985')。注意日期不再包含天。

- `main()`

在这个函数中，你需要：

- 调用`get_input_descriptor`函数去获取文件描述符
- 提示将要求平均值的列
- 调用`get_data_list`函数
- 调用`average_data`函数
- 输出最高的6个平均值（选中的列）和最低的6个平均值，输出数据平均值和年月信息。

### 上交要求

`proj06.py` -- 你的解答源代码（记得包含你的班级，日期，课程号和必要的注释）

1. 请务必使用这样的文件名字，例如：“proj06.py”
2. 在你的CSE账户磁盘里面做一次备份（CSE电脑磁盘的H盘）
3. 你需要使用提交程序上交一份电子版的拷贝，提交程序在这里： [http://www.cse.msu.edu/handin/webclient](http://www.cse.msu.edu/handin/webclient)

### 需要下载的文件

table.csv

### 任务说明

1. 当读取输入文件的时候，你需要注意第一行不包含任何数据
2. 记得去用`split()`函数，这个函数接受一个参数作为分隔符，并且返回一个字符串的列表
3. 不要忘记将字符串转换成数字再计算
4. 因为有好多列数据，所以最好做一些测试（例如输出一些处理的信息）来确信你得到了正确的数据。
5. 排序函数要注意。

`my_list = [ (3,2), (1,2), (2,5)]`


`sorted_list = sorted(my_list) # 排序之后的列表是： [(1,2), (2,5), (3,2)], 按每个元组的第一个值进行排序`

6. 当你打开一个文件之后记得关闭

`file_object.close()    #关闭文件非常重要`

7. 要创建一个元组的话，记得只用逗号，例如两个条目的元组可以这样创建：

> `my_tuple = x,y`

当你存储日期和每月的平均值的时候，按文件中的的格式进行存储可能更容易一些，例如：`“11-2007”`

将这个元组追加到列表中你可以直接用`my_list.append(my_tuple)`方法。然后访问元组中的每一项，例如，如果你将上面的元组追加到列表的话：

> `my_list[0][0]` 将返回x
> `my_list[0][1]` 将返回y

### 示例输入

```
In [121]: main()
Open what file:fred
Bad file name, try again
Open what file:irving
Bad file name, try again
Open what file:table.csv
What column:6
Lowest 6 for column 6
Date:08-1985, Value: 1.70
Date:09-1985, Value: 1.77
Date:06-1985, Value: 1.84
Date:10-1985, Value: 1.90
Date:07-1985, Value: 1.93
Date:11-1985, Value: 2.19
Date:05-1985, Value: 2.21

Highest 6 for column 6
Date:09-2012, Value:674.54
Date:08-2012, Value:635.39
Date:10-2012, Value:628.17
Date:04-2012, Value:597.19
Date:07-2012, Value:592.33
Date:03-2012, Value:569.11
```