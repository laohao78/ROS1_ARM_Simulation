# ROS1_ARM_Simulation

<p align="center">
  <strong>ROS 机器人视觉感知与手眼标定仿真套</strong>
</p>

<p align="center">
  <a href="#快速开始"><strong>快速开始</strong></a> •
  <a href="#实验流程"><strong>实验流程</strong></a> •
  <a href="#常见问题"><strong>FAQ</strong></a> •
  <a href="#贡献指南"><strong>贡献</strong></a>
</p>
<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License: MIT"></a>
  <a href="https://github.com/Suyixiu/robot_sim"><img src="https://img.shields.io/badge/Based%20on-Suyixiu%2Frobot__sim-blue" alt="Based on Suyixiu/robot_sim"></a>
</p>


覆盖机器人研究全流程的 Gazebo 仿真环境，集成相机标定、深度配准、手眼标定、智能抓取、数据采集等核心实验。适合课程教学、项目参考和工程实践。

**核心内容：**

- ✅ **相机标定**（RGB/IR）
- ✅ **深度图配准**
- ✅ **手眼标定**（eye-on-hand）
- ✅ **抓取实验**（几何法 + 深度学习方法 GPD）
- ✅ **数据采集**流程

| 项目总览 |
| :--: |
| ![](docs/总.png) |

