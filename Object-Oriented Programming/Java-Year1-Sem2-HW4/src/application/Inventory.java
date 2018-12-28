package application;
import java.util.ArrayList;

/* Name: Tamir Hazut
 * ID: 313521965
 */
public interface Inventory<T extends MusicalInstrument> {

	public void addAllStringInstruments(ArrayList<? extends MusicalInstrument> instrumentsArray,
			ArrayList<? super MusicalInstrument> stringInstruments);

	public void addAllWindInstruments(ArrayList<? extends MusicalInstrument> instrumentsArray,
			ArrayList<? super MusicalInstrument> windInstruments);

	public void sortByBrandAndPrice(ArrayList<T> instrumentArray);

	public int binarySearchByBrandAndPrice(ArrayList<T> instrumentsArray, String brand, Number price);

	public void addInstrument(ArrayList<? super MusicalInstrument> instrumentsArray, MusicalInstrument instrument);

	public <E extends T> boolean removeInstruments(ArrayList<T> instrumentsArray, E instrument);

	public boolean removeAll(ArrayList<T> instrumentsArray);
}
