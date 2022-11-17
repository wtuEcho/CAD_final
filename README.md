基于半边数据结构的欧拉操作和扫掠的实现

![image-20221117213704380](C:\Users\zy\Desktop\CAD_final\jpg\image-20221117213704380.png)![image-20221117213752486](C:\Users\zy\Desktop\CAD_final\jpg\image-20221117213752486.png)

![image-20221117214607891](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214607891.png)

## 1.1  实验环境及代码结构

实验环境：Visual Studio 2019，x86编译。

l  B-rep：包含6个头和6个实现文件，实现了B-rep的基本组织结构；

l  EularOperation：包含1个头文件和1个实现文件，实现了5个基本的欧拉操作；

l  Sweep：包含1个头文件和1个实现文件，实现了扫掠操作；

l  Example：一个头文件，给出了三个案例

l  main：一个实现文件，实现了绘制操作

## 1.2  样例及使用方法

实验共绘制了三个样例：

l  使用欧拉操作构建的中空长方体；

l  使用欧拉和扫掠构建的平行体；

l  使用欧拉和扫掠构建的复杂图形。

有两种调用方法（esc退出，d切换为线框/点模型，左键拖动查看）：

l  命令传参式：切换到Debug目录，执行CAD_final.exe 1为运行案例1，改变数字为2或3即可执行案例2或案例3；

l  VS调试式：修改宏定义中的DRAW_EXAMPLE为1、2或3，再运行程序即可。



## 样例1-详述

样例1只使用欧拉操作构建出一个中空立方体，共计使用了16个顶点，生成了10个面。

系统内部对面自动进行了编号，顶点及面的编号如下图所示：

![image-20221117214717958](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214717958.png)

构建该体的具体函数调用过程如下：

\1.   构建长方体外轮廓的第一个方形（黑箭头为f[0]环的方向）

 ![image-20221117214732590](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214732590.png)

\2.   构建长方体外轮廓的第二个方形

 ![image-20221117214742373](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214742373.png)

\3.   构建长方体全部外轮廓

 ![image-20221117214755673](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214755673.png)

\4.   构建内轮廓的第一个环

 ![image-20221117214805194](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214805194.png)

![image-20221117214814431](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214814431.png)

\5.   向内构造内轮廓

 ![image-20221117214823778](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214823778.png)

\6.   构造四个内面及环，得到完全体

 ![image-20221117214831985](C:\Users\zy\Desktop\CAD_final\md_photo\image-20221117214831985.png)

