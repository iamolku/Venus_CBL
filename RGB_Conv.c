//RGB Value conversion - differentiating different colors in different lighting situations
//Best approach is to do this with color ratios? set a ratio for each color and essentially differentiate the different colors accordingly

//EXAMPLE CODE BEGIN

#include <stdio.h>
#include <stdint.h>

// Function to calculate RGB ratios
void calculate_rgb_ratios(uint16_t sensor_r, uint16_t sensor_g, uint16_t sensor_b, float *ratio_r, float *ratio_g, float *ratio_b) {
    // Calculate the sum of the sensor values to get the total intensity
    uint16_t intensity = sensor_r + sensor_g + sensor_b;

    // Avoid division by zero
    if (intensity == 0) {
        intensity = 1;
    }

    // Calculate the ratio of each color component to the total intensity
    *ratio_r = (float)sensor_r / intensity;
    *ratio_g = (float)sensor_g / intensity;
    *ratio_b = (float)sensor_b / intensity;
}

int main() {
    // Example sensor values under different lighting conditions
    uint16_t sensor_r = 10;
    uint16_t sensor_g = 25;
    uint16_t sensor_b = 40;

    float ratio_r, ratio_g, ratio_b;
    
    calculate_rgb_ratios(sensor_r, sensor_g, sensor_b, &ratio_r, &ratio_g, &ratio_b);
    
    printf("RGB Ratios: R=%.2f, G=%.2f, B=%.2f\n", ratio_r, ratio_g, ratio_b);

    // Use these ratios for color differentiation
    // Example: If ratio_r is highest, it's more likely to be red, etc.
    if (ratio_r > ratio_g && ratio_r > ratio_b) {
        printf("Color is predominantly Red\n");
    } else if (ratio_g > ratio_r && ratio_g > ratio_b) {
        printf("Color is predominantly Green\n");
    } else if (ratio_b > ratio_r && ratio_b > ratio_g) {
        printf("Color is predominantly Blue\n");
    } else {
        printf("Color is ambiguous\n");
    }

    return 0;
}

//EXAMPLE CODE END
