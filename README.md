# 本项目正在开发中，未完成初版


# 项目介绍
这是一个用来快速购买管理Vultr网站上服务器的软件

- 基于Vultr官方API，访问速度快
- ~~针对云编译场景优化，提供了些快捷功能。~~ ~~ssh客户端写不完了，咕咕咕~~


起因是我第一次编译rootfs时花了近5个小时才完成，然后报错启动不了。。。。赶紧租台云服务器编译

# 开发进度

## 开发至
- 实现能发送api规范的get请求
- 登陆界面，实现按下按钮后对输入框内填入的API_KEY进行验证
- 功能类，创建配置文件的功能，自动将登陆界面的apikey保存到文件，并在启动时自动检测读取文件填入输入框
- 个人信息界面，展示个人用户名 邮箱 帐户余额
- 功能类，通过api获取可创建vps机型，json拆解并进行分类
- 功能类，对机型对应的可部署机方，进行分类并翻译
- 功能类，通过api获取vps可选系统类型，json拆解并进行分类
- 购买界面，让机型选择栏，可部署机房栏联动

## 待完成界面功能
- 购买界面，完成购买按钮，一键下单当前选择的vps类型 部署机房
- 个人信息界面，展示帐户内所有的实例
- 实例信息界面，展示本实例的ip 用户名 密码 
- 实例信息界面，添加销毁实例按钮
- 实例信息界面，添加一键打开putty，并使用本实例的信息进行登陆
- 实例信息界面，添加一键打开winscp，并使用本实例的信息进行登陆
- 实例信息界面，添加开关机重启按钮
- 个人信息界面，添加当实例就绪，自动弹出实例信息界面的功能
- 建立翻译更新机制，将机型对应编号，性能描述，机房代码改成写在文件内，建立git库，软件内设按钮一键拉取git上的更新文本
