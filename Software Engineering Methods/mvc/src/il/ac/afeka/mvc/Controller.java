package il.ac.afeka.mvc;

import il.ac.afeka.input.Mouse;

public class Controller {

	private View view;
	private Model model;
	
	public Model getModel() { return model; }
	
	public void setModel(Model m) { model = m; }
	
	public View getView() { return view; }
	
	public void startUp() {
		controlInitialize();
		controlLoop();
		controlTerminate();
	}

	public void controlInitialize() {
	}

	public void controlTerminate() {
	}

	public void controlLoop() {
		while (isControlActive()) {
			controlActivity();
			Thread.yield();
		}
	}

	public void controlActivity() {
		View aView = view.subViewWantingControl();
		if (aView != null)
			aView.getController().startUp();
	}

	public boolean isControlActive() {
		return viewHasCursor();
	}

	public boolean isControlWanted() {
		return viewHasCursor();
	}

	public boolean viewHasCursor() {
		return view != null && view.containsPoint(Mouse.instance().cursorPoint());
	}

	public void setView(View view) {
		this.view = view;
	}
}
