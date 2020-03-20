package il.ac.afeka.graphics;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.FontMetrics;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.GraphicsConfiguration;
import java.awt.GraphicsDevice;
import java.awt.GraphicsEnvironment;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Line2D;

import il.ac.afeka.geom.Point;
import il.ac.afeka.geom.Rectangle;
import il.ac.afeka.input.Mouse;

public class Display {

	private static Display theDisplay;
	
	public static Display instance() {
		
		if (theDisplay == null)
			theDisplay = new Display();
		
		return theDisplay;
	}

	private Frame mainFrame;
	private GraphicsDevice device;
	
	private Display() {
        GraphicsEnvironment env = GraphicsEnvironment.getLocalGraphicsEnvironment();
        device = env.getDefaultScreenDevice();
        
        GraphicsConfiguration gc = device.getDefaultConfiguration();
        mainFrame = new Frame(gc);
        mainFrame.setUndecorated(true);
        mainFrame.setIgnoreRepaint(true);
        mainFrame.addMouseListener(Mouse.instance());
        device.setFullScreenWindow(mainFrame);
	}
	
	public void fillRect(Rectangle rect, Color color) {
        Graphics g = mainFrame.getGraphics();
        g.setColor(color);
        g.fillRect(rect.getOrigin().getX().intValue(),rect.getOrigin().getY().intValue(), rect.getWidth().intValue(), rect.getHeight().intValue());
        g.dispose();

	}
	
	public void drawRect(Rectangle rect, Color color) {
        Graphics g = mainFrame.getGraphics();
        g.setColor(color);
        g.drawRect(rect.getOrigin().getX().intValue(),rect.getOrigin().getY().intValue(), rect.getWidth().intValue(), rect.getHeight().intValue());
        g.dispose();		
	}

	public void drawRectXOR(Rectangle rect, Color color, Color altColor) {
        Graphics g = mainFrame.getGraphics();
        g.setColor(color);
//      g.setXORMode(altColor);
        g.drawRect(rect.getOrigin().getX().intValue(),rect.getOrigin().getY().intValue(), rect.getWidth().intValue(), rect.getHeight().intValue());
        g.dispose();		
	}

	public void drawLine(Point start, Point end, Color color, int width) {
        Graphics2D g = (Graphics2D)mainFrame.getGraphics();
        g.setColor(color);
        g.setStroke(new BasicStroke(width));
        g.draw(new Line2D.Double(start.getX(), start.getY(), end.getX(), end.getY()));
        g.dispose();
	}
	
	public void drawCircle(Point center, Double radius, Color color, int width) {
        Graphics2D g = (Graphics2D)mainFrame.getGraphics();
        g.setColor(color);
        g.setStroke(new BasicStroke(width));
        g.draw(new Ellipse2D.Double(center.getX() - radius, center.getY() - radius, 2*radius, 2*radius));
        g.dispose();
		
	}
	
	public void text(Point point, String message, Color color) {
        Graphics g = mainFrame.getGraphics();
        g.setColor(color);
        g.drawString(message, point.getX().intValue(), point.getY().intValue());
        g.dispose();
	}
	
	public Point measureText(String message) {
		
        Graphics g = mainFrame.getGraphics();
		FontMetrics metrics = g.getFontMetrics(g.getFont());
        g.dispose();
        return new Point(metrics.stringWidth(message), metrics.getHeight());
	}
	
	public void close() {
       	device.setFullScreenWindow(null);
	}
}
