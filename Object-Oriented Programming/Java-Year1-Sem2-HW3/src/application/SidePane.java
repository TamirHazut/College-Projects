package application;

import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;

public class SidePane extends Pane {
	private final double DEFAULT_PADDING_SIZE = AfekaInstruments.DEFAULT_PADDING_SIZE;
	private VBox sidePane = new VBox();
	private Button buttonItem = new Button();
	private boolean funcionality; // true = next item | false = last item | default = last item (boolean default =
									// false)

	public SidePane(String buttonText, boolean funcionality, AfekaInventory<MusicalInstrument> afekaInventory,
			CenterPane centerPane) {
		setFuncionality(funcionality);
		setButtonItem(buttonText, afekaInventory, centerPane);
		setSidePane();
	}

	public VBox getSidePane() {
		return sidePane;
	}

	private void setSidePane() {
		sidePane.getChildren().add(getButtonItem());
		sidePane.setAlignment(Pos.CENTER);
		sidePane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
	}

	protected Button getButtonItem() {
		return buttonItem;
	}

	private void setButtonItem(String buttonText, AfekaInventory<MusicalInstrument> afekaInventory,
			CenterPane centerPane) {
		this.buttonItem.setText(buttonText);
		this.buttonItem.setOnAction(e -> {
				centerPane.setIndex(centerPane.getIndex(), (getFuncionality() ? "N" : "L"));
				centerPane.showData(centerPane.getIndex());
		});
	}

	protected Boolean getFuncionality() {
		return funcionality;
	}

	protected void setFuncionality(boolean funcionality) {
		this.funcionality = true;
	}

}
