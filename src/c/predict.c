#include <stdio.h>
#include <time.h>
#include "TLE.h"






int main(void)
{
    // Your TLE data (ISS example)
    char line1[] = "1 60550U 24149CL  25314.66366007  .00003701  00000-0  32780-3 0  9999";
    char line2[] = "2 60550  97.6968  29.1289 0007731  88.0392 272.1715 14.96835693 67363";
    
    // Create TLE structure
    TLE tle;
    
    // Parse the TLE
    parseLines(&tle, line1, line2);
    
    // Check for parsing errors
    if (tle.sgp4Error != 0) {
        printf("Error initializing TLE: %d\n", tle.sgp4Error);
        return 1;
    }
    
    printf("Satellite: %s\n", tle.objectID);
    printf("Epoch: %ld ms since 1970\n\n", tle.epoch);
    
    // Arrays to store position and velocity
    double r[3];  // position in km
    double v[3];  // velocity in km/s
    
    // METHOD 1: Get position at TLE epoch (time 0)
    getRV(&tle, 0.0, r, v);
    printf("Position at epoch:\n");
    printf("  X = %14.6f km\n", r[0]);
    printf("  Y = %14.6f km\n", r[1]);
    printf("  Z = %14.6f km\n", r[2]);
    printf("Velocity at epoch:\n");
    printf("  VX = %14.9f km/s\n", v[0]);
    printf("  VY = %14.9f km/s\n", v[1]);
    printf("  VZ = %14.9f km/s\n\n", v[2]);
    
    // METHOD 2: Get position 60 minutes after epoch
    getRV(&tle, 60.0, r, v);
    printf("Position 60 minutes after epoch:\n");
    printf("  X = %14.6f km\n", r[0]);
    printf("  Y = %14.6f km\n", r[1]);
    printf("  Z = %14.6f km\n", r[2]);
    printf("\n");
    
    // METHOD 3: Get position at specific date/time
    // Calculate current time in milliseconds since Jan 1, 1970
    time_t now = time(NULL);
    long millisNow = now * 1000;
    
    getRVForDate(&tle, millisNow, r, v);
    printf("Position at current time:\n");
    printf("  X = %14.6f km\n", r[0]);
    printf("  Y = %14.6f km\n", r[1]);
    printf("  Z = %14.6f km\n", r[2]);
    printf("\n");
    
    // METHOD 4: Predict multiple positions (e.g., next 24 hours)
    printf("Positions over next 6 hours (hourly):\n");
    printf("Time(min)       X(km)          Y(km)          Z(km)\n");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i <= 6; i++) {
        double minutesFromEpoch = i * 60.0;  // every hour
        getRV(&tle, minutesFromEpoch, r, v);
        printf("%6.0f    %14.6f %14.6f %14.6f\n", 
               minutesFromEpoch, r[0], r[1], r[2]);
    }
    
    return 0;
}