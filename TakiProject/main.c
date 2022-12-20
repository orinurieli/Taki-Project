#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>	
#include <stdbool.h>

#define STOP "STOP"
#define TAKI "TAKI"
#define PLUS "+"
#define DIRECTION "<->"
#define COLOR "COLOR"
#define MAX_FIRST_NAME 20
#define MAX_CARDS 4
#define NUM_PLAYERS 10


// Structs
typedef struct cardDetailes {
	char color;			// R | G | B | Y
	int number;			// 1 - 9
	char special[6];	// TAKI | STOP | <-> | COLOR | +
} CARD;

typedef struct upperDetailes {
	char color;			// R | G | B | Y
	int number;			// 1 - 9
	char special[6];	// TAKI | STOP | <-> | COLOR | +
} UPPERCARD;

typedef struct playerDetailes {
	char firstName[MAX_FIRST_NAME];
	int howManyCards;
	CARD* playerCards;
} PLAYER;


// Declarations
void printWelcome();
void getPlayersNames(PLAYER* players, int numOfPlayers);				// enters players names to PLAYER struct
void createUpperCard(UPPERCARD* upperCard);								// prints a card frame 
int random(int start, int end);											// make random number according to range given
char* randomSpecial(int random);										// returns random special card
char randomColor(int random);											// returns random color R G B Y
void fillCardsArr(PLAYER* players, int numOfPlayers);
void printPlayerCards(PLAYER* players, int turn, int howManyCards);
void gameManager(PLAYER* players, int numOfPlayers, UPPERCARD* upperCard);
void currentTurn(PLAYER* players, int turn, int numOfPlayers);
void printCard(CARD card);
void makeAmove(PLAYER* players, int* turn, UPPERCARD* upperCard, int numOfPlayers);		// prints a message for current player to make a move
CARD* cardsRealloc(CARD* cards, int size, int newSize);
int* intRealloc(int* intArr, int size, int newSize);
void printUpperCard(UPPERCARD* card);
void createExtraCard(CARD* card);
bool isValidMove(PLAYER player, int choice, UPPERCARD* upperCard);
void isSpecialMove(PLAYER* player, int* turn, int choice);
bool checkIsGameOver(PLAYER player);									// prints ending message if someone has no more cards


main()
{
	time_t t;
	srand(time(&t));
	int num, numOfPlayers = 1;
	PLAYER* playersArr;
	UPPERCARD* upperCard;

	// while (!isGameOver) // until game is over and someone has no cards

	printWelcome();

	printf("Please enter the number of players:\n");
	scanf("%d", &numOfPlayers);

	playersArr = (PLAYER*)malloc(numOfPlayers * sizeof(PLAYER)); // allocate memory according to number of players

	getPlayersNames(&playersArr, numOfPlayers);

	//createUpperCard(&upperCard); // create upper card and save it to upperCard by reference

	gameManager(&playersArr, numOfPlayers, &upperCard);




	free(playersArr);
}




void printWelcome()
{
	printf("************  Welcome to TAKI game !!! ***********\n");
}

int random(int start, int end)
{
	int random;

	if (start == 0)
		random = rand() % end;
	else
		random = start + rand() % end;

	return random;
}

void getPlayersNames(PLAYER* players, int numOfPlayers)
{
	int j = 0;

	// enter first names to struct
	for (int i = 1; i <= numOfPlayers; i++)
	{
		printf("Please enter the first name of player #%d:\n", i);
		scanf("%s", players[j].firstName);
		j++;
	}

}

void createUpperCard(UPPERCARD* upperCard)
{
	printf("\nUpper card:\n");
	printf("*********\n");
	printf("*       *\n");

	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 8)
			printf("*");
		else if (i == 4)
		{
			upperCard->number = randomNumber(random(1, 9));
			printf("%d", upperCard->number);
		}
		else
			printf(" ");
	}

	printf("\n");

	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 8)
			printf("*");
		else if (i == 4)
		{
			upperCard->color = randomColor(random(0, 3)); // prints a random color 
			printf("%c", upperCard->color);
		}
		else
			printf(" ");
	}

	printf("\n*       *\n");
	printf("*********\n\n");

}

int randomNumber(int random)
{
	switch (random)
	{
	case 1:
		return 1;
		break;
	case 2:
		return 2;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 4;
		break;
	case 5:
		return 5;
		break;
	case 6:
		return 6;
		break;
	case 7:
		return 7;
		break;
	case 8:
		return 8;
	case 9:
		return 9;
		break;
	}


	return random;
}

