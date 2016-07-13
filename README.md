#![](http://i.imgur.com/S7xBFja.png)Sundy#
## GateWay##

###1.使用说明###
 将Gateway插入电脑，在我的电脑->管理->设备管理器中查看插入的串口的串口号，比如说如果是com3. 那么就打开次程序中的main.cpp文件，更改  SerialTest(3); //3 is COM3这一行，将串口对应的号码填进去。
###2.数据包解析###
 只需要在Robot.h中更改数据包的格式，对应的数据包和 [https://github.com/sundyCoder/MultiRobots](https://github.com/sundyCoder/MultiRobots) 代码中的数据包格式是一样的。

###3.输出格式###
 输出格式是根据你要输出数据包中的哪些数据，然后在Robot.cpp的DispPackInfo函数中进行更改即可。

