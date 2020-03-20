package il.ac.afeka.battleship;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.mvc.views.StandardSystemView;

import java.awt.*;

public class BattleShipPlayer {
    private StandardSystemView playerView;
    private PrimaryStandardSystemView primaryBoardSystemView;
    private TrackingStandardSystemView trackingBoardSystemView;

    private int playerNumber;

    public BattleShipPlayer(int playerNum) {
        this.playerNumber = playerNum;
        playerView = new StandardSystemView("Player #" + playerNumber);
        playerView.windowViewport(new Rectangle(new Point (0.0,  0.0), new Point(1.0,1.0)), new Rectangle(new Point(0.,0.), new Point(0.5, 1.)));
        playerView.setBackgroundColor(Color.DARK_GRAY);

        /* Primary Board */
        primaryBoardSystemView = new PrimaryStandardSystemView("Primary Board");

        /* Tracking Board */
        trackingBoardSystemView = new TrackingStandardSystemView("Tracking Board");

        playerView.addSubview(primaryBoardSystemView);
        playerView.addSubview(trackingBoardSystemView);
    }

    public StandardSystemView getPlayerView() {
        return playerView;
    }
}
