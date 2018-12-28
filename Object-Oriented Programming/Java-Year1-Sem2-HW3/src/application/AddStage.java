package application;

import java.text.NumberFormat;
import java.util.InputMismatchException;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.control.TextFormatter;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.util.converter.NumberStringConverter;

public class AddStage {
	private final double DEFAULT_PADDING_SIZE = AfekaInstruments.DEFAULT_PADDING_SIZE;
	private final double DEFAULT_VGAP_SPACING = 20;
	private final double DEFAULT_HGAP_SPACING = 30;
	private Stage addStage = new Stage();
	private ObservableList<String> instruments = FXCollections.observableArrayList("Guitar", "Bass", "Flute",
			"Saxophone");
	private ObservableList<String> guitarType = FXCollections.observableArrayList("Acoustic", "Classic", "Electric");
	private ObservableList<String> fluteType = FXCollections.observableArrayList("Bass", "Flute", "Recorder");
	private ObservableList<String> fluteMaterial = FXCollections.observableArrayList("Metal", "Plastic", "Wood");
	private BorderPane addSceneBorderPane = new BorderPane();
	private GridPane addSceneGridPane = new GridPane();
	private Scene addScene;
	private HBox topPane = new HBox();
	private HBox centerPane = new HBox();
	private HBox bottomPane = new HBox();
	private ComboBox<String> addComboBox = new ComboBox<>();
	private final TextField addSceneBrandTextField = new TextField();
	private final TextField addScenePriceTextField = new TextField();
	private final TextField addSceneNumberOfStringsTextField = new TextField();
	private final CheckBox fretlessGuitar = new CheckBox();
	private ComboBox<String> typeComboBox = new ComboBox<>();
	private ComboBox<String> materialComboBox = new ComboBox<>();

	public AddStage(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane mainSceneCenterPane,
			BorderPane mainSceneBorderPane) {
		setComboBox(afekaInventory, mainSceneCenterPane, mainSceneBorderPane);
		setAddScene();
		setAddStage();
	}

	public Stage getAddStage() {
		return addStage;
	}

	private void setAddStage() {
		addStage.setTitle("Afeka Instruments - Add New Instrument");
		addStage.setScene(getAddScene());
		addStage.show();
	}

	private Scene getAddScene() {
		return addScene;
	}

	private void setAddScene() {
		addScene = new Scene(getAddSceneBorderPane(), 300, 400);
	}

	private BorderPane getAddSceneBorderPane() {
		return addSceneBorderPane;
	}

	private HBox getTopPane() {
		return topPane;
	}

	private void setTopPane(Node node) {
		topPane.getChildren().add(node);
		topPane.setAlignment(Pos.CENTER);
		topPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		getAddSceneBorderPane().setTop(getTopPane());
	}

	private HBox getCenterPane() {
		return centerPane;
	}

	private void setCenterPane(Node node) {
		centerPane.getChildren().add(node);
		centerPane.setAlignment(Pos.CENTER);
		centerPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		getAddSceneBorderPane().setCenter(getCenterPane());
	}

	private HBox getBottomPane() {
		return bottomPane;
	}

	private void setBottomPane(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane mainSceneCenterPane,
			BorderPane mainSceneBorderPane) {
		final Button addButton = new Button("Add");
		bottomPane.getChildren().add(addButton);
		bottomPane.setAlignment(Pos.CENTER);
		bottomPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		getAddSceneBorderPane().setBottom(getBottomPane());
		addButton.setOnAction(e -> {
			try {
				checkTextFields(getComboBox().getValue().toString());
				checkNewInstrumentToAdd(getComboBox().getValue().toString(), afekaInventory, mainSceneBorderPane);
				mainSceneCenterPane.setIndex(afekaInventory.getInstrumentsInventoryArrayList().size() - 1);
				mainSceneCenterPane.showData(mainSceneCenterPane.getIndex());
			} catch (InputMismatchException ex) {
				AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error!", ex.getMessage());
				AfekaInstruments.setAndRequestFocus(addSceneBorderPane);
			}
		});
	}

