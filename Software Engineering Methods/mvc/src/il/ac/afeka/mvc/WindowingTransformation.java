package il.ac.afeka.mvc;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.matrix.Matrix;

public class WindowingTransformation {

	private Matrix trans;
	
	public WindowingTransformation() {
		trans = Matrix.Identity(3);
	}
	
	private WindowingTransformation(Matrix t) {
		this.trans = t;
	}
	
	public WindowingTransformation compose(WindowingTransformation other) {
		
		return new WindowingTransformation(this.trans.multBy(other.trans));
	}
	
	public WindowingTransformation invert() {
		
		return new WindowingTransformation(this.trans.invert());
	}
	
	public WindowingTransformation scaleBy(Point scale) {
		
		return new WindowingTransformation(this.trans.multBy(scale.asScale()));
		
	}
	
	public WindowingTransformation translateBy(Point translation) {
		return new WindowingTransformation(this.trans.multBy(translation.asTranslation()));
	}
	
	public Point applyTo(Point point) {
		
		return new Point(trans.multBy(point.asVector()));		
	}

	public Rectangle applyTo(Rectangle rect) {
		
		return new Rectangle(applyTo(rect.getOrigin()), applyTo(rect.getCorner()));
	}

	public static WindowingTransformation windowToViewport(Rectangle window, Rectangle viewport) {

		WindowingTransformation scale = new WindowingTransformation().scaleBy(viewport.getDimension().divideBy(window.getDimension()));
		WindowingTransformation translation = new WindowingTransformation().translateBy(viewport.getOrigin().subtract(scale.applyTo(window).getOrigin()));
				
		return translation.compose(scale);
	}
}
