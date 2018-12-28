import java.util.InputMismatchException;
import java.util.Scanner;

public class Guitar extends StringInstruments {
	private final static int MIN_NUM_OF_STRINGS_FOR_GUITAR = 6;
	private final static int MAX_NUM_OF_STRINGS_FOR_ELECTRIC_GUITAR = 8;
	protected final static int DEFAULT_NUM_OF_STRINGS = 6;

	private String type;

	private enum Types {
		ACOUSTIC, ELECTRIC, CLASSIC
	}

	public Guitar(Scanner input) {
		super(input);
		try {
			String cleanBuffer = input.nextLine(); // Not in use, Only to clean buffer.
			setType(input.nextLine());
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
	}

	public Guitar(double price, String brand, String type) {
		super(price, brand, DEFAULT_NUM_OF_STRINGS);
		setType(type);
	}

	public Guitar(double price, String brand, int numOfStrings, String type) {
		super(price, brand, numOfStrings);
		setType(type);
	}

	protected void setType(String type) {
		try {
			if (!type.equalsIgnoreCase(Types.ACOUSTIC.toString()) && !type.equalsIgnoreCase(Types.CLASSIC.toString())
					&& !type.equalsIgnoreCase(Types.ELECTRIC.toString())) {
				throw new IllegalArgumentException("Types for Guitars are: Acoustic, Classic, Electric Only!");
			}
		} catch (IllegalArgumentException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
		this.type = type.substring(0, 1).toUpperCase() + type.substring(1).toLowerCase();
		validateNumOfStrings(this.getNumOfStrings());
	}

	protected void validateNumOfStrings(int numOfStrings) {
		if (this.getType() != null) {
			if ((this.getType().equalsIgnoreCase(Types.ELECTRIC.toString())
					&& (numOfStrings < MIN_NUM_OF_STRINGS_FOR_GUITAR
							|| numOfStrings > MAX_NUM_OF_STRINGS_FOR_ELECTRIC_GUITAR))) {
				throw new InvalidFormatException(this.getType() + " Guitars number of strings is a number between "
						+ MIN_NUM_OF_STRINGS_FOR_GUITAR + " and " + MAX_NUM_OF_STRINGS_FOR_ELECTRIC_GUITAR + ".");
			} else if ((this.getType().equalsIgnoreCase(Types.ACOUSTIC.toString())
					|| this.getType().equalsIgnoreCase(Types.CLASSIC.toString()))
					&& numOfStrings != DEFAULT_NUM_OF_STRINGS) {
				throw new InvalidFormatException(this.getType() + " Guitars have " + DEFAULT_NUM_OF_STRINGS
						+ " strings, not " + this.getNumOfStrings() + ".");
			}
		}
	}

	public String getType() {
		return type;
	}

	@Override
	protected void setNumOfStrings(int numOfStrings) {
		try {
			validateNumOfStrings(numOfStrings);
		} catch (IllegalArgumentException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
		super.setNumOfStrings(numOfStrings);
	}

	@Override
	public boolean equals(Object obj) {
		if ((obj instanceof Guitar) && (this.getType().equalsIgnoreCase(((Guitar) obj).getType()))) {
			return super.equals(obj);
		}
		return false;
	}

	@Override
	public String toString() {
		return String.format("%s %10s", super.toString() + "Type:", getType());
	}
}