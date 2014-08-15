# Cocos2dx 进阶 #
=============

# 序 #
　　新年伊始，总会有个目标，其他的暂且不表，多年积累下来的知识其实需要好好整理回顾一下，又正好有朋友怂恿，于是在 [51cto](http://kingzeus.blog.51cto.com/) 开了博客，打算分享一些干货。

　　先来介绍下自己，10年的游戏开发经验，号称全机种制霸，几乎开发过所有的掌机平台游戏。好多知名游戏背后的屌丝IT男。现在也混迹于手机游戏圈，依然是苦力开发，每日工作至半夜，并且乐此不疲。（求包养，可以么……）

　　cocos2dx 其实很早就接触了，用了很久。也维护了一个自有的 Cocos2dx 分支版本（还在用 opengl es 1.x），几乎重写了大部分的代码。最近，又开始维护一个 cocosbuilder 的一个分支版本。好吧，我的目标和引擎团队不同，稳定，高效，能友好的支持开发就够了，所以，我不太关注 js 脚本和 chipmunk ，lua 和 box2d 足矣。如果能坚持下去，我会按模块把有些有用的和大家分享下。

　　                           Date: 2014-01-17
                                于杭州家中
                                
                                
                                
                                
                                

# 写作动机 #
本书《Cocos2dx 进阶》是个人在空余时间写的，由于时间仓促，加上自身水平有限，不可能写的很完善，也难免出现错误，如果你发现本书中的错误，或者有更好的想法，欢迎给我反馈，我会第一时间给予答复。后续我会坚持完善这一系列的文章。也希望感兴趣的同学和我一起完成。

本书的创作出于以下两个目的：

- 传播知识，介绍有关 Cocos2dx 以及游戏编程的相关知识。希望本书可以通过对 Cocos2dx 引擎本身的内部实现分析以及优化来帮助广大的 C++ 开发者更好的学习游戏编程。
- 自我激励和提高。创作本书的另一个目的是自我激励和提高。在创作本书的过程中我会查阅大量资料，时间长了，自己学到的东西就慢慢积累多了。同时，在写作的时候为了表达清楚和准确，个别语句我会不断推敲，对自己的思维和语言表达能力很有帮助的。


> 本书还处于创作早期( 2014-01-17 提交第一行内容)，还有很多内容需要修正和完善，如果你对此感兴趣，希望能加入到我们的队伍中(虽然目前还只有我一人孤身奋战)一起来完成 《Cocos2dx 进阶》，传播知识，方便他人，提高自我吧。


# 计划 #
　　好了，目前的计划:

- cocos2dx事件体系的前世今生和实现
- 实现一个和Cocosdx兼容的unit test工具
- cocosbuilder的插件开发
- Cocos2dx的插件系统的再造
- Cocos2dx的一个mvc实现
- 如果利用C11来对引擎进行优化

……

# 本书创作发起人 #

> Yefei Fan（kingzues）

 -  微博: @kingzeus([http://www.weibo.com/2405704](http://www.weibo.com/2405704))
 -  blog：[http://kingzeus.blog.51cto.com/](http://kingzeus.blog.51cto.com/)
 -  QQ：2405704

# 贡献者名单 #

> 欢迎申请加入该名单 ;-)

# License #

The MIT License (MIT)

Copyright (c) 2014 Fan Yefei

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.



# 最后 #

希望，能坚持下来，……

所有内容同步更新:

-  [51cto](http://kingzeus.blog.51cto.com/)
-  [github](https://github.com/kingzeus/cocos2dx_gems)


