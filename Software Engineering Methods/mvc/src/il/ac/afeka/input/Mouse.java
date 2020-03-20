package il.ac.afeka.input;

import java.awt.MouseInfo;
import java.awt.PointerInfo;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import il.ac.afeka.geom.Point;
import il.ac.afeka.mvc.View;

public class Mouse implements MouseListener {

	private static Mouse theMouse;

	public static Mouse instance() {
		if (theMouse == null)
			theMouse = new Mouse();
		return theMouse;
	}

	private boolean button1Pressed;
	private boolean button2Pressed;
	private boolean button3Pressed;

	private boolean button1Released;
	private boolean button2Released;
	private boolean button3Released;

	public boolean button1Pressed() { boolean state = button1Pressed; button1Pressed = false; return state; }
	public boolean button2Pressed() { boolean state = button2Pressed; button2Pressed = false; return state; }
	public boolean button3Pressed() { boolean state = button3Pressed; button3Pressed = false; return state; }

	public boolean button1Released() { boolean state = button1Released; button1Released = false; return state; }
	public boolean button2Released() { boolean state = button2Released; button2Released = false; return state; }
	public boolean button3Released() { boolean state = button3Released; button3Released = false; return state; }

	public Point cursorPoint() {
		
		PointerInfo pointerInfo = MouseInfo.getPointerInfo();
		return new Point(pointerInfo.getLocation().getX(), pointerInfo.getLocation().getY());
	}

	@Override
	public void mouseClicked(MouseEvent e) {
	}

	@Override
	public void mousePressed(MouseEvent e) {
		if (e.getButton() == MouseEvent.BUTTON1) {
			button1Pressed = true;
			button1Released = false;
		}
		if (e.getButton() == MouseEvent.BUTTON2) {
			button2Pressed = true;
			button2Released = false;
		}
		if (e.getButton() == MouseEvent.BUTTON3) {
			button3Pressed = true;
			button3Released = false;
		}
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		if (e.getButton() == MouseEvent.BUTTON1) {
			button1Released = true;
			button1Pressed = false;
		}
		if (e.getButton() == MouseEvent.BUTTON2) {
			button2Released = true;
			button2Pressed = false;
		}
		if (e.getButton() == MouseEvent.BUTTON3) {
			button3Released = true;
			button3Pressed = false;
		}
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
}
