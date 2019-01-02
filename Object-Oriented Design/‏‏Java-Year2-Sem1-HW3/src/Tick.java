import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import javafx.application.Platform;

public class Tick implements Runnable {
	private int sleepTime = 1000;
	private ClockPane clockPane;
	private Lock lock = new ReentrantLock();
	private Condition stopCondition = lock.newCondition();
	private boolean suspended = false;

	public Tick(ClockPane clockPane) {
		setClockPane(clockPane);
	}

	@Override
	public void run() {
		playClock();
	}

	protected void playClock() {
		while (true) {
			lock.lock();
			try {
				if (isSuspended()) {
					keepThreadSuspended();
				} else {
					keepThreadPlaying();
				}
			} finally {
				lock.unlock();
			}
		}
	}

	protected void keepThreadSuspended() {
		try {
			stopCondition.await();
		} catch (InterruptedException ex) {
			ex.printStackTrace();
		}
	}

	protected void keepThreadPlaying() {
		Platform.runLater(() -> {
			setAndPlayTime();
		});
		try {
			Thread.sleep(sleepTime);
		} catch (InterruptedException ex) {
			ex.printStackTrace();
		}
	}

	protected void setAndPlayTime() {
		getClockPane().setCurrentTime();
		speakCurrentTime();
		getClockPane().paintClock();
	}

	protected void speakCurrentTime() {
		if (getClockPane().getSecond() == 0) {
			new Thread(new AnnounceTimeOnSeparateThread(getClockPane().getHour(), getClockPane().getMinute())).start();
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
		if (lock.tryLock()) {
			try {
				setSuspended(false);
				stopCondition.signal();
			} finally {
				lock.unlock();
			}
		}
	}

	protected void pause() {
		setSuspended(true);
	}
}
