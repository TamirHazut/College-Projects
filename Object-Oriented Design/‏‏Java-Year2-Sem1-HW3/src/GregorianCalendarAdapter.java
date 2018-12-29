import java.util.Calendar;
import java.util.GregorianCalendar;

public class GregorianCalendarAdapter implements Clock {
	private Calendar calendar = new GregorianCalendar();

	@Override
	public int getHour() {
		return calendar.get(Calendar.HOUR);
	}

	@Override
	public int getMinute() {
		return calendar.get(Calendar.MINUTE);
	}

	@Override
	public int getSecond() {
		return calendar.get(Calendar.SECOND);
	}

}