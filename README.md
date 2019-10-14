# kfc_thread

This is a simple user-level preemptive thread library for study.
> 目前只支持运行在x86-64平台
# 设计

* pcb及线程栈
![](https://github.com/JungHsu/kfc_thread/blob/master/Resource/WX20190330-224916@2x.png?raw=true)

* 简单起见，栈的大小为4096 x 3 - 120 = 12168字节

# 参考文献
* x86-64汇编
* 《操作系统真相还原》