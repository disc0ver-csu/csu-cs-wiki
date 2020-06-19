
# 理想滤波器

频率域平滑锐化常用的几个滤波器的数学表达和实现都已经在[数字图像处理——频率域平滑锐化图像常用滤波器](https://www.edwardzcn98yx.com/post/e371c683.html)一文中实现。

之前我们讨论到了振铃现象，本文中的实验主要是动手实现测试了 ILPF 对图片的模糊效果及其振铃现象，并且跟随课本尝试解释 ILPF 在空间域的振铃特性。

## 理想低通滤波器 ILPF

描述如下

$$
H_{ILPF}(u,v) = \left \{
\begin{aligned}
1, & D(u,v) \le D_0 \\
0, & D(u,b) > D_0
\end{aligned}
\right.
$$

其中$D_0$是一个正常数，$D(u,v)$表示频率域中的点$(u,v)$距离频率域中心$(\frac{P}{2},\frac{Q}{2})$的距离。

## 理想高通滤波器 IHPF

描述如下

$$
H_{IHPF}(u,v) = \left \{
\begin{aligned}
0, & D(u,v) \le D_0 \\
1, & D(u,b) > D_0
\end{aligned}
\right.
$$

## 代码实现

代码实现`getIdealMask()`也在[数字图像处理——频率域平滑锐化图像常用滤波器](https://www.edwardzcn98yx.com/post/e371c683.html)给出，在此不再转述。

两组测试均为 100x100 大小，截至半径为 20 的低通和高通滤波器实验结果。

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/TypeOfFilter/3.png)

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/TypeOfFilter/4.png)

## 使用一个 ILPF 平滑图像

```python
def getIdealFilterPassImg(input_img : np.array, filter_type : str , filter_d0, size = None):
    assert filter_type in ("lpf","hpf")
    # 内部进行填充 （mask大小与原图相等 进行2K-1的0填充）
    pad_img = getPaddingImg(input_img,input_img.shape,"corner")

    f_img = np.fft.fft2(input_img , s = size)
    shift_img = np.fft.fftshift(f_img)
    mask_shift_img = getIdealMask(f_img.shape,filter_d0,filter_type)
    new_shift_img = mask_shift_img*shift_img
    new_manitude_img = 20*np.log(np.abs(new_shift_img+eps))
    new_f_img = np.fft.ifftshift(new_shift_img)
    new_img = np.fft.ifft2(new_f_img)
    new_img = np.abs(new_img)

    # 内部进行裁剪
    new_img = cutOriginalImg(new_img, input_img.shape, "corner")
    return new_img,new_manitude_img,mask_shift_img

# 使用书上例子，cv库读取图像
original_img = cv2.imread('./DIP3E_Original_Images_CH04/Fig0441(a)(characters_test_pattern).tif',0)
# 设定截止半径
d_list = [10,30,60,160,460]

for d in d_list:
    smmoth_img,manitude_img,mask_img = getIdealFilterPassImg(original_img, "lpf" , d)
    showTwoImg(smmoth_img,manitude_img,f"Smooth Img with $D_0$ = {d}", f"Manitude with $D_0$ = {d}")
```

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/1.png)

<!--more-->

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/2.png)

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/3.png)

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/4.png)

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/5.png)

# 振铃现象

由上图可以看出随着阈值增大，频谱中保留功率的增大，图像细节逐渐明晰，模糊效果越来越差。这说明我们的滤波器是成功的（不过这里与课本 P171 图比较会清晰一些，不清楚原因）

另外，我们也可以很明显的发现**振铃现象**，间隙处原本统一的纹理由于模糊变得有明暗起伏。而随着被滤去的高频内容的数量的减少，图像的纹理变得越来越好，甚至我们仔细看第三幅图，也能发现振铃现象的纹理，课本是这么评价振铃现象和 ILPF 的。

> 这种振铃现象是理想滤波器的一种特性，从这个例子我们可以清楚地看到，理想低通滤波器并不是非常实用。然而，作为滤波概念发展的一部分，研究这种滤波器的特性非常有用。

## 振铃现象的一些见解

```python
# 绘制空间域表示图和水平线灰度剖面图

for d in d_list:
    fre_mask=getIdealMask((688,688),d,"lpf")
    spa_mask=frequencyToSpatial(fre_mask)
    X = [i for i in range(spa_mask.shape[0])]
    Y = spa_mask[spa_mask.shape[0]//2]
    plt.figure(figsize=(8,4))
    ax1 = plt.subplot(121)
    ax2 = plt.subplot(122)
    ax1.set_title(f"Spatial Img with $D_0 = {d}$")
    ax2.set_title(f"Grayscale with $D_0 = {d}$")
    ax1.imshow(spa_mask,cmap = "gray")
    ax2.plot(X,Y)
    ax2.spines['left'].set_color('none')
    ax2.spines['top'].set_color('none')
    ax2.spines['right'].set_color('none')
    ax2.set_yticks([])
    ax2.set_yticklabels([])
```

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/6.png)

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/7.png)

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/8.png)

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/9.png)

![png](https://eddyblog.oss-cn-shenzhen.aliyuncs.com/ImageProcess/IdealFilter/10.png)

分别对应了上面的阈值，观察其滤波器的空间与表示，在$D_0$较小的时候有很明显的波动函数形状。

> ILPF 的模糊和振铃特性可用卷积定理来解释。由于 ILPF 在频率域的剖面图类似于盒状滤波器，因此可以预料相应空间滤波器具有 sinc 函数形状。空间域滤波可通过$h(x,y)$于图像卷积来实现。讲图像中的每个像素想象为一个离散冲击，它的强度与所在位置的灰度成正比。一个 sinc 函数与一个冲激卷积就是在冲激处复制这个 sinc 函数。**sinc 函数的中心波瓣是引起模糊的主因，而外侧较小的波瓣是造成振铃的主要原因。sinc 函数“展开度”与$H(u,v)$半径成反比，所以$D_0$越大，空间 sinc 函数就趋近于一个卷积时不会导致模糊但也不会产生振铃的冲激**
