package application;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.input.KeyCode;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.util.Duration;

/* Name: Tamir Hazut
 * ID: 313521965
 */
public class GUI extends BorderPane {
	private final double DEFAULT_PADDING_SIZE = 10;
	private final double DEFAULT_SPACING_SIZE = 5;
	private boolean animationMoving;
	private int currentIndex;

	private AfekaInventory<MusicalInstrument> afekaInventory;
	private AfekaInventory<MusicalInstrument> searchAfekaInventory;

	private Scene mainScene = new Scene(getMainSceneBorderPane(), 930, 400);

	private final Text typeText = new Text("Type:");
	private final Text brandText = new Text("Brand:");
	private final Text priceText = new Text("Price:");
	private TextField typeTextField = new TextField();
	private TextField brandTextField = new TextField();
	private TextField priceTextField = new TextField();

	private TextField searchField = new TextField();

	public GUI(AfekaInventory<MusicalInstrument> afekaInventory) {
		setAfekaInventory(afekaInventory);
		setSearchAfekaInventory(afekaInventory);
		setMainSceneBorderPane();
		showData();
		setAndRequestFocus(getMainSceneBorderPane());
	}

	private void setMainSceneBorderPane() {
		setTop(setTop());
		setRight(setRight());
		setLeft(setLeft());
		setBottom(setBottom());
		setCenter(setCenter());
		setCurrentIndex(0);
		setKeyListeners();
	}

	protected BorderPane getMainSceneBorderPane() {
		return this;
	}

	protected Scene getMainScene() {
		return mainScene;
	}

	/* Top Layout and Properties */
	private HBox setTop() {
		final Button go = new Button("Go");
		go.setOnAction(e -> search());

		HBox.setHgrow(searchField, Priority.ALWAYS);
		searchField.setPromptText("Search...");

		HBox topPane = new HBox();
		topPane.getChildren().addAll(searchField, go);
		topPane.setAlignment(Pos.CENTER);
		topPane.setSpacing(DEFAULT_SPACING_SIZE);
		topPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		return topPane;
	}

	protected void search() {
		String searchWord = searchField.getText();
		if (searchWord != null) {
			AfekaInventory<MusicalInstrument> newAfekaInventory = new AfekaInventory<>();
			for (int i = 0; i < getAfekaInventory().getInstrumentsInventoryArrayList().size(); i++) {
				if (getAfekaInventory().getInstrumentsInventoryArrayList().get(i).toString().contains(searchWord)) {
					newAfekaInventory.addInstrument(newAfekaInventory.getInstrumentsInventoryArrayList(),
							getAfekaInventory().getInstrumentsInventoryArrayList().get(i));
				}
			}
			setSearchAfekaInventory(newAfekaInventory);
		} else {
			setSearchAfekaInventory(getAfekaInventory());
		}
		setCurrentIndex(0);
		showData();
		setAndRequestFocus(getMainSceneBorderPane());
	}

	/* Right Layout and Properties */
	private VBox setRight() {
		final Button rightButtonItem = new Button(">");
		rightButtonItem.setOnAction(e -> showNextItem());

		VBox rightPane = new VBox();
		rightPane.getChildren().add(rightButtonItem);
		rightPane.setAlignment(Pos.CENTER);
		rightPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		return rightPane;
	}

	protected void showNextItem() {
		if (getCurrentIndex() == getSearchAfekaInventory().getInstrumentsInventoryArrayList().size() - 1)
			setCurrentIndex(0);
		else
			setCurrentIndex(getCurrentIndex() + 1);
		showData();
	}

	/* Left Layout and Properties */
	private VBox setLeft() {
		final Button leftButtonItem = new Button("<");
		leftButtonItem.setOnAction(e -> showLastItem());

		VBox leftPane = new VBox();
		leftPane.getChildren().add(leftButtonItem);
		leftPane.setAlignment(Pos.CENTER);
		leftPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		return leftPane;
	}

	protected void showLastItem() {
		if (getCurrentIndex() == 0)
			setCurrentIndex(getSearchAfekaInventory().getInstrumentsInventoryArrayList().size() - 1);
		else
			setCurrentIndex(getCurrentIndex() - 1);
		showData();
	}

