package application;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Optional;
import java.util.Scanner;

import javafx.application.Application;
import javafx.scene.control.Alert;
import javafx.scene.control.TextInputDialog;
import javafx.scene.control.Alert.AlertType;
import javafx.stage.Stage;

/* Name: Tamir Hazut
 * ID: 313521965
 */
public class AfekaInstruments extends Application {

	@Override
	public void start(Stage primaryStage) throws Exception {
		ArrayList<MusicalInstrument> allInstruments = new ArrayList<>();
		AfekaInventory<MusicalInstrument> afekaInventory = new AfekaInventory<>();
		File file = getInstrumentsFileFromUser();
		loadInstrumentsFromFile(file, allInstruments, afekaInventory, primaryStage);

		GUI mainScene = new GUI(afekaInventory);

		/* Stage Run */
		primaryStage.setTitle("Afeka Instruments Music Store");
		primaryStage.setScene(mainScene.getMainScene());
		primaryStage.show();
	}

	public static void main(String[] args) {
		launch(args);
	}

	public static File getInstrumentsFileFromUser() {
		boolean stopLoop = true;
		File file;
		TextInputDialog fileTextInputDialog = new TextInputDialog();
		fileTextInputDialog.setTitle("Confirmation");
		fileTextInputDialog.setHeaderText("Load Instruments From File");
		fileTextInputDialog.setContentText("Please enter file name:");
		Alert fileNotFound = new Alert(null);
		do {
			Optional<String> filePath = fileTextInputDialog.showAndWait();
			if (!filePath.isPresent()) {
				System.exit(1);
			}

			file = new File(filePath.get());
			stopLoop = file.exists() && file.canRead();
			if (!stopLoop) {
				setAlertProperties(fileNotFound, AlertType.ERROR, "File Error!",
						"Cannot read from file, please try again");
			}
		} while (!stopLoop);
		return file;
	}

	public static void loadInstrumentsFromFile(File file, ArrayList<MusicalInstrument> allInstruments,
			AfekaInventory<MusicalInstrument> afekaInventory, Stage primaryStage) {
		Scanner scanner = null;
		Alert alertMsg = new Alert(null);
		try {
			scanner = new Scanner(file);
			addAllInstruments(allInstruments, loadGuitars(scanner));
			addAllInstruments(allInstruments, loadBassGuitars(scanner));
			addAllInstruments(allInstruments, loadFlutes(scanner));
			addAllInstruments(allInstruments, loadSaxophones(scanner));
			addAllInstruments(afekaInventory.getInstrumentsInventoryArrayList(), allInstruments);
			if (allInstruments.size() == 0)
				setAlertProperties(new Alert(null), AlertType.INFORMATION, "Array Size", "Array is empty!");
			else
				setAlertProperties(alertMsg, AlertType.INFORMATION, "Success",
						"Instruments loaded from file successfully!");
		} catch (InputMismatchException | IllegalArgumentException ex) {
			setAlertProperties(alertMsg, AlertType.ERROR, "Error!", ex.getMessage());
			System.exit(1);
		} catch (FileNotFoundException ex) {
			setAlertProperties(alertMsg, AlertType.ERROR, "File Error!", "Cannot read from file, please try again");
			System.exit(2);
		} finally {
			scanner.close();
		}
	}

	public static ArrayList<Guitar> loadGuitars(Scanner scanner) {
		int numOfInstruments = scanner.nextInt();
		ArrayList<Guitar> guitars = new ArrayList<>(numOfInstruments);
		for (int i = 0; i < numOfInstruments; i++)
			guitars.add(new Guitar(scanner));
		return guitars;
	}

	public static ArrayList<Bass> loadBassGuitars(Scanner scanner) {
		int numOfInstruments = scanner.nextInt();
		ArrayList<Bass> bassGuitars = new ArrayList<>(numOfInstruments);
		for (int i = 0; i < numOfInstruments; i++)
			bassGuitars.add(new Bass(scanner));
		return bassGuitars;
	}

	public static ArrayList<Flute> loadFlutes(Scanner scanner) {
		int numOfInstruments = scanner.nextInt();
		ArrayList<Flute> flutes = new ArrayList<>(numOfInstruments);
		for (int i = 0; i < numOfInstruments; i++)
			flutes.add(new Flute(scanner));
		return flutes;
	}

	public static ArrayList<Saxophone> loadSaxophones(Scanner scanner) {
		int numOfInstruments = scanner.nextInt();
		ArrayList<Saxophone> saxophones = new ArrayList<>(numOfInstruments);
		for (int i = 0; i < numOfInstruments; i++)
			saxophones.add(new Saxophone(scanner));
		return saxophones;
	}

	public static void addAllInstruments(ArrayList<MusicalInstrument> instruments,
			ArrayList<? extends MusicalInstrument> moreInstruments) {
		for (int i = 0; i < moreInstruments.size(); i++) {
			instruments.add(moreInstruments.get(i));
		}
	}

	public static <T extends MusicalInstrument> void printInstruments(ArrayList<T> instruments) {
		if (instruments.isEmpty())
			System.out.println("There Are No Instruments To Show");
		else {
			for (int i = 0; i < instruments.size(); i++)
				System.out.println(instruments.get(i));
		}
	}

	public static <T extends MusicalInstrument> int getNumOfDifferentElements(ArrayList<T> instruments) {
		int numOfDifferentInstruments;
		ArrayList<T> differentInstruments = new ArrayList<>();
		System.out.println();
		for (int i = 0; i < instruments.size(); i++) {
			if (!differentInstruments.contains((instruments.get(i)))) {
				differentInstruments.add(instruments.get(i));
			}
		}
		if (differentInstruments.size() == 1)
			numOfDifferentInstruments = 0;
		else
			numOfDifferentInstruments = differentInstruments.size();
		return numOfDifferentInstruments;
	}

