package il.ac.afeka.battleship;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.graphics.Display;
import il.ac.afeka.mvc.View;

import java.awt.Color;


public class BattleShipButtonView extends View {
    private int row, col;
    private boolean ship = false;
    private boolean isATrackingBoard;

    public BattleShipButtonView(BattleShipModel battleShipModel, int row, int col, boolean isATrackingBoard) {
        this.row = row;
        this.col = col;
        this.isATrackingBoard = isATrackingBoard;
        setModel(battleShipModel);
        if (!isATrackingBoard)
            setController(new BattleShipButtonController());
    }

    public int Row() { return row; }
    public int Col() { return col; }

    private void displayMiss() {
        Rectangle rect = displayTransformation().applyTo(getWindow().insetBy(0.05));
        Display.instance().drawLine(rect.getOrigin(), rect.getCorner(), Color.RED, 3);
        Display.instance().drawLine(rect.getLowerLeft(), rect.getUpperRight(), Color.RED, 3);
    }

    private void displayHit() {

        Rectangle rect = displayTransformation().applyTo(getWindow().insetBy(0.05));
        double x = (rect.getUpperRight().getX()-rect.getOrigin().getX());
        Point lowerMiddle = new Point((rect.getUpperRight().getX()+rect.getOrigin().getX())/2, rect.getLowerLeft().getY());
        Point leftUpperCorner = new Point(rect.getOrigin().getX()+(x/4), rect.getOrigin().getY());
        Point rightUpperCorner = new Point(rect.getUpperRight().getX()-(x/4), rect.getUpperRight().getY());
        Display.instance().drawLine(leftUpperCorner, lowerMiddle, Color.GREEN, 3);
        Display.instance().drawLine(lowerMiddle, rightUpperCorner, Color.GREEN, 3);
    }
    private void displayShip() {
        this.setBackgroundColor(Color.GREEN);
        ship = true;
    }

    public void displayView() {

        if (model != null) {
            int piece = ((BattleShipModel)model).pieceAt(row, col);
            if (!ship){
                boolean isAShip = ((BattleShipModel)model).isAShip(row, col);
                if (isAShip)
                    displayShip();
            }
            if (piece == BattleShipModel.X)
                displayMiss();
            else if (piece == BattleShipModel.V)
                displayHit();
        }
    }

    public BattleShipModel getModel() {
        return (BattleShipModel)model;
    }

    public void update() {
        displayView();
    }
}
