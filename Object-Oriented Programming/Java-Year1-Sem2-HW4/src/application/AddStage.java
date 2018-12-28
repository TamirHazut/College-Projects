package application;

import java.text.NumberFormat;

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

/* Name: Tamir Hazut
 * ID: 313521965
 */
public class AddStage extends Stage {
	private final double DEFAULT_PADDING_SIZE = 10;
	private final double DEFAULT_VGAP_SPACING = 20;
	private final double DEFAULT_HGAP_SPACING = 30;

	private final static String INSTRUMENT_TYPE[] = { "Guitar", "Bass", "Flute", "Saxophone" };

	private BorderPane addSceneBorderPane = new BorderPane();
	private GridPane addSceneGridPane = new GridPane();
	private Scene addScene = new Scene(addSceneBorderPane, 300, 400);

	private ObservableList<String> instruments = FXCollections.observableArrayList(INSTRUMENT_TYPE);
	private ObservableList<String> guitarType = FXCollections.observableArrayList(Guitar.GUITAR_TYPE);
	private ObservableList<String> fluteType = FXCollections.observableArrayList(Flute.FLUET_TYPE);
	private ObservableList<String> fluteMaterial = FXCollections
			.observableArrayList(WindInstrument.WIND_INSTRUMENT_MATERIAL);

	private ComboBox<String> addComboBox = new ComboBox<>();

	private final TextField addSceneBrandTextField = new TextField();
	private final TextField addScenePriceTextField = new TextField();

	private final TextField addSceneNumberOfStringsTextField = new TextField();

	private final CheckBox fretlessGuitar = new CheckBox();

	private ComboBox<String> typeComboBox = new ComboBox<>();

	private ComboBox<String> materialComboBox = new ComboBox<>();

	public AddStage() {
		setAddStage();
	}

	protected Stage getAddStage() {
		return this;
	}

	private void setAddStage() {
		setAddComboBox();
		setTitle("Afeka Instruments - Add New Instrument");
		setScene(addScene);
	}

	protected void showAddStage() {
		show();
	}

	/* BorderPane */
	private HBox setTopPane(Node node) {
		HBox topPane = new HBox();
		topPane.getChildren().add(node);
		topPane.setAlignment(Pos.CENTER);
		topPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		addSceneBorderPane.setTop(topPane);
		return topPane;
	}

	private void setCenterPane(Node node) {
		HBox centerPane = new HBox();
		centerPane.getChildren().add(node);
		centerPane.setAlignment(Pos.CENTER);
		centerPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		addSceneBorderPane.setCenter(centerPane);
	}

	private void setBottomPane() {
		HBox bottomPane = new HBox();
		final Button addButton = new Button("Add");
		bottomPane.getChildren().add(addButton);
		bottomPane.setAlignment(Pos.CENTER);
		bottomPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		addSceneBorderPane.setBottom(bottomPane);
		addButton.setOnAction(e -> {
			if (checkEmptyTextFields())
				hide();
		});
	}

	/* ComboBox - Instrment */
	protected ComboBox<String> getAddComboBox() {
		return addComboBox;
	}

	private void setAddComboBox() {
		addComboBox.getItems().addAll(getInstruments());
		addComboBox.setValue("Choose Instrument Type Here");
		setCenterPane(getAddComboBox());
		addComboBox.setOnAction(e -> {
			setAddSceneGridPane(getAddComboBox().getValue());
			addSceneGridPane.setVgap(DEFAULT_VGAP_SPACING);
			addSceneGridPane.setHgap(DEFAULT_HGAP_SPACING);
			if (addSceneBorderPane.getTop() == null) {
				setTopPane(getAddComboBox());
				setCenterPane(addSceneGridPane);
				setBottomPane();
			}
			setAndRequestFocus(addSceneBorderPane);
		});
	}

	/* ComboBox - Type */
	public ComboBox<String> getTypeComboBox() {
		return typeComboBox;
	}

	public void setTypeComboBox(ObservableList<String> types) {
		typeComboBox.getItems().clear();
		typeComboBox.getItems().addAll(types);
		typeComboBox.setValue("Type");
	}

	/* ComboBox - Material */
	public ComboBox<String> getMaterialComboBox() {
		return materialComboBox;
	}

	public void setMaterialComboBox(ObservableList<String> materials) {
		materialComboBox.getItems().clear();
		materialComboBox.getItems().addAll(materials);
		materialComboBox.setValue("Material");
	}

