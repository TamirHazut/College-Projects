package il.ac.afeka.battleship;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.mvc.View;

public abstract class BattleShipBoardView extends View {
    private final int GRID_SIZE = 10;
    private BattleShipButtonView[][] buttonGrid = new BattleShipButtonView[GRID_SIZE][GRID_SIZE];
    protected void displayBoard(BattleShipModel battleShipModel, boolean isATrackingBoard) {
        for(int i =0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                buttonGrid[i][j] = new BattleShipButtonView(battleShipModel, i, j, isATrackingBoard);
                buttonGrid[i][j].windowViewport(new Rectangle(new Point(0.0, 0.0), new Point(1.0, 1.0)), new Rectangle(new Point(i * 0.1, j * 0.1), new Point(i * 0.1 + 0.1, j * 0.1 + 0.1)));
                buttonGrid[i][j].displayView();
                addSubview(buttonGrid[i][j]);
            }
        }
    }
}
