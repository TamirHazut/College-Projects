package il.ac.afeka.matrix;

import static org.junit.Assert.*;

import org.junit.Test;

public class TestMatrix {

	@Test
	public void testMultByMatrix() {
		
		assertEquals(Matrix.Identity(3).multBy(Matrix.Identity(3)), Matrix.Identity(3));
	}

	@Test
	public void testAddTo() {
		
		Matrix m1 = Matrix.Identity(3);
		Matrix m2 = Matrix.Identity(3);
		
		assertEquals(m1.addTo(m2), m1.multBy(2.0));
	}

	@Test
	public void testMultByDouble() {
		
		Matrix m = Matrix.random(3,2);
		
		assertEquals(m.multBy(1.0), m);
	}

	@Test
	public void testMultByVector3() {
		
		Matrix v = Matrix.random(3,1);
		Matrix m = Matrix.Identity(3);
		assertEquals(m.multBy(v), v);
	}

	@Test
	public void testInvert() {
		
		Matrix matrix = Matrix.random(3,3);
		
		assertTrue(matrix.invert().invert().equalsWithTolerance(matrix, 0.0001));
		
	}

}
