import java.io.RandomAccessFile;

public interface MyAddressBookPane {

	RandomAccessFile getRaf();

	AddressBookPaneNoButtons getPane();

	void configureButtons(CommandButton... buttons);

}
