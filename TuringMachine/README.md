# Turing Machine实验报告

DZ1933019 刘旭同

实验要求中的所有功能均已实现，报告结构如下：

  - 编译运行说明
  - 分析与设计思路
  - 实验中遇到的问题及解决方案
  - 演示
  - 总结感想  


## 编译运行说明


运行在Ubuntu，C++14，使用CMake构建
```sh
$ /clion-2019.2.2/bin/cmake/linux/bin/cmake -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" /home/lau/CLionProjects/Turing
```
该项目已编译完成，可直接运行
```sh
$ cd Turing/
$ ./Turing case1
$ ./Turing case2
```



## 分析与设计思路  


1. 任务一：多带图灵机程序解析器  
其实是一个**字符串处理问题**。按照任务中规定的语法，写出的图灵机是一个字符串，对用来表示图灵机的字符串的解析，是读字符串并处理的过程。把用字符串描述的图灵机转化成可以运行的图灵机，就是从字符串到数据结构的转化。因此我**把图灵机形式化成C++中的一个类**：TM，图灵机的七元组是TM类的七个成员变量。  
对于Transition Function，由于它是一个五元组，因此为它定义一个数据结构：Transition。
对每一行输入，图灵机解析器判断它是七元组中的哪一个，如果是注释或者空白行就跳过，否则将其花括号内的内容逐条读出并写入图灵机实例。

2. 任务二：多带图灵机程序解析器
    - 图灵机的输入字符串是C++ STL中的string类，因此用string.find()函数可以判断字符串合法性。
    - 对合法输入串模拟运行:模拟运行分两部分来讨论，一部分是Transition Function的循环，另一部分是分步骤执行信息的打印。
    - Transition Function实现为一个函数search_rule(),该函数的输入是图灵机的转移规则，旧状态和旧字符组，返回新状态，新字符组，和方向组。初始情况下旧状态时图灵机的初始状态。在函数内部，每匹配到一个符合条件的规则，就加入到候选集合中，最终返回的是通配符最少的那个规则。
    模拟运行一直循环直到search_rule()返回的新规则是Final State。
    - 执行信息的打印：根据题目要求，每条tape都需要打印下列三个信息：Index[i], Tape[i], Head[i]。i表示第i条纸带。因此我们维护三个Index，Tape，Head三个容器。初始时刻tape[0]中存的是input，其余tape是空。Head是int类型，初始时刻head都是0，表示当前指向0位置，head的值表示的是tape当前被head指向的下标。每一个step，首先从每一条tape[i]中读出head所指的那个字符，汇总成old characters，然后用search_rule()读出的new characters来改写tape上的字符，用direction来改写head的值，方向为左则head[i]--。，方向为右则head[i]++。方向为通配符则head[i]不变。
    - 由于输出中的index规定都是整数，如果head指向了纸带原本开头的左边，则这样下标应当为负的位置也以绝对值表示，所以，每次head值变化，都要检测head值有没有变成负数（因为每个单步都检测，所以只可能变成-1）。如果head变成-1，则把head置为零，并在index左边push一个比当前最左值加一的值，并在tape的开头位置插入一个“_”。为了能使index既能从左插值，也能从右插值，我使用了STL中的deque结构来表示index。

3. 实现两个图灵机程序  

    - K是一个斐波那契数  
    斐波那契的前两个数是1，1，后面的数满足f(n) = f(n-1) + f(n-2)。主要思路是除了tape0记录当前剩余的input外，另外用三条纸带记录f(n-1) ， f(n-2)和f(n)。每次用tape1连接tape2的结果写入tape3，tape3的长度就是下一个满足条件的斐波那契数列，然后给tape0减去tape3那么多的0，如果tape0中的0的个数不够减，则reject；如果tape0中的个数刚好和tape3中的零的个数一样多，则accept；否则继续下一轮。下一轮开始的时候，先把tape1的内容复制到tape2中，再把tape3中的内容复制到tape1中，实现f(n-1)和f(n-2)的更新。  
    - 满足ww的01串  
    实现思路：(1) 如果input的长度是奇数，则直接reject。(2) 如果input的长度是偶数，则找到字符串的中点，一个head指向开头，另一个head指向中点之后的第一个字符，然后同时向后走，每次指向的字符串不同则reject，如果第二个head能走到遇到第一个blank，则accept。具体来说：
        * 判断字符串长度奇偶的办法：除了tape0写着input之外，再用一条纸带tape1，初始情况下tape1写0，index0从左向右读tape0，每读到一个字符，就给tape1上的这个单个字符取反（0变1，1变0），直到tape0读完全部input就检查tape1上的字符，如果是0则input的长度是偶数，如果是1则input的长度是奇数。
        * 找到字符串中点的办法：用tape1把tape0上的初始input复制下来。再tape1两头各加一个“#”。通过index0和index1的移动来实现两条纸带的换值操作，从而每次把两头的“#”各往中间挪一个。举个例子，第一步是“#11001100#”，第二步是“1#1001100#”，第三步是“1#100110#0”，继续下去直到tape1变成“1100##1100”,这样从后往前看到的第一个“#”的右面就是index1要指向的那个“中点”。   
  


## 实验中遇到的问题及解决方案  


###  数据结构的选择
代码实现采用了C++ STL中的vector，string类，它们封装良好，提供了便捷的接口，非常适合用来定义TM类和Transition结构。题目中的图灵机是双向纸带，会出现index 是“3 2 1 0 1 2 3”这样的情况，因此用STL中的deque（双向队列）结构来实现index。
    
## 演示


![串ww的图灵机运行过程](https://github.com/liu906/TuringMachine/blob/master/1.png)
![串ww的图灵机运行过程](https://github.com/liu906/TuringMachine/blob/master/2.png)


## 感想   


如果题目直接是“写一个多带图灵机程序来模拟接受ww的图灵机”，就会比较难想，好在题目是循序渐进分了三问，其实是给出程序结构的一个提示——先要有一个形式化的图灵机字符串表示，然后要有一个解析程序来解析字符串，将字符串表示的图灵机转换成程序表示的图灵机。对于一个给定的串，先要判断其合法性，接着要有一个simulate程序来模拟图灵机的运行。


这个实验加深了我对以下知识点的理解：  
- 图灵机是一个n元组，双向纸带，读写头
- 利用多带图灵机简化运行
- 图灵机可以像计算机那样编程
- 图灵机表示成一个字符串    

最后谈一下我对课程的感想。这门课是本学期我付出时间精力最多的一门课程，它循序渐进地讲了表示能力越来越强的几种语言，让我对什么是语言，什么是问题，计算机能做什么不能做什么有了更深刻的认识，总之这是一门非常精妙的学科，感谢老师和助教的付出。




