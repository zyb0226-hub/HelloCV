# HelloCV
仓库
2025210498 AI+先进技术 赵奕博

一、安装配置ROS2

1.设置locale
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8

2.添加ROS2仓库
sudo apt install software-properties-common
sudo add-apt-repository universe
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

3.安装ROS2基础包
sudo apt update
sudo apt install ros-humble-ros-base -y

4.配置环境变量
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
source ~/.bashrc

5.验证安装
ros2 --help
ros2 pkg list
