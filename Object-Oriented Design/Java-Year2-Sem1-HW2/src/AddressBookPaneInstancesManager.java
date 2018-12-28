import java.util.ArrayList;

abstract class AddressBookPaneInstancesManager {
	private final static int MAX_SECONDERY_PANES = 2;
	private final static int MAX_INSTANCES = 3;
	private static int addressBookPanesCounter = 0;

	private static ArrayList<MyAddressBookPane> panesManager = new ArrayList<MyAddressBookPane>();

	public static MyAddressBookPane getInstance() {
		if (addressBookPanesCounter < MAX_SECONDERY_PANES) {
			addressBookPanesCounter++;
			panesManager.add(new StandardAddressBookPane(AddressBookPaneNoButtons.getInstance()));
			return panesManager.get(panesManager.size() - 1);
		} else if (addressBookPanesCounter < MAX_INSTANCES) {
			addressBookPanesCounter++;
			panesManager.add(
					new ExpandedAddressBookPane(new StandardAddressBookPane(AddressBookPaneNoButtons.getInstance())));
			return panesManager.get(panesManager.size() - 1);
		}
		System.out.printf("Singelton violation. Only %d panes were created\n", MAX_INSTANCES);
		return null;
	}

	public static void changeAfterFirstClick() {
		for (MyAddressBookPane a : panesManager) {
			if (!(a instanceof ExpandedAddressBookPane)) {
				if (a.getPane().isAnyButtonFirstClicked()) {
					new PreviousButton(a.getPane(), a.getRaf()).Execute();
				}
			}
		}
	}
}
