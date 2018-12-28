package application;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Optional;
import java.util.Scanner;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.TextInputDialog;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.Pane;

public class AfekaInstruments extends Application {
	static final double DEFAULT_PADDING_SIZE = 10;
	static final double DEFAULT_SPACING_SIZE = 5;

	@Override
	public void start(Stage primaryStage) throws Exception {
		ArrayList<MusicalInstrument> allInstruments = new ArrayList<>();
		AfekaInventory<MusicalInstrument> afekaInventory = new AfekaInventory<>();
		File file = getInstrumentsFileFromUser();
		loadInstrumentsFromFile(file, allInstruments, afekaInventory, primaryStage);
	}

	public static void main(String[] args) {
		launch(args);
	}

	public static void startMainScene(Stage mainStage, AfekaInventory<MusicalInstrument> afekaInventory) {
		BorderPane mainSceneBorderPane = new BorderPane();
		Scene mainScene = new Scene(mainSceneBorderPane, 930, 400);
		CenterPane centerPane = new CenterPane(afekaInventory);
		TopPane topPane = new TopPane(afekaInventory, centerPane, mainSceneBorderPane);
		SidePane leftPane = new SidePane("<", false, afekaInventory, centerPane);
		SidePane rightPane = new SidePane(">", true, afekaInventory, centerPane);
		BottomPane bottomPane = new BottomPane(mainScene, centerPane, afekaInventory, topPane, mainSceneBorderPane);
		centerPane.showData(centerPane.getIndex());
		mainSceneBorderPane.setTop(topPane.getTopPane());
		mainSceneBorderPane.setCenter(centerPane.getCenterPane());
		mainSceneBorderPane.setLeft(leftPane.getSidePane());
		mainSceneBorderPane.setRight(rightPane.getSidePane());
		mainSceneBorderPane.setBottom(bottomPane.getBottomPane());
		setAndRequestFocus(mainSceneBorderPane);
		setKeyListeners(afekaInventory, mainScene, mainSceneBorderPane, centerPane, topPane, leftPane, rightPane,
				bottomPane);
		mainStage.setTitle("Afeka Instruments Music Store");
		mainStage.setScene(mainScene);
		mainStage.show();
	}

	public static void setAndRequestFocus(Pane pane) {
		pane.setFocusTraversable(true);
		pane.requestFocus();
	}

	public static void setKeyListeners(AfekaInventory<MusicalInstrument> afekaInventory, Scene mainScene,
			BorderPane mainSceneBorderPane, CenterPane centerPane, TopPane topPane, SidePane leftPane,
			SidePane rightPane, BottomPane bottomPane) {
		mainScene.setOnKeyPressed(e -> {
			if (e.getCode() == KeyCode.RIGHT) {
				centerPane.setIndex(centerPane.getIndex(), "N");
				centerPane.showData(centerPane.getIndex());
			} else if (e.getCode() == KeyCode.LEFT) {
				centerPane.setIndex(centerPane.getIndex(), "L");
				centerPane.showData(centerPane.getIndex());
			} else if (e.getCode() == KeyCode.A) {
				bottomPane.openAddStage(afekaInventory, centerPane, topPane, mainSceneBorderPane);
			} else if (e.getCode() == KeyCode.ENTER) {
				topPane.search(afekaInventory, topPane.getSearchField().getText(), centerPane, mainSceneBorderPane);
			} else if (e.getCode() == KeyCode.DELETE) {
				bottomPane.delItemFromScene(afekaInventory, centerPane);
			}
		});
	}

	public static File getInstrumentsFileFromUser() {
		boolean stopLoop = true;
		File file;
		TextInputDialog fileTextInputDialog = new TextInputDialog("instruments1b.txt");
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
			afekaInventory.addAllStringInstruments(allInstruments, afekaInventory.getInstrumentsInventoryArrayList());
			afekaInventory.addAllWindInstruments(allInstruments, afekaInventory.getInstrumentsInventoryArrayList());
			if (allInstruments.size() == 0)
				setAlertProperties(new Alert(null), AlertType.INFORMATION, "Array Size", "Array is empty!");
			else
				setAlertProperties(alertMsg, AlertType.INFORMATION, "Success",
						"Instruments loaded from file successfully!");
			startMainScene(primaryStage, afekaInventory);
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

	public static void setAlertProperties(Alert alert, AlertType alertType, String header, String contentText) {
		alert.setAlertType(alertType);
		alert.setHeaderText(header);
		alert.setContentText(contentText);
		alert.showAndWait();
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

}
