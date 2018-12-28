import java.util.InputMismatchException;
import java.util.Scanner;

public class Bass extends StringInstruments {
	private boolean fretless;

	private final static int MIN_NUM_OF_STRINGS_FOR_BASS_GUITAR = 4;
	private final static int MAX_NUM_OF_STRINGS_FOR_BASS_GUITAR = 6;

	public Bass(Scanner input) {
		super(input);
		try {
			setFretless(input.nextBoolean());
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException(
					"Whether a Bass Guitar is fretless or not, It is a boolean, any other string than \"True\" or \"False\" is not acceptable.");
		}
	}

	public Bass(double price, String brand, int numOfStrings, boolean fretless) {
		super(price, brand, numOfStrings);
		setFretless(fretless);
	}

	public void setFretless(Boolean fretless) {
		this.fretless = fretless;
	}

	public boolean isFretless() {
		return (this.fretless ? true : false);
	}

	@Override
	protected void setNumOfStrings(int numOfStrings) {
		try {
			if (numOfStrings < MIN_NUM_OF_STRINGS_FOR_BASS_GUITAR
					|| numOfStrings > MAX_NUM_OF_STRINGS_FOR_BASS_GUITAR) {
				throw new IllegalArgumentException("Bass Guitars number of strings is a number between "
						+ MIN_NUM_OF_STRINGS_FOR_BASS_GUITAR + " and " + MAX_NUM_OF_STRINGS_FOR_BASS_GUITAR + ".");
			}
		} catch (IllegalArgumentException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
		super.setNumOfStrings(numOfStrings);
	}

	@Override
	public boolean equals(Object obj) {
		if ((obj instanceof Bass) && (this.isFretless() && ((Bass) obj).isFretless())) {
			return super.equals(obj);
		}
		return false;
	}

	@Override
	public String toString() {
		return String.format("%s %6s", super.toString() + "Fretless:", (isFretless() ? "Yes" : "NO"));
	}

}