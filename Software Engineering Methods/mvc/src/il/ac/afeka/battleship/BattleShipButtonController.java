package il.ac.afeka.battleship;

import il.ac.afeka.input.Mouse;
import il.ac.afeka.mvc.Controller;

public class BattleShipButtonController extends Controller {
    public void controlActivity() {
        super.controlActivity();

        if (Mouse.instance().button1Pressed()) {

            BattleShipButtonView buttonView = (BattleShipButtonView)getView();

            ((BattleShipModel)getModel()).playAt(buttonView.Row(), buttonView.Col());
        }

    }
}