char* randomSpecial(int random)
{
	switch (random)
	{
	case 10:
		return COLOR;
		break;
	case 11:
		return DIRECTION;
		break;
	case 12:
		return TAKI;
		break;
	case 13:
		return STOP;
		break;
	case 14:
		return PLUS;
		break;
	}


}

char randomColor(int random)
{
	// random between 0 - 3
	char ch;

	if (random == 0) {
		ch = 'R';
		return ch;
	}
	else if (random == 1) {
		ch = 'G';
		return ch;
	}
	else if (random == 2) {
		ch = 'B';
		return ch;
	}
	else {
		ch = 'Y';
		return ch;
	}

}

void fillCardsArr(PLAYER* players, int numOfPlayers)
{

	for (int i = 0; i < numOfPlayers; i++)
	{
		players[i].playerCards = (CARD*)malloc(4 * sizeof(CARD));	// malloc for starting 4 cards

		if (players[i].playerCards)
		{
			for (int c = 0; c < 4; c++)
			{
				int randomZeroToThree = random(0, 3); // every loop generates new random

				players[i].playerCards[c].color = randomColor(randomZeroToThree);

				int randomOneToFourteen = random(1, 14); // every loop generates new random

				if (randomOneToFourteen <= 9)
				{
					players[i].playerCards[c].number = randomNumber(randomOneToFourteen);
					strcpy(players[i].playerCards[c].special, ""); // empty str to special
				}
				else
				{
					char* temp = (char*)malloc(10);
					temp = randomSpecial(randomOneToFourteen);
					strcpy(players[i].playerCards[c].special, temp);	// copy the returned str to playerCards
					players[i].playerCards[c].number = 0;				// number equals to zero
				}
			}
		}
		else
			printf("Memory Allocation Failed!!!!");
	}

	printf("\n");

}

void gameManager(PLAYER* players, int numOfPlayers, UPPERCARD* upperCard)
{
	// Sequence: current turn -> player cards -> print game request -> current turn -> upper card -> player cards ...

	int turn = -1; // when someone ends his turn, turn++
	bool isGameOver = false;

	// every player starts with 4 cards
	for (int k = 0; k < numOfPlayers; k++)
	{
		players[k].howManyCards = 4;
	}

	fillCardsArr(players, numOfPlayers);

	while (!isGameOver)
	{
		if (turn == -1)
		{
			createUpperCard(upperCard); // create upper card 
			turn = 0;
		}
		else
			printUpperCard(upperCard); // print upper card after change 

		currentTurn(players, turn, numOfPlayers);

		printPlayerCards(players, turn, players[turn].howManyCards);

		makeAmove(players, &turn, upperCard, numOfPlayers);



		isGameOver = checkIsGameOver(players[turn]); // checks if the current player has no cards left

		turn++;
		if (turn == numOfPlayers)
			turn = 0;
	}


}

void currentTurn(PLAYER* players, int turn, int numOfPlayers)
{
	if (turn >= numOfPlayers) // back to the first player
		turn = 0;

	printf("\n%s's turn:\n", players[turn].firstName);

}

void printPlayerCards(PLAYER* players, int turn, int howManyCards)
{

	for (int j = 0; j < howManyCards; j++)
	{
		printf("\nCard #%d:\n", j + 1);

		// ### if strcmp(playerCards[j].special,COLOR) dont display playerCards.color ###

		printCard(players[turn].playerCards[j]);
	}

}

void printCard(CARD card)
{
	printf("*********\n");
	printf("*       *\n");

	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 8)
			printf("*");

		else if (i == 2 && strcmp(card.special, COLOR) == 0)
		{
			printf("%s", card.special);
			i = 6;
		}
		else if (i == 3 && strcmp(card.special, DIRECTION) == 0)
		{
			printf("%s", card.special);
			i = 5;
		}
		else if (i == 3 && strcmp(card.special, TAKI) == 0)
		{
			printf("%s", card.special);
			i = 6;
		}
		else if (i == 3 && strcmp(card.special, STOP) == 0)
		{
			printf("%s", card.special);
			i = 6;
		}

		else if (i == 4)
		{
			if (card.number > 0 && card.number < 10)
				printf("%d", card.number);
			else
			{
				if (strcmp(card.special, PLUS) == 0)
					printf("%s", card.special);
				else
					printf(" ");
			}
		}

		else
			printf(" ");
	}

	printf("\n");

	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 8)
			printf("*");
		else if (i == 4)
		{
			if (strcmp(card.special, COLOR) == 0)
				printf(" ");
			else
				printf("%c", card.color);
		}

		else
			printf(" ");
	}

	printf("\n*       *\n");
	printf("*********\n");


}

