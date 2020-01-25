# Fall-2019-Group-37

This project requires `rosserial-arduino` and `rplidar_ros`. Install the `rosserial-arduino` binaries by running:

```
sudo apt-get install ros-melodic-rosserial-arduino
sudo apt-get install ros-melodic-rosserial
```

Then install the catkin code, where &lt;ws&gt; represents your catkin workspace:

```
cd <ws>/src
git clone https://github.com/ros-drivers/rosserial.git
cd <ws>
catkin_make
catkin_make install
```

Then install `rplidar_ros` with:
```
cd <ws>/src
git clone https://github.com/robopeak/rplidar_ros.git
cd <ws>
catkin_make
catkin_make install
```

Lastly, copy this code into your catkin workspace as well:

```
cd <ws>/src
git clone --branch catkin https://github.com/ucfcs/Fall-2019-Group-37.git egoat
cd <ws>
catkin_make
catkin_make install
```
