import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.ListIterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Priority;
import javafx.stage.Stage;

public class HW1_TamirHazut extends Application {
	public static void main(String[] args) {
		launch(args);
	}

	@Override
	public void start(Stage primaryStage) throws Exception {
		AddressBookPane pane = new AddressBookPane();
		Scene scene = new Scene(pane);
		scene.getStylesheets().add("styles.css");
		primaryStage.setTitle("AddressBook");
		primaryStage.setScene(scene);
		primaryStage.show();
		primaryStage.setAlwaysOnTop(true);
	}
}

class AddressBookPane extends GridPane {
	private RandomAccessFile raf;
	// Text fields
	private TextField jtfName = new TextField();
	private TextField jtfStreet = new TextField();
	private TextField jtfCity = new TextField();
	private TextField jtfState = new TextField();
	private TextField jtfZip = new TextField();
	// Buttons
	private AddButton jbtAdd;
	private FirstButton jbtFirst;
	private NextButton jbtNext;
	private PreviousButton jbtPrevious;
	private LastButton jbtLast;
	private Sort1Button jbtSort1;
	private Sort2Button jbtSort2;
	private IterButton jbtIter;
	public EventHandler<ActionEvent> ae = new EventHandler<ActionEvent>() {
		public void handle(ActionEvent arg0) {
			((Command) arg0.getSource()).Execute();
		}
	};

	public AddressBookPane() { // Open or create a random access file
		try {
			raf = new RandomAccessFile("address.dat", "rw");
		} catch (IOException ex) {
			System.out.print("Error: " + ex);
			System.exit(0);
		}
		jtfState.setAlignment(Pos.CENTER_LEFT);
		jtfState.setPrefWidth(80);
		jtfZip.setPrefWidth(60);
		jbtAdd = new AddButton(this, raf);
		jbtFirst = new FirstButton(this, raf);
		jbtNext = new NextButton(this, raf);
		jbtPrevious = new PreviousButton(this, raf);
		jbtLast = new LastButton(this, raf);
		jbtSort1 = new Sort1Button(this, raf);
		jbtSort2 = new Sort2Button(this, raf);
		jbtIter = new IterButton(this, raf);
		Label state = new Label("State");
		Label zp = new Label("Zip");
		Label name = new Label("Name");
		Label street = new Label("Street");
		Label city = new Label("City");
		// Panel p1 for holding labels Name, Street, and City
		GridPane p1 = new GridPane();
		p1.add(name, 0, 0);
		p1.add(street, 0, 1);
		p1.add(city, 0, 2);
		p1.setAlignment(Pos.CENTER_LEFT);
		p1.setVgap(8);
		p1.setPadding(new Insets(0, 2, 0, 2));
		GridPane.setVgrow(name, Priority.ALWAYS);
		GridPane.setVgrow(street, Priority.ALWAYS);
		GridPane.setVgrow(city, Priority.ALWAYS);
		// City Row
		GridPane adP = new GridPane();
		adP.add(jtfCity, 0, 0);
		adP.add(state, 1, 0);
		adP.add(jtfState, 2, 0);
		adP.add(zp, 3, 0);
		adP.add(jtfZip, 4, 0);
		adP.setAlignment(Pos.CENTER_LEFT);
		GridPane.setHgrow(jtfCity, Priority.ALWAYS);
		GridPane.setVgrow(jtfCity, Priority.ALWAYS);
		GridPane.setVgrow(jtfState, Priority.ALWAYS);
		GridPane.setVgrow(jtfZip, Priority.ALWAYS);
		GridPane.setVgrow(state, Priority.ALWAYS);
		GridPane.setVgrow(zp, Priority.ALWAYS);
		// Panel p4 for holding jtfName, jtfStreet, and p3
		GridPane p4 = new GridPane();
		p4.add(jtfName, 0, 0);
		p4.add(jtfStreet, 0, 1);
		p4.add(adP, 0, 2);
		p4.setVgap(1);
		GridPane.setHgrow(jtfName, Priority.ALWAYS);
		GridPane.setHgrow(jtfStreet, Priority.ALWAYS);
		GridPane.setHgrow(adP, Priority.ALWAYS);
		GridPane.setVgrow(jtfName, Priority.ALWAYS);
		GridPane.setVgrow(jtfStreet, Priority.ALWAYS);
		GridPane.setVgrow(adP, Priority.ALWAYS);
		// Place p1 and p4 into jpAddress
		GridPane jpAddress = new GridPane();
		jpAddress.add(p1, 0, 0);
		jpAddress.add(p4, 1, 0);
		GridPane.setHgrow(p1, Priority.NEVER);
		GridPane.setHgrow(p4, Priority.ALWAYS);
		GridPane.setVgrow(p1, Priority.ALWAYS);
		GridPane.setVgrow(p4, Priority.ALWAYS);
		// Set the panel with line border
		jpAddress.setStyle("-fx-border-color: grey;" + " -fx-border-width: 1;" + " -fx-border-style: solid outside ;");
		// Add buttons to a panel
		FlowPane jpButton = new FlowPane();
		jpButton.setHgap(5);
		jpButton.getChildren().addAll(jbtAdd, jbtFirst, jbtNext, jbtPrevious, jbtLast, jbtSort1, jbtSort2, jbtIter);
		jpButton.setAlignment(Pos.CENTER);
		GridPane.setVgrow(jpButton, Priority.NEVER);
		GridPane.setVgrow(jpAddress, Priority.ALWAYS);
		GridPane.setHgrow(jpButton, Priority.ALWAYS);
		GridPane.setHgrow(jpAddress, Priority.ALWAYS);
		// Add jpAddress and jpButton to the stage
		this.setVgap(5);
		this.add(jpAddress, 0, 0);
		this.add(jpButton, 0, 1);
		jbtAdd.setOnAction(ae);
		jbtFirst.setOnAction(ae);
		jbtNext.setOnAction(ae);
		jbtPrevious.setOnAction(ae);
		jbtLast.setOnAction(ae);
		jbtSort1.setOnAction(ae);
		jbtSort2.setOnAction(ae);
		jbtIter.setOnAction(ae);
		jbtFirst.Execute();
	}

