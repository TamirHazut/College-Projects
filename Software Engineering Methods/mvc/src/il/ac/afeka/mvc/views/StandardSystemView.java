package il.ac.afeka.mvc.views;

import java.awt.Color;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.mvc.View;

public class StandardSystemView extends View {

	private View titleBar;
	
	public StandardSystemView(String title) {
		
		 titleBar = new TextView(title);
		 titleBar.windowViewport(new Rectangle(new Point(0.0, 0.0), new Point(1.0, 1.0)), new Rectangle(new Point(0.0, 0.0), new Point(1.0,0.125)));
		 titleBar.setBackgroundColor(Color.yellow);

		 this.addSubview(titleBar);

		 setController(new StandardSystemController());
	} 

	public boolean titleBarContainsPoint(Point cursorPoint) {
		
		return titleBar.containsPoint(cursorPoint);
	}
}
