public class InvalidFormatException extends RuntimeException {
	private boolean empty = false;

	/* Purpose:
	 * Default exception message with instructions how to use.
	 */
	public InvalidFormatException() {
		super("Invalid File Format or Input!\n");
	}

	/* Method Purpose:
	 * Special for calling exception on the cause of empty. 
	 */
	public InvalidFormatException(String getMessage, boolean empty) {
		this(getMessage);
		this.empty = empty;
	}

	public InvalidFormatException(String getMessage) {
		super(getMessage);
	}

	public boolean isEmpty() {
		return empty;
	}

}