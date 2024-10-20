#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid_p2, pid_p3, pid_p4;

    printf("P1 process ID: %d\n", getpid());

    // Create child process P2
    pid_p2 = fork();
    if (pid_p2 < 0) {
        perror("Failed to fork P2");
        return 1;
    } else if (pid_p2 == 0) {
        // Inside child process P2
        printf("P2 process ID: %d, Parent ID: %d\n", getpid(), getppid());

        // Create child process P3
        pid_p3 = fork();
        if (pid_p3 < 0) {
            perror("Failed to fork P3");
            return 1;
        } else if (pid_p3 == 0) {
            // Inside child process P3
            printf("P3 process ID: %d, Parent ID: %d\n", getpid(), getppid());
        } else {
            // Create child process P4
            pid_p4 = fork();
            if (pid_p4 < 0) {
                perror("Failed to fork P4");
                return 1;
            } else if (pid_p4 == 0) {
                // Inside child process P4
                printf("P4 process ID: %d, Parent ID: %d\n", getpid(), getppid());
            } else {
                // P2 waits for both P3 and P4 to finish
                wait(NULL);
                wait(NULL);
            }
        }
    } else {
        // P1 waits for P2 to finish
        wait(NULL);
    }

    return 0;
}
