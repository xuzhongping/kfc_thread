# kfc_thread

This is a simple user-level preemptive thread library for study.
这是一个用来学习使用的用户级线程库，它是抢占式的。
> 目前只支持运行在x86-64平台
## 设计

* pcb及线程栈
![](https://github.com/JungHsu/kfc_thread/kfc_thread/Resource/WX20190330-223221@2x.jpg)

* 简单起见，栈的大小为4096 x 3 - 120 = 12168字节

## 知识库
* x86-64汇编
* 《操作系统真相还原》