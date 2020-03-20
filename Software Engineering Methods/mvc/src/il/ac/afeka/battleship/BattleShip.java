package il.ac.afeka.battleship;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.graphics.Display;
import il.ac.afeka.mvc.View;


import java.awt.*;

public class BattleShip {
    public static void main(String[] args) {
        try {
            View desktop = new View().windowViewport(new Rectangle(new Point (0.0,  0.0), new Point(1.0,1.0)), new Rectangle(new Point(100.0,100.0), new Point(1200.0, 600.0)));
            desktop.setBackgroundColor(Color.gray);
            BattleShipPlayer player1 = new BattleShipPlayer(1);
            desktop.addSubview(player1.getPlayerView());
            desktop.display();

            desktop.getController().startUp();


            try { Thread.sleep(1000); } catch(InterruptedException e) {}

        } finally {
            Display.instance().close();
            System.exit(0);
        }
    }
}
