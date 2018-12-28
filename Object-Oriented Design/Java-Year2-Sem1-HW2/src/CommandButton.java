import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;

import javafx.scene.control.Button;

interface Command {
	public void Execute();
}

class CommandButton extends Button implements Command {
	public final static int NAME_SIZE = 32;
	public final static int STREET_SIZE = 32;
	public final static int CITY_SIZE = 20;
	public final static int STATE_SIZE = 2;
	public final static int ZIP_SIZE = 5;
	public final static int RECORD_SIZE = (NAME_SIZE + STREET_SIZE + CITY_SIZE + STATE_SIZE + ZIP_SIZE);
	protected AddressBookPaneNoButtons myAddressBookPane;
	protected RandomAccessFile raf;

	public CommandButton(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super();
		myAddressBookPane = pane;
		raf = r;
	}

	public void Execute() {
	}

	/** Write a record at the end of the file */
	public void writeAddress() {
		try {
			if ((getBasicAddressBookPane().GetName().length() > 0)
					|| (getBasicAddressBookPane().GetStreet().length() > 0)
					|| (getBasicAddressBookPane().GetCity().length() > 0)
					|| (getBasicAddressBookPane().GetState().length() > 0)
					|| (getBasicAddressBookPane().GetZip().length() > 0)) {
				raf.seek(raf.length());
				FixedLengthStringIO.writeFixedLengthString(getBasicAddressBookPane().GetName(), NAME_SIZE, raf);
				FixedLengthStringIO.writeFixedLengthString(getBasicAddressBookPane().GetStreet(), STREET_SIZE, raf);
				FixedLengthStringIO.writeFixedLengthString(getBasicAddressBookPane().GetCity(), CITY_SIZE, raf);
				FixedLengthStringIO.writeFixedLengthString(getBasicAddressBookPane().GetState(), STATE_SIZE, raf);
				FixedLengthStringIO.writeFixedLengthString(getBasicAddressBookPane().GetZip(), ZIP_SIZE, raf);
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

	/** Read a record at the specified position */
	public void readAddress(long position) throws IOException {
		if (!isEmpty()) {
			raf.seek(position);
			String name = FixedLengthStringIO.readFixedLengthString(NAME_SIZE, raf);
			String street = FixedLengthStringIO.readFixedLengthString(STREET_SIZE, raf);
			String city = FixedLengthStringIO.readFixedLengthString(CITY_SIZE, raf);
			String state = FixedLengthStringIO.readFixedLengthString(STATE_SIZE, raf);
			String zip = FixedLengthStringIO.readFixedLengthString(ZIP_SIZE, raf);
			getBasicAddressBookPane().SetName(name);
			getBasicAddressBookPane().SetStreet(street);
			getBasicAddressBookPane().SetCity(city);
			getBasicAddressBookPane().SetState(state);
			getBasicAddressBookPane().SetZip(zip);
		} else {
			myAddressBookPane.showBlankTextFields();
		}
	}

	public boolean isEmpty() throws IOException {
		return (raf.length() == 0);
	}

	protected AddressBookPaneNoButtons getBasicAddressBookPane() {
		return (AddressBookPaneNoButtons) myAddressBookPane;
	}

}

abstract class MementoButtons extends CommandButton {
	protected static ArrayList<AddressBookOriginator.AddressBookMemento> mementoList = new ArrayList<>();;
	protected static AddressBookOriginator expandedAddressBookOriginator = new AddressBookOriginator();
	protected static int savedStates = 0;
	protected static int currentState = 0;

	public MementoButtons(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super(pane, r);
		if (savedStates == 0) {
			initMemento();
		}
	}

	protected void addMemento() {
		try {
			raf.seek(raf.getFilePointer() - CommandButton.RECORD_SIZE * 2);
			String address = FixedLengthStringIO.readFixedLengthString(CommandButton.RECORD_SIZE, raf);
			getExpandedAddressBookOriginator().setState(address);
			add(getExpandedAddressBookOriginator().saveStateToMemento());
			if (currentState == savedStates) {
				savedStates++;
				currentState++;
			} else {
				savedStates = ++currentState;
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	protected void initMemento() {
		try {
			raf.seek(CommandButton.RECORD_SIZE * 2);
			while (raf.getFilePointer() <= raf.length()) {
				addMemento();
				raf.seek(raf.getFilePointer() + CommandButton.RECORD_SIZE * 2);
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	protected void add(AddressBookOriginator.AddressBookMemento memento) {
		mementoList.add(memento);
	}

	protected AddressBookOriginator.AddressBookMemento get(int index) {
		return mementoList.get(index);
	}

	protected AddressBookOriginator getExpandedAddressBookOriginator() {
		return expandedAddressBookOriginator;
	}
}

class AddButton extends MementoButtons {
	public AddButton(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Redo");
	}

	@Override
	public void Execute() {
		writeAddress();
	}
}

class RedoButton extends MementoButtons {
	public RedoButton(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Redo");
	}

	@Override
	public void Execute() {
		redoAddress();
	}

	protected void redoAddress() {
		try {
			if ((savedStates - 1) >= currentState) {
				getExpandedAddressBookOriginator().getStateToMemento(get(currentState));
				currentState++;
				raf.seek(raf.length());
				FixedLengthStringIO.writeFixedLengthString(getExpandedAddressBookOriginator().getState(),
						CommandButton.RECORD_SIZE, raf);
				new LastButton(myAddressBookPane, raf).Execute();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

class UndoButton extends MementoButtons {
	public UndoButton(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Undo");
	}

	@Override
	public void Execute() {
		undoAddress();
	}

	protected void undoAddress() {
		try {
			if ((currentState >= 1) && (raf.length() > 0)) {
				currentState--;
				getExpandedAddressBookOriginator().getStateToMemento(get(currentState));
				if (currentState > 0) {
					raf.seek(raf.length());
					new PreviousButton(myAddressBookPane, raf).Execute();
				} else {
					myAddressBookPane.showBlankTextFields();
				}
				raf.setLength(raf.length() - CommandButton.RECORD_SIZE * 2);
				AddressBookPaneInstancesManager.changeAfterFirstClick();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

class NextButton extends CommandButton {
	public NextButton(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Next");
	}

	@Override
	public void Execute() {
		showNext();
	}

	private void showNext() {
		try {
			long currentPosition = raf.getFilePointer();
			if (currentPosition < raf.length()) {
				readAddress(currentPosition);
			}
			if (!(myAddressBookPane.isAnyButtonFirstClicked())) {
				myAddressBookPane.setAnyButtonFirstClicked(true);
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}

class PreviousButton extends CommandButton {
	public PreviousButton(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Previous");
	}

	@Override
	public void Execute() {
		showPrevious();
	}

	private void showPrevious() {
		try {
			long currentPosition = raf.getFilePointer();
			if (currentPosition - 2 * 2 * RECORD_SIZE >= 0) {
				readAddress(currentPosition - 2 * 2 * RECORD_SIZE);
			} else {
				myAddressBookPane.showBlankTextFields();
			}
			if (!(myAddressBookPane.isAnyButtonFirstClicked())) {
				myAddressBookPane.setAnyButtonFirstClicked(true);
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}

class LastButton extends CommandButton {
	public LastButton(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Last");
	}

	@Override
	public void Execute() {
		showLast();
	}

	private void showLast() {
		try {
			long lastPosition = raf.length();
			if (lastPosition > 0) {
				readAddress(lastPosition - 2 * RECORD_SIZE);
			}
			if (!(myAddressBookPane.isAnyButtonFirstClicked())) {
				myAddressBookPane.setAnyButtonFirstClicked(true);
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}

class FirstButton extends CommandButton {
	public FirstButton(AddressBookPaneNoButtons pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("First");
	}

	@Override
	public void Execute() {
		showFirst();
	}

	private void showFirst() {
		try {
			if (raf.length() > 0) {
				readAddress(0);
			}
			if (!(myAddressBookPane.isAnyButtonFirstClicked())) {
				myAddressBookPane.setAnyButtonFirstClicked(true);
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}
