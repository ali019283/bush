#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *a[512];
char *ap[512];
char l[1024];
int n = -1;

void sighand(int no) {
    signal(SIGINT, sighand);
    fflush(stdout);
}

void sp(const char s[2], char **okl, char *okk) {
    char *tok;
    tok = strtok(okk, s);
    for (int i = 0; tok != NULL; i++) {
        okl[i] = tok;
        tok = strtok(NULL, s);
    }
}

int ex(int w, int f, int la, char *z) {
    n++;
    memset(a, 0, 512);
    if (z != NULL)
        sp(" ", a, ap[n]);
    else
        sp(" ", a, l);
    int g[2];
    pipe(g);
    if (strcmp(a[0], "exit") == 0) {
        exit(0);
    }
    pid_t pid = fork();
    if (!pid) {
        if (f == 1 && la == 0 && w == 0) {
            dup2(g[1], STDOUT_FILENO);
        } else if (f == 0 && la == 0 && w != 0) {
            dup2(w, STDIN_FILENO);
            dup2(g[1], STDOUT_FILENO);
        } else {
            dup2(w, STDIN_FILENO);
        }
        if (execvp(a[0], a) == -1) {
            puts("cant find command");
            exit(0);
        }
    }
    if (w)
        close(w);
    close(g[1]);
    if (la)
        close(g[0]);
    return g[0];
}

int main(void) {
    signal(SIGINT, sighand);
    while (1) {
        if (!fgets(l, 1024, stdin))
            return 0;
        n = -1;
        int w = 0, f = 1;
        char *cm = l;
        l[strlen(l) - 1] = 0;
        char *z = strchr(cm, '|');
        while (z != NULL) {
            sp("|", ap, cm);
            *z = '\0';
            w = ex(w, f, 0, z);
            cm = z + 1;
            z = strchr(cm, '|');
            f = 0;
        }
        w = ex(w, f, 1, cm);
    }
}
