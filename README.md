# 记录学习OpenGL

## 傻瓜式九步完成开发OpenGL的环境配置

本教程适用于VS2019，高于2019应该也可以，低于2019不保证可行

1.工具->NuGet包管理器->管理解决方案的NuGet程序包

2.搜索glew下载安装

3.右键解决方案->在文件资源管理器中打开文件夹

4.进入packages文件夹，检查是否有glew.x.x.x.x以及glew.redist.x.x.x.x , x为版本号

5.同1，搜索glfw下载安装

6.同4，检查是否有glfw.x.x.x.x文件夹

7.右键解决方案下的项目->属性->配置属性->c/c++->常规->附加包含目录，编辑附加包含目录，在其中添加刚刚在packages文件夹中查看的文件夹中的include文件夹，类似如下，根据存放路径的不同，在packages之前的路径基本都不相同：

> E:\GitProject\openGL\OpenGL\packages\glfw.3.3.0.1\build\native\include
>
> E:\GitProject\openGL\OpenGL\packages\glew.1.9.0.1\build\native\include

8..接着是右键解决方案下的项目->属性->配置属性->链接器->常规->附加库目录，编辑附加库目录，在其中添加glew.lib的路径，类似如下，根据存放路径的不同，在packages之前的路径基本都不相同，具体可以进入类似路径下查看是否有glew.lib：

> E:\GitProject\openGL\OpenGL\packages\glew.1.9.0.1\build\native\lib\v110\x64\Debug\static

9.右键解决方案下的项目->属性->配置属性->链接器->输入->附加依赖项

编辑附加依赖项，添加如下：

> glew.lib
> opengl32.lib

配置完成后，即可F5运行。

可选插件，glsl插件

