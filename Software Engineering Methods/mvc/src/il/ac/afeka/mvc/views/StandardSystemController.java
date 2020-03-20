package il.ac.afeka.mvc.views;

import java.awt.Color;

import il.ac.afeka.geom.Point;
import il.ac.afeka.graphics.Display;
import il.ac.afeka.input.Mouse;
import il.ac.afeka.mvc.Controller;

public class StandardSystemController extends Controller {
	
	public void controlActivity() {
		
		if (getView().titleBarContainsPoint(Mouse.instance().cursorPoint())) {
			if (Mouse.instance().button1Pressed()) {
				if (getView().getSuperView().getSubViews().indexOf(getView()) == getView().getSuperView().getSubViews().size()-1) {
					Point origin = Mouse.instance().cursorPoint();

					Point delta = Mouse.instance().cursorPoint().subtract(origin);

					Display.instance().drawRectXOR(getView().displayBox().translateBy(delta), Color.black, Color.gray);

					while (!Mouse.instance().button1Released()) {

						Display.instance().drawRectXOR(getView().displayBox().translateBy(delta), Color.black, Color.gray);
						delta = Mouse.instance().cursorPoint().subtract(origin);
						Display.instance().drawRectXOR(getView().displayBox().translateBy(delta), Color.black, Color.gray);
					}

					Display.instance().drawRectXOR(getView().displayBox().translateBy(delta), Color.black, Color.gray);

					Point newLocalOrigin = getView().getSuperView().inverseDisplayTransform().applyTo(delta.add(getView().displayBox().getOrigin()));

					getView().setViewport(getView().getViewport().moveTo(newLocalOrigin));
				}
				getView().getTopView().getSubViews().remove(getView());
				getView().getTopView().addSubview(getView());
				getView().getTopView().display();
			}
		}
		else {
			super.controlActivity();
		}
		
	}
	
	public StandardSystemView getView() {
		return (StandardSystemView)super.getView();
	}

}
