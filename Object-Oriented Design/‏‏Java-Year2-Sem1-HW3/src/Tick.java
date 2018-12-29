
import javafx.application.Platform;

public class Tick implements Runnable {
	private int sleepTime = 1000;
	private ClockPane clockPane;
	private boolean suspended = false;

	public Tick(ClockPane clockPane) {
		setClockPane(clockPane);
	}

	@Override
	public void run() {
		moveClock();
	}

	protected void moveClock() {
		try {
			while (true) {
				if (isSuspended()) {
					Thread.yield();
				} else {
					Platform.runLater(() -> getClockPane().setCurrentTime());
					Thread.sleep(sleepTime);
					if (getClockPane().getSecond() == 0) {
						new Thread(new AnnounceTimeOnSeparateThread(new GregorianCalendarAdapter())).start();
					}
				}
			}
		} catch (InterruptedException ex) {
		}
	}

	protected boolean isSuspended() {
		return suspended;
	}

	protected void setSuspended(boolean suspended) {
		this.suspended = suspended;
	}

	protected ClockPane getClockPane() {
		return clockPane;
	}

	protected void setClockPane(ClockPane clockPane) {
		this.clockPane = clockPane;
	}

	protected void play() {
		setSuspended(false);
	}

	protected void pause() {
		setSuspended(true);
	}
}
