package il.ac.afeka.battleship;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.mvc.View;
import il.ac.afeka.mvc.views.StandardSystemView;

public class PrimaryStandardSystemView extends StandardSystemView {
    private BattleShipModel primaryModel = new BattleShipModel();
    private PrimaryGridView primaryGridView = new PrimaryGridView(primaryModel);;

    public PrimaryStandardSystemView(String title) {
        super(title);
        this.windowViewport(new Rectangle(new Point(0.0, 0.0), new Point(1.0, 1.0)), new Rectangle(new Point(0., 0.125), new Point(1.,0.5625)));
        primaryGridView.windowViewport(new Rectangle(new Point(0.0, 0.0), new Point(1.0, 1.0)), new Rectangle(new Point(0.0,0.125), new Point(1, 1)));
        this.addSubview(primaryGridView);
    }

    @Override
    public View getTopView() {
        return getSuperView();
    }
}
