import java.util.InputMismatchException;
import java.util.Scanner;

public class Flute extends WindInstruments {
	private String type;

	private static enum Types {
		BASS, FLUTE, RECORDER
	}

	public Flute(Scanner input) {
		super(input);
		try {
			setType(input.nextLine());
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
	}

	public Flute(double price, String brand, String material, String type) {
		super(price, brand, material);
		try {
			setType(type);
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
	}

	public String getType() {
		return type;
	}

	protected void setType(String type) {
		try {
			if (!type.equalsIgnoreCase(Types.FLUTE.toString()) && !type.equalsIgnoreCase(Types.BASS.toString())
					&& !type.equalsIgnoreCase(Types.RECORDER.toString())) {
				throw new IllegalArgumentException("Types for Flutes are: Flute, Bass, Electric Only!");
			}
		} catch (IllegalArgumentException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
		this.type = type.substring(0, 1).toUpperCase() + type.substring(1).toLowerCase();
	}

	@Override
	public String toString() {
		return String.format("%s %10s", super.toString() + "Type:", getType());
	}

	@Override
	public boolean equals(Object obj) {
		if ((obj instanceof Flute) && (this.getType().equalsIgnoreCase(((Flute) obj).getType()))) {
			return super.equals(obj);
		}
		return false;
	}

}