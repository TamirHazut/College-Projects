package il.ac.afeka.battleship;

import il.ac.afeka.mvc.Model;

public class BattleShipModel extends Model {

    public static int EMPTY = 0;
    public static int X = 1;
    public static int V = 2;

    private int board[][];
    private boolean shipsOnBoard[][];


    private int turn = V;

    public BattleShipModel() {
        board = new int[10][10];
        shipsOnBoard = new boolean[10][10];
        clearBoard();
    }

    public void playAt(int row, int col) {
        atput(row, col, turn);
/*
        if (turn == X) turn = O;
        else if (turn == O) turn = X;
 */
    }

    public void clearBoard() {
        for(int i =0 ;i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = EMPTY;
                shipsOnBoard[i][j] = false;
            }
        }
    }

    public void atput(int row, int col, int piece) {
        if (board[row][col] == EMPTY) {
            board[row][col] = piece;
            notifyViews();
        }
    }
    public boolean isAShip(int row, int col) {
        return shipsOnBoard[row][col];
    }
    public void setAShip(int row, int col) {
        shipsOnBoard[row][col] = true;
    }

    public int pieceAt(int row, int col) {
        return board[row][col];
    }
}
