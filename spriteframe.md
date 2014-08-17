## SpriteFrame 的实现与优化 ##
=====

# 简介 #
　　`SpriteFrame` 其实是为了优化贴图描画而存在的。我们知道为了更好的利用图形绘制 API，我们常常把一些细小的贴图合并到一起，然后每次只绘制这张贴图中需要的那个部分，这个就是 SpriteFrame。

　　`SpriteFrameCache` 是为了配合 `SpriteFrame` 而存在的，主要用于载入，管理，缓存 `SpriteFrame`。
　　
# 属性 #
　　先来解释几个概念:

 -  `图片`    指原先的那个小贴图
 -  `贴图`    由一堆 `图片` 组成的大图
 
 
　　SpriteFrame 中有几个必须的属性：

 -  `贴图`    指定了 `图片` 对应的 `贴图`
 -  `旋转`    表示了 `图片` 是否在 `贴图` 中旋转
 -  `贴图区域`    表示 `图片` 在 `贴图` 中的区域坐标
 -  `原始尺寸`    表示了 `图片` 的大小
 -  `图片偏移`    表示了实际的 `贴图区域` 相对于 `图片` 的偏移坐标
 
 **注意** 当 `贴图` 中存在四周透明的情况时，为了优化大小，`贴图` 会去掉这些四周的透明像素，从而使 `贴图区域` 和`原始尺寸` 可能存在不一致的情况。
 
# 实现 #
　　`SpriteFrame` 的实现较为简单，暂且略过。
　　Cocos2dx 中的 `SpriteFrameCache` 实现经历过几次重大的变化：

 -  `1.0.1` 使用 `CCDictionary` 来作为存储容器，支持从外部文件读入
 -  `2.0rc2` 增加了载入的文件列表
 -  `3.0` 使用了 `map` 代替 `CCDictionary` 来作为存储容器
 