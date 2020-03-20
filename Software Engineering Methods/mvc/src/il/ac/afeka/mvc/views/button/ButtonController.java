package il.ac.afeka.mvc.views.button;

import il.ac.afeka.input.Mouse;
import il.ac.afeka.mvc.Controller;

public class ButtonController extends Controller {
		
	public void controlActivity() {
		super.controlActivity();
				
		if (Mouse.instance().button1Pressed() ) {
			((ButtonModel)getModel()).flip();
		}		
	}

}
