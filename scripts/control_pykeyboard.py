#!/usr/bin/env python3
import rospy
from std_msgs.msg import String
from geometry_msgs.msg import Twist
# import keyboard
from pynput.keyboard import Key, Listener
import numpy as np

global key_press, key_prev
key_press = 'No'
global key_use, v_x, a_z
key_use = 'N'
key_prev='No'
global key_used
key_used = 0


v_x = 0
a_z = 0

def on_press(key):
    global key_press
    key_press = key
    


def on_release(key):
    x = 1




def control_pykeyboard():
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    rospy.init_node('control_pykeyboard', anonymous=True)
    rate = rospy.Rate(10) # 10hz

    global key_press, key_prev, v_x, a_z, key_use, key_used

    delta_v = 0.025
    delta_a = 0.1
    threshold = 60*3.1415/180

    while not rospy.is_shutdown():
        velocity = Twist()
        # key = keyboard.read_key()

        if key_press != key_prev or key_used == 1:
            key_use = key_press
            key_used = 0
        else:
            key_use = "No"

        # print("key_press", key_press)
        # print("key_prev", key_prev)
        # print("key_use", key_use)


        
        if key_use != "No":
            string_key = format(key_use.char) 
            if string_key == 'w':
                v_x = v_x + delta_v
            elif string_key == 's':
                v_x= v_x - delta_v
            elif string_key == 'a':
                a_z = a_z + delta_a
            elif string_key == 'd':
                a_z = a_z - delta_a
            # print('string_key', string_key=='w')
            key_used = 1
            key_press = "No"

        if a_z != 0:
            a_z = min(abs(a_z),threshold)*abs(a_z)/a_z
        velocity.linear.x  = v_x
        velocity.angular.z = v_x*np.tan(a_z)/0.25

        key_prev = key_press

        print('linear_velocity',v_x)
        print('angular_velocity', v_x*np.tan(a_z)/0.25)
        print('steering_angle', a_z)
       

        pub.publish(velocity)
        rate.sleep()




if __name__ == '__main__':  
    try:
        with Listener(on_press = on_press,on_release = on_release) as listener: 
            control_pykeyboard()
            listener.join()
    except rospy.ROSInterruptException:
        pass
        

    