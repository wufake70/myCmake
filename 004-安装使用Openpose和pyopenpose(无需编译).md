# 安装使用openpose 和 pyopenpose(无需编译)
* ```
    OpenPose是一个开源计算机视觉库，用于进行人体姿势估计。
    它能够从图像或视频中检测和跟踪人体的关键点，如头部、手臂、腿部等，以及估计人体的姿势。
    总之，OpenPose是一个用于人体姿势估计的开源库，而PyOpenPose是它的Python绑定库，
    通过PyOpenPose可以在Python环境中方便地使用OpenPose的功能。

## 构建操作
* ```
    openpose目前最新版1.7.0
    openpose的GitHub大部分资源已经脱机，无法下载。
    使用已打包好的资源即可。
    本例使用1.7.0的资源包(2.2G)进行演示
* `openpose环境`
* ```
    GPU版 需要NVIDIA显卡，对应驱动，CUDA编译器(nvcc)，cuDNN(深度神经网络库，与nvcc对应)
    python
    cmake(cmake-gui)
    visual studio  
### 可以不编译，直接使用(包括pyopenpose)
* ```
    # 解压后目录
        d-----         2021/5/29     19:39                .github
        d-----         2021/5/29     19:39                3rdparty
        d-----         2021/5/29     19:39                build
        d-----         2021/5/29     19:39                cmake
        d-----         2021/5/29     19:39                doc
        d-----         2021/5/29     19:39                examples
        d-----         2021/5/29     19:39                include
        d-----         2021/5/29     19:39                models
        d-----         2021/5/29     19:39                python
        d-----         2021/5/29     19:39                scripts
        d-----         2021/5/29     19:39                src
        -a----        2020/11/17     13:48           2351 .gitignore
        -a----        2020/11/17     13:48            221 .gitmodules
        -a----        2020/11/17     13:48           5413 .travis.yml
        -a----        2020/11/17     13:48           1427 appveyor.yml
        -a----        2020/11/17     13:48          43800 CMakeLists.txt
        -a----        2020/11/17     13:48           9686 LICENSE
        -a----        2020/11/17     13:48          16504 README.md

    # 直接使用 编译好的openposedemo.exe
    # 将根目录下的 'models'复制到'build'中，cmd进入build目录，将'x64\Debug'下所有文件复制到 'bin'
        xcopy /s /y models\* build\models\
        cd build
        xcopy /s /y "x64\Debug\*" "bin\"
        bin\OpenPoseDemo.exe --video ..\examples\media\video.avi
    # 弹出带有骨架视频窗口 即成功，
* [更多使用请看](https://github.com/CMU-Perceptual-Computing-Lab/openpose)
* ```
    # 使用python 调用openpose
    # 需要注意 'build\python\openpose\Debug'中的 pyopenpose.cp38-win_amd64.pyd 文件。
    # .pyd 文件是在 Windows 平台上使用的 Python 扩展模块文件。它是通过使用 C/C++ 编写的 Python 扩展模块的编译结果。
    # cp38-win_amd64表示需要使用python3.8.x的解释器，才能可以调用他(import pyopenpose as op)。
    # 同时还需要使用 opencv-python库，pip下载即可。
    # cmd进入build文件夹，并将 bin中所有文件 复制到 'python\openpose\Debug\'
        cd build
        xcopy /s/y bin\* python\openpose\Debug\
        cd ..\examples\tutorial_api_python\
        python 01_body_from_image.py        # python 3.8.x
    # 弹出带有骨架视频窗口 即成功，
    # 需要注意 py中两行代码，才可正确导入 pyopenpose库
        sys.path.append(dir_path + '/../../build/python/openpose/Debug');
        os.environ['PATH']  = os.environ['PATH'] + ';' + dir_path + '/../../build/x64/Debug;' +  dir_path + '/../../build/bin;'
* [更多使用请看](https://github.com/CMU-Perceptual-Computing-Lab/openpose)