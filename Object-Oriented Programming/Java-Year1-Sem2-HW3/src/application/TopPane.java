package application;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Priority;

public class TopPane extends Pane {
	private final double DEFAULT_PADDING_SIZE = AfekaInstruments.DEFAULT_PADDING_SIZE;
	private final double DEFAULT_SPACING_SIZE = AfekaInstruments.DEFAULT_SPACING_SIZE;
	private Button go = new Button("Go");
	private TextField searchField = new TextField();
	private HBox topPane = new HBox();

	public TopPane(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane centerPane,
			BorderPane mainSceneBorderPane) {
		setSearchField();
		setTopPane(afekaInventory, centerPane, mainSceneBorderPane);
	}

	public TextField getSearchField() {
		return searchField;
	}

	public Button getGo() {
		return go;
	}

	private void setSearchField() {
		HBox.setHgrow(searchField, Priority.ALWAYS);
		searchField.setPromptText("Search...");
	}

	public HBox getTopPane() {
		return topPane;
	}

	private void setTopPane(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane centerPane,
			BorderPane mainSceneBorderPane) {
		topPane.getChildren().addAll(getSearchField(), getGo());
		topPane.setAlignment(Pos.CENTER);
		topPane.setSpacing(DEFAULT_SPACING_SIZE);
		topPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		getGo().setOnAction(e -> search(afekaInventory, getSearchField().getText(), centerPane, mainSceneBorderPane));
	}

	protected void search(AfekaInventory<MusicalInstrument> afekaInventory, String searchWord, CenterPane centerPane,
			BorderPane mainSceneBorderPane) {
		if (searchWord != null) {
			AfekaInventory<MusicalInstrument> newAfekaInventory = new AfekaInventory<>();
			for (int i = 0; i < afekaInventory.getInstrumentsInventoryArrayList().size(); i++) {
				if (afekaInventory.getInstrumentsInventoryArrayList().get(i).toString().contains(searchWord)) {
					newAfekaInventory.addInstrument(newAfekaInventory.getInstrumentsInventoryArrayList(),
							afekaInventory.getInstrumentsInventoryArrayList().get(i));
				}
			}
			centerPane.setCurrentAfekaInventory(newAfekaInventory);

		} else {
			centerPane.setCurrentAfekaInventory(afekaInventory);
		}
		centerPane.setIndex(0);
		centerPane.showData(0);
		mainSceneBorderPane.setCenter(centerPane.getCenterPane());
		AfekaInstruments.setAndRequestFocus(mainSceneBorderPane);
	}

}