	private void checkNewInstrumentToAdd(String comboBoxChoice, AfekaInventory<MusicalInstrument> afekaInventory,
			BorderPane mainSceneBorderPane) {
		String brand = addSceneBrandTextField.getText(), type;
		int numOfStrings;
		double price = Double.parseDouble(addScenePriceTextField.getText());
		switch (comboBoxChoice) {
		case "Guitar":
			numOfStrings = new Integer(addSceneNumberOfStringsTextField.getText());
			type = getTypeComboBox().getValue();
			afekaInventory.addInstrument(afekaInventory.getInstrumentsInventoryArrayList(),
					new Guitar(brand, price, numOfStrings, type));
			break;
		case "Bass":
			numOfStrings = new Integer(addSceneNumberOfStringsTextField.getText());
			boolean fretless = (fretlessGuitar.isSelected() ? true : false);
			afekaInventory.addInstrument(afekaInventory.getInstrumentsInventoryArrayList(),
					new Bass(brand, price, numOfStrings, fretless));
		case "Flute":
			String material = getMaterialComboBox().getValue();
			type = getTypeComboBox().getValue();
			afekaInventory.addInstrument(afekaInventory.getInstrumentsInventoryArrayList(),
					new Flute(brand, price, material, type));
			break;
		case "Saxophone":
			afekaInventory.addInstrument(afekaInventory.getInstrumentsInventoryArrayList(),
					new Saxophone(brand, price));
		}
		setAndRequestFocus(mainSceneBorderPane);
		getAddStage().close();
	}

	private void checkEmptyTextField(TextField textField, String emptyMessage) {
		if (textField.getText().isEmpty())
			throw new InputMismatchException(emptyMessage);
	}

	private void checkTextFields(String instrument) {
		int numOfStrings;
		checkEmptyTextField(addSceneBrandTextField, "Brand was not entered");
		checkEmptyTextField(addScenePriceTextField, "Price was not entered");
		switch (instrument) {
		case "Guitar":
			checkEmptyTextField(addSceneNumberOfStringsTextField, "Number of string was not entered");
			numOfStrings = Integer.parseInt(addSceneNumberOfStringsTextField.getText());
			if (numOfStrings < 0)
				throw new InputMismatchException("Number of strings cannot be negative!");
			if (getTypeComboBox().getValue().equals("Type"))
				throw new InputMismatchException("Type was not selected");
			break;
		case "Bass":
			checkEmptyTextField(addSceneNumberOfStringsTextField, "Number of string was not entered");
			numOfStrings = Integer.parseInt(addSceneNumberOfStringsTextField.getText());
			if (numOfStrings > Bass.MAX_NUM_OF_STRINGS || numOfStrings < Bass.MIN_NUM_OF_STRINGS)
				throw new InputMismatchException("Bass number of strings is a number between " + Bass.MIN_NUM_OF_STRINGS
						+ " and " + Bass.MAX_NUM_OF_STRINGS);
			break;
		case "Flute":
			if (getMaterialComboBox().getValue().equals("Material"))
				throw new InputMismatchException("Material was not selected");
			if (getTypeComboBox().getValue().equals("Type"))
				throw new InputMismatchException("Type was not selected");
			break;
		}
	}

	private ComboBox<String> getComboBox() {
		return addComboBox;
	}

	private void setComboBox(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane mainSceneCenterPane,
			BorderPane mainSceneBorderPane) {
		addComboBox.getItems().addAll(getInstruments());
		addComboBox.setValue("Choose Instrument Type Here");
		setCenterPane(getComboBox());
		addComboBox.setOnAction(e -> {
			setAddSceneGridPane(getComboBox().getValue());
			getAddSceneGridPane().setVgap(DEFAULT_VGAP_SPACING);
			getAddSceneGridPane().setHgap(DEFAULT_HGAP_SPACING);
			if (getAddSceneBorderPane().getTop() == null) {
				setTopPane(getComboBox());
				setCenterPane(getAddSceneGridPane());
				setBottomPane(afekaInventory, mainSceneCenterPane, mainSceneBorderPane);
			}
			setAndRequestFocus(getCenterPane());
		});
	}

	public void setTypeComboBox(ObservableList<String> types) {
		typeComboBox.getItems().clear();
		typeComboBox.getItems().addAll(types);
		typeComboBox.setValue("Type");
	}

	public ComboBox<String> getTypeComboBox() {
		return typeComboBox;
	}

	public void setMaterialComboBox(ObservableList<String> materials) {
		materialComboBox.getItems().clear();
		materialComboBox.getItems().addAll(materials);
		materialComboBox.setValue("Material");
	}

	public ComboBox<String> getMaterialComboBox() {
		return materialComboBox;
	}

	private NumberFormat setNumberFormatForTextFields() {
		NumberFormat format = NumberFormat.getIntegerInstance();
		format.setGroupingUsed(false);
		return format;
	}

