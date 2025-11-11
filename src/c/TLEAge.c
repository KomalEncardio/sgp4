#include <stdio.h>
#include <time.h>
#include "TLE.h"

int main(void) {
    char line1[] = "1 60550U 24149CL  25314.66366007  .00003701  00000-0  32780-3 0  9999";
    char line2[] = "2 60550  97.6968  29.1289 0007731  88.0392 272.1715 14.96835693 67363";
    
    TLE tle;
    parseLines(&tle, line1, line2);
    
    // Get current time
    long currentMillis = time(NULL) * 1000;
    
    // Calculate TLE age    
    long ageMillis = currentMillis - tle.epoch;
    double ageHours = ageMillis / (1000.0 * 3600.0);
    double ageDays = ageHours / 24.0;
    
    printf("TLE Epoch: %ld ms\n", tle.epoch);
    printf("Current Time: %ld ms\n", currentMillis);
    printf("\nTLE Age:\n");
    printf("  %.2f hours\n", ageHours);
    printf("  %.2f days\n", ageDays);
    
    if (ageDays > 7) {
        printf("\n⚠️  WARNING: TLE is over 7 days old!\n");
        printf("   Predictions may be inaccurate.\n");
    }
    
    return 0;
}