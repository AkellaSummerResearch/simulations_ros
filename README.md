# simulations_ros
Repositoy for our sim

steps for installing

## 1. Install ROS 

   First, install **ROS Kinetic** using the following instructions: http://wiki.ros.org/kinetic/Installation/Ubuntu 

   Do _Desktop Install_  
   Make sure to follow all the way through the installation (until _Step 1.7_ at the end of the page)

## 2. Set Up Catkin workspace 

We use catkin build instead of catkin_make. Please install the following: 
```
sudo apt-get install python-wstool python-rosinstall-generator python-catkin-tools
```

Then, initialize the catkin workspace: 
```
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws
catkin init
```

## 3. Dependencies installation 

Install `mavros` and `mavlink` from source: 
```
cd ~/catkin_ws
wstool init ~/catkin_ws/src

rosinstall_generator --upstream mavros | tee /tmp/mavros.rosinstall
rosinstall_generator mavlink | tee -a /tmp/mavros.rosinstall
wstool merge -t src /tmp/mavros.rosinstall
wstool update -t src
rosdep install --from-paths src --ignore-src --rosdistro `echo $ROS_DISTRO` -y

catkin build
```

## 4. Clone our ROS package repository 

```
cd ~/catkin_ws/src 
git clone https://github.com/AkellaSummerResearch/simulations_ros.git
```

## 5. Build instructions 
   Inside `catkin_ws`, run `catkin build`

```
cd ~/catkin_ws 
catkin build 
```


## 6. Install Gazebo

Setup your computer to accept software from http://packages.osrfoundation.org:
```
sudo sh -c 'echo "deb http://packages.osrfoundation.org/gazebo/ubuntu-stable `lsb_release -cs` main" > /etc/apt/sources.list.d/gazebo-stable.list'
```

Setup keys:
```
wget http://packages.osrfoundation.org/gazebo.key -O - | sudo apt-key add - 
```

Reload software list: 
```
sudo apt-get update
```

Install Gazebo: 
```
sudo apt-get install gazebo7 libgazebo7-dev
```

Install ROS plugins: 
```
sudo apt install ros-kinetic-gazebo-ros ros-kinetic-gazebo-plugins
```



## 6. Install Px4 

run ubuntu_sim_common_deps.sh
```
cd ~/cd catkin_ws/src/simulations_ros/scripts/
./ubuntu_sim_common_deps.sh
sudo apt install libprotobuf-dev protobuf-compiler
cd ~/Firmware 
make posix_sitl_default gazebo
```