	/* Bottom Layout and Properties */
	private VBox setBottom() {
		final Button add = new Button("Add");
		final Button del = new Button("Delete");
		final Button clear = new Button("Clear");
		add.setOnAction(e -> openAddStage());
		del.setOnAction(e -> delItemFromScene());
		clear.setOnAction(e -> clearItemsFromScene());

		Text sale = new Text("Testing");
		Timeline timeline = animationProperties(sale);
		setSaleText(sale, timeline);

		HBox bottomTopPane = new HBox();
		bottomTopPane.getChildren().addAll(add, del, clear);
		bottomTopPane.setAlignment(Pos.CENTER);
		bottomTopPane.setSpacing(DEFAULT_SPACING_SIZE);
		bottomTopPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));

		VBox bottomPane = new VBox();
		bottomPane.getChildren().addAll(bottomTopPane, sale);
		bottomPane.setAlignment(Pos.CENTER);
		bottomPane.setSpacing(DEFAULT_SPACING_SIZE);
		bottomPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		return bottomPane;
	}

	private void setSaleText(Text sale, Timeline timeline) {
		setCurrentTime(sale);
		sale.setFont(Font.font("Arial", FontWeight.BOLD, 16));
		sale.setFill(Color.RED);
		playAnimation(timeline);
		sale.setOnMouseEntered(e -> pauseAnimation(timeline));
		sale.setOnMouseExited(e -> playAnimation(timeline));
	}

	private Timeline animationProperties(Text sale) {
		Duration startDuration = Duration.ZERO;
		Duration endDuration = Duration.seconds(10);
		KeyValue startKeyValue = new KeyValue(sale.translateXProperty(), -(getMainScene().getWidth()));
		KeyFrame startKeyFrame = new KeyFrame(startDuration, startKeyValue);
		KeyValue endKeyValue = new KeyValue(sale.translateXProperty(), getMainScene().getWidth());
		KeyFrame endKeyFrame = new KeyFrame(endDuration, endKeyValue);
		Timeline timeline = new Timeline(startKeyFrame, endKeyFrame);
		timeline.setCycleCount(Timeline.INDEFINITE);
		timeline.setAutoReverse(true);
		return timeline;
	}

	private void playAnimation(Timeline timeline) {
		if (!isAnimationMoves()) {
			timeline.play();
			setAnimationMoves(true);
		}
	}

	private void pauseAnimation(Timeline timeline) {
		if (isAnimationMoves()) {
			timeline.pause();
			setAnimationMoves(false);
		}
	}

	private boolean isAnimationMoves() {
		return animationMoving;
	}

	private void setAnimationMoves(boolean animationMoves) {
		this.animationMoving = animationMoves;
	}

	private void setCurrentTime(Text sale) {
		final Timeline currentTime = new Timeline(new KeyFrame(Duration.seconds(1), e -> {
			String date1 = LocalDateTime.now().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"));
			sale.setText(date1
					+ " Afeka Instrumnets Music Store $$$ ON SALE!!! $$$ Guitars, Basses, Flutes, Saxophones and more!");
		}));
		currentTime.setCycleCount(Animation.INDEFINITE);
		currentTime.play();
	}

	protected void clearItemsFromScene() {
		getAfekaInventory().removeAll(getAfekaInventory().getInstrumentsInventoryArrayList());
		getSearchAfekaInventory().removeAll(getSearchAfekaInventory().getInstrumentsInventoryArrayList());
		setCurrentIndex(0);
		showData();
	}

	protected void delItemFromScene() {
		boolean deleted = getAfekaInventory().removeInstruments(getAfekaInventory().getInstrumentsInventoryArrayList(),
				getAfekaInventory().getInstrumentsInventoryArrayList().get(getCurrentIndex()));
		if (deleted) {
			AfekaInstruments.setAlertProperties(new Alert(null), AlertType.INFORMATION, "Success",
					"Item deleted successfully");
			setCurrentIndex(0);
			showData();
		} else {
			AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error!", "Item was not deleted");
		}
	}

	protected void openAddStage() {
		AddStage addStage = new AddStage();
		addStage.getAddStage().setOnHiding(e -> {
			if (isTextFieldsOK(addStage)) {
				addNewInstrument(addStage);
				if ((!searchField.getText().isEmpty() && getAfekaInventory().getInstrumentsInventoryArrayList()
						.get(getAfekaInventory().getInstrumentsInventoryArrayList().size() - 1).toString()
						.contains(searchField.getText())) || searchField.getText().isEmpty()) {
					setCurrentIndex(getSearchAfekaInventory().getInstrumentsInventoryArrayList().size() - 1);
					showData();
				}
			}
			addStage.close();
			setAndRequestFocus(getMainSceneBorderPane());
		});
		addStage.showAddStage();
	}

	/* Center Layout and Properties */
	private VBox setCenter() {
		typeTextField.setEditable(false);
		brandTextField.setEditable(false);
		priceTextField.setEditable(false);

		GridPane centerGridPane = setCenterGridPane();

		VBox centerPane = new VBox();
		centerPane.setAlignment(Pos.CENTER);
		centerPane.getChildren().add(centerGridPane);
		return centerPane;
	}

	private GridPane setCenterGridPane() {
		GridPane centerGridPane = new GridPane();
		centerGridPane.setHgap(40);
		centerGridPane.setVgap(5);
		centerGridPane.add(typeText, 0, 0);
		centerGridPane.add(typeTextField, 1, 0);
		centerGridPane.add(brandText, 0, 1);
		centerGridPane.add(brandTextField, 1, 1);
		centerGridPane.add(priceText, 0, 2);
		centerGridPane.add(priceTextField, 1, 2);
		centerGridPane.setAlignment(Pos.CENTER);
		GridPane.setFillHeight(typeTextField, true);
		GridPane.setFillWidth(typeTextField, true);
		GridPane.setFillHeight(brandTextField, true);
		GridPane.setFillWidth(brandTextField, true);
		GridPane.setFillHeight(priceTextField, true);
		GridPane.setFillWidth(priceTextField, true);
		return centerGridPane;
	}

	private void showData() {
		if (!getSearchAfekaInventory().getInstrumentsInventoryArrayList().isEmpty()) {
			String type = getSearchAfekaInventory().getInstrumentsInventoryArrayList().get(getCurrentIndex()).getClass()
					.getSimpleName();
			String brand = getSearchAfekaInventory().getInstrumentsInventoryArrayList().get(getCurrentIndex())
					.getBrand();
			Number price = getSearchAfekaInventory().getInstrumentsInventoryArrayList().get(getCurrentIndex())
					.getPrice();
			typeTextField.setText(type);
			brandTextField.setText(brand);
			priceTextField.setText(price.toString());
		} else {
			typeTextField.setText("");
			brandTextField.setText("");
			priceTextField.setText("");
		}
	}

	protected int getCurrentIndex() {
		return currentIndex;
	}

	protected void setCurrentIndex(int currentIndex) {
		this.currentIndex = currentIndex;
	}

	/* Others */
	public static void setAndRequestFocus(Pane pane) {
		pane.setFocusTraversable(true);
		pane.requestFocus();
	}

	protected AfekaInventory<MusicalInstrument> getAfekaInventory() {
		return afekaInventory;
	}

	protected void setAfekaInventory(AfekaInventory<MusicalInstrument> afekaInventory) {
		this.afekaInventory = afekaInventory;
	}

	protected AfekaInventory<MusicalInstrument> getSearchAfekaInventory() {
		return searchAfekaInventory;
	}

	protected void setSearchAfekaInventory(AfekaInventory<MusicalInstrument> searchAfekaInventory) {
		this.searchAfekaInventory = searchAfekaInventory;
	}

	private void addNewInstrument(AddStage addStage) {
		MusicalInstrument instrument = null;
		String brand = addStage.getAddSceneBrandTextField().getText();
		Double price = Double.parseDouble(addStage.getAddScenePriceTextField().getText());
		int numOfStrings;
		String type;
		switch (addStage.getAddComboBox().getValue()) {
		case "Guitar":
			numOfStrings = Integer.parseInt(addStage.getAddSceneNumberOfStringsTextField().getText());
			type = addStage.getTypeComboBox().getValue();
			instrument = new Guitar(brand, price, numOfStrings, type);
			break;
		case "Bass":
			numOfStrings = Integer.parseInt(addStage.getAddSceneNumberOfStringsTextField().getText());
			boolean fretless = (addStage.getFretlessGuitar().isSelected() ? true : false);
			instrument = new Bass(brand, price, numOfStrings, fretless);
			break;
		case "Flute":
			String material = addStage.getMaterialComboBox().getValue();
			type = addStage.getTypeComboBox().getValue();
			instrument = new Flute(brand, price, material, type);
			break;
		case "Saxophone":
			instrument = new Saxophone(brand, price);
		}
		getAfekaInventory().addInstrument(getAfekaInventory().getInstrumentsInventoryArrayList(), instrument);
		getSearchAfekaInventory().addInstrument(getSearchAfekaInventory().getInstrumentsInventoryArrayList(),
				instrument);
	}

	private void setKeyListeners() {
		mainScene.setOnKeyPressed(e -> {
			if (e.getCode() == KeyCode.RIGHT) {
				showNextItem();
				setAndRequestFocus(getMainSceneBorderPane());
			} else if (e.getCode() == KeyCode.LEFT) {
				showLastItem();
				setAndRequestFocus(getMainSceneBorderPane());
			} else if (e.getCode() == KeyCode.A) {
				openAddStage();
			} else if (e.getCode() == KeyCode.ENTER) {
				search();
				setAndRequestFocus(getMainSceneBorderPane());
			} else if (e.getCode() == KeyCode.DELETE) {
				delItemFromScene();
				setAndRequestFocus(getMainSceneBorderPane());
			}
		});
	}

	protected boolean isTextFieldsOK(AddStage addStage) {
		if (addStage.getAddComboBox().getValue().toString().equals("Choose Instrument Type Here"))
			return false;
		if (!isMusicalTextFieldOK(addStage.getAddScenePriceTextField()))
			return false;
		switch (addStage.getAddComboBox().getValue()) {
		case "Guitar":
			if (!isGuitarFieldsOK(addStage.getAddSceneNumberOfStringsTextField(), addStage.getTypeComboBox()))
				return false;
			break;
		case "Bass":
			if (!isBassFieldsOK(addStage.getAddSceneNumberOfStringsTextField()))
				return false;
			break;
		}
		return true;
	}

	private boolean isBassFieldsOK(TextField addSceneNumberOfStringsTextField) {
		int numOfStrings = Integer.parseInt(addSceneNumberOfStringsTextField.getText());
		if (numOfStrings < Bass.MIN_NUM_OF_STRINGS || numOfStrings > Bass.MAX_NUM_OF_STRINGS) {
			AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error",
					"Bass number of strings is a number between " + Bass.MIN_NUM_OF_STRINGS + " and "
							+ Bass.MAX_NUM_OF_STRINGS);
			return false;
		}
		return true;
	}

	private boolean isGuitarFieldsOK(TextField addSceneNumberOfStringsTextField, ComboBox<String> typeComboBox) {
		int numOfStrings = Integer.parseInt(addSceneNumberOfStringsTextField.getText());
		switch (typeComboBox.getValue().toString()) {
		case "Classic":
			if (numOfStrings != Guitar.CLASSIC_NUM_OF_STRINGS) {
				AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error",
						"Classic Guitars have 6 strings, not " + numOfStrings);
				return false;
			}
			break;
		case "Acoustic":
			if (numOfStrings != Guitar.ACOUSTIC_NUM_OF_STRINGS) {
				AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error",
						"Acoustic Guitars have 6 strings, not " + numOfStrings);
				return false;
			}
			break;
		case "Electric":
			if (numOfStrings < Guitar.ELEC_MIN_NUM_OF_STRINGS || numOfStrings > Guitar.ELEC_MAX_NUM_OF_STRINGS) {
				AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error",
						"Acoustic Guitars have 6 strings, not " + numOfStrings);
				return false;
			}
		}
		return true;
	}

	private boolean isMusicalTextFieldOK(TextField addScenePriceTextField) {
		if (Double.parseDouble(addScenePriceTextField.getText()) < 0) {
			AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error",
					"Price must be a positive number!");
			return false;
		}
		return true;
	}
}
