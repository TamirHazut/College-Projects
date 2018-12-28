
public class AddressBookOriginator {
	private String state;

	protected void setState(String newState) {
		state = newState;
	}

	protected String getState() {
		return state;
	}

	protected AddressBookMemento saveStateToMemento() {
		return new AddressBookMemento(state);
	}

	protected void getStateToMemento(AddressBookMemento memento) {
		setState(memento.getState());
	}
	
	public static class AddressBookMemento {
		private String state;

		private AddressBookMemento(String newState) {
			this.state = newState;
		}

		private String getState() {
			return state;
		}
	}
}