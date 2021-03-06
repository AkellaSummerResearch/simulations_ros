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
catkin config --extend /opt/ros/kinetic
catkin config --cmake-args -DCMAKE_BUILD_TYPE=Release
catkin config --merge-devel
```

## 3. Dependencies installation (catkin_make)

```
sudo apt-get install ros-kinetic-mavlink
sudo apt-get install ros-kinetic-geographic-msgs
sudo apt-get install ros-kinetic-move-base-msgs
sudo apt-get install ros-kinetic-control-toolbox
cd ~/catkin_ws/src
git clone https://github.com/mavlink/mavros.git
git clone https://github.com/AkellaSummerResearch/tf_publisher
```

## 4. Clone our ROS package repositories

```
cd ~/catkin_ws/src 
git clone https://github.com/AkellaSummerResearch/simulations_ros.git
```

## 5. Make instructions 
   Inside `catkin_ws`, run `catkin_make`

```
cd ~/catkin_ws 
catkin_make 
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

Give permissions to your users:
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

If the previous command fails with

```
[FATAL] [1538090263.500882984]: UAS: GeographicLib exception: File not readable /usr/share/GeographicLib/geoids/egm96-5.pgm | Run install_geographiclib_dataset.sh script in order to install Geoid Model dataset!
```

run 
```
cd catkin_ws/src/mavros/mavros/scripts/
./install_geographiclib_datasets.sh
``` 

after a few seconds the drone will initialize and you can command the drone to takeoff. In the px4 terminal run:

```
commander takeoff
```

If you want to see the quad's camera, type:
```
rosrun image_view image_view image:=/stereo/camera/left/image_raw
```

## 9. Remove GPS noise in PX4

In the terminal that is running px4, run the following:

```
param set EKF2_GPS_P_NOISE 0.01
param set EKF2_GPS_V_NOISE 0.1
param set EKF2_BARO_NOISE 0.5
param set EKF2_GPS_DELAY 0
```

PX4 should save these parameters. The next time you run PX4, the parameters should be set to the ones above. To make sure they are right, run the following in PX4's terminal:

```
param show EKF2_GPS_P_NOISE
param show EKF2_GPS_V_NOISE
param show EKF2_BARO_NOISE
param show EKF2_GPS_DELAY
```
