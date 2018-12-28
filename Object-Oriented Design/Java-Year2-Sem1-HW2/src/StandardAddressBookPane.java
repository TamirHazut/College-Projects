class StandardAddressBookPane extends AddressBookPaneDecorator implements MyAddressBookPane {
	private FirstButton jbtFirst;
	private NextButton jbtNext;
	private PreviousButton jbtPrevious;
	private LastButton jbtLast;

	public StandardAddressBookPane(MyAddressBookPane myAddressBookPane) {
		super(myAddressBookPane);
		jbtFirst = new FirstButton(getMyAddressBookPane(), getRaf());
		jbtNext = new NextButton(getMyAddressBookPane(), getRaf());
		jbtPrevious = new PreviousButton(getMyAddressBookPane(), getRaf());
		jbtLast = new LastButton(getMyAddressBookPane(), getRaf());
		configureButtons(jbtFirst, jbtNext, jbtPrevious, jbtLast);
		jbtFirst.Execute();
		getPane().setAnyButtonFirstClicked(false);
	}

	@Override
	public void configureButtons(CommandButton... buttons) {
		super.configureButtons(buttons);
	}

}