	public void actionHandled(ActionEvent e) {
		((Command) e.getSource()).Execute();
	}

	public void SetName(String text) {
		jtfName.setText(text);
	}

	public void SetStreet(String text) {
		jtfStreet.setText(text);
	}

	public void SetCity(String text) {
		jtfCity.setText(text);
	}

	public void SetState(String text) {
		jtfState.setText(text);
	}

	public void SetZip(String text) {
		jtfZip.setText(text);
	}

	public String GetName() {
		return jtfName.getText();
	}

	public String GetStreet() {
		return jtfStreet.getText();
	}

	public String GetCity() {
		return jtfCity.getText();
	}

	public String GetState() {
		return jtfState.getText();
	}

	public String GetZip() {
		return jtfZip.getText();
	}
}

interface Command {
	public void Execute();
}

class CommandButton extends Button implements Command {
	public final static int NAME_SIZE = 32;
	public final static int STREET_SIZE = 32;
	public final static int CITY_SIZE = 20;
	public final static int STATE_SIZE = 10;
	public final static int ZIP_SIZE = 5;
	public final static int RECORD_SIZE = (NAME_SIZE + STREET_SIZE + CITY_SIZE + STATE_SIZE + ZIP_SIZE);
	public final static int RECORD_SIZE_IN_BYTES = RECORD_SIZE * 2;
	protected AddressBookPane p;
	protected RandomAccessFile raf;

	public CommandButton(AddressBookPane pane, RandomAccessFile r) {
		super();
		p = pane;
		raf = r;
	}

	public void Execute() {
	}

