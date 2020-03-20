package edu.afeka.se.mvc;

import static org.junit.Assert.*;

import org.junit.Test;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.mvc.WindowingTransformation;

public class TestWindowingTransformation {

	@Test
	public void test() {
		Rectangle window = new Rectangle(new Point(1.0,1.0), new Point(3.0,4.0));
		Rectangle viewport = new Rectangle(new Point(5.0,6.0), new Point(11.0,10.0));
		
		WindowingTransformation t = WindowingTransformation.windowToViewport(window, viewport);
		
		assertEquals(viewport, t.applyTo(window));
		
	}

}