	/* GridPane Properties */
	private void setMusicalInstrumentFields() {
		addScenePriceTextField
				.setTextFormatter(new TextFormatter<>(new NumberStringConverter(setNumberFormatForTextFields())));
		addSceneGridPane.addRow(0, new Text("Brand:"), addSceneBrandTextField);
		addSceneGridPane.addRow(1, new Text("Price:"), addScenePriceTextField);
	}

	private void setStringInstrumentFields() {
		addSceneNumberOfStringsTextField
				.setTextFormatter(new TextFormatter<>(new NumberStringConverter(setNumberFormatForTextFields())));
		addSceneGridPane.addRow(2, new Text("Number of strings:"), addSceneNumberOfStringsTextField);
	}

	private void setGuitarFields() {
		setTypeComboBox(getGuitarType());
		addSceneGridPane.addRow(3, new Text("Guitar Type:"), getTypeComboBox());
		addSceneBrandTextField.setPromptText("Ex: Gibson");
		addScenePriceTextField.setPromptText("Ex: 7500");
		addSceneNumberOfStringsTextField.setPromptText("Ex: 6");
	}

	private void setBassFields() {
		addSceneGridPane.addRow(3, new Text("Fretless:"), fretlessGuitar);
		addSceneBrandTextField.setPromptText("Ex: Fender Jaz");
		addScenePriceTextField.setPromptText("Ex: 7500");
		addSceneNumberOfStringsTextField.setPromptText("Ex: 4");
	}

	private void setFluteFields() {
		setTypeComboBox(getFluteType());
		setMaterialComboBox(getFluteMaterial());
		addSceneGridPane.addRow(2, new Text("Material:"), getMaterialComboBox());
		addSceneGridPane.addRow(3, new Text("Flute Type"), getTypeComboBox());
		addSceneBrandTextField.setPromptText("Ex: Levit");
		addScenePriceTextField.setPromptText("Ex: 300");
	}

	private void setSaxophoneFields() {
		addSceneBrandTextField.setPromptText("Ex: Jupiter");
		addScenePriceTextField.setPromptText("Ex: 5000");
	}

	private void setAddSceneGridPane(String instrument) {
		addSceneGridPane.getChildren().clear();
		addSceneGridPane.setAlignment(Pos.CENTER);
		setMusicalInstrumentFields();
		addRowsByInstrument(instrument);
	}

	private void addRowsByInstrument(String instrument) {
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

	/* Lists */
	protected ObservableList<String> getInstruments() {
		return this.instruments;
	}

	protected ObservableList<String> getGuitarType() {
		return this.guitarType;
	}

	protected ObservableList<String> getFluteType() {
		return this.fluteType;
	}

	protected ObservableList<String> getFluteMaterial() {
		return this.fluteMaterial;
	}

	/* Others */
	private void setAndRequestFocus(Pane pane) {
		pane.setFocusTraversable(true);
		pane.requestFocus();
	}

	private NumberFormat setNumberFormatForTextFields() {
		NumberFormat format = NumberFormat.getIntegerInstance();
		format.setGroupingUsed(false);
		return format;
	}

	protected TextField getAddSceneBrandTextField() {
		return this.addSceneBrandTextField;
	}

	protected TextField getAddScenePriceTextField() {
		return this.addScenePriceTextField;
	}

	protected TextField getAddSceneNumberOfStringsTextField() {
		return this.addSceneNumberOfStringsTextField;
	}

	protected CheckBox getFretlessGuitar() {
		return this.fretlessGuitar;
	}

	private boolean checkEmptyTextField(TextField textField, String emptyMessage) {
		if (textField.getText().isEmpty()) {
			AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error", emptyMessage);
			return true;
		}
		return false;
	}

	protected boolean checkEmptyTextFields() {
		if (checkEmptyTextField(getAddSceneBrandTextField(), "Brand was not entered")
				|| checkEmptyTextField(getAddScenePriceTextField(), "Price was not entered"))
			return false;
		switch (getAddComboBox().getValue()) {
		case "Guitar":
			if (checkEmptyTextField(getAddSceneNumberOfStringsTextField(), "Number of string was not entered"))
				return false;
			if (getTypeComboBox().getValue().equals("Type")) {
				AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error", "Type was not selected");
				return false;
			}
			break;
		case "Bass":
			if (checkEmptyTextField(getAddSceneNumberOfStringsTextField(), "Number of string was not entered"))
				return false;
			break;
		case "Flute":
			if (getMaterialComboBox().getValue().equals("Material")) {
				AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error",
						"Material was not selected");
				return false;
			}
			if (getTypeComboBox().getValue().equals("Type")) {
				AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error", "Type was not selected");
				return false;
			}
			break;
		}
		return true;
	}

}
