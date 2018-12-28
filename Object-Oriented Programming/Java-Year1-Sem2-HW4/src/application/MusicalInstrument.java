package application;

import java.util.InputMismatchException;
import java.util.Scanner;

/* Name: Tamir Hazut
 * ID: 313521965
 */
public abstract class MusicalInstrument implements InstrumentFunc<MusicalInstrument> {
	private Number price;
	private String brand;

	public MusicalInstrument(String brand, double price) {
		setBrand(brand);
		setPrice(price);
	}

	public MusicalInstrument(Scanner scanner) {
		double price = 0;
		String brand;

		try {
			price = scanner.nextDouble();
		} catch (InputMismatchException ex) {
			throw new InputMismatchException("Price not found!");
		}
		setPrice(price);
		scanner.nextLine();
		brand = scanner.nextLine();
		setBrand(brand);
	}

	protected String getBrand() {
		return brand;
	}

	protected void setBrand(String brand) {
		this.brand = brand;
	}

	protected Number getPrice() {
		return price;
	}

	protected void setPrice(Number price) {
		if (price.doubleValue() > 0) {
			if (Math.ceil(price.doubleValue()) == Math.floor(price.doubleValue()))
				price = new Integer(price.intValue());
			else
				price = new Double(price.doubleValue());
			this.price = price;
		} else
			throw new InputMismatchException("Price must be a positive number!");
	}

	protected boolean isValidType(String[] typeArr, String material) {
		for (int i = 0; i < typeArr.length; i++) {
			if (material.equals(typeArr[i])) {
				return true;
			}
		}
		return false;
	}

	@Override
	public int compareTo(MusicalInstrument o) {
		int brandDifference = this.getBrand().compareTo(o.getBrand());
		if (brandDifference == 0) {
			double priceDifference = (this.getPrice().doubleValue() - o.getPrice().doubleValue());
			if (priceDifference == 0.0)
				return 0;
			else if (priceDifference > 0)
				return 1;
			return -1;
		}
		return brandDifference;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o)
			return true;
		if (o == null || !(o instanceof MusicalInstrument))
			return false;

		MusicalInstrument otherInstrument = (MusicalInstrument) o;

		return getPrice().doubleValue() == otherInstrument.getPrice().doubleValue()
				&& getBrand().equals(otherInstrument.getBrand());
	}

	@Override
	public String toString() {
		return String.format("%-8s %-9s| Price: " + (getPrice() instanceof Double ? "%7.2f," : "%7d,"), getBrand(),
				getClass().getCanonicalName(), getPrice());
	}
}
