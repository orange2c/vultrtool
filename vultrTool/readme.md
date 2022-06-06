文件介绍
## 界面类
- pagelogin 打开软件弹出的第一个登陆窗口
- pageinformation 登陆成功后，显示个人账户信息的
- pagebug 在个人信息界面点击购买服务器按钮后，进入此界面，列出可购买信息

## 基本功能类
- linkedlist 链表，实现了一个链表类，供需要的其他类来调用
- spider 爬虫类，内含构建get post请求，对json数据进行提取等功能
- vultr 主类，负责调用其他各种类，存储账户信息，更新服务器信息等

## 服务器的信息类
主要用于存储信息，方便主类进行操作
- vpsmodel 可购买的机型配置信息
- vpsos 可选择的镜像
- vpsocations 可部署地区
- vpsinstances  用户已创建的实例