	public static <T extends MusicalInstrument> MusicalInstrument getMostExpensiveInstrument(ArrayList<T> instruments)
			throws CloneNotSupportedException {
		double maxPrice = 0;
		MusicalInstrument mostExpensive = instruments.get(0);
		for (int i = 0; i < instruments.size(); i++) {
			MusicalInstrument temp = instruments.get(i);
			if (temp.getPrice().doubleValue() > maxPrice) {
				maxPrice = temp.getPrice().doubleValue();
				mostExpensive = temp;
			}
		}
		return mostExpensive;
	}

	public static void startInventoryMenu(Scanner input, ArrayList<MusicalInstrument> allInstruments)
			throws IOException {
		AfekaInventory<MusicalInstrument> afekaInventory = new AfekaInventory<>();
		int choice, search;
		boolean exitMenu = false;
		do {
			System.out.println("\n-------------------------------------------------------------------------\n"
					+ "AFEKA MUSICAL INSTRUMENT INVENTORY MENU\n"
					+ "-------------------------------------------------------------------------\n"
					+ "1. Copy All String Instruments To Inventory\n" + "2. Copy All Wind Instruments To Inventory\n"
					+ "3. Sort Instruments By Brand And Price\n" + "4. Search Instrument By Brand And Price\n"
					+ "5. Delete Instrument\n" + "6. Delete all Instruments\n" + "7. Print Inventory Instruments\n"
					+ "Choose your option or any other key to EXIT\n");
			try {
				choice = input.nextInt();
			} catch (InputMismatchException ex) {
				choice = 0;
			}
			System.out.print("Your Option: ");
			switch (choice) {
			case 1:
				System.out.println("1\n");
				afekaInventory.addAllStringInstruments(allInstruments,
						afekaInventory.getInstrumentsInventoryArrayList());
				System.out.println("\nAll String Instruments Added Successfully!");
				break;
			case 2:
				System.out.println("2\n");
				afekaInventory.addAllWindInstruments(allInstruments, afekaInventory.getInstrumentsInventoryArrayList());
				System.out.println("\nAll Wind Instruments Added Successfully!");
				break;
			case 3:
				System.out.println("3\n");
				afekaInventory.sortByBrandAndPrice(afekaInventory.getInstrumentsInventoryArrayList());
				System.out.println("Instruments Sorted Successfully!");
				break;
			case 4:
				System.out.println("4\n");
				search = getSearchData(input, afekaInventory);
				if (search != -1)
					System.out.printf(":\n%s",
							afekaInventory.getInstrumentsInventoryArrayList().get(search).toString());
				else
					System.out.println("Instrument Not Found!");
				break;
			case 5:
				System.out.println("5\n");
				search = getSearchData(input, afekaInventory);
				if (search != -1) {
					System.out.printf(":\n%s\n",
							afekaInventory.getInstrumentsInventoryArrayList().get(search).toString());
					boolean removeInstrument = confirm(input);
					if (removeInstrument) {
						afekaInventory.removeInstruments(afekaInventory.getInstrumentsInventoryArrayList(),
								afekaInventory.getInstrumentsInventoryArrayList().get(search));
						System.out.println("Instrument Deleted Successfully!");
					}
				} else
					System.out.println("Instrument Not Found!");
				break;
			case 6:
				System.out.println("6\n");
				System.out.println("DELETE ALL INSTRUMENTS:");
				boolean removeInstrument = confirm(input);
				if (removeInstrument) {
					boolean removedAllInstruments = afekaInventory
							.removeAll(afekaInventory.getInstrumentsInventoryArrayList());
					if (removedAllInstruments)
						System.out.println("All Instruments Deleted Successfully!");
					else
						System.out.println("Not All Instruments Deleted Successfully!");
				}
				break;
			case 7:
				System.out.println("7\n");
				System.out.println(afekaInventory.toString());
				break;
			default:
				System.out.println("Exit\n");
				exitMenu = true;
				break;
			}
		} while (!exitMenu);
		input.close();
	}

	public static int getSearchData(Scanner choice, AfekaInventory<MusicalInstrument> afekaInventory) {
		Double price = null;
		choice.nextLine();
		System.out.print("Brand: ");
		String brand = choice.nextLine();
		do {
			try {
				System.out.print("Price: ");
				price = new Double(choice.nextDouble());
			} catch (InputMismatchException | NullPointerException e) {
				System.err.print("Invalid Choice!\n");
			}
			choice.nextLine();
		} while (price == null);
		int search = afekaInventory.binarySearchByBrandAndPrice(afekaInventory.getInstrumentsInventoryArrayList(),
				brand, price);
		return search;
	}

	public static boolean confirm(Scanner choice) {
		boolean chooseOption = false, selectedOption = false;
		while (!chooseOption) {
			System.out.println("Are You Sure?(Y/N)");
			String option = choice.next();
			if (option.equalsIgnoreCase("N")) {
				chooseOption = true;
			} else if (option.equalsIgnoreCase("Y")) {
				selectedOption = true;
				chooseOption = true;
			}
		}
		return selectedOption;
	}

	public static void setAlertProperties(Alert alert, AlertType alertType, String header, String contentText) {
		alert.setAlertType(alertType);
		alert.setHeaderText(header);
		alert.setContentText(contentText);
		alert.showAndWait();
	}
}