	/** Write a record at the end of the file */
	public void writeAddress() {
		try {
			raf.seek(raf.length());
			FixedLengthStringIO.writeFixedLengthString(p.GetName(), NAME_SIZE, raf);
			FixedLengthStringIO.writeFixedLengthString(p.GetStreet(), STREET_SIZE, raf);
			FixedLengthStringIO.writeFixedLengthString(p.GetCity(), CITY_SIZE, raf);
			FixedLengthStringIO.writeFixedLengthString(p.GetState(), STATE_SIZE, raf);
			FixedLengthStringIO.writeFixedLengthString(p.GetZip(), ZIP_SIZE, raf);
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}

	/** Read a record at the specified position */
	public void readAddress(long position) throws IOException {
		raf.seek(position);
		String name = FixedLengthStringIO.readFixedLengthString(NAME_SIZE, raf);
		String street = FixedLengthStringIO.readFixedLengthString(STREET_SIZE, raf);
		String city = FixedLengthStringIO.readFixedLengthString(CITY_SIZE, raf);
		String state = FixedLengthStringIO.readFixedLengthString(STATE_SIZE, raf);
		String zip = FixedLengthStringIO.readFixedLengthString(ZIP_SIZE, raf);
		p.SetName(name);
		p.SetStreet(street);
		p.SetCity(city);
		p.SetState(state);
		p.SetZip(zip);
	}

	public void optimizedBubbleSortBy(Comparator<String> comp) throws IOException {
		boolean swapped = true;
		for (long i = (raf.length() - RECORD_SIZE_IN_BYTES); i > 0 && swapped; i -= RECORD_SIZE_IN_BYTES) {
			swapped = false;
			for (long j = 0; j < i; j += RECORD_SIZE_IN_BYTES) {
				raf.seek(j);
				String address1 = FixedLengthStringIO.readFixedLengthString(RECORD_SIZE, raf);
				String address2 = FixedLengthStringIO.readFixedLengthString(RECORD_SIZE, raf);
				int compareResult = comp.compare(address1, address2);
				if (compareResult > 0) {
					swap(j, address1, address2);
					swapped = true;
				}
			}
		}
		new FirstButton(p, raf).Execute();
	}

	public void swap(long pointerInFileForAddress1, String address1, String address2) throws IOException {
		raf.seek(pointerInFileForAddress1);
		FixedLengthStringIO.writeFixedLengthString(address2, RECORD_SIZE, raf);
		FixedLengthStringIO.writeFixedLengthString(address1, RECORD_SIZE, raf);
	}
}

class MyComparator implements Comparator<String> {
	private enum typesToCompare {
		GENERAL, ZIPCODE
	};

	private int startIndexForSubstring;
	private int lastIndexForSubstring;
	private String type;

	public MyComparator(int startIndex, int lastIndex) {
		this(startIndex, lastIndex, typesToCompare.GENERAL.toString());
	}

	public MyComparator(int startIndex, int lastIndex, String type) {
		this.startIndexForSubstring = startIndex;
		this.lastIndexForSubstring = lastIndex;
		this.type = type.toUpperCase();
	}

	@Override
	public int compare(String o1, String o2) {
		if (this.type.equals(typesToCompare.ZIPCODE.toString())) {
			Integer v1 = Integer.parseInt(o1.substring(startIndexForSubstring, lastIndexForSubstring).trim());
			Integer v2 = Integer.parseInt(o2.substring(startIndexForSubstring, lastIndexForSubstring).trim());
			return v1.compareTo(v2);
		} else {
			String v1 = o1.substring(startIndexForSubstring, lastIndexForSubstring);
			String v2 = o2.substring(startIndexForSubstring, lastIndexForSubstring);
			return v1.compareTo(v2);
		}
	}
}

class StreetComparator implements Comparator<String> {
	@Override
	public int compare(String o1, String o2) {
		int compared = new MyComparator(CommandButton.NAME_SIZE - 1,
				CommandButton.STREET_SIZE + CommandButton.NAME_SIZE - 1).compare(o1, o2);
		if (compared == 0) {
			return o1.compareTo(o2);
		}
		return compared;
	}
}

class AddButton extends CommandButton {
	public AddButton(AddressBookPane pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Add");
	}

	@Override
	public void Execute() {
		writeAddress();
	}
}

class NextButton extends CommandButton {
	public NextButton(AddressBookPane pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Next");
	}

