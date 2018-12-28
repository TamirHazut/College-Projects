import java.util.InputMismatchException;
import java.util.Scanner;

public class WindInstruments extends AfekaInstruments {
	private String material;

	private static enum Materials {
		METAL, WOOD, PLASTIC
	}

	public WindInstruments(Scanner input) {
		super(input);
		try {
			setMaterial(input.nextLine());
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
	}

	public WindInstruments(double price, String brand, String material) {
		super(price, brand);
		setMaterial(material);
	}

	public String getMaterial() {
		return material;
	}

	protected void setMaterial(String material) {
		try {
			if (!material.equalsIgnoreCase(Materials.METAL.toString())
					&& !material.equalsIgnoreCase(Materials.WOOD.toString())
					&& !material.equalsIgnoreCase(Materials.PLASTIC.toString())) {
				throw new IllegalArgumentException("Materials for wind instruments are: Metal, Wood or Plastic Only!");
			}
		} catch (IllegalArgumentException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
		this.material = material.substring(0, 1).toUpperCase() + material.substring(1).toLowerCase();
	}

	@Override
	public String toString() {
		return String.format("%s %13s | ", super.toString() + "Made of:", getMaterial());
	}

	@Override
	public boolean equals(Object obj) {
		if ((obj instanceof WindInstruments)
				&& (this.getMaterial().equalsIgnoreCase(((WindInstruments) obj).getMaterial()))) {
			return super.equals(obj);
		}
		return false;
	}

}