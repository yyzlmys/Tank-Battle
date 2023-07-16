# Tank-Battle

#### 介绍
南开大学高级语言程序设计2-2大作业——坦克大战（2213512 闫永昭）

#### 软件架构
这是一个坦克大战小游戏，有红方和绿方坦克，还有一个双方都可以攻击的假想敌。坦克既可以攻击对方，也可以攻击假想敌，而赢得比赛的要求是击中10次假想敌。  

图形化库使用浙大acllib，这是一个基础的win编程图形库，封装的都是最基础的win编程API，体量很小。本来是c语言的库，笔者把它适配成cpp文件了。为了面向对象，笔者修改了acllib源码的键盘事件接口部分，原版仍附在src文件夹中。  

这是坦克大战1.0版本，运用c++11的新特性，如可变参数列表，包装器绑定器等，从而构建了较为完美的具体游戏物体类与类间接口的框架，继承与多态贯穿始终，真正实现了高内聚、低耦合。  

在最终版本里，有几个最顶端或者说最基础的类，分别是Game,Keymanager,Messager。Game类管理游戏场景的加载切换，Keymanager类负责其他类的键盘事件函数注册，Messager类负责类间的通信。而GameObject类是所有游戏物体（Tank,Boom,Target）的父类，其成员属性是这些游戏物体的共有属性。  

b站——https://www.bilibili.com/video/BV1Ds4y1P7g9/?spm_id_from=333.999.0.0&vd_source=a7c24098714e47cf5b5a9d219a831739

#### 使用说明

打开解决方案运行即可。