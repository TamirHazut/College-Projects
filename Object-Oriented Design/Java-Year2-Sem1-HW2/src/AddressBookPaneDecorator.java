import java.io.RandomAccessFile;

abstract class AddressBookPaneDecorator implements MyAddressBookPane {
	private MyAddressBookPane myAddressBookPane;

	public AddressBookPaneDecorator(MyAddressBookPane myAddressBookPane) {
		this.myAddressBookPane = myAddressBookPane;
	}

	protected AddressBookPaneNoButtons getMyAddressBookPane() {
		return myAddressBookPane.getPane();
	}

	@Override
	public void configureButtons(CommandButton... buttons) {
		this.getMyAddressBookPane().configureButtons(buttons);
	}

	@Override
	public RandomAccessFile getRaf() {
		return this.getMyAddressBookPane().getRaf();
	}

	@Override
	public AddressBookPaneNoButtons getPane() {
		return this.getMyAddressBookPane().getPane();
	}
}