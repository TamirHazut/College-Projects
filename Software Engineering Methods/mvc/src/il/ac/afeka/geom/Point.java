package il.ac.afeka.geom;

import il.ac.afeka.matrix.Matrix;

public class Point {

	private Double x;
	private Double y;
	
	public Point(Double x, Double y) {
		this.x = x;
		this.y = y;
	}
	
	public Point(Matrix vector) {
		x = vector.at(0,0);
		y = vector.at(1,0);	
	}
	
	public Point(Integer x, Integer y) {
		this.x = x.doubleValue();
		this.y = y.doubleValue();
	}

	public Double getX() { return x; }
	
	public Double getY() { return y; }

	public Matrix asVector() {
		
		Matrix result = new Matrix(3,1);
		
		result.putAt(0, 0, x);
		result.putAt(1, 0, y);
		result.putAt(2, 0, 1.0);
		
		return result;
	}

	public Matrix asScale() {
		
		Matrix result = Matrix.Identity(3);
		
		result.putAt(0,0,  x);
		result.putAt(1,1,  y);
		
		return result;
	}

	public Matrix asTranslation() {
		
		Matrix result = Matrix.Identity(3);
		
		result.putAt(0,2,  x);
		result.putAt(1,2,  y);
		
		return result;
	}

	public Point subtract(Point other) {
		return new Point(this.x - other.x, this.y - other.y);
	}
	
	public Point divideBy(Point other) {
		return new Point(this.x / other.x, this.y / other.y);
	}

	public Point multBy(Point other) {
		return new Point(this.x * other.x, this.y * other.y);
	}

	public Point multBy(Double d) {
		return new Point(this.x * d, this.y * d);
	}

	public Point max(Point other) {
		return new Point(Math.max(x, other.x), Math.max(y, other.y));
	}
	public Point min(Point other) {
		return new Point(Math.min(x, other.x), Math.min(y, other.y));
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		result = prime * result + ((x == null) ? 0 : x.hashCode());
		result = prime * result + ((y == null) ? 0 : y.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		return getClass() == obj.getClass() && x.equals(((Point)obj).x) && y.equals(((Point)obj).y);
	}

	@Override
	public String toString() {
		return x + "@" + y;
	}

	public Point add(Double quantity) {
		return new Point(x + quantity, y + quantity);
	}

	public Point add(Point other) {
		return new Point(x + other.x, y + other.y);
	}

}
