package il.ac.afeka.mvc.views;

import java.awt.Color;

import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.graphics.Display;
import il.ac.afeka.mvc.View;

public class TextView extends View {

	private String text;
	
	public TextView(String text) {
		this.text = text;
	}
	
	public void displayView() {
		
		Rectangle rect = displayTransformation().applyTo(getWindow()).insetBy(10.0);

		Display.instance().text(rect.getLowerLeft(), text, Color.black);
		
	}
}
