#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

int score = 0;

void error(char *msg)
{
    fprintf(stderr, "%s : %s \n", msg, strerror(errno));
    exit(1);
}

void game_over(int sig)
{
    printf("Game Over\n");
    printf("Your score is %i \n", score);
    exit(0);
}

void time_out(int sig)
{
    printf("Time Up \n");
    raise(SIGINT); /* �Լ����������źţ��ó������game_over */
}

int catch_signal(int sig, void (*handle)(int))
{
    struct sigaction action;
    action.sa_handler = handle;
    sigemptyset(&action.sa_mask); /* ���������sigactionҪ������źţ�ͨ������һ�������� */
    action.sa_flags = 0; /* ���ӱ�־λ */
    return sigaction(sig, &action, NULL);
}

int main(int argc, char *argv[])
{
    int answer;
    int a, b;

    /* ��Ҫ����sigint�ź� */
    if (catch_signal(SIGINT, game_over) == -1) {
        error("catch signal failed");
    }

    /* ����5������ź� */
    if (catch_signal(SIGALRM, time_out) == -1) {
        error("catch signal failed");
    }

    srandom(time(0));
    while (1)
    {
        a = random() % 11;
        b = random() % 11;

        alarm(5); /* ÿ���ⶨʱʱ��Ϊ5�� */
        printf("What is %i * %i = ? \n", a, b);

        scanf("%i", &answer);
        if (answer == a * b) {
            score++;
        } else {
            printf("Wrong! Score: %i\n", score);
        }
    }

    return 0;
}
