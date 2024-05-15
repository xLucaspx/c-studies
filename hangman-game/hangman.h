#define WORD_LENGTH 20
#define MAX_TRIES 6

void addWord();

void chooseWord();

void drawGameHeader();

void drawGibbet();

void guess();

void hangmanGame();

void resetGame();

int alreadyGuessed(char letter);

int hanged();

int won();

int wordContains(char letter);
