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

Give permissions to your uses:
```
sudo chown $USER .gazebo/
```


## 6. Install Px4 

run ubuntu_sim_common_deps.sh
```
cd ~/catkin_ws/src/simulations_ros/scripts/
./ubuntu_sim_common_deps.sh
sudo apt install libprotobuf-dev protobuf-compiler libignition-math2-dev
cd ~/Firmware 
make posix_sitl_default gazebo
```
## 7. Add paths to .bashrc

```
export GAZEBO_MODEL_PATH=${GAZEBO_MODEL_PATH}:~/catkin_ws/src/simulations_ros/models
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/Firmware
export ROS_PACKAGE_PATH=$ROS_PACKAGE_PATH:~/Firmware/Tools/sitl_gazebo
source ~/Firmware/Tools/setup_gazebo.bash ~/Firmware ~/Firmware/build/posix_sitl_default
```
source bashrc
```
source ~/.bashrc
```

## 8. Running Simulation

move script to start px4 sitl 
```
cp ~/catkin_ws/src/simulations_ros/scripts/startsim.sh ~
```

In first terminal 
```
./startsim.sh
```
In another terminal

```
roslaunch simulations_ros px4.launch
```

after a few seconds the drone will initialize and you can command the drone to takeoff. In the px4 terminal run

if the previos command fails with
```
[FATAL] [1538090263.500882984]: UAS: GeographicLib exception: File not readable /usr/share/GeographicLib/geoids/egm96-5.pgm | Run install_geographiclib_dataset.sh script in order to install Geoid Model dataset!
```

run 
```
cd catkin_ws/src/mavros/mavros/scripts/
./install_geographiclib_datasets.sh
``` 

```
commander takeoff
```

to view camera
```
rosrun image_view image_view image:=/stereo/camera/left/image_raw
```

## 9. Remove GPS noise in PX4

In the terminal that is running px4, run the following:

```
param set EKF2_GPS_P_NOISE 0.01
param set EKF2_GPS_V_NOISE 0.01
param set EKF2_BARO_NOISE 0.01
param set EKF2_GPS_DELAY 0
param set EKF2_TAU_POS 0.1
param set EKF2_TAU_VEL 0.1
```

PX4 should save these parameters. The next time you run PX4, the parameters should be set to the ones above. To make sure they are right, run the following in PX4's terminal:

```
param show EKF2_GPS_P_NOISE
param show EKF2_GPS_V_NOISE
param show EKF2_BARO_NOISE
param show EKF2_GPS_DELAY
param show EKF2_TAU_POS
param show EKF2_TAU_VEL
```
