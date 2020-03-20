package il.ac.afeka.mvc;

import java.awt.Color;
import java.util.LinkedList;
import java.util.List;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.graphics.Display;

public class View {

	private List<View> subViews;
	private View superView;
	private Rectangle window;
	private WindowingTransformation transformation;
	private Color backgroundColor;
	private Color borderColor;
	private Controller controller;
	private Rectangle viewport;
	protected Model model;
	
	public View() {
		subViews = new LinkedList<View>();
		superView = null;
		controller = new Controller();
		controller.setView(this);
		window = new Rectangle(new Point(0.0,0.0), new Point(1.0,1.0));
		viewport = new Rectangle(new Point(0.0,0.0), new Point(1.0,1.0));
		transformation = new WindowingTransformation();
		backgroundColor = Color.white;
		borderColor = Color.black;
	}
	
	public View windowViewport(Rectangle newWindow, Rectangle newViewport) {
		window = newWindow;
		viewport = newViewport;
		transformation = WindowingTransformation.windowToViewport(newWindow, newViewport);
		return this;
	}
	
	public void setModel(Model m) {
		if (m != model) {
			if (model != null) 
				model.removeView(this);
			model = m;
			if (model != null)
				model.addView(this);
			
			if (controller != null)
				controller.setModel(m);
		}
		update();
	}
	
	public boolean isTopView() { return superView == null; }
	
	public void setWindow(Rectangle newWindow) {
		window = newWindow;
		transformation = WindowingTransformation.windowToViewport(newWindow, viewport);
	}
	
	public void setViewport(Rectangle newViewport) {
		viewport = newViewport;
		transformation = WindowingTransformation.windowToViewport(window, newViewport);		
	}
	
	public void setBackgroundColor(Color color) {
		backgroundColor = color;
	}
	
	public void setBorderColor(Color color) {
		borderColor = color;
	}

	public WindowingTransformation displayTransformation() {
		if (isTopView())
			return transformation;
		else
			return superView.displayTransformation().compose(transformation);
	}
	
	public Rectangle displayBox() {
		if (isTopView())
			return displayTransformation().applyTo(window);
		else
			return displayTransformation().applyTo(window).intersect(superView.displayBox());
	}
	
	public void display() {
		displayBorder();
		displayView();
		displaySubViews();
	}
	
	public void displayBorder() {
		
		Display.instance().fillRect(displayBox(), backgroundColor);
		
		Display.instance().drawRect(displayBox(), borderColor);
	}

	public void displayView() {
	}

	public void displaySubViews() {
		for(View view : subViews)
			view.display();
	}

	public List<View> getSubViews() {
		return subViews;
	}

	public void addSubview(View subView) {
		subViews.add(subView);
		subView.superView = this;
	}

	public boolean containsPoint(Point cursorPoint) {
		return displayBox().containsPoint(cursorPoint);
	}

	public Controller getController() {
		return controller;
	}
	
	public void setController(Controller controller) {
		this.controller = controller;
		if (controller != null) {
			controller.setView(this);
			controller.setModel(model);
		}
	}

	public View subViewWantingControl() {
		for(View sub : subViews) {
			if (sub.controller.isControlWanted())
				return sub;
		}
		return null;
	}

	public void update() {
		display();
	}

	public Rectangle getWindow() {
		return window;
	}
	
	public Rectangle getViewport() {
		return viewport;
	}
	
	public View getSuperView() {
		return superView;
	}
	
	public View getTopView() {
		if (superView == null)
			return this;
		else 
			return superView.getTopView();
	}

	public WindowingTransformation inverseDisplayTransform() {
		return displayTransformation().invert();
	}
}
