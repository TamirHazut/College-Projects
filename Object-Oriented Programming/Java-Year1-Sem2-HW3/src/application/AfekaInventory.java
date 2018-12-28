package application;
import java.util.ArrayList;
import java.util.Collections;

/* Name: Tamir Hazut
 * ID: 313521965
 */
public class AfekaInventory<T extends MusicalInstrument> implements Inventory<T> {
	private ArrayList<T> instrumentsInventoryArrayList;
	private Double totalPrice;
	boolean isArraySorted;

	public AfekaInventory() {
		this.instrumentsInventoryArrayList = new ArrayList<>();
		setTotalPrice(0);
		setArraySorted(false);
	}

	public double getTotalPrice() {
		if (totalPrice == null)
			return 0;
		return totalPrice;
	}

	private void setTotalPrice(Number totalPrice) {
		this.totalPrice = calc(getTotalPrice(), totalPrice);
	}

	public boolean isArraySorted() {
		return isArraySorted;
	}

	private void setArraySorted(boolean isArraySorted) {
		this.isArraySorted = isArraySorted;
	}

	public ArrayList<T> getInstrumentsInventoryArrayList() {
		return instrumentsInventoryArrayList;
	}

	@Override
	public void addAllStringInstruments(ArrayList<? extends MusicalInstrument> instrumentsArray,
			ArrayList<? super MusicalInstrument> stringInstruments) {
		for (int i = 0; i < instrumentsArray.size(); i++) {
			if (instrumentsArray.get(i) instanceof StringInstrument) {
				addInstrument(stringInstruments, (MusicalInstrument) instrumentsArray.get(i));
			}
		}
	}

	@Override
	public void addAllWindInstruments(ArrayList<? extends MusicalInstrument> instrumentsArray,
			ArrayList<? super MusicalInstrument> windInstruments) {
		for (int i = 0; i < instrumentsArray.size(); i++) {
			if (instrumentsArray.get(i) instanceof WindInstrument) {
				addInstrument(windInstruments, (MusicalInstrument) instrumentsArray.get(i));
			}
		}
	}

	public <E1 extends Number, E2 extends Number> Double calc(E1 num1, E2 num2) {
		return (num1.doubleValue() + num2.doubleValue());
	}

	@Override
	public void sortByBrandAndPrice(ArrayList<T> instrumentArray) {
		Collections.sort(instrumentArray);
		setArraySorted(true);
	}

	@Override
	public int binarySearchByBrandAndPrice(ArrayList<T> instrumentsArray, String brand, Number price) {
		if (!isArraySorted)
			return -1;
		int middle, high = instrumentsArray.size() - 1, low = 0;
		while (high >= low) {
			middle = (high + low) / 2;
			int brandComapreResault = instrumentsArray.get(middle).getBrand().compareTo(brand);
			if (brandComapreResault == 0) {
				if (instrumentsArray.get(middle).getPrice().doubleValue() == price.doubleValue()) {
					return middle;
				} else if (instrumentsArray.get(middle).getPrice().doubleValue() > price.doubleValue()) {
					high = middle - 1;
				} else {
					low = middle + 1;
				}
			} else if (brandComapreResault > 0) {
				high = middle - 1;
			} else {
				low = middle + 1;
			}
		}
		return -1;
	}

	@Override
	public void addInstrument(ArrayList<? super MusicalInstrument> instrumentsArray, MusicalInstrument instrument) {
		setTotalPrice(instrument.getPrice().doubleValue());
		instrumentsArray.add(instrument);
		if (isArraySorted)
			setArraySorted(false);
	}

	@Override
	public <E extends T> boolean removeInstruments(ArrayList<T> instrumentsArray, E instrument) {
		if (instrumentsArray.isEmpty() || (instrumentsArray.indexOf(instrument) == -1))
			return false;
		setTotalPrice(-(instrument.getPrice().doubleValue()));
		instrumentsArray.remove(instrument);
		return true;
	}

	@Override
	public boolean removeAll(ArrayList<T> instrumentsArray) {
		boolean removeAllInstruments;
		while (!instrumentsArray.isEmpty()) {
			removeAllInstruments = removeInstruments(instrumentsArray,
					instrumentsArray.get(instrumentsArray.size() - 1));
			if (!removeAllInstruments)
				return false;
		}
		setArraySorted(false);
		return true;
	}

	@Override
	public String toString() {
		StringBuilder str = new StringBuilder("-------------------------------------------------------------------------\n"
				+ "AFEKA MUSICAL INSTRUMENTS INVENTORY\n"
				+ "-------------------------------------------------------------------------\n");
		for (int i = 0; i < getInstrumentsInventoryArrayList().size(); i++) {
			str.append(getInstrumentsInventoryArrayList().get(i).toString() + "\n");
		}
		return str.toString() + String.format("\nTotal Price: %-10.2f,  Sorted: %b\n",
				(getInstrumentsInventoryArrayList().isEmpty() ? 0.00 : getTotalPrice()), isArraySorted);
	}

}