package il.ac.afeka.battleship;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.mvc.View;
import il.ac.afeka.mvc.views.StandardSystemView;

public class TrackingStandardSystemView extends StandardSystemView {
    private BattleShipModel trackingModel;
    private TrackingGridView trackingGridView;

    public TrackingStandardSystemView(String title) {
        super(title);
        trackingModel = new BattleShipModel();
        displayShips();
        trackingGridView = new TrackingGridView(trackingModel);
        this.windowViewport(new Rectangle(new Point(0.0, 0.0), new Point(1.0, 1.0)), new Rectangle(new Point(0., 0.5625), new Point(1.,1.)));
        trackingGridView.windowViewport(new Rectangle(new Point(0.0, 0.0), new Point(1.0, 1.0)), new Rectangle(new Point(0.0,0.125), new Point(1, 1)));
        this.addSubview(trackingGridView);
    }

    private void displayShips() {
        trackingModel.setAShip(0, 0);
//        System.out.println(trackingModel.isAShip(0,0) + "0 0");
        trackingModel.setAShip(1, 0);
        trackingModel.setAShip(2, 0);
        trackingModel.setAShip(3, 0);
        trackingModel.setAShip(0, 4);
        trackingModel.setAShip(0, 5);
        trackingModel.notifyViews();
//        trackingGridView.display();
    }
    @Override
    public View getTopView() {
        return getSuperView();
    }
}
