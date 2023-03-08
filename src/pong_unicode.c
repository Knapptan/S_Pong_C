#include <stdio.h>

int key(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
        int bollspeedx, int bollspeedy, int q);

void prfild(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
            int bollspeedx, int bollspeedy, int q);

void core(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
          int bollspeedx, int bollspeedy, int q);

int main() {
    int i = 0, j = 0;
    int pozition1 = 12;
    int pozition2 = 12;
    int score1 = 0;
    int score2 = 0;
    int bollposy = 11;
    int bollposx = 2;
    int bollspeedy = 1;
    int bollspeedx = 1;
    int q = 0;

    // Вывод приветствия в самом начале, без выбора, по этому просто фризится через юслип
    printf("\033[0d\033[2J");
    printf("\033[1;32m");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("\n                                    PONG GAME\n\n");
    printf(
        "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
        "\n");
    printf("> This game is an imitation of the Ping Pong game\n");
    printf(
        "> Control buttons are: \n> 'M' 'K' ore 'm' 'k' for right player\n> 'A' 'Z' ore 'a' 'z' for left "
        "player\n");
    printf("> For quit press 'Q' or 'q'\n");
    printf("> If Score = 10 payer = winner\n");
    printf("For start press 'Enter'\n");
    if (key(i, j, pozition1, pozition2, score1, score2, bollposy, bollposx, bollspeedx, bollspeedy, q) == 1)
        printf("Bye !\n");

    return 0;
}

// функция управления, реализована через stdi по этому ожидает нажатия энтр
int key(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
        int bollspeedx, int bollspeedy, int q) {
    char key = getchar();
    if (key == 'A' || key == 'a') {
        if (pozition1 >= 1) pozition1--;
    } else if (key == 'Z' || key == 'z') {
        if (pozition1 <= 23) pozition1++;
    } else if (key == 'M' || key == 'm') {
        if (pozition2 <= 23) pozition2++;
    } else if (key == 'K' || key == 'k') {
        if (pozition2 >= 1) pozition2--;
    } else if (key == 'Q' || key == 'q')
        return 1;
    else if (q == 1) {
        printf("Left payer win !!!\n");
        return 1;
    } else if (q == 2) {
        printf("Right payer win !!!\n");
        return 1;
    }
    core(i, j, pozition1, pozition2, score1, score2, bollposy, bollposx, bollspeedx, bollspeedy, q);
    return 0;
}

// Функция вывода поля, так как по заданию нельзя использовать массивы, реализована циклами и stdo
void prfild(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
            int bollspeedx, int bollspeedy, int q) {
    printf("\033[0d\033[2J");
    printf("\nSCORE:                              %2d  ┋┋ %2d\n", score1, score2);
    printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");

    for (i = 0; i < 25; i++) {
        printf("┃");
        for (j = 0; j < 80; j++) {
            if ((i == pozition1 && j == 0) || (i == pozition1 + 1 && j == 0) ||
                (i == pozition1 - 1 && j == 0))
                printf("┃");
            else if ((i == pozition2 && j == 79) || (i == pozition2 + 1 && j == 79) ||
                     (i == pozition2 - 1 && j == 79))
                printf("┃");
            else if (i == bollposy && j == bollposx)
                printf("●");
            else if (j == 39)
                printf("┋");
            else if (j == 40)
                printf("┋");
            else {
                printf(" ");
            }
        }
        printf("┃\n");
    }
    printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    key(i, j, pozition1, pozition2, score1, score2, bollposy, bollposx, bollspeedx, bollspeedy, q);
}

// Функция ядра игры, тут описана логика поведения мяча и начисления счета.
void core(int i, int j, int pozition1, int pozition2, int score1, int score2, int bollposy, int bollposx,
          int bollspeedx, int bollspeedy, int q) {
    if (bollposy == 0)
        bollspeedy *= -1;
    else if (bollposy == 24)
        bollspeedy *= -1;
    else if (bollposx == 1 &&
             (bollposy == pozition1 || bollposy == pozition1 + 1 || bollposy == pozition1 - 1))
        bollspeedx *= -1;
    else if (bollposx == 78 &&
             (bollposy == pozition2 || bollposy == pozition2 + 1 || bollposy == pozition2 - 1))
        bollspeedx *= -1;

    bollposx += bollspeedx;
    bollposy += bollspeedy;

    if (bollposx == 0) {
        bollposx = 1;
        bollposy = pozition1;
        score2 += 1;
    } else if (bollposx == 80) {
        bollposx = 78;
        bollposy = pozition2;
        score1 += 1;
    } else if (score2 == 10)
        q = 2;
    else if (score1 == 10)
        q = 1;

    prfild(i, j, pozition1, pozition2, score1, score2, bollposy, bollposx, bollspeedx, bollspeedy, q);
}