	private void setMusicalInstrumentFields() {
		addScenePriceTextField
				.setTextFormatter(new TextFormatter<>(new NumberStringConverter(setNumberFormatForTextFields())));
		getAddSceneGridPane().addRow(0, new Text("Brand:"), addSceneBrandTextField);
		getAddSceneGridPane().addRow(1, new Text("Price:"), addScenePriceTextField);
	}

	private void setStringInstrumentFields() {
		addSceneNumberOfStringsTextField
				.setTextFormatter(new TextFormatter<>(new NumberStringConverter(setNumberFormatForTextFields())));
		getAddSceneGridPane().addRow(2, new Text("Number of strings:"), addSceneNumberOfStringsTextField);
	}

	private void setGuitarFields() {
		setTypeComboBox(getGuitarType());
		getAddSceneGridPane().addRow(3, new Text("Guitar Type:"), getTypeComboBox());
		setTextFieldPromt("Guitar", addSceneBrandTextField, addScenePriceTextField, addSceneNumberOfStringsTextField);
	}

	private void setBassFields() {
		getAddSceneGridPane().addRow(3, new Text("Fretless:"), fretlessGuitar);
		setTextFieldPromt("Bass", addSceneBrandTextField, addScenePriceTextField, addSceneNumberOfStringsTextField);
	}

	private void setFluteFields() {
		setTypeComboBox(getFluteType());
		setMaterialComboBox(getFluteMaterial());
		getAddSceneGridPane().addRow(2, new Text("Material:"), getMaterialComboBox());
		getAddSceneGridPane().addRow(3, new Text("Flute Type"), getTypeComboBox());
		setTextFieldPromt("Flute", addSceneBrandTextField, addScenePriceTextField, new TextField(null));
	}

	private void setSaxophoneFields() {
		setTextFieldPromt("Saxophone", addSceneBrandTextField, addScenePriceTextField);
	}

	private GridPane getAddSceneGridPane() {
		return addSceneGridPane;
	}

	private void setAddSceneGridPane(String instrument) {
		getAddSceneGridPane().getChildren().clear();
		getAddSceneGridPane().setAlignment(Pos.CENTER);
		setMusicalInstrumentFields();
		addRowsByInstrument(instrument, addSceneBrandTextField, addScenePriceTextField, typeComboBox);
	}

	private void addRowsByInstrument(String instrument, TextField addSceneBrandTextField,
			TextField addScenePriceTextField, ComboBox<String> typeComboBox) {
		if (instrument.equals("Guitar") || instrument.equals("Bass")) {
			setStringInstrumentFields();
			if (instrument.equals("Guitar")) {
				setGuitarFields();
			} else {
				setBassFields();
			}
		} else if (instrument.equals("Flute")) {
			setFluteFields();
		} else if (instrument.equals("Saxophone")) {
			setSaxophoneFields();
		}
	}

	private void setTextFieldPromt(String instrument, TextField addSceneBrandTextField,
			TextField addScenePriceTextField, TextField addSceneNumberOfStringsTextField) {
		if (instrument.equals("Guitar")) {
			addSceneBrandTextField.setPromptText("Ex: Gibson");
			addScenePriceTextField.setPromptText("Ex: 7500");
			addSceneNumberOfStringsTextField.setPromptText("Ex: 6");
		} else if (instrument.equals("Bass")) {
			addSceneBrandTextField.setPromptText("Ex: Fender Jaz");
			addScenePriceTextField.setPromptText("Ex: 7500");
			addSceneNumberOfStringsTextField.setPromptText("Ex: 4");
		} else if (instrument.equals("Flute")) {
			addSceneBrandTextField.setPromptText("Ex: Levit");
			addScenePriceTextField.setPromptText("Ex: 300");
		}
	}

	private void setTextFieldPromt(String instrument, TextField addSceneBrandTextField,
			TextField addScenePriceTextField) {
		if (instrument.equals("Saxophone")) {
			addSceneBrandTextField.setPromptText("Ex: Jupiter");
			addScenePriceTextField.setPromptText("Ex: 5000");
		}
	}

	private void setAndRequestFocus(Pane pane) {
		pane.setFocusTraversable(true);
		pane.requestFocus();
	}

	protected ObservableList<String> getInstruments() {
		return instruments;
	}

	protected ObservableList<String> getGuitarType() {
		return guitarType;
	}

	protected ObservableList<String> getFluteType() {
		return fluteType;
	}

	protected ObservableList<String> getFluteMaterial() {
		return fluteMaterial;
	}

}
