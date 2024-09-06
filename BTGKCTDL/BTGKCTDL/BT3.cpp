#include <iostream>
using namespace std;

struct Player {
	bool isEliminated;
	int place;
};

Player initPlayer(int place){
	Player player;
	player.isEliminated = false;
	player.place = place;
	return player;
}

struct Node {
	Player player;
	Node* next, * prev;
};

Node* createNode(int place) {
	Player player = initPlayer(place);
	Node* p = new Node;
	p->player = player;
	p->next = p->prev = NULL;
	return p;
}

struct Round {
	Node* head;
	int numberOfPlayer;
};

void initRound(Round &r) {
	r.head = NULL;
}

void insertPlayer(Round &r, int numberOfPlayer) {
	for (int i = 1; i <= numberOfPlayer; i++) {
		if (r.head == NULL)
			r.head = createNode(i);
		else {
			Node* p = r.head;
			while (p->next != NULL)
				p = p->next;
			p->next = createNode(i);
			p->next->prev = p;
		}
	}
	r.numberOfPlayer = numberOfPlayer;
}

void exportPlayerList(Round r) {
	Node* p = r.head;
	cout << "Number of player: " << r.numberOfPlayer<<endl;
	while (p != NULL) {
		cout << "Player " << p->player.place << " | Is eliminated: " << ((p->player.isEliminated) ? "Yes" : "No") << endl;
		p = p->next;
	}
}

bool isPrimeNum(int x) {
	if (x <= 1)
		return false;
	if (x > 1) {
		for (int i = 2; i <= sqrt(x); i++) {
			if (x % i == 0)
				return false;
		}
	}
	return true;
}

void startGame(Round &r, int startPlace) {
	if (r.numberOfPlayer == 0) {
		cout << "There is no player :(\n";
		return;
	}
	else {
		Node* p = r.head;
		while (p != NULL && p->player.place != startPlace)
			p = p->next;
		if (p == NULL) {
			cout << "There is no player " << startPlace << " :(\n";
		}
		else {
			int count = 0;
			while (r.numberOfPlayer > 1) {
				if (p->player.isEliminated == false) {
					count++;
					if (isPrimeNum(count)) {
						p->player.isEliminated = true;
						r.numberOfPlayer--;
					}
					p = p->next;
					if (p == NULL)
						p = r.head;
				}
				else {
					p = p->next;
					if (p == NULL)
						p = r.head;
				}
			}
		}
		
	}
}

void startGameWithRotate(Round& r, int startPlace) {
	if (r.numberOfPlayer == 0) {
		cout << "There is no player :(\n";
		return;
	}
	else {
		Node* p = r.head;
		while (p != NULL && p->player.place != startPlace)
			p = p->next;
		if (p == NULL) {
			cout << "There is no player " << startPlace << " :(\n";
		}
		else {
			int count = 0;
			bool isRotate = false;
			while (r.numberOfPlayer > 1) {
				if (p->player.isEliminated == false) {
					count++;
					if (isPrimeNum(count)) {
						p->player.isEliminated = true;
						r.numberOfPlayer--;
						if (isRotate)
							isRotate = false;
						else
							isRotate = true;
					}
					if (isRotate) {
						p = p->prev;
						if(p==NULL){
							p = r.head;
							while (p->next != NULL)
								p = p->next;
						}
					}
					else {
						p = p->next;
						if (p == NULL)
							p = r.head;
					}
				}
				else {
					if (isRotate) {
						p = p->prev;
						if (p == NULL) {
							p = r.head;
							while (p->next != NULL)
								p = p->next;
						}
					}
					else {
						p = p->next;
						if (p == NULL)
							p = r.head;
					}
				}
			}
		}

	}
}

int getWinnerPlace(Round r) {
	Node* p = r.head;
	while (p != NULL && p->player.isEliminated)
		p = p->next;
	if (p == NULL)
		return 0;
	return p->player.place;
}

void restoreRound(Round& r) {
	int numberOfPlayer = 0;
	Node* p = r.head;
	while (p != NULL) {
		numberOfPlayer++;
		p->player.isEliminated = false;
		p = p->next;
	}
	r.numberOfPlayer = numberOfPlayer;
}

int findStartPlace(Round& r, int winnerPlace) {
	restoreRound(r);
	if (winnerPlace <= r.numberOfPlayer) {
		for (int i = 1; i <= r.numberOfPlayer; i++) {
			startGame(r, i);
			if (getWinnerPlace(r) == winnerPlace)
				return i;
			restoreRound(r);
		}
	}
	else {
		cout << "There is no player " << winnerPlace << " :(\n";
		return 0;
	}
}

int findStartPlaceWithRotate(Round& r, int winnerPlace) {
	restoreRound(r);
	if (winnerPlace <= r.numberOfPlayer) {
		for (int i = 1; i <= r.numberOfPlayer; i++) {
			startGameWithRotate(r, i);
			if (getWinnerPlace(r) == winnerPlace)
				return i;
			restoreRound(r);
		}
	}
	else {
		cout << "There is no player " << winnerPlace << " :(\n";
		return 0;
	}
}

int main() {
	Round r;
	initRound(r);
	insertPlayer(r,6);
	startGameWithRotate(r,3);
	exportPlayerList(r);
	cout << "Player " << 4 << " is the winner and the starter is Player " << findStartPlaceWithRotate(r, 4) << endl;
	system("pause");
	return 0;
}