void makeAmove(PLAYER* players, int* turn, UPPERCARD* upperCard, int numOfPlayers)
{
	int choice = -1;
	UPPERCARD* temp = upperCard;

	// prints a message for current player to make a move
	printf("\nPlease enter 0 if you want to take a card from the deck\nor 1-%d if you want to put one of your cards in the middle:\n", players[*turn].howManyCards);
	scanf("%d", &choice);

	// checks valid choice
	while (choice < 0 || choice > players[*turn].howManyCards)
	{
		printf("Invalid choice! Try again.");
		printf("Please enter 0 if you want to take a card from the deck\nor 1-%d if you want to put one of your cards in the middle:\n", players[*turn].howManyCards);
		scanf("%d", &choice);
	}

	if (choice == 0)
	{
		players[*turn].howManyCards++; // 6
		players[*turn].playerCards = cardsRealloc(players[*turn].playerCards, (players[*turn].howManyCards - 1), players[*turn].howManyCards); // realloc cards
		createExtraCard(&players[*turn].playerCards[players[*turn].howManyCards - 1]); // create the extra card

		// test
		printf("\ninfo for %s\n", players[*turn].firstName);
		printf("cards left: %d\n", players[*turn].howManyCards);
		players[*turn].howManyCards--; // 5
		printf("extra card is: color:%d, number: %d\n\n", players[*turn].playerCards[players[*turn].howManyCards].color, players[*turn].playerCards[players[*turn].howManyCards].number);
		players[*turn].howManyCards++; // 6

	}
	else
	{
		while (!isValidMove(players[*turn], choice, upperCard))
		{
			printf("Invalid card! Try again.\n");
			printf("Please enter 0 if you want to take a card from the deck\nor 1-%d if you want to put one of your cards in the middle:\n", players->howManyCards);
			scanf("%d", &choice);

			if (choice == 0)
			{
				players[*turn].howManyCards++;
				players[*turn].playerCards = (CARD*)cardsRealloc(players[*turn].playerCards, (players[*turn].howManyCards - 1), players[*turn].howManyCards); // realloc cards
				printf("\ninfo for %s\n", players[*turn].firstName);
				printf("cards left: %d\n", players[*turn].howManyCards);
				printf("first card: color:%d, number: %d\n\n", players[*turn].playerCards[*turn].color, players[*turn].playerCards[*turn].number);
				break;
			}
		}
		if (isValidMove(players[*turn], choice, upperCard))
		{
			choice = choice - 1;
			players[*turn].howManyCards--;

			isSpecialMove(&players[*turn], turn, choice, numOfPlayers);
			// ^ it changes turn and upper card is not for the correct player!!!
			temp->color = players[*turn].playerCards[choice].color;
			temp->number = players[*turn].playerCards[choice].number;
			strcpy(temp->special, players[*turn].playerCards[choice].special);


			upperCard = temp;
		}
	}









}

CARD* cardsRealloc(CARD* cards, int size, int newSize)
{
	CARD* res = (CARD*)malloc(newSize * sizeof(CARD));

	if (res)
	{
		for (int i = 0; i < size && i < newSize; i++)
			res[i] = cards[i]; // copy players to res

		free(cards);
	}

	else
	{
		printf("Memory Allocation Failed!!!");
		exit(1);
	}

	return res;
}

void createExtraCard(CARD* card)
{
	int randomZeroToThree = random(0, 3); // every loop generates new random

	card->color = randomColor(randomZeroToThree);

	int randomOneToFourteen = random(1, 14); // every loop generates new random

	if (randomOneToFourteen <= 9)
	{
		card->number = randomNumber(randomOneToFourteen);
		strcpy(card->special, ""); // empty str to special
	}
	else
	{
		strcpy(card->special, randomSpecial(randomOneToFourteen));	// copy the returned str to playerCards
		card->number = 0;											// number equals to zero
	}
}

