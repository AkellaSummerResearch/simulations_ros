CATKIN_PATH='~/lockheed_ws'

eval cd $CATKIN_PATH/src
git clone https://github.com/AkellaSummerResearch/nlopt.git 
git clone https://github.com/AkellaSummerResearch/mav_comm.git
git clone https://github.com/AkellaSummerResearch/catkin_simple.git
git clone https://github.com/AkellaSummerResearch/eigen_catkin.git
eval cd $CATKIN_PATH
catkin_make

eval cd $CATKIN_PATH/src
git clone https://github.com/AkellaSummerResearch/glog_catkin.git
eval cd glog_catkin
git checkout 314b53e 
eval cd $CATKIN_PATH
catkin_make

eval cd $CATKIN_PATH/src
git clone https://github.com/AkellaSummerResearch/eigen_checks.git
eval cd $CATKIN_PATH
catkin_make

eval cd $CATKIN_PATH/src
git clone https://github.com/AkellaSummerResearch/mav_trajectory_generation.git
eval cd $CATKIN_PATH
catkin_make