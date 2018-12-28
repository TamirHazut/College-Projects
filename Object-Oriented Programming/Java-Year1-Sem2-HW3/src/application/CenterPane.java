package application;

import javafx.geometry.Pos;
import javafx.scene.control.TextField;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;

public class CenterPane extends Pane {
	private VBox centerPane = new VBox();
	private GridPane centerGridPane = new GridPane();
	private final Text typeText = new Text("Type:");
	private TextField typeTextField = new TextField();
	private final Text brandText = new Text("Brand:");
	private TextField brandTextField = new TextField();
	private final Text priceText = new Text("Price:");
	private TextField priceTextField = new TextField();
	private AfekaInventory<MusicalInstrument> currentAfekaInventory;
	private int index;

	public CenterPane(AfekaInventory<MusicalInstrument> afekaInventory) {
		setIndex(0);
		setCurrentAfekaInventory(afekaInventory);
		setCenterGridPane();
		setCenterPane();
		getTypeTextField().setEditable(false);
		getBrandTextField().setEditable(false);
		getPriceTextField().setEditable(false);
	}

	public AfekaInventory<MusicalInstrument> getCurrentAfekaInventory() {
		return currentAfekaInventory;
	}

	public void setCurrentAfekaInventory(AfekaInventory<MusicalInstrument> currentAfekaInventory) {
		this.currentAfekaInventory = currentAfekaInventory;
	}

	private GridPane getCenterGridPane() {
		return centerGridPane;
	}

	private void setCenterGridPane() {
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
	}

	public VBox getCenterPane() {
		return centerPane;
	}

	protected TextField getTypeTextField() {
		return typeTextField;
	}

	protected TextField getBrandTextField() {
		return brandTextField;
	}

	protected TextField getPriceTextField() {
		return priceTextField;
	}

	private void setTypeTextField(String typeTextField) {
		this.typeTextField.setText(typeTextField);
	}

	private void setBrandTextField(String brandTextField) {
		this.brandTextField.setText(brandTextField);
	}

	private void setPriceTextField(Number priceTextField) {
		this.priceTextField.setText(priceTextField.toString());
	}

	public void showData(int index) {
		if (!getCurrentAfekaInventory().getInstrumentsInventoryArrayList().isEmpty()) {
			String type = getCurrentAfekaInventory().getInstrumentsInventoryArrayList().get(index).getClass()
					.getSimpleName();
			String brand = getCurrentAfekaInventory().getInstrumentsInventoryArrayList().get(index).getBrand();
			Number price = getCurrentAfekaInventory().getInstrumentsInventoryArrayList().get(index).getPrice();
			setTypeTextField(type);
			setBrandTextField(brand);
			setPriceTextField(price);
		} else {
			setTypeTextField("");
			setBrandTextField("");
			setPriceTextField(0);
		}
	}

	protected void setIndex(int index, String howToAct) {
		if (!getCurrentAfekaInventory().getInstrumentsInventoryArrayList().isEmpty()) {
			if (howToAct.equals("N")) {
				if (index == getCurrentAfekaInventory().getInstrumentsInventoryArrayList().size() - 1)
					index = 0;
				else
					index++;
			} else if (howToAct.equals("L")) {
				if (index == 0)
					index = getCurrentAfekaInventory().getInstrumentsInventoryArrayList().size() - 1;
				else
					index--;
			}
			this.index = index;
		}
	}

	protected int getIndex() {
		return index;
	}

	protected void setIndex(int index) {
		this.index = index;
	}

	private void setCenterPane() {
		centerPane.setAlignment(Pos.CENTER);
		centerPane.getChildren().add(getCenterGridPane());
	}
}
