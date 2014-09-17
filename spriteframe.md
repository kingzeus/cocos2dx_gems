# SpriteFrame 的实现与优化 #
=====

## 简介 ##
　　`SpriteFrame` 其实是为了优化贴图描画而存在的。我们知道为了更好的利用图形绘制 API，我们常常把一些细小的贴图合并到一起，然后每次只绘制这张贴图中需要的那个部分，这个就是 SpriteFrame。

　　`SpriteFrameCache` 是为了配合 `SpriteFrame` 而存在的，主要用于载入，管理，缓存 `SpriteFrame`。
　　
## 属性 ##
　　先来解释几个概念:

 -  `set`          集合 ，一般对应一个 `plist` 的数据文件或者数据库中的一组数据 -  `alias`        别名，对应了某个 `SpriteFrame` -  `texture`      贴图，一个 `set` 一般存在一个贴图 -  `textureName`  贴图名称，和贴图一一对应（绑定） -  `SpriteFrame`  图片，指贴图中的一块区域
 关系:
-  `set` : `SpriteFrame`   是一对多的关系-  `SpriteFrame` : `alias` 是一对多的关系-  `set` : `texture`       是一对一的关系
 
 
 
　　SpriteFrame 中有几个必须的属性：

 -  `贴图`        指定了 `图片` 对应的 `贴图`
 -  `集合名称`    图片对应的集合的名称 
 -  `旋转`        表示了 `图片` 是否在 `贴图` 中旋转
 -  `贴图区域`    表示 `图片` 在 `贴图` 中的区域坐标
 -  `原始尺寸`    表示了 `图片` 的大小
 -  `图片偏移`    表示了实际的 `贴图区域` 相对于 `图片` 的偏移坐标
 
 **注意** 当 `贴图` 中存在四周透明的情况时，为了优化大小，`贴图` 会去掉这些四周的透明像素，从而使 `贴图区域` 和`原始尺寸` 可能存在不一致的情况。
 
## 实现 ##
　　`SpriteFrame` 的实现较为简单，暂且略过。

　　Cocos2dx 中的 `SpriteFrameCache` 实现经历过几次重大的变化：

 -  `1.0.1` 使用 `CCDictionary` 来作为存储容器，支持从外部文件读入
 -  `2.0rc2` 增加了载入的文件列表
 -  `3.0` 使用了 `map` 代替 `CCDictionary` 来作为存储容器
 
 

## SpriteFrameCache
 `SpriteFrameCache` 实际上就是 `spriteFrame` 的管理器。主要实现了以下的功能：
 
  -  载入，从 `plist` 载入 `spriteFrame`
  -  管理,对所有的 SpriteFrame 进行统一的管理,可以移出不再使用的
  

## 优化 
优化大致包括了以后的部分:


### 代码风格调整
具体可以参考 [项目的风格指南](styleguide/index.md)


### SpriteFrame 内部计算优化 (未完成)

### SpriteFrameCache singleton 模式替换
使用了 kzlib::TSingleton

### SpriteFrameCache 内部使用容器替换,原则就是尽量使用 STL 容器
 -  set 替换成 unordered_set
 -  CCDictionary 替换成 unordered_map

因为 unordered 系列容器内部使用了 hash 值，因为比字符串更加有效率。又是 STL 容器，使用方便，稳定高效。

### SpriteFrameCache 内部逻辑调整
-  在 SpriteFrame 内部增加了 `setName` ,优化了 SpriteFrameCache 对于 `set` 的管理
-  优化了 set 的载入和释放

### SpriteFrameCache 支持贴图创建
支持了从贴图到 SpriteFrame 的转换,保证了使用的统一


### SpriteFrameCache 支持更多的数据格式 (未完成)
### SpriteFrameCache 支持贴图的后载入 (未完成)


## 代码
 -  [spriteframe.h](code/spriteframe.h)
 -  [spriteframe.cpp](code/spriteframe.cpp)
 -  [spriteframecache.h](code/spriteframecache.h)
 -  [spriteframecache.cpp](code/spriteframecache.cpp)
 
 
 ---- 
<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/3.0/cn/"><img alt="知识共享许可协议" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/3.0/cn/88x31.png" /></a><br />本作品采用<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/3.0/cn/">知识共享署名-非商业性使用-相同方式共享 3.0 中国大陆许可协议</a>进行许可。 