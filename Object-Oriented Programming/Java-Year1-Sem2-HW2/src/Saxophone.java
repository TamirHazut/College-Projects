import java.util.Scanner;

public class Saxophone extends WindInstruments {
	private enum Materials {
		METAL
	}

	public Saxophone(Scanner input) {
		super(input);
	}

	public Saxophone(double price, String brand, String material) {
		super(price, brand, material);
	}

	@Override
	protected void setMaterial(String material) {
		try {
			if (!material.equalsIgnoreCase(Materials.METAL.toString())) {
				throw new IllegalArgumentException("Material for Saxophones is Metal Only!");
			}
		} catch (IllegalArgumentException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
		super.setMaterial(material.substring(0, 1).toUpperCase() + material.substring(1).toLowerCase());
	}

	@Override
	public boolean equals(Object obj) {
		if ((obj instanceof Saxophone)) {
			return super.equals(obj);
		}
		return false;
	}

}