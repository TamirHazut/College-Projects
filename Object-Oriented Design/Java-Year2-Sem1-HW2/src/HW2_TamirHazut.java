import java.util.ArrayList;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class HW2_TamirHazut extends Application {
	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		int numberOfAddressBooksToOpen = 3;
		startAddressBooks(numberOfAddressBooksToOpen);
	}

	public void startAddressBooks(int numOfInstances) {
		ArrayList<MyAddressBookPane> addressBookPaneList = new ArrayList<MyAddressBookPane>();
		for (int i = 0; i < numOfInstances; i++) {
			MyAddressBookPane abp = AddressBookPaneInstancesManager.getInstance();
			addressBookPaneList.add(abp);
			if (abp != null) {
				showStage(new Stage(), new Scene(addressBookPaneList.get(i).getPane()));
			}
		}
	}

	public void showStage(Stage stage, Scene scene) {
		scene.getStylesheets().add("styles.css");
		stage.setTitle("AddressBook");
		stage.setScene(scene);
		stage.setAlwaysOnTop(true);
		stage.show();
	}
}