	@Override
	public void Execute() {
		try {
			long currentPosition = raf.getFilePointer();
			if (currentPosition < raf.length())
				readAddress(currentPosition);
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}

class PreviousButton extends CommandButton {
	public PreviousButton(AddressBookPane pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Previous");
	}

	@Override
	public void Execute() {
		try {
			long currentPosition = raf.getFilePointer();
			if (currentPosition - 2 * 2 * RECORD_SIZE >= 0)
				readAddress(currentPosition - 2 * 2 * RECORD_SIZE);
			else
				;
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}

class LastButton extends CommandButton {
	public LastButton(AddressBookPane pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Last");
	}

	@Override
	public void Execute() {
		try {
			long lastPosition = raf.length();
			if (lastPosition > 0)
				readAddress(lastPosition - 2 * RECORD_SIZE);
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}

class FirstButton extends CommandButton {
	public FirstButton(AddressBookPane pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("First");
	}

	@Override
	public void Execute() {
		try {
			if (raf.length() > 0)
				readAddress(0);
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}

class Sort1Button extends CommandButton {
	public Sort1Button(AddressBookPane pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Sort1");
	}

	@Override
	public void Execute() {
		try {
			if (raf.length() > 0)
				optimizedBubbleSortBy(new MyComparator(0, CommandButton.NAME_SIZE - 1));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}

class Sort2Button extends CommandButton {
	public Sort2Button(AddressBookPane pane, RandomAccessFile r) {
		super(pane, r);
		this.setText("Sort2");
	}

	@Override
	public void Execute() {
		try {
			if (raf.length() > 0)
				optimizedBubbleSortBy(new MyComparator(CommandButton.RECORD_SIZE - CommandButton.ZIP_SIZE - 1,
						CommandButton.RECORD_SIZE - 1, "ZIPCODE"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}

class IterButton extends CommandButton {
	private boolean firstRun = true;
	private Map<String, String> iteratedHashMap = null;
	private AddressBookPane pane;

	protected Map<String, String> getIteratedHashMap() {
		return iteratedHashMap;
	}

	protected void setIteratedHashMap(Map<String, String> iteratedHashMap) {
		this.iteratedHashMap = iteratedHashMap;
	}

	public IterButton(AddressBookPane pane, RandomAccessFile r) {
		super(pane, r);
		this.pane = pane;
		this.setText("Iter");
	}

	protected boolean isFirst() {
		return firstRun;
	}

	protected void setFirst(boolean isFirst) {
		this.firstRun = isFirst;
	}

	@Override
	public void Execute() {
		try {
			if (raf.length() > 0) {
				MyListIterator lit = (MyListIterator) listIterator(0);
				if (isFirst()) {
					setIteratedHashMap(startFileToMapIterator(lit));
					setFirst(false);
				} else {
					mapToTreeSet(lit, getIteratedHashMap());
				}
				new FirstButton(pane, raf).Execute();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	protected void mapToTreeSet(MyListIterator lit, Map<String, String> iteratedHashMap) throws IOException {
		Set<String> treeSet = new TreeSet<>(new StreetComparator());
		treeSet.addAll(iteratedHashMap.values());
		lit.clear();
		for (String s : treeSet)
			lit.add(s);
	}

	protected Map<String, String> startFileToMapIterator(MyListIterator lit) throws IOException {
		Map<String, String> iteratedHashMap = new HashMap<String, String>();
		while (lit.hasNext()) {
			String address = lit.next();
			String key = address.substring(0, RECORD_SIZE - ZIP_SIZE - 1);
			iteratedHashMap.put(key, address);
		}
		lit.clear();
		for (String s : iteratedHashMap.values())
			lit.add(s);
		return iteratedHashMap;
	}

	public java.util.ListIterator<String> listIterator(long current) throws IOException {
		return new MyListIterator(current, raf);
	}

	private class MyListIterator implements ListIterator<String> {
		private final int RECORD_SIZE = CommandButton.RECORD_SIZE;
		private final int RECORD_SIZE_IN_BYTES = CommandButton.RECORD_SIZE_IN_BYTES;
		private long lastPos = 0;
		private long currentPos = -1;

		protected RandomAccessFile raf;

		public MyListIterator(long currentPos, RandomAccessFile raf) throws IOException {
			setRaf(raf);
			setCurrentPos(currentPos);
		}

		protected void setCurrentPos(long currentPos) {
			this.currentPos = currentPos;
		}

		protected long getCurrentPos() {
			return this.currentPos;
		}

		protected long getLastPos() {
			return lastPos;
		}

		protected void setLastPos(long lastPos) {
			this.lastPos = lastPos;
		}

		protected void setRaf(RandomAccessFile raf) {
			this.raf = raf;
		}

		protected long size() throws IOException {
			return raf.length();
		}

		protected void clear() throws IOException {
			while (hasNext()) {
				raf.seek(0);
				setCurrentPos(0);
				next();
				remove();
			}
			setCurrentPos(0);
			setLastPos(0);
			raf.setLength(0);
		}

		@Override
		public boolean hasNext() {
			try {
				return (nextIndex() < size() / RECORD_SIZE_IN_BYTES);
			} catch (IOException e) {
				return false;
			}
		}

		@Override
		public boolean hasPrevious() {
			return (previousIndex() > 0);
		}

		@Override
		public String next() {
			try {
				if (hasNext()) {
					setLastPos(getCurrentPos());
					raf.seek(getCurrentPos());
					String strFromFile = FixedLengthStringIO.readFixedLengthString(RECORD_SIZE, raf);
					setCurrentPos(raf.getFilePointer());
					return strFromFile;
				}
				return null;
			} catch (IOException e) {
				return null;
			}
		}

		@Override
		public String previous() {
			try {
				if (hasPrevious()) {
					long calcedNewPos = getCurrentPos() - RECORD_SIZE_IN_BYTES;
					raf.seek(calcedNewPos);
					String strFromFile = FixedLengthStringIO.readFixedLengthString(RECORD_SIZE, raf);
					setCurrentPos(calcedNewPos);
					return strFromFile;
				}
				return null;
			} catch (IOException e) {
				return null;
			}
		}

		@Override
		public int nextIndex() {
			return ((int) getCurrentPos() / RECORD_SIZE_IN_BYTES);
		}

		@Override
		public int previousIndex() {
			return ((int) getCurrentPos() / RECORD_SIZE_IN_BYTES) - 2;
		}

		@Override
		public void remove() {
			try {
				if (getLastPos() != -1 && size() > 0) {
					if (hasNext()) {
						ArrayList<String> str = new ArrayList<String>();
						readAddressesToMove(str, raf);
						raf.seek(getCurrentPos() - RECORD_SIZE_IN_BYTES);
						writeAdrressesToMove(str, raf);
					}
					setCurrentPos(raf.getFilePointer());
					setLastPos(-1);
					raf.setLength(size() - RECORD_SIZE_IN_BYTES);
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void set(String e) {
			try {
				if (getLastPos() != -1) {
					raf.seek(getCurrentPos() - RECORD_SIZE_IN_BYTES);
					FixedLengthStringIO.writeFixedLengthString(e, RECORD_SIZE, raf);
				}
			} catch (IOException e1) {
				e1.printStackTrace();
			}
		}

		public void readAddressesToMove(ArrayList<String> al, RandomAccessFile raf) throws IOException {
			while (hasNext())
				al.add(next());
		}

		public void writeAdrressesToMove(ArrayList<String> al, RandomAccessFile raf) throws IOException {
			for (String s : al)
				FixedLengthStringIO.writeFixedLengthString(s, RECORD_SIZE, raf);
		}

		@Override
		public void add(String e) {
			try {
				ArrayList<String> al = new ArrayList<String>();
				al.add(e);
				long tempCurrent = getCurrentPos() + RECORD_SIZE_IN_BYTES;
				if (hasNext()) {
					readAddressesToMove(al, raf);
					raf.seek(getCurrentPos());
				}
				writeAdrressesToMove(al, raf);
				setCurrentPos(tempCurrent);
				setLastPos(-1);
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
	}
}
