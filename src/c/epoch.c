#include <stdio.h>
#include <time.h>

int main(void) {
    long epochMillis = 1762845613000; // Example epoch in milliseconds since Jan 1, 1970
    
    // Convert to seconds
    time_t epochSeconds = epochMillis / 1000;
    
    // Convert to readable format
    struct tm *timeinfo = gmtime(&epochSeconds);
    
    printf("Epoch Date/Time (UTC):\n");
    printf("  Year:   %d\n", timeinfo->tm_year + 1900);
    printf("  Month:  %d\n", timeinfo->tm_mon + 1);
    printf("  Day:    %d\n", timeinfo->tm_mday);
    printf("  Hour:   %d\n", timeinfo->tm_hour);
    printf("  Minute: %d\n", timeinfo->tm_min);
    printf("  Second: %d\n", timeinfo->tm_sec);
    
    // Or use a simple format
    printf("\nFormatted: %s", asctime(timeinfo));
    
    return 0;
}
