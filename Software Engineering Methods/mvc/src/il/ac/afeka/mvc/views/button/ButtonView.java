package il.ac.afeka.mvc.views.button;

import java.awt.Color;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.graphics.Display;
import il.ac.afeka.mvc.View;

public class ButtonView extends View {

	private Color pressedColor;
	private Color unpressedColor;
	private Double buttonBorderSize;
	
	public void setButtonBorderSize(Double d) {
		buttonBorderSize = d;
	} 
	
	public void setPressedColor(Color c) {
		pressedColor = c;
	}
	
	public void setUnpressedColor(Color c) {
		unpressedColor = c;
	}
	
	private Color selectColor() {
		if (((ButtonModel)model).isPressed())
			return pressedColor;
		else
			return unpressedColor;
	}
	
	public void displayView() {
		
		Rectangle rect = displayTransformation().applyTo(getWindow().insetBy(buttonBorderSize));
		Display.instance().fillRect(rect, selectColor());
		Point textCenter = Display.instance().measureText(selectText()).multBy(new Point(0.5, -0.5));
		Display.instance().text(rect.getCenter().subtract(textCenter), selectText(), Color.black);
	}

	private String selectText() {
		if (((ButtonModel)model).isPressed())
			return "On";
		else
			return "Off";
	}
}
