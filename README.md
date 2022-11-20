# mbed-HW7

## Introduction
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
In this program, we use **STM32** to sense the value of acceleration and apply a high pass filter on the data. We first use Matlab to get the coefficient of a high pass filter and then call the ```arm_fir_init_f32()``` function to implement a high pass filter on the original data. The images in result folder show the visualized data before and after going through the filter.

To run the program, there're few steps to be done:
1. Create an empty project
2. Replace the origin ```main.cpp``` by the one here
3. Put both ```BSP_B-L475E-IOT01``` folder and ```mbed-dsp``` into your program folder
4. Run the program
5. Then we may see the sensing result printed in the console

**We use Matlab to visualize our data, you may choose your prefer way to do it yourself.**

code reference: https://github.com/ARM-software/CMSIS-DSP/tree/main/Examples/ARM/arm_fir_example


## Example

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
For example, we first run the program and then use matlab to visualize our data. 
- **AX**: acceleration in x-direction
- **AY**: acceleration in y-direction
- **AZ**: acceleration in z-direction

<br></br>

### Filter (Here we implement a high pass filter)
<a href="https://imgur.com/BhaGflc"><img src="https://i.imgur.com/BhaGflc.png" title="source: imgur.com" /></a>


### The sensor data of acceleration in both time and frequency domain
<a href="https://imgur.com/XmTYUnn"><img src="https://i.imgur.com/XmTYUnn.png" title="source: imgur.com" /></a>
