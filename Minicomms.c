#include "Minicomms.h"

#include <stdlib.h>

void sendShot(struct packet *p) {
	static int t = 0;

	// Send data

	// Recieve didHit and didWin

	p->didHit = t++%2;
	p->didWin = 0;

	return;
}

struct packet listenShot(enum tileType *board) {
	static int x = 5;
	static int y = 6;
	struct packet p;
	p.x = ++x%10;
	p.y = ++y%10;

	// Recieve data

	p.didHit = board[p.x + p.y*COLUMNS] & TILE_SHIP;
	board[p.x + p.y*COLUMNS] |= p.didHit ? TILE_HIT : TILE_MISS;

	p.didWin = 1;
	for(int i = 0; i < ROWS*COLUMNS; ++ i)
		if((board[i] & TILE_SHIP) && ((board[i]) & TILE_HIT) == 0)
			p.didWin = 0;

	// Send back didWin and didHit data

	return p;
}
