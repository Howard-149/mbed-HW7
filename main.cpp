/** \example arm_fir_example_f32.c
 */

/* ----------------------------------------------------------------------
** Include Files
** ------------------------------------------------------------------- */
#include "mbed.h"
#include "arm_math.h"
#include "math_helper.h"
#include "stdio.h"

#include "stm32l475e_iot01_gyro.h"
#include "stm32l475e_iot01_accelero.h"
#include <cstdio>

#if defined(SEMIHOSTING)
#include <stdio.h>
#endif


/* ----------------------------------------------------------------------
** Macro Defines
** ------------------------------------------------------------------- */

#define TEST_LENGTH_SAMPLES  320
/*

This SNR is a bit small. Need to understand why
this example is not giving better SNR ...

*/
#define SNR_THRESHOLD_F32    75.0f
#define BLOCK_SIZE            32

#if defined(ARM_MATH_MVEF) && !defined(ARM_MATH_AUTOVECTORIZE)
/* Must be a multiple of 16 */
#define NUM_TAPS_ARRAY_SIZE              32
#else
#define NUM_TAPS_ARRAY_SIZE              29
#endif

#define NUM_TAPS              29

/* -------------------------------------------------------------------
 * Declare Test output buffer
 * ------------------------------------------------------------------- */
static float32_t testOutputX[TEST_LENGTH_SAMPLES];
static float32_t testOutputY[TEST_LENGTH_SAMPLES];
static float32_t testOutputZ[TEST_LENGTH_SAMPLES];
/* -------------------------------------------------------------------
 * Declare State buffer of size (numTaps + blockSize - 1)
 * ------------------------------------------------------------------- */

static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];



const float32_t firCoeffs32[NUM_TAPS_ARRAY_SIZE] = {
  -0.001402,-0.001535,0.002281,0.004023,-0.004739,-0.010169,0.008392,0.022227,-0.012550,-0.044797,0.016369,0.093801,-0.019046,-0.314143,0.520207,-0.314143,-0.019046,0.093801,0.016369,-0.044797,-0.012550,0.022227,0.008392,-0.010169,-0.004739,0.004023,0.002281,-0.001535,-0.001402
};


/* ------------------------------------------------------------------
 * Global variables for FIR LPF Example
 * ------------------------------------------------------------------- */

uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = TEST_LENGTH_SAMPLES/BLOCK_SIZE;

float32_t  snr;


float32_t accx[320];
float32_t accy[320];
float32_t accz[320];


/* ----------------------------------------------------------------------
 * FIR LPF Example
 * ------------------------------------------------------------------- */

int32_t main(void)
{


    float sensor_value = 0;
        int16_t pDataXYZ[3] = {0};
        float pGyroDataXYZ[3] = {0};
        int sample_num=0;
        BSP_GYRO_Init();
        BSP_ACCELERO_Init();
        while (sample_num<320){
            // printf("new_loop\n");
            BSP_ACCELERO_AccGetXYZ(pDataXYZ);
            float x = pDataXYZ[0], y = pDataXYZ[1], z = pDataXYZ[2];
            accx[sample_num]=x;
            accy[sample_num]=y;
            accz[sample_num]=z;
            sample_num++;
            ThisThread::sleep_for(100ms);
            printf("receive %d data\n",sample_num);
        } 
    uint32_t i;
    arm_fir_instance_f32 S;
    arm_status status;
    float32_t  *inputF32, *outputF32, *inputF32X, *outputF32X,*inputF32Y, *outputF32Y,*inputF32Z, *outputF32Z;

    /* Initialize input and output buffer pointers */
    inputF32X = &accx[0];
    inputF32Y = &accx[0];
    inputF32Z = &accx[0];

    outputF32X = &testOutputX[0];
    outputF32Y = &testOutputY[0];
    outputF32Z = &testOutputZ[0];

    /* Call FIR init function to initialize the instance structure. */
    arm_fir_init_f32(&S, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], blockSize);
    printf("finished init \n");
    /* ----------------------------------------------------------------------
    ** Call the FIR process function for every blockSize samples
    ** ------------------------------------------------------------------- */

    for(i=0; i < numBlocks; i++)
    {
        arm_fir_f32(&S, inputF32X + (i * blockSize), outputF32X + (i * blockSize), blockSize);
        arm_fir_f32(&S, inputF32Y + (i * blockSize), outputF32Y + (i * blockSize), blockSize);
        arm_fir_f32(&S, inputF32Z + (i * blockSize), outputF32Z + (i * blockSize), blockSize);
    }
    printf("finished fir \n");
    /* ----------------------------------------------------------------------
    ** Compare the generated output against the reference output computed
    ** in MATLAB.
    ** ------------------------------------------------------------------- */

    //snr = arm_snr_f32(&refOutput[0], &testOutputX[0], TEST_LENGTH_SAMPLES);
    printf("finished snr \n");
    //status = (snr < SNR_THRESHOLD_F32) ? ARM_MATH_TEST_FAILURE : ARM_MATH_SUCCESS;
    printf("here\n");
    //printf("status = %d\n",status);
    printf("accx = \n");
    for(int i=0;i<320;i++){
        printf("%f,",accx[i]);
    }
    printf("\n\n\n\nouputX = \n");
     for(int i=0;i<320;i++){
        printf("%f,",testOutputX[i]);
    }
    printf("\n\n\naccy = \n");
    for(int i=0;i<320;i++){
        printf("%f,",accy[i]);
    }
    printf("\n\n\n\nouputY = \n");
     for(int i=0;i<320;i++){
        printf("%f,",testOutputY[i]);
    }
     printf("\n\n\naccz = \n");
    for(int i=0;i<320;i++){
        printf("%f,",accz[i]);
    }
    printf("\n\n\n\nouputZ = \n");
     for(int i=0;i<320;i++){
        printf("%f,",testOutputZ[i]);
    }
    printf("\n\n\n\n finished\n");
}
