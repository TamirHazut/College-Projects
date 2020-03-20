package il.ac.afeka.mvc.views.button;

import il.ac.afeka.mvc.Model;

public class ButtonModel extends Model {

	private boolean isPressed;
	
	public boolean isPressed() { return isPressed; }
	
	ButtonModel() {
		super();
		isPressed = false;
	}
	
	public void flip() {
		isPressed = !isPressed;
		notifyViews();
	}
}
