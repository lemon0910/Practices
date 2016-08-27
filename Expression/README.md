## introductions

这个程序是我在阅读C++沉思录时写下的，主要功能是实现计算表达式的解析，然后计算出结果。程序中考虑到了单目，双目和三目运算符。下面举个例子说明。

## 问题描述

算术表达式树，(-5) * (3+4)

![tree](/Expression/1.png)

## 代码展示

    void main()  
    {  
      Expr expression = Expr("*", Expr("-", "5"), Expr("+", "3", "4"));  
      cout << expression << endl;  
      expression = Expr("*", expression, expression);  
      cout << expression << endl;  
    }
    输出：
    ((-5)*(3 + 4))  
    ((-5)*(3 + 4))*((-5)*(3 + 4))   

## 分析

树的结构分为三种结点：（1）整数表达式，无子节点；（2）一元表达式，有一个操作符和一个子节点；（3）二元表达式，有一个操作符和两个子节点。引入句柄类Expr类，所有的Expr_Node的继承层次都包含在Expr，而用户不再能看到Expr_Node对象。
