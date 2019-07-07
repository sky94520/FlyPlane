# 1.简介
>本游戏是基于SDL_Engine开发的一个飞机大战的游戏，在内部采用了box2d作为物理碰撞。
# 2.不满意的地方
>1. GameScene有太多的Delegate
>2. 在何处实现bullet的数目更新,目前是在PlayerLayer::update()每次发送信息
>3. 使用物理碰撞时，都是使用的是body，来获取对应的实体，今天用Fixture，会无时无刻在碰撞。莫名其妙