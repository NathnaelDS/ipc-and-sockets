#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

int main()
{
    int fd[2];  // Parent write to Child
    int fd2[2]; // Child write to Parent

    pid_t pid;

    pipe(fd);
    pipe(fd2);

    pid = fork();

    if (pid == 0)
    {
        // child process
        char parentPhrases[3][64] = {"Enkoklish", "Tsegurun abetro gebeya yemiweta", "Gobez"};

        int read_value;

        int write_value = 0;

        close(fd[WRITE]);
        close(fd2[READ]);
        while (1)
        {
            read(fd[READ], &read_value, sizeof(int));
            // first read
            printf("Parent says: %s\n", parentPhrases[read_value]);

            switch (read_value)
            {
            case 0:
                sleep(1);
                write_value++;
                write(fd2[WRITE], &write_value, sizeof(int));
                break;

            case 1:
                sleep(1);
                write_value++;
                write(fd2[WRITE], &write_value, sizeof(int));
                break;

            case 2:
                sleep(1);
                write_value++;
                write(fd2[WRITE], &write_value, sizeof(int));
                exit(EXIT_SUCCESS);
                break;

            default:
                break;
            }
        }
    }
    else if (pid > 0)
    {
        // parent process
        char childPhrases[3][64] = {"Min Awekeleh?", "Ante", "Yaw min taregewaleh"};
        int int_value = 0;

        int parent_read_value;

        close(fd[READ]);
        close(fd2[WRITE]);
        write(fd[WRITE], &int_value, sizeof(int));

        while (1)
        {
            read(fd2[READ], &parent_read_value, sizeof(int));
            printf("Child says: %s\n", childPhrases[parent_read_value - 1]);

            switch (parent_read_value)
            {
            case 1:
                sleep(1);
                int_value++;
                write(fd[WRITE], &int_value, sizeof(int));
                break;

            case 2:
                sleep(1);
                int_value++;
                write(fd[WRITE], &int_value, sizeof(int));
                break;
            
            case 3:
                sleep(1);
                exit(EXIT_SUCCESS);
                break;

            default:
                break;
            }
        }
    }
}