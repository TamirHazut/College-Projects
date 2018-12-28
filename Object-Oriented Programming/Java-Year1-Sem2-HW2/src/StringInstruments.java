import java.util.InputMismatchException;
import java.util.Scanner;

public class StringInstruments extends AfekaInstruments {
	private int numOfStrings;

	public StringInstruments(Scanner input) {
		super(input);
		try {
			setNumOfStrings(input.nextInt());
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException("String instruments must have at least 1 String");
		}
	}

	public StringInstruments(double price, String brand, int numOfStrings) {
		super(price, brand);
		setNumOfStrings(numOfStrings);
	}

	public int getNumOfStrings() {
		return numOfStrings;
	}

	protected void setNumOfStrings(int numOfStrings) {
		try {
			if (numOfStrings <= 0) {
				throw new IllegalArgumentException("String instruments must have at least 1 String");
			}
		} catch (IllegalArgumentException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
		this.numOfStrings = numOfStrings;
	}

	@Override
	public String toString() {
		return String.format("%s %3s | ", super.toString() + "Number of strings:", getNumOfStrings());
	}

	@Override
	public boolean equals(Object obj) {
		if ((obj instanceof StringInstruments)
				&& (this.getNumOfStrings() == ((StringInstruments) obj).getNumOfStrings())) {
			return super.equals(obj);
		}

		return false;
	}

}