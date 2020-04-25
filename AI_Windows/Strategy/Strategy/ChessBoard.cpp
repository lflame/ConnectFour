#include "ChessBoard.h"
#include "Judge.h"
#include <cassert>

ChessBoard::ChessBoard(int m, int n, int lastX, int lastY, int noX, int noY, int* const* board, const int* top)
{
	this->m = m;
	this->n = n;
	this->lastX = lastX;
	this->lastY = lastY;
	this->noX = noX;
	this->noY = noY;
	this->board = board;
	for (int j = 0; j < n; ++j)
		this->top[j] = top[j];
	turn = 2;  // 注意初始化时一定为己方回合
}


// 在第 col 列走子，保证合法，返回走的位置的 x 值
int ChessBoard::move(int col) {
	int ret = --top[col];
	board[ret][col] = turn;
	// 保证 top[col]-1 为可走子处或 0
	if (col == noY && top[col] - 1 == noX)
		top[col]--;
	turn = 3 - turn;
	lastX = ret, lastY = col;
	return ret;
}


// 检查局面的胜负状态
// 0: 未结束; 1: 对方胜利; 2: 己方胜利; 3: 平局
int ChessBoard::getStatus() {
	if (lastX == -1 && lastY == -1) return 0;  // 还未开始下子
	if (board[lastX][lastY] == 1) {
		// 只可能是 0, 1, 3
		if (userWin(lastX, lastY, m, n, board)) {
			return 1;
		}
		else if (isTie(n, top)) {
			return 3;
		}
		else {
			return 0;
		}
	}
	else if (board[lastX][lastY] == 2) {
		// 只可能是 0, 2, 3
		if (machineWin(lastX, lastY, m, n, board)) {
			return 2;
		}
		else if (isTie(n, top)) {
			return 3;
		}
		else {
			return 0;
		}
	}
	else {
		assert(0); // TODO
	}
}


// 保存局面
void ChessBoard::saveBoard() {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			tmpBoard[i][j] = board[i][j];
		}
	}
	for (int j = 0; j < n; ++j) {
		tmpTop[j] = top[j];
	}
	tmpTurn = turn;
	tmpLastX = lastX, tmpLastY = lastY;
}

// 载入局面
void ChessBoard::loadBoard() {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			board[i][j] = tmpBoard[i][j];
		}
	}
	for (int j = 0; j < n; ++j) {
		top[j] = tmpTop[j];
	}
	turn = tmpTurn;
	lastX = tmpLastX, lastY = tmpLastY;
}