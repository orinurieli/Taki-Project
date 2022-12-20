# Taki Project in C

The project focuses on computational learning with Python, analyzing large amounts of data and working with the Pandas and Numpy libraries. 
# Instructions

1. At the beginning of the program, the user will be shown the following opening message.
2. The program will request and receive the number of players participating in the game.
3. The program will request and receive the first names of the players participating in the game. You can
Assume that the names do not contain spaces or spaces-white of any kind, and that a name contains all
The most 20 characters.
4. The program will deal each participant 4 cards from the cash register and take out a card to the center of the table (this card will only be
One of the numbers 1-9 and not a special card.
5. As long as there is no winner in the game:
1.5. The program will print the top card in the center of the table.
Each card will be represented by a frame of stars in the center of which will be written a number (1-9) or the type of card



## Using Structs 

```
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

```
## Game Manager

```
void gameManager(PLAYER* players, int numOfPlayers, UPPERCARD* upperCard)
{
	// Sequence: current turn -> player cards -> print game request -> current turn -> upper card -> player cards ...

	int turn = -1; // when someone ends his turn, turn++
	bool isGameOver = false;

	// every player starts with 4 cards
	for (int k = 0; k < numOfPlayers; k++)
		players[k].howManyCards = 4;

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

		currentTurn(players, turn, numOfPlayers);		printPlayerCards(players, turn, players[turn].howManyCards);
		makeAmove(players, &turn, upperCard, numOfPlayers);

		isGameOver = checkIsGameOver(players[turn]); // checks if the current player has no cards left

		turn++;
		if (turn == numOfPlayers)
			turn = 0;
	}
}
```


## Main Goals

- Learning Basic Data Structures
- Write Dynamic Code using Funcitons
- Working with C language and pointers
