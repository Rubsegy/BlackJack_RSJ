#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARDS 52
#define CARD_VALUES 13
#define MAX_HAND 10

char *values[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
char *suits[] = {"❤", "💎", "♠", "🍀"};

struct carta {
    char *value;
    char *suit;
    int numericValue;
};


struct carta deck[TOTAL_CARDS];
struct carta playerHand[MAX_HAND];
struct carta dealerHand[MAX_HAND];
int numPlayerCards = 0;
int numDealerCards = 0;
int playerSum = 0;
int dealerSum = 0;
char choice;

int main() {

    for (int i = 0; i < TOTAL_CARDS; i++) {
        deck[i].value = values[i % CARD_VALUES];
        deck[i].suit = suits[i / CARD_VALUES];
        if (i % CARD_VALUES < 9) {
            // Para 2, 3, 4, 5, 6, 7, 8, 9, 10
            deck[i].numericValue = (i % CARD_VALUES) + 2;
        } else if (i % CARD_VALUES < 12) {
            // Para J, Q, K
            deck[i].numericValue = 10;
        } else {
            // Para A
            deck[i].numericValue = 11;
        }
    }


    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARDS; i++) {
        int j = rand() % TOTAL_CARDS;
        struct carta temp = deck[i];
        deck[i] = deck[j];
        deck[j] = temp;
    }

    printf("Bienvenido al Blackjack!\n");


    playerHand[numPlayerCards++] = deck[0];
    playerHand[numPlayerCards++] = deck[1];


    playerSum = 0;
    for (int i = 0; i < numPlayerCards; i++) {
        playerSum += playerHand[i].numericValue;
    }


    for (int i = 0; i < numPlayerCards; i++) {
        printf("  %s de %s\n", playerHand[i].value, playerHand[i].suit);
    }
    printf("Suma total: %d\n", playerSum);


    while (playerSum < 21) {
        printf("¿Quieres otra carta? (s/n): ");
        scanf(" %c", &choice);

        if (choice == 's' || choice == 'S') {
            playerHand[numPlayerCards] = deck[numPlayerCards + 1];
            numPlayerCards++;
            playerSum = 0;
            for (int i = 0; i < numPlayerCards; i++) {
                playerSum += playerHand[i].numericValue;
            }

            for (int i = 0; i < numPlayerCards; i++) {
                printf("  %s de %s\n", playerHand[i].value, playerHand[i].suit);
            }
            printf("Suma total: %d\n", playerSum);
        } else {
            break;
        }
    }
    if (playerSum <= 21) {
        printf("Turno del crupier:\n");
        while (dealerSum < 17) {
            dealerHand[numDealerCards] = deck[numPlayerCards + numDealerCards];
            numDealerCards++;
            dealerSum = 0;
            for (int i = 0; i < numDealerCards; i++) {
                dealerSum += dealerHand[i].numericValue;
                printf("El crupier ha sacado un %s de %s\n", dealerHand[i].value, dealerHand[i].suit);
            }

            for (int i = 0; i < numDealerCards; i++) {
                printf("  %s de %s\n", dealerHand[i].value, dealerHand[i].suit);
            }
            printf("Suma total del crupier: %d\n", dealerSum);
        }
    }

    // Comparar las sumas del jugador y del crupier para determinar quién gana
    if (playerSum > 21) {
        printf("Te has pasado el Crupier ha ganado. Fin del juego.\n");
    } else if (dealerSum > 21) {
        printf("El crupier se ha pasado. Has ganado.\n");
    } else if (playerSum > dealerSum) {
        printf("Has ganado. Fin del juego.\n");
    } else if (playerSum < dealerSum) {
        printf("El crupier ha ganado. Fin del juego.\n");
    } else {
        printf("Empate. Fin del juego.\n");
    }
    return 0;
}