int* intRealloc(int* intArr, int size, int newSize)
{
	int* res = (int*)malloc(newSize * sizeof(int));
	int i = 0;

	if (res)
	{
		for (i = 0; i < size && i < newSize; i++)
			res[i] = intArr[i]; // copy players to res

		free(intArr);
	}

	else
	{
		printf("Memory Allocation Failed!!!");
		exit(1);
	}

	return res;
}

bool isValidMove(PLAYER player, int choice, UPPERCARD* upperCard)
{
	// checks for specific player - the one whose turn to play
	// reminder: i put 0 in card number if a special symbol generated

	choice = choice - 1;

	if (player.playerCards[choice].number != 0) // there is a number, not a special symbol
	{
		if (player.playerCards[choice].color == upperCard->color || player.playerCards[choice].number == upperCard->number)
			return true;
	}

	else // special symbol and not a number 
	{
		if (player.playerCards[choice].color == upperCard->color || strcmp(player.playerCards[choice].special, COLOR) == 0)
			return true;
	}

	return false;
}

void printUpperCard(UPPERCARD* card)
{
	printf("\nUpper card:\n");
	printf("*********\n");
	printf("*       *\n");

	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 8)
			printf("*");

		else if (i == 2 && strcmp(card->special, COLOR) == 0)
		{
			printf("%s", card->special);
			i = 6;
		}
		else if (i == 3 && strcmp(card->special, DIRECTION) == 0)
		{
			printf("%s", card->special);
			i = 5;
		}
		else if (i == 3 && strcmp(card->special, TAKI) == 0)
		{
			printf("%s", card->special);
			i = 6;
		}
		else if (i == 3 && strcmp(card->special, STOP) == 0)
		{
			printf("%s", card->special);
			i = 6;
		}

		else if (i == 4)
		{
			if (card->number > 0 && card->number < 10)
				printf("%d", card->number);
			else
			{
				if (strcmp(card->special, PLUS) == 0)
					printf("%s", card->special);
				else
					printf(" ");
			}
		}

		else
			printf(" ");
	}

	printf("\n");

	for (int i = 0; i < 9; i++)
	{
		if (i == 0 || i == 8)
			printf("*");
		else if (i == 4)
			printf("%c", card->color);

		else
			printf(" ");
	}

	printf("\n*       *\n");
	printf("*********\n");


}

bool checkIsGameOver(PLAYER player)
{
	if (player.howManyCards == 0 && player.playerCards[0].special != PLUS && player.playerCards[0].special != STOP)
		return true;
	else
	{
		printf("\n%s has %d cards left\n", player.firstName, player.howManyCards);
		return false;
	}
}

void isSpecialMove(PLAYER* player, int* turn, int choice, int numOfPlayers)
{
	// Color card --> ask for color
	// Taki card --> loop until enters 0, turn stays and print cards and new upper card again
	// + card --> turn stays and the card[choice] goes to upperCard
	// STOP --> skips one after turn (--2)
	// <-> 

	int tempColor;
	char tempChar = 'Y';

	// COLOR
	if (strcmp(player->playerCards[choice].special, COLOR) == 0)
	{
		printf("\nPlease enter your color choice:\n");
		printf("1 - Yellow\n");
		printf("2 - Red\n");
		printf("3 - Blue\n");
		printf("4 - Green\n");

		scanf("%d", &tempColor);

		switch (tempColor)
		{
		case 1:
			tempChar = 'Y';
			break;
		case 2:
			tempChar = 'R';
			break;
		case 3:
			tempChar = 'B';
			break;
		case 4:
			tempChar = 'G';
			break;
		}

		player->playerCards[choice].color = tempChar; // change color of Color according to choice
	}

	// TAKI	
	if (strcmp(player->playerCards[choice].special, TAKI) == 0)
	{





	}

	// PLUS	
	if (strcmp(player->playerCards[choice].special, PLUS) == 0)
	{
		*turn -= 1;
	}

	// STOP	
	if (strcmp(player->playerCards[choice].special, STOP) == 0)
	{





	}

	// DIRECTION	
	if (strcmp(player->playerCards[choice].special, DIRECTION) == 0)
	{
		if (*turn >= 1)
			*turn -= 2;
		else if (*turn == 0)
			*turn = numOfPlayers - 2;
	}
}

//bool validateMoveOnTaki()
//{
//	
//
//	if (strcmp(info->upperCard.type, TAKI) == 0) {
//		return true;
//	}
//	if (info->upperCard.colour != takiColour)
//		return false;
//	return true;
//}