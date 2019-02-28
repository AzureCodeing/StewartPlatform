/*********************************************************************                                                                                * Software License Agreement (BSD License)
*
*  Copyright (c) 2018, RainBowAurora
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the copyright holder nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#include <ros/ros.h>
#include "mpu9250_device/i2c.h"
#include "mpu9250_device/mpu9250.h"
#include "mpu9250_device/Imu.h"

_ins mpu9250_data;
mpu9250_device::Imu imu_msg;

void Imu_Publisher();
int main(int argc, char *argv[])
{
    ros::init(argc, argv, "mpu9250");
    ros::NodeHandle n;
    ros::Publisher imu_pub = n.advertise<mpu9250_device::Imu>("Imu_data", 1000);
    mpu9250 sensor_mpu9250("/dev/i2c-1", 0x68);
    ros::Rate loop_rate(1);

    while (ros::ok())
    {
        sensor_mpu9250.update_sensor(&mpu9250_data);
        Imu_Publisher();
        imu_pub.publish(imu_msg);
        loop_rate.sleep();
    }    
    return 0;
}

void Imu_Publisher()
{
    imu_msg.gyro.x = mpu9250_data.gyro.x;
    imu_msg.gyro.y = mpu9250_data.gyro.y;
    imu_msg.gyro.z = mpu9250_data.gyro.z;

    imu_msg.accel.x = mpu9250_data.accel.x;
    imu_msg.accel.y = mpu9250_data.accel.y;
    imu_msg.accel.z = mpu9250_data.accel.z;

    imu_msg.mag.x = mpu9250_data.mag.x;
    imu_msg.mag.y = mpu9250_data.mag.y;
    imu_msg.mag.z = mpu9250_data.mag.z;
}
