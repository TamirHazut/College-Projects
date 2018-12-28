class ExpandedAddressBookPane extends AddressBookPaneDecorator {
	private AddButton jbtAdd;
	private RedoButton jbtRedo;
	private UndoButton jbtUndo;

	public ExpandedAddressBookPane(MyAddressBookPane myAddressBookPane) {
		super(myAddressBookPane);
		if (myAddressBookPane != null) {
			jbtAdd = new AddButton(getMyAddressBookPane(), getRaf());
			jbtRedo = new RedoButton(getMyAddressBookPane(), getRaf());
			jbtUndo = new UndoButton(getMyAddressBookPane(), getRaf());
			configureButtons(jbtAdd, jbtRedo, jbtUndo);
			new FirstButton(getMyAddressBookPane(), getRaf()).Execute();
		}
	}

	@Override
	public void configureButtons(CommandButton... buttons) {
		super.configureButtons(buttons);
	}

}