import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;

public class AfekaInstruments {
	private double price;
	private String brand;

	public static void main(String[] args) throws FileNotFoundException {
		getFile();
	}

	/*
	 * Method Purpose: Keep asking for a real file from the user.
	 */
	public static void getFile() throws FileNotFoundException {
		Scanner input = new Scanner(System.in);
		File file = new File("");
		do {
			try {
				System.out.println("Please enter instruments file name / path:");
				String path = input.nextLine();
				file = new File(path);
				if (!file.exists()) {
					throw new FileNotFoundException(
							"Error! \"" + file + "\" The system cannot find the file specified.");
				}
			} catch (FileNotFoundException ex) {
				System.err.println(ex.getMessage());
			}
		} while (!file.exists());
		try {
			analyzeFile(file);
		} catch (InvalidFormatException ex) {
			if (!ex.isEmpty())
				System.err.println(ex.getMessage());
			else
				System.out.println(ex.getMessage());
			input.close();
			System.exit(0);
		}
	}

	/*
	 * Method Purpose: Create a list of instruments that is being read from the file
	 * entered by the user.
	 */

	public static void analyzeFile(File file) throws FileNotFoundException {
		Scanner s = new Scanner(file);
		ArrayList dataAnalyzer = new ArrayList();
		addAllInstruments(dataAnalyzer, loadGuitars(s));
		addAllInstruments(dataAnalyzer, loadBass(s));
		addAllInstruments(dataAnalyzer, loadFlutes(s));
		addAllInstruments(dataAnalyzer, loadSaxophones(s));

		System.out.println("Instruments loaded from file successfully!\n");
		statistics(dataAnalyzer);
		s.close();
	}

	public static ArrayList loadGuitars(Scanner s) {
		ArrayList guitars = new ArrayList();
		try {
			int numOfGuitars = s.nextInt();
			for (int i = 0; i < numOfGuitars && s.hasNext(); i++) {
				guitars.add(new Guitar(s));
			}
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException();
		}
		return guitars;
	}

	public static ArrayList loadBass(Scanner s) {
		ArrayList bass = new ArrayList();
		try {
			int numOfBass = s.nextInt();
			for (int i = 0; i < numOfBass && s.hasNext(); i++) {
				bass.add(new Bass(s));
			}
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException("");
		}
		return bass;
	}

	public static ArrayList loadFlutes(Scanner s) {
		ArrayList flutes = new ArrayList();
		try {
			int numOfFlutes = s.nextInt();
			for (int i = 0; i < numOfFlutes && s.hasNext(); i++) {
				flutes.add(new Flute(s));
			}
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException();
		}
		return flutes;
	}

	public static ArrayList loadSaxophones(Scanner s) {
		ArrayList saxophones = new ArrayList();
		try {
			int numOfSaxophones = s.nextInt();
			for (int i = 0; i < numOfSaxophones && s.hasNext(); i++) {
				saxophones.add(new Saxophone(s));
			}
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException();
		}
		return saxophones;
	}

	public static void statistics(ArrayList list) {
		printInstruments(list);
		System.out.println("\nDifferent Instruments: " + getNumOfDifferentElements(list));
		System.out.println("\nMost Expensive Instrument:\n" + getMostExpensiveInstrument(list));
	}

	/*
	 * Method Purpose: Copy items from an ArrayList to the class ArrayList.
	 */
	public static void addAllInstruments(ArrayList list1, ArrayList list2) {
		for (int i = 0; i < list2.size(); i++) {
			list1.add(list2.get(i));
		}
	}

	/*
	 * Method Purpose: Print all items from the class ArrayList.
	 */
	public static void printInstruments(ArrayList list) {
		checkEmpty(list);
		for (int i = 0; i < list.size(); i++) {
			System.out.println(list.get(i).toString());
		}
	}

	public static void checkEmpty(ArrayList list) {
		if (list.isEmpty() || list == null) {
			throw new InvalidFormatException("There are no instruments in the store currently.", true);
		}
	}

	/*
	 * Method Purpose: Compare all instruments prices and prints the most expensive
	 * instrument.
	 */
	public static AfekaInstruments getMostExpensiveInstrument(ArrayList list) {
		checkEmpty(list);
		int indexForMostExpernsiveInstrument = 0;
		for (int i = 0; i < list.size(); i++) {
			if (list.get(i) instanceof AfekaInstruments && ((AfekaInstruments) list.get(i))
					.getPrice() > ((AfekaInstruments) list.get(indexForMostExpernsiveInstrument)).getPrice()) {
				indexForMostExpernsiveInstrument = i;
			}
		}
		return (AfekaInstruments) list.get(indexForMostExpernsiveInstrument);
	}

	/*
	 * Method Purpose: Count how many different instruments are there in the class
	 * ArrayList.
	 */
	public static int getNumOfDifferentElements(ArrayList list) {
		checkEmpty(list);
		int numOfDifferntInstruments = 1;
		for (int i = 0; i < list.size(); i++) {
			if (isDifferent(list, i)) {
				numOfDifferntInstruments++;
			}

		}
		return numOfDifferntInstruments;
	}

	private static boolean isDifferent(ArrayList list, int index) {
		for (int i = 1; i < list.size(); i++) {
			if (index != list.size() - 1 && i == index) {
				++i;
			}
			if ((list.get(index)).equals(list.get(i))) {
				return false;
			}
		}
		return true;
	}

	public AfekaInstruments(Scanner input) {
		try {
			setPrice(input.nextDouble());
			String cleanBuffer = input.nextLine(); // Don't do anything but clear buffer
			setBrand(input.nextLine());
		} catch (InputMismatchException ex) {
			throw new InvalidFormatException(ex.getMessage());
		}
	}

	public AfekaInstruments(double price, String brand) {
		setPrice(price);
		setBrand(brand);
	}

	public double getPrice() {
		return price;
	}

	protected void setPrice(double price) {
		if (price <= 0) {
			throw new InputMismatchException("Price must be a positive number!");
		}
		this.price = price;

	}

	public String getBrand() {
		return brand;
	}

	protected void setBrand(String brand) {
		this.brand = brand;
	}

	@Override
	public boolean equals(Object obj) {
		if ((obj instanceof AfekaInstruments) && (this.getBrand().equalsIgnoreCase(((AfekaInstruments) obj).getBrand()))
				&& (this.getPrice() == ((AfekaInstruments) obj).getPrice())) {
			return true;
		}
		return false;
	}

	@Override
	public String toString() {
		return String.format("%-10s %-10s | %s %10s, ", getBrand(), this.getClass().getCanonicalName(), "Price:",
				String.format("%.2f", getPrice()));
	}

}