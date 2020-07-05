package utilities;
import java.io.*;

public class Message implements Serializable{
	private String userFrom;
	private String userTo;
	private String message;
	private String groupName;
	
	public Message(String userFrom, String userTo, String message) {
		this.groupName = "###";
		this.userFrom =userFrom;
		this.userTo = userTo;
		this.message = message;
	}

	public Message(String groupName, String userFrom, String userTo, String message) {
		this.groupName = groupName;
		this.userFrom =userFrom;
		this.userTo = userTo;
		this.message = message;
	}

	public String getGroupName(){return this.groupName;}
	public String getContent() {
		return this.message;
	}
	public String getUserFrom() {
		return this.userFrom;
	}
	public String getUserTo() {
		return this.userTo;
	}
	
}
