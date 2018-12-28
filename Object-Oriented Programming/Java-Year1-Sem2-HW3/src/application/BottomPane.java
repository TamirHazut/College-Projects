package application;

import java.util.Calendar;
import java.util.GregorianCalendar;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.KeyValue;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.layout.BorderPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Pane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.scene.text.Text;
import javafx.util.Duration;

public class BottomPane extends Pane {
	private final double DEFAULT_PADDING_SIZE = AfekaInstruments.DEFAULT_PADDING_SIZE;
	private final double DEFAULT_SPACING_SIZE = AfekaInstruments.DEFAULT_SPACING_SIZE;
	private VBox bottomPane = new VBox();
	private HBox bottomTopPane = new HBox();
	private final Button add = new Button("Add");
	private final Button del = new Button("Delete");
	private final Button clear = new Button("Clear");
	private Text sale = new Text("");
	private Timeline timeline;
	private boolean animationMoving;

	public BottomPane(Scene mainScene, CenterPane centerPane, AfekaInventory<MusicalInstrument> afekaInventory,
			TopPane topPane, BorderPane mainSceneBorderPane) {
		setSale(mainScene);
		setBottomTopPane(afekaInventory, centerPane, topPane, mainSceneBorderPane);
		setBottomPane();
	}

	private void setSale(Scene mainScene) {
		setCurrentTime();
		animationProperties(mainScene);
		sale.setFont(Font.font("Arial", FontWeight.BOLD, 16));
		sale.setFill(Color.RED);
		playAnimation();
		sale.setOnMouseEntered(e -> pauseAnimation());
		sale.setOnMouseExited(e -> playAnimation());
	}

	private Text getSale() {
		return sale;
	}

	public VBox getBottomPane() {
		return bottomPane;
	}

	private void setBottomPane() {
		bottomPane.getChildren().addAll(getBottomTopPane(), getSale());
		bottomPane.setAlignment(Pos.CENTER);
		bottomPane.setSpacing(DEFAULT_SPACING_SIZE);
		bottomPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
	}

	private HBox getBottomTopPane() {
		return bottomTopPane;
	}

	private void setBottomTopPane(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane centerPane,
			TopPane topPane, BorderPane mainSceneBorderPane) {
		bottomTopPane.getChildren().addAll(add, del, clear);
		bottomTopPane.setAlignment(Pos.CENTER);
		bottomTopPane.setSpacing(DEFAULT_SPACING_SIZE);
		bottomTopPane.setPadding(new Insets(DEFAULT_PADDING_SIZE));
		add.setOnAction(e -> openAddStage(afekaInventory, centerPane, topPane, mainSceneBorderPane));
		del.setOnAction(e -> delItemFromScene(afekaInventory, centerPane));
		clear.setOnAction(e -> clearItemsFromScene(afekaInventory, centerPane));
	}

	protected void clearItemsFromScene(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane centerPane) {
		afekaInventory.removeAll(afekaInventory.getInstrumentsInventoryArrayList());
		centerPane.setIndex(afekaInventory.getInstrumentsInventoryArrayList().size());
		centerPane.showData(centerPane.getIndex());
		System.out.println("");
	}

	protected void delItemFromScene(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane centerPane) {
		boolean deleted = afekaInventory.removeInstruments(afekaInventory.getInstrumentsInventoryArrayList(),
				afekaInventory.getInstrumentsInventoryArrayList().get(centerPane.getIndex()));
		if (deleted) {
			AfekaInstruments.setAlertProperties(new Alert(null), AlertType.INFORMATION, "Success",
					"Item deleted successfully");
			centerPane.setIndex(0);
			centerPane.showData(centerPane.getIndex());
		} else {
			AfekaInstruments.setAlertProperties(new Alert(null), AlertType.ERROR, "Error!", "Item was not deleted");
		}
	}

	protected void openAddStage(AfekaInventory<MusicalInstrument> afekaInventory, CenterPane centerPane,
			TopPane topPane, BorderPane mainSceneBorderPane) {
		if (!topPane.getSearchField().getText().isEmpty())
			topPane.getSearchField().clear();
		AddStage addStage = new AddStage(afekaInventory, centerPane, mainSceneBorderPane);
		addStage.getAddStage().show();
	}

	private void animationProperties(Scene mainScene) {
		Duration startDuration = Duration.ZERO;
		Duration endDuration = Duration.seconds(10);
		KeyValue startKeyValue = new KeyValue(getSale().translateXProperty(), -(mainScene.getWidth()));
		KeyFrame startKeyFrame = new KeyFrame(startDuration, startKeyValue);
		KeyValue endKeyValue = new KeyValue(getSale().translateXProperty(), mainScene.getWidth());
		KeyFrame endKeyFrame = new KeyFrame(endDuration, endKeyValue);
		timeline = new Timeline(startKeyFrame, endKeyFrame);
		timeline.setCycleCount(Timeline.INDEFINITE);
		timeline.setAutoReverse(true);
	}

	private Timeline getTimeline() {
		return timeline;
	}

	public void playAnimation() {
		if (!isAnimationMoves()) {
			getTimeline().play();
			setAnimationMoves(true);
		}
	}

	public void pauseAnimation() {
		if (isAnimationMoves()) {
			getTimeline().pause();
			setAnimationMoves(false);
		}
	}

	protected boolean isAnimationMoves() {
		return animationMoving;
	}

	protected void setAnimationMoves(boolean animationMoves) {
		this.animationMoving = animationMoves;
	}

	private void setCurrentTime() {
		final Timeline currentTime = new Timeline(new KeyFrame(Duration.seconds(0), new EventHandler<ActionEvent>() {
			@Override
			public void handle(ActionEvent actionEvent) {
				Calendar date = GregorianCalendar.getInstance();
				int year = date.get(Calendar.YEAR);
				int month = date.get(Calendar.MONTH);
				int day = date.get(Calendar.DAY_OF_MONTH);
				int hour = date.get(Calendar.HOUR_OF_DAY);
				int minute = date.get(Calendar.MINUTE);
				int second = date.get(Calendar.SECOND);
				getSale().setText(year + "-" + month + "-" + day + " " + hour + ":" + minute + ":" + second
						+ " Afeka Instrumnets Music Store $$$ ON SALE!!! $$$ Guitars, Basses, Flutes, Saxophones and more!");
			}
		}), new KeyFrame(Duration.seconds(1)));
		currentTime.setCycleCount(Animation.INDEFINITE);
		currentTime.play();
	}

}
