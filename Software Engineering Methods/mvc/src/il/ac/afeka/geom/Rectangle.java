package il.ac.afeka.geom;

public class Rectangle {

	private Point origin, corner; 
	
	public Rectangle(Point origin, Point corner) {
		this.origin = origin;
		this.corner = corner;
	}
	
	public Point getOrigin() { return origin; }
	
	public Point getCorner() { return corner; }

	public Point getLowerLeft() { return origin.add(new Point(0.0, getHeight())); }

	public Point getUpperRight() { return corner.add(new Point(0.0, -getHeight())); }

	public Double getWidth() {
		return corner.getX() - origin.getX();
	}
	
	public Double getHeight() {
		return corner.getY() - origin.getY();
	}
	
	public Point getDimension() { return new Point(getWidth(), getHeight()); }
	
	public Rectangle intersect(Rectangle other) {
		return new Rectangle(origin.max(other.origin), corner.min(other.corner));
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + corner.hashCode();
		result = prime * result + origin.hashCode();
		return result;
	}

	@Override
	public String toString() {
		return "Rectangle [origin=" + origin + ", corner=" + corner + "]";
	}

	@Override
	public boolean equals(Object obj) {
		Rectangle other = (Rectangle) obj;
		return getClass() == obj.getClass() && origin.equals(other.origin) && corner.equals(other.corner);
	}

	public boolean containsPoint(Point point) {
		return origin.min(point).equals(origin) && corner.max(point).equals(corner); 
	}

	public Rectangle insetBy(Double d) {
		return new Rectangle(origin.add(d), corner.add(-d));
	}

	public Point getCenter() {
		return origin.add(corner).multBy(0.5);
	}
	
	public Rectangle alignCenter(Point newCenter) {
		Point difference = newCenter.subtract(getCenter());
		return new Rectangle(origin.add(difference), corner.add(difference));
	}

	public Rectangle translateBy(Point point) {
		return new Rectangle(origin.add(point), corner.add(point));
	}
	
	public Rectangle moveTo(Point point) {
		return new Rectangle(point, point.add(new Point(getWidth(), getHeight())));
	}
}