> **原始项目作者与核心思路参考：**
> - [Suyixiu/robot_sim](https://github.com/Suyixiu/robot_sim)
> - [踩坑过程 CSDN 博客](https://blog.csdn.net/qq_38620941/article/details/125321347)

## 📋 目录

- [📚 项目亮点](#项目亮点)
- [🔧 环境要求](#环境要求)
- [🚀 快速开始](#快速开始)
- [📂 项目结构](#项目结构)
- [🔬 实验流程](#实验流程)
- [❓ 常见问题](#常见问题)
- [📖 进阶文档](#进阶文档)
- [🤝 贡献指南](#贡献指南)
- [🙏 致谢](#致谢)
- [⚖️ 许可说明](#许可说明)

## 📚 项目亮点

| 特性 | 描述 |
|-----|------|
| 🎓 **教学友好** | 完整工程化设计，将多个机器人基础实验有机串联。适合大学课程教学、专业培训和自学进阶 |
| 🔬 **方法对比** | 同时实现传统几何法与深度学习（GPD）两种抓取算法，便于深入理解不同方法的原理与优缺点 |
| 🛠️ **开箱即用** | 基于成熟的 Gazebo + MoveIt + ROS 生态，高度集成，无需硬件投入即可完整学习机器人工程 |
| 📊 **完整数据管道** | 从仿真场景设计、多传感器数据采集、标定参数验证到模型训练，形成闭环学习链路 |

## 🔧 环境要求

### 💻 系统环境

- **操作系统**：Ubuntu 16.04+ （推荐 18.04 或 20.04）
- **ROS 版本**：Kinetic / Melodic / Noetic
- **依赖工具**：
  - Gazebo（≥ 7.0）
  - MoveIt
  - OpenCV（≥ 3.0，用于深度图配准）
  - Python 3.6+

### 📦 依赖包

仓库中已包含或关联以下核心开源包：

| 包名 | 用途 | 来源 |
|-----|------|------|
| `aruco_ros` | ArUco 码识别与位姿估计 | [pal-robotics](https://github.com/pal-robotics/aruco_ros) |
| `easy_handeye` | 手眼标定框架 | [IFL-CAMP](https://github.com/IFL-CAMP/easy_handeye) |
| `gpd` / `gpd_ros` | 深度学习抓取算法 | [atenpas/gpd](https://github.com/atenpas/gpd) |
| `universal_robot` | UR 机械臂驱动包 | [ros-industrial](https://github.com/ros-industrial/universal_robot) |
| `roboticsgroup_gazebo_plugins` | Gazebo 物理插件增强 | 仓库内 |

> 💡 **首次使用提示**：建议在干净的 Catkin 工作空间中编译，避免旧缓存影响。如使用 GPD，特别注意其编译要求。

## 🚀 快速开始（5 分钟入门）

### 1️⃣ 编译与环境

~~~bash
# 在 Catkin 工作空间根目录执行
cd ~/catkin_ws
catkin_make
~~~

### 2️⃣ 加载环境变量

~~~bash
source devel/setup.bash
~~~

### 3️⃣ 可选：复制 ArUco 模型到 Gazebo

~~~bash
cp -r src/robot_sim/experiment/hand_eye_calibration/urdf/aruco ~/.gazebo/models
~~~

这一步是为手眼标定实验准备的标记物模型。

### 4️⃣ 运行第一个实验 —— 相机标定 🎥

~~~bash
# 启动 Gazebo 加载相机和标定板
roslaunch robot_sim camera_calibration.launch
~~~

稍等几秒，Gazebo 会加载场景，你应该能看到相机和棋盘。

---

## 📂 项目结构

~~~
arm_all_sim/
├── src/
│   ├── robot_sim/                          # 核心功能包
│   │   ├── experiment/
│   │   │   ├── camera_calibration/         # 相机标定实验
│   │   │   ├── depth_image_registration/   # 深度配准实验
│   │   │   ├── hand_eye_calibration/       # 手眼标定实验
│   │   │   ├── grasp/                      # 抓取实验（几何法 + GPD）
│   │   │   └── data_collection/            # 数据采集
│   │   ├── launch/                         # ROS 启动文件
│   │   ├── urdf/                           # 模型描述文件
│   │   └── src/                            # C++ 源码
│   ├── aruco_ros/                          # ArUco 识别包
│   ├── easy_handeye/                       # 手眼标定框架
│   ├── gpd_ros/                            # GPD 抓取包
│   ├── universal_robot/                    # UR 机械臂包
│   └── roboticsgroup_gazebo_plugins/       # Gazebo 物理插件
├── devel/                                  # 编译输出
├── build/                                  # 编译文件
├── docs/                                   # 文档与图片
└── README.md
~~~

## 🔬 实验流程

本项目围绕机器人感知与操作的完整链路设计了 5 个核心实验，建议按顺序执行。

---

### 📷 实验 1：相机标定

**🎯 目标**：计算 RGB 和 IR 相机的内参矩阵，这是后续所有视觉任务的基础

**📝 方式 A：脚本采图 + 脚本计算内参**

~~~bash
# 启动 Gazebo 加载相机与标定板（棋盘 7x6，每格 0.01m）
roslaunch robot_sim camera_calibration.launch

# 另起终端：移动标定板并保存照片（每秒随机移动一次）
rosrun robot_sim camera_calibration

# 采集足够多的照片后（建议 30+ 张），Ctrl+C 停止
# 然后运行脚本计算相机内参
cd src/robot_sim/experiment/camera_calibration/scripts
python3 camera_calibration.py

# 查看计算结果
python3 check.py
~~~

**🔄 方式 B：ROS 官方工具（实时交互式标定）**

~~~bash
# 方式 A 采集的图片不足，可用该工具进行实时标定
# 注意修改 --size 和 --square 参数以匹配你的棋盘

# RGB 相机
rosrun camera_calibration cameracalibrator.py --size 7x6 --square 0.01 \
  image:=/camera/rgb/image_raw camera:=/camera/rgb

# IR 相机
rosrun camera_calibration cameracalibrator.py --size 7x6 --square 0.01 \
  image:=/camera/ir/image_raw camera:=/camera/ir
~~~

⚡ **提示**：若需自定义棋盘尺寸（如 9x7 或更大），编辑 `robot_sim/experiment/camera_calibration/urdf/create_chessboard.py` 的参数后运行脚本即可生成。标定板大小直接影响标定精度。

---

### 🔗 实验 2：深度图配准

**🎯 目标**：计算 RGB 与 IR 相机之间的旋转矩阵与平移向量，用于后续的多传感器融合

**📋 前置条件**：已完成 **实验 1**，生成 `RGB_cameraintrinsic_parameters.npz` 和 `IR_cameraintrinsic_parameters.npz`

~~~bash
# 计算配准矩阵（输出到 Registration_matrix.txt）
cd src/robot_sim/experiment/depth_image_registration/scripts
python3 depth_image_registration.py

# 验证配准效果（编译并运行 C++ 程序）
cd ../src
g++ ./depth_image_registration.cpp -o depth_image_registration \
  $(pkg-config --cflags --libs opencv4)
./depth_image_registration
~~~

✨ **验证**：程序会实时显示配准前后的深度图对齐效果。误差应在 1-2 像素内。

---

### 🦾 实验 3：手眼标定（Eye-on-Hand）

**🎯 目标**：通过 ArUco 码与机械臂运动学，自动计算末端执行器（End-Effector）相对于相机的 6D 变换矩阵

**📌 应用场景**：一旦获得手眼矩阵，机械臂便能根据相机中物体的像素坐标准确计算出其在机械臂坐标系中的实际位置，是实现视觉伺服和精准抓取的必要前提

**步骤**：

1️⃣ **启动机械臂和 Gazebo**

~~~bash
roslaunch yixiuge_ur10_moveit_config yixiuge_ur_moveit.launch
~~~

稍等机械臂加载完成（通常需要 10-15 秒）。

2️⃣ **启动手眼标定程序**

~~~bash
roslaunch robot_sim hand_eye_calibration.launch
~~~

3️⃣ **触发 ArUco 识别发布**

~~~bash
# 因为 aruco_ros 是"懒发布"（Lazy Publisher），需要有订阅者
# 打开另一个终端启动图像查看器
rqt_image_view
# 在弹出的窗口中选择 /aruco_tracker/result 话题
~~~

4️⃣ **采集标定点**

- 在 RViz 中拖动虚拟球体移动机械臂
- 采集至少 17 个点（建议 25-40 个以获得更好精度）
- 点击 **Calibrate** 计算变换矩阵
- 点击 **Save** 保存标定结果

📊 **标定结果查看**：

```yaml
位置：~/.ros/easy_handeye/easy_handeye_eye_on_hand.yaml
内容：包括平移向量和旋转四元数
```

5️⃣ **验证标定结果**

~~~bash
# 启动机械臂
roslaunch yixiuge_ur10_moveit_config yixiuge_ur_moveit.launch

# 查看真实坐标系变换（URDF 中设置的值）
rosrun tf tf_echo yixiuge_ee_link camera_rgb_optical_frame

# 启动标定结果发布
roslaunch robot_sim hand_eye_calibration_result.launch
~~~

---

### ✋ 实验 4：机械臂抓取（对比学习）

**🎯 目标**：基于已标定的相机与手眼矩阵，演示两种不同范式的抓取方法，体验从传统方法向学习方法的演进

**前置准备**：启动仿真环境并加载物体

~~~bash
# 终端 1：启动场景
roslaunch robot_sim grasp_world.launch

# 终端 2：加载物体到 Gazebo 中
source devel/setup.bash
cd src/robot_sim/experiment/grasp/scripts
python3 spawn_objects.py
~~~

#### 🔶 方法 1：传统几何法抓取

**💡 原理**：
1. 通过背景掩膜分割出物体
2. 提取物体轮廓并计算二阶矩
3. 用 PCA 计算主轴与副轴方向
4. 在副轴与轮廓的交点处生成抓取矩形

~~~bash
rosrun robot_sim geometric_method_grasp
~~~

**✅ 优势**：
- ⚡ 算法简单，实时性好（毫秒级响应）
- 🧠 易于理解与调试
- 💪 对规则形状（圆形、长条形）鲁棒

**⚠️ 局限**：
- 对图像分割质量敏感
- 难以处理重叠或遮挡物体
- 仅适用于单个物体场景

#### 🟦 方法 2：深度学习方法（GPD）

**💡 原理**：
1. 从点云中随机或网格采样候选位置
2. 在每个位置生成 6D 抓取候选（位置 + 角度）
3. 用预训练的卷积神经网络评估每个候选的成功概率
4. 返回置信度最高的抓取位姿

~~~bash
# 终端 3：启动 GPD 推理服务
roslaunch robot_sim gpd_run.launch type:=2 topic:=/cloud_sample

# 终端 4：启动抓取程序
rosrun robot_sim GPD_method_grasp
~~~

**✅ 优势**：
- 🧠 数据驱动，能处理复杂场景与遮挡
- 🎯 抓取成功率更高
- 🔧 可通过数据增强持续改进

**⚠️ 局限**：
- ⏱️ 推理时间较长（秒级，需 GPU 加速）
- 📊 需要大量标注数据训练
- 🎓 超参数调优复杂

#### 🔍 GPD 自检与故障排除

如遇到 GPD 运行报错，按以下步骤自检：

~~~bash
catkin_make --only-pkg-with-deps robot_sim
roslaunch robot_sim gpd_run.launch type:=2 topic:=/cloud_sample
roslaunch robot_sim test_gpd.launch
~~~

⚠️ **常见 GPD 问题**：
- 版本冲突：建议使用 GPD 1.5.0 或 2.0.0，避免中间版本
- Caffe 模型路径错误：检查 launch 文件中的配置路径
- CUDA 版本不匹配：需要 CUDA 10.0+

---

### 📊 实验 5：数据采集与标注

**🎯 目标**：自动生成机械臂多视角观察场景的RGB/深度/红外图像、点云以及对应的机械臂位姿标签，为后续的模型训练准备数据集

~~~bash
# 启动场景
roslaunch robot_sim grasp_world.launch

# 加载物体
source devel/setup.bash
cd src/robot_sim/experiment/grasp/scripts
python3 spawn_objects.py

# 启动数据采集程序
rosrun robot_sim data_collection
~~~

📤 **生成的数据集结构**：

```
data_collection_output/
├── images/
│   ├── rgb_*.png           # RGB 彩色图像
│   ├── depth_*.png         # 深度图（16-bit）
│   └── ir_*.png            # 红外热图像
├── point_clouds/
│   └── cloud_*.pcd         # 3D 点云数据（PCD 格式）
├── poses/
│   └── poses_*.json        # 机械臂 6D 位姿和相机 K 矩阵
├── labels/
│   └── labels_*.json       # 物体分类标签与 3D 边界框
└── config.yaml             # 采集参数与传感器配置
```

💾 **用途**：
- 训练自定义深度学习抓取模型
- 3D 物体检测与实例分割
- SLAM 与视觉里程计测试

## ❓ 常见问题与故障排除

### ❌ Q1：手眼标定时看不到 ArUco 识别结果？

**✅ 解决方案**：aruco_ros 使用"懒发布"机制，只有当有订阅者时才会发布数据。

**解决方案**：
1. 确保 `rqt_image_view` 已启动
2. 在 rqt 窗口中选择 `/aruco_tracker/result` 话题
3. 检查 launch 文件中 ArUco 参数（ID、大小等）是否正确

~~~bash
# 调试：查看所有可用话题
rostopic list | grep aruco

# 查看话题发布频率
rostopic hz /aruco_tracker/result
~~~

### ❌ Q2：GPD 报错或无法生成抓取位姿？

**✅ 解决方案**：GPD 是整个项目中最容易出问题的部分。按以下步骤排查：

**步骤 1：检查 GPD 安装**

~~~bash
catkin_make --only-pkg-with-deps robot_sim
roslaunch robot_sim test_gpd.launch
~~~

如果 test_gpd 能正常运行，说明 GPD 库已正确安装。

**步骤 2：检查 launch 配置**

打开 `robot_sim/launch/gpd_run.launch`，确认：
- Caffe 模型文件路径是否正确
- 点云话题名称 (`topic:=/cloud_sample`) 是否与发布者一致
- GPU/CPU 计算资源配置

**步骤 3：检查点云话题**

~~~bash
rostopic list | grep cloud
rostopic hz /cloud_sample
~~~

**常见版本问题**：
- ✅ GPD 1.5.0 - 推荐使用
- ✅ GPD 2.0.0 - 较新但配置更复杂
- ❌ 1.6.x - 中间版本，可能有 bug

### ❌ Q3：Gazebo 中抓取时物体抖动、滑落或被夹坏？

**✅ 解决方案**：这是位置控制（而非力控制）导致的常见问题。

**解决方案**：
1. 启用项目中的 gazebo-pkgs 插件（已集成）
2. 调整夹爪接触检测阈值
3. 增加抓取阻尼参数

相关文件：`robot_sim/package/gazebo-pkgs/` 和 URDF 中的插件配置。

### ⚠️ Q4：编译失败，出现 `package not found` 或 `find_package` 错误？

**✅ 解决方案**：通常是依赖包未下载或路径问题。

~~~bash
# 方案 1：重新安装依赖
rosdep install --from-paths src --ignore-src --rosdistro=<你的ROS发行版>

# 方案 2：检查包是否在 src 目录
find src -name "package_name" -type d

# 方案 3：清除编译缓存后重新编译
rm -rf build devel
catkin_make
~~~

### ⚠️ Q5：Gazebo 或 RViz 启动缓慢，运行卡顿甚至崩溃？

**✅ 解决方案**：通常是 GPU 或 CPU 资源不足。

**优化建议**：
- 关闭不必要的 Gazebo 插件
- 降低物理模拟频率
- 减少模型纹理分辨率
- 检查是否有其他进程占用资源

~~~bash
# 查看系统资源使用
htop
nvidia-smi  # 若有 NVIDIA GPU
~~~

### ⚠️ Q6：相机标定误差大，后续手眼标定精度不满足要求？

**✅ 解决方案**：标定质量取决于采集图像的数量和质量。

**改进建议**：
- 采集 50+ 张图片（覆盖相机视野的各个区域）
- 确保棋盘清晰可见，避免模糊和遮挡
- 变换棋盘位置时保持足够的角度变化
- 使用尽可能多的不同深度距离

### ℹ️ Q7：如何自定义抓取物体、修改场景或添加新的传感器？

**✅ 解决方案**：修改对应的 launch 文件和 URDF 模型。

~~~bash
# 相关文件位置：
robot_sim/launch/grasp_world.launch       # 场景配置
robot_sim/urdf/                            # 物体模型
src/robot_sim/experiment/grasp/scripts/spawn_objects.py  # 物体生成脚本
~~~

### ℹ️ Q8：如何将仿真实验迁移到真实机器人？

**✅ 解决方案**：需要适配真实硬件的驱动和配置。基本步骤：
1. 将 gazebo 命令替换为真实机器人驱动
2. 调整相机话题名称和参数
3. 重新运行标定流程以适应真实环境

这部分超出当前项目范围，建议参考具体机器人品牌的官方文档。

## 📖 进阶文档

欲了解更深层的算法原理、完整的数学推导、实验截图与可视化效果，请参考：

📄 **[src/robot_sim/readme.md](src/robot_sim/readme.md)**
- 相机标定的数学模型与内参计算
- 深度图配准的几何变换原理
- 手眼标定的位姿求解算法（DH 参数法与直接求解）
- 两种抓取方法的详细实现细节与对比分析
- 完整的实验截图与运行演示

## 🤝 贡献指南

热烈欢迎各类形式的贡献：Issue、Pull Request、文档改进、示例代码、Bug 报告等！

### 📋 贡献流程

1. **Fork** 本仓库
2. **创建特性分支** (`git checkout -b feature/amazing-feature`)
3. **本地测试**：确保你的改动能够编译和运行
4. **提交清晰的 PR 描述**：说明改动内容、测试方法和预期效果
5. **通过 CI 检查**（如有）

### 💡 贡献建议与规范

- 发现 bug 时优先提 Issue 进行讨论
- 大规模重构前请在 Issue 中提案
- 新增功能时请附带相关测试和文档更新
- 遵循项目已有的代码风格和注释规范

## 🙏 致谢

本项目的完成离不开以下优秀开源项目和社区的支持，特此致谢：

- **[aruco_ros](https://github.com/pal-robotics/aruco_ros)** - ArUco 码识别框架
- **[easy_handeye](https://github.com/IFL-CAMP/easy_handeye)** - 手眼标定工具包
- **[gpd](https://github.com/atenpas/gpd)** - 深度学习抓取算法
- **[universal_robot](https://github.com/ros-industrial/universal_robot)** - UR 机械臂驱动
- **[gazebo-pkgs](https://github.com/JenniferBuehler/gazebo-pkgs)** - Gazebo 物理插件增强
- **[dh_gripper_ros](https://github.com/DH-Robotics/dh_gripper_ros)** - DH 机器人夹爪驱动

🌟 **特别致谢**：感谢原始项目作者 [Suyixiu](https://github.com/Suyixiu) 的创意与无私贡献，本项目在其基础上进行了工程化完善和文档改进。

## ⚖️ 许可说明

**当前状态** ✅：本项目采用 **MIT License** 开源许可证。

**许可证文件**：[LICENSE](LICENSE)

### 📜 许可证说明

**MIT License 的含义**：
- ✅ 可自由使用、修改、分发
- ✅ 可用于商业目的
- ✅ 可私有修改后使用
- ⚠️ 需保留原作者版权声明
- ⚠️ 不提供任何担保

### 📋 依赖包许可证

本项目的所有依赖包均已采用开源许可证配置，使用本项目时请遵循各依赖包的许可要求：

| 包名 | 许可证 | 出处 |
|-----|--------|------|
| `aruco_ros` | BSD | [pal-robotics](https://github.com/pal-robotics/aruco_ros) |
| `easy_handeye` | BSD | [IFL-CAMP](https://github.com/IFL-CAMP/easy_handeye) |
| `gpd` | BSD | [atenpas/gpd](https://github.com/atenpas/gpd) |
| `universal_robot` | BSD | [ros-industrial](https://github.com/ros-industrial/universal_robot) |
| `roboticsgroup_gazebo_plugins` | BSD | 仓库内 |

> 💡 **提示**：MIT 和 BSD 许可证兼容，可直接集成使用。

---

<p align="center">
  ⭐ 如果本项目对你有帮助，欢迎 Star 和分享！
</p>
