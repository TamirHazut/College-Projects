package il.ac.afeka.mvc;

import java.util.LinkedList;
import java.util.List;

public class Model {

	protected List<View> views;
	
	public Model() {
		views = new LinkedList<View>();
	}
	
	public void addView(View newView) {
		views.add(newView);
	}
	
	public void removeView(View view) {
		views.remove(view);
	}
	
	public void notifyViews() {
		for(View view : views) 
			view.update();
	}
}
