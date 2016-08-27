## introductions

进行BT种子地址解析的程序，下面介绍了BT种子的格式。

## bencode编码格式

bt种子文件,包括以后的DHT网络中，都是用这种编码的。网上有很多介绍，这里简单再重复一遍。bencode 有 4 种数据类型: string, integer, list 和 dictionary。

### string

字符是以这种方式编码的: <字符串长度>:<字符串>。如 hell: 4:hell

### integer

整数是一这种方式编码的: i<整数>e。如1999: i1999e

### list

列表是一这种方式编码的: l[数据1][数据2][数据3][…]e。如列表[hello, world, 101]：l5:hello5:worldi101ee

### dictionary

字典是一这种方式编码的: d[key1][value1][key2][value2][…]e，其中 key 必须是 string 而且按照字母顺序排序。如字典 {aa:100, bb:bb, cc:200}： d2:aai100e2:bb2:bb2:cci200ee

## 程序实现

程序分别使用C和C++语言实现了对bencode编码格式的解析，将解析结果保存在了程序的变量中，使用两种语言实现，主要用来对两种语言的风格进行对比。
