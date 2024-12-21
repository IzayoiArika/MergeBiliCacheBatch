以Android系统为例，通过文件管理器进入/storage/emulated/0/Android/data/tv.danmaku.bili/download/文件夹。
该文件夹下有一大堆以数字命名的文件夹，这就是B站的缓存文件夹。把这些文件夹全部压缩打包，发送至电脑，解压到你喜欢的位置。
将本程序（bilimerge.exe）复制到缓存文件夹同级目录中（例如，你的缓存文件夹位于C:\Downloads，那么本程序也应位于C:\Downloads），然后运行本程序即可。

哦对，这玩意使用了C++17引入的filesystem，如果要自己修改编译的话请确保__cplusplus>=201703